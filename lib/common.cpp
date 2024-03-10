#include "common.h"

void setup_uart()
{
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

void uart_print(const char *str)
{
    while (*str)
    {
        uart_putc(UART_ID, *str++);
    }
    uart_putc(UART_ID, '\n');
}