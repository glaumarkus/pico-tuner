#pragma once

#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "common.h"

// bool read_adc_callback(struct repeating_timer *t);
void setup_adc();
void core_1_loop();
void core_0_loop();
void single_core_loop();

class Timer
{
public:
    Timer();
    void Measure();
    void Reset();

private:
    absolute_time_t start_time_;
};
