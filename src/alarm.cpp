#include "alarm.hpp"
#include "time_calendar.hpp"
// #include "globals.hpp"

extern Time_calendar tc;


Alarm::Alarm(int pin) {
    alarm_pin = pin;
    pinMode(pin, OUTPUT);
    digitalWrite(alarm_pin, 0);
}

Alarm::~Alarm() {
}


void Alarm::set_alarm(int year, int month, int day, int hour, int minute, int second) {
    alarm_pin_set = false;
    digitalWrite(alarm_pin, 0);
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
    if(second != -1) {
        this->second_end = second+2;
        second_start = second;
        if(second_end > 59)
            second_start -= 60;
    }
    else {
        second_end = second_start = -1;
    }
}

void Alarm::check_alarm() {
    bool ended = (tc.years > year || year==-1) && 
                   (tc.months > month || month==-1) && 
                   (tc.days > day || day==-1) && 
                   (tc.hours > hour || hour==-1) &&
                   (tc.minutes > minute || minute==-1) ||
                   (tc.seconds > second_end || second_end==-1);

    bool started = (tc.years >= year || year==-1) && 
                   (tc.months >= month || month==-1) && 
                   (tc.days >= day || day==-1) && 
                   (tc.hours >= hour || hour==-1) &&
                   (tc.minutes >= minute || minute==-1) &&
                   (tc.seconds >= second_start || second_start==-1) && !ended;

    if(started && !alarm_pin_set && enabled) {
        digitalWrite(alarm_pin, 1);
        alarm_pin_set = true;
    }
    if(ended && alarm_pin_set && enabled) {
        digitalWrite(alarm_pin, 0);
        alarm_pin_set = false;
    }
}

String Alarm::get_alarm() {
    return String(year) + ":" + 
           String(month) + ":" +
           String(day) + ":" +
           String(hour) + ":" +
           String(minute) + ":" +
           String(second_end) + ":" +
           String(enabled);
}