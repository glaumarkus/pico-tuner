#include "adc_record.h"

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/timer.h"
#include "fft.h"
#include "common.h"
#include "display.h"
#include "hardware/i2c.h"
#include "pico/multicore.h"
#include "hardware/irq.h"

Timer::Timer() : start_time_(get_absolute_time())
{
}

void Timer::Measure()
{
    auto end_time = get_absolute_time();
    auto elapsed_us = absolute_time_diff_us(start_time_, end_time);
    char msg[64];
    snprintf(msg, sizeof(msg), "%lld us\n", elapsed_us);
    uart_print(msg);
}
void Timer::Reset()
{
    start_time_ = get_absolute_time();
}

bool read_adc_callback(struct repeating_timer *t)
{
    // read sample
    auto sample = adc_read();
    // attach to map
    Instance::GetProcessor()->Add(static_cast<FFT_SCALAR>(sample));
    return true;
}

void setup_adc()
{
    adc_init();
    adc_select_input(0);
}

void core_1_loop()
{

    // signal availability
    multicore_fifo_push_blocking(kCoreStarted);

    // keep alive
    while (true)
    {
        // recorded buffer available for FFT
        auto msg = multicore_fifo_pop_blocking();
        if (msg == kNewMeasurement)
        {
            // perform fft debug ~ 75ms, release 67ms -> only 10 updates per second
            float frequency = Instance::GetProcessor()->GetFrequency();
            multicore_fifo_push_blocking(kFFTDone);
            multicore_fifo_push_blocking(frequency);


            // dummy values
            // frequency = 445.0;
            // multicore_fifo_push_blocking(kFFTDone);
            // multicore_fifo_push_blocking(frequency);

            // frequency = 435.0;
            // multicore_fifo_push_blocking(kFFTDone);
            // multicore_fifo_push_blocking(frequency);

            // frequency = 440.0;
            // multicore_fifo_push_blocking(kFFTDone);
            // multicore_fifo_push_blocking(frequency);
        }
        tight_loop_contents();
    }
}

void core_0_loop()
{
    // start stdio
    stdio_init_all();

    // set up uart
    setup_uart();

    // set up fft processor
    if (!Instance::GetProcessor()->Init())
    {
        // some error occured
        uart_puts(UART_ID, "Error setting up fft processor\n");
    }

    // setup display
    setup_display();

    // prerender outline
    AddTunerOutline();

    // setup adc
    setup_adc();

    // launch other core
    multicore_launch_core1(core_1_loop);
    uint32_t msg = multicore_fifo_pop_blocking();
    if (msg == kCoreStarted)
    {

        // add read adc task
        struct repeating_timer timer;
        add_repeating_timer_us(-1000, read_adc_callback, NULL, &timer);

        while (true)
        {

            // // wait for new measurement
            msg = multicore_fifo_pop_blocking();

            if (msg == kFFTDone)
            {
                // get frequency
                float freq = multicore_fifo_pop_blocking();

                if (freq >= FFTParams::kAreaOfInterestBegin && freq <= FFTParams::kAreaOfInterestEnd)
                {
                    // valid frequency
                    // get note
                    NoteIdx note_idx = CurrentNote(freq);

                    // get limits
                    NoteLimit note_limit = GetNoteLimits(note_idx);

                    // set tuner locator
                    AddTunerLocator(note_limit.scalar);

                    // set note
                    AddLabel(note_idx.note);
                }

                // render
                Render();

                // reset display
                Clear();
                AddTunerOutline();
            }

            // trigger from other
            // uart_puts(UART_ID, "Trigger\n");

            // // perform fft
            // float frequency = Instance::GetProcessor()->GetFrequency();

            // // get note
            // NoteIdx note_idx = CurrentNote(frequency);

            // // get limits
            // NoteLimit note_limit = GetNoteLimits(note_idx);

            // // set tuner locator
            // AddTunerLocator(note_limit.scalar);

            // // set note
            // AddLabel(note_idx.note);
        }
    }
}

// void single_core_loop()
// {
//     // start stdio
//     stdio_init_all();

// #ifdef ENABLE_LOGGING
//     setup_uart();
//     uart_puts(UART_ID, "Timer Callback\n");
// #endif

//     // set up fft processor
//     if (!Instance::GetProcessor()->Init())
//     {
// #ifdef ENABLE_LOGGING
//         uart_puts(UART_ID, "Error setting up fft processor\n");
// #endif
//     }

//     // // setup adc
//     // setup_adc();

//     // // setup display
//     // setup_display();

//     // // prerender outline
//     // AddTunerOutline();

// #ifdef ENABLE_LOGGING
//     uart_puts(UART_ID, "Starting Timer\n");
// #endif

//     struct repeating_timer timer;
//     // Setup a repeating timer that calls the callback at the specified SAMPLE_RATE
//     int64_t delay_us = 1000000 / 44000;
//     add_repeating_timer_us(-delay_us, repeating_timer_callback, NULL, &timer);

//     // // add timer
//     // struct repeating_timer timer;
//     // add_repeating_timer_us(-FFTParams::kRecordTaskus, read_adc_callback, NULL, &timer);

//     while (true)
//     {
//         tight_loop_contents();

//         // sleep_ms(FFTParams::kScreenUpdateEveryUs);

//         // // perform fft
//         // float frequency = Instance::GetProcessor()->GetFrequency();

//         // // get note
//         // NoteIdx note_idx = CurrentNote(frequency);

//         // // get limits
//         // NoteLimit note_limit = GetNoteLimits(note_idx);

//         // // set tuner locator
//         // AddTunerLocator(note_limit.scalar);

//         // // set note
//         // AddLabel(note_idx.note);

//         // // render
//         // Render();

//         // // reset display
//         // Clear();
//         // AddTunerOutline();
//     }
// }
