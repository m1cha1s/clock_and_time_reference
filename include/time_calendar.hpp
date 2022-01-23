#pragma once

#include <Arduino.h>

const uint8_t day_count[] PROGMEM = {
  31,
  29,
  31,
  30,
  31,
  30,
  31,
  31,
  30,
  31,
  30,
  31
};

class Time_calendar
{
public:
    uint8_t hours=0;
    uint8_t minutes=0;
    uint8_t seconds=0;
    uint8_t prev_seconds=0;

    uint8_t months=0;
    uint8_t days=0;
    uint32_t years=0;
public:
    Time_calendar();
    ~Time_calendar();
    void tick();
    String time_date();
    bool changed();
    void set_time(int hour, int minute, int second);
    void set_date(int year, int month, int day);
};


