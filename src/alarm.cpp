#include "alarm.hpp"


Alarm::Alarm(int pin) {
    alarm_pin = pin;
    pinMode(pin, OUTPUT);
}

Alarm::~Alarm() {
}
