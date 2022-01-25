#include <Arduino.h>
#include <hardware/timer.h>
#include <hardware/irq.h>
// #include <pico/multicore.h>
#include <SevSeg.h>

#include "config.hpp"
// #include "globals.hpp"
#include "source.hpp"
#include "time_calendar.hpp"
#include "alarm.hpp"

#define ALARM_NUM 1

Time_calendar tc;

uint8_t source=0;

Source sources[3];
Alarm alarms[2] = {Alarm(4), Alarm(5)};

// Serial interface

String cmd_array[20];
int cmd_len=0;

// Display vars

// byte d1 = 13;
// byte d2 = 12;
// byte d3 = 11;
// byte d4 = 10;

// byte A = 18;
// byte B = 19;
// byte C = 20;
// byte D = 21;
// byte E = 9;
// byte F = 8;
// byte G = 7;
// byte DP = 6;

byte digit_pins[] = {13, 12, 11, 10};
byte segment_pins[] = {18, 19, 20, 21, 9, 8, 7, 6};

SevSeg disp;

// Function definitions

static void alarm_in_us_arm(uint32_t delay_us);
static void alarm_in_us(uint32_t delay_us);

void isr_in_32kHz_A();
void isr_in_32kHz_B();

void source_switch();

// void core1();

// Code start

void setup() {
  // multicore_launch_core1(core1);

  Serial.begin(115200);

  for(int i=0; i<3; i++) {
    Source *newSource = new Source();
    sources[i] = *newSource;
  }

  disp.begin(COMMON_CATHODE,
          4,
          digit_pins,
          segment_pins,
          true,
          false, 
          false,
          false);
  disp.setBrightness(100);

  alarm_in_us(4000000/IN_32KHZ_FREQ);

  attachInterrupt(IN_32KHZ_A, isr_in_32kHz_A, RISING);
  attachInterrupt(IN_32KHZ_B, isr_in_32kHz_B, RISING);
}

void loop() {
  if(Serial.available()) {
    for(int i=0;i<20;i++) {
      cmd_array[i] = "";
    }
    String cmd = Serial.readStringUntil('\n');
    cmd_len=0;

    // Split command

    while (cmd.length()) {
      int index = cmd.indexOf(" ");
      if(index == -1) {
        cmd_array[cmd_len++] = cmd;
        break;
      }
      else {
        cmd_array[cmd_len++] = cmd.substring(0, index);
        cmd = cmd.substring(index+1);
      }
    }

    // Parse command
    if(cmd_len) {
      if(cmd_array[0] == "get_time_date" && cmd_len == 1) {
        Serial.println(tc.time_date());
        Serial.println("OK");
      }
      if(cmd_array[0] == "set_time" && cmd_len == 4) {
        tc.set_time(cmd_array[1].toInt(),
                    cmd_array[2].toInt(),
                    cmd_array[3].toInt());
        Serial.println("OK");
      }
      if(cmd_array[0] == "set_date" && cmd_len == 4) {
        tc.set_date(cmd_array[1].toInt(),
                    cmd_array[2].toInt(),
                    cmd_array[3].toInt());
        Serial.println("OK");
      }
      if(cmd_array[0] == "set_alarm" && cmd_len == 8) {
        int alarm_num = cmd_array[1].toInt();
        if(alarm_num == 0 || alarm_num == 1) {
          alarms[alarm_num].set_alarm(cmd_array[2].toInt(),
                                      cmd_array[3].toInt(),
                                      cmd_array[4].toInt(),
                                      cmd_array[5].toInt(),
                                      cmd_array[6].toInt(),
                                      cmd_array[7].toInt());
          Serial.println("OK");
        }
      }
      if(cmd_array[0] == "get_alarm" && cmd_len == 2) {
        int alarm_num = cmd_array[1].toInt();
        if(alarm_num == 0 || alarm_num == 1) {
          Serial.println(alarms[alarm_num].get_alarm());
          Serial.println("OK");
        }
      }
      if(cmd_array[0] == "en_alarm" && cmd_len == 3) {
        int alarm_num = cmd_array[1].toInt();
        if(alarm_num == 0 || alarm_num == 1) {
          if(cmd_array[2] == 0)
            alarms[alarm_num].enabled = false;
          else
            alarms[alarm_num].enabled = true;
          Serial.println("OK");
        }
      }
    }
  }

  char disp_str[] = "00.00";

  if(tc.seconds%2==0)
    sprintf(disp_str, "%02i.%02i", tc.hours, tc.minutes);
  else
    sprintf(disp_str, "%02i%02i", tc.hours, tc.minutes);

  disp.setChars(disp_str);
  disp.refreshDisplay();
}

inline void check_alarms() {
  for(int i = 0; i < 2; i ++) {
    alarms[i].check_alarm();
  }
}

void isr_in_32kHz_A() {
  bool ticked = sources[0].tick();
  if(source == 0 && ticked) {
    tc.tick();
    check_alarms();
  }
}

void isr_in_32kHz_B() {
  bool ticked = sources[1].tick();
  if(source == 1 && ticked) {
    tc.tick();
    check_alarms();
  }
}

void source_switch() {
  hw_clear_bits(&timer_hw->intr, 1u << ALARM_NUM);
  alarm_in_us_arm(1000000/(IN_32KHZ_FREQ));

  if(sources[0].changed()) {
    source=0;
    return;
  }

  if(sources[1].changed()) {
    source=1;
    return;
  }

  bool ticked = sources[2].tick();
  if(source == 2 && ticked) {
    tc.tick();
  }

  if(sources[2].changed()) {
    source=2;
    return;
  }
}

static void alarm_in_us_arm(uint32_t delay_us) {
  uint64_t target = timer_hw->timerawl + delay_us;
  timer_hw->alarm[ALARM_NUM] = (uint32_t) target;
}

static void alarm_in_us(uint32_t delay_us) {
  hw_set_bits(&timer_hw->inte, 1u << ALARM_NUM);
  irq_set_exclusive_handler(TIMER_IRQ_1, source_switch);
  irq_set_enabled(TIMER_IRQ_1, true);
  alarm_in_us_arm(delay_us);
}