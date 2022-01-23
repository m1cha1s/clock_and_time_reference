#include "source.hpp"

Source::Source(uint16_t counts_in_second) {
    this->counts_in_second = counts_in_second;
}

Source::~Source() {}

bool Source::tick() {
    counts++;
    if(!(counts%counts_in_second) && counts) {
        counts=0;
        return true;
    }
    return false;
}

bool Source::changed() {
    bool did_change = counts != prev_counts;
    prev_counts = counts;
    return did_change;
}
