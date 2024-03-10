#include "pico/stdlib.h"
#include "display.h"
#include "hardware/i2c.h"

int main()
{
    stdio_init_all();

    i2c_init(i2c_default, SSD1306_I2C_CLK * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    // init
    SSD1306_init();
    Clear();
    Render();

    auto render_basic_stuff = []()
    {
        Render();
        sleep_ms(500);
        Clear();
        AddTunerOutline();
        AddTunerLocator(0.1);
    };

    while (true)
    {

        // render all letters
        AddLabel(Note::A);
        render_basic_stuff();
        AddLabel(Note::A_sharp);
        render_basic_stuff();
        AddLabel(Note::B);
        render_basic_stuff();
        AddLabel(Note::C);
        render_basic_stuff();
        AddLabel(Note::C_sharp);
        render_basic_stuff();
        AddLabel(Note::D);
        render_basic_stuff();
        AddLabel(Note::D_sharp);
        render_basic_stuff();
        AddLabel(Note::E);
        render_basic_stuff();
        AddLabel(Note::F);
        render_basic_stuff();
        AddLabel(Note::F_sharp);
        render_basic_stuff();
        AddLabel(Note::G);
        render_basic_stuff();
        AddLabel(Note::G_sharp);
        render_basic_stuff();
    }

    return 0;
}
