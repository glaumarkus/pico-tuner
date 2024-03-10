#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/timer.h"
#include <cstdio>

// #ifdef NDEBUG
__asm("bkpt #0");
// #endif

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define SAMPLE_RATE 1000
#define SAMPLES_PER_SECOND 1000
uint16_t samples[SAMPLES_PER_SECOND];
volatile int sample_index = 0;

bool repeating_timer_callback(struct repeating_timer *t)
{
    // uart_puts(UART_ID, "Timer Callback\n");
    if (sample_index < SAMPLES_PER_SECOND)
    {
        samples[sample_index++] = adc_read();
    }
    return true; // Keep repeating
}

void setup_adc()
{
    adc_init();
    adc_select_input(0); // Select ADC channel (e.g., ADC0)
}

void setup_uart()
{
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

int main()
{
    stdio_init_all();
    setup_uart();
    setup_adc();

    struct repeating_timer timer;
    // Setup a repeating timer that calls the callback at the specified SAMPLE_RATE
    int64_t delay_us = 1000000 / SAMPLE_RATE;
    add_repeating_timer_us(-delay_us, repeating_timer_callback, NULL, &timer);

    while (true)
    {
        tight_loop_contents();
        if (sample_index >= SAMPLES_PER_SECOND)
        {
            // Data collection complete
            // Disable the timer to stop collecting samples
            cancel_repeating_timer(&timer);

            // Process or export data here
            // For example, iterate over samples and send via UART
            for (int i = 0; i < SAMPLES_PER_SECOND; i++)
            {
                char buffer[6]; // Enough to hold all digits of a uint16_t and null terminator
                snprintf(buffer, sizeof(buffer), "%u", samples[i]);
                for (size_t i = 0; buffer[i] != '\0'; i++)
                {
                    uart_putc(UART_ID, buffer[i]);
                }
                uart_puts(UART_ID, "\n");
            }

            uart_puts(UART_ID, "Sample\n");

            // set timer again
            sample_index = 0;
            add_repeating_timer_us(-delay_us, repeating_timer_callback, NULL, &timer);
        }
    }

    return 0;
}
