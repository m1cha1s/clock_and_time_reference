#pragma once

#include <Arduino.h>

#include "config.hpp"
#include "globals.hpp"

class Source
{
private:
    uint64_t counts=0, prev_counts=0;
    uint16_t counts_in_second;
public:
    Source(uint16_t counts_in_second = IN_32KHZ_FREQ);
    ~Source();
    bool tick();
    bool changed();
};
