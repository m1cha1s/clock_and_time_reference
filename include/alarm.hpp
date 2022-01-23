#pragma once

#include <Arduino.h>

class Alarm
{
private:
    int year = -1, 
        month = -1, 
        day = -1, 
        hour = -1, 
        minute = -1, 
        second = -1, 
        duration = -1,
        alarm_pin = -1;
public:
    Alarm(int pin);
    ~Alarm();
    void set_alarm(int year, int month, int day, int hour, int minute, int second, int duration);
};