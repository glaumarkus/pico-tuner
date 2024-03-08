#include "pico/stdlib.h"
#include "display.h"

int main()
{
    stdio_init_all();

    i2c_init(i2c_default, SSD1306_I2C_CLK * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    while (true)
    {
        // init
        SSD1306_init();
        Clear();
        Render();

        // render all letters
        AddLabel(Note::A);
        Render();
        sleep_ms(500);
        AddLabel(Note::A_sharp);
        Render();
        sleep_ms(500);
        AddLabel(Note::B);
        Render();
        sleep_ms(500);
        AddLabel(Note::C);
        Render();
        sleep_ms(500);
        AddLabel(Note::C_sharp);
        Render();
        sleep_ms(500);
        AddLabel(Note::D);
        Render();
        sleep_ms(500);
        AddLabel(Note::D_sharp);
        Render();
        sleep_ms(500);
        AddLabel(Note::E);
        Render();
        sleep_ms(500);
        AddLabel(Note::F);
        Render();
        sleep_ms(500);
        AddLabel(Note::F_sharp);
        Render();
        sleep_ms(500);
        AddLabel(Note::G);
        Render();
        sleep_ms(500);
        AddLabel(Note::G_sharp);
        Render();
        sleep_ms(500);
    }

    return 0;
}
