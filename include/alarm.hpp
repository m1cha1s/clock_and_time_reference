#pragma once

#include <Arduino.h>

class Alarm
{
public:
    int year = -1, 
        month = -1, 
        day = -1, 
        hour = -1, 
        minute = -1, 
        second_start = -1, 
        second_end = -1,
        alarm_pin = -1;
    bool alarm_pin_set=false,
         enabled = false;
public:
    Alarm(int pin);
    ~Alarm();
    void set_alarm(int year, int month, int day, int hour, int minute, int second);
    void check_alarm();
    String get_alarm();
};