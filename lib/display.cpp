#include "display.h"
#include <cstring>

#ifdef PICO
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#else
#endif

static uint8_t sDisplayBuffer[kBufLen];

uint8_t *GetDisplayBuffer()
{
    return sDisplayBuffer;
}

void SSD1306_send_cmd(uint8_t cmd)
{
    uint8_t buf[2] = {0x80, cmd};
#ifdef PICO
    i2c_write_blocking(i2c_default, SSD1306_I2C_ADDR, buf, 2, false);
#endif
}

void SSD1306_send_cmd_list(uint8_t *buf, int num)
{
    for (int i = 0; i < num; i++)
        SSD1306_send_cmd(buf[i]);
}

void SSD1306_send_buf()
{
    uint8_t temp_buf[kBufLen + 1];
    temp_buf[0] = 0x40;
    std::memcpy(temp_buf + 1, sDisplayBuffer, kBufLen);
#ifdef PICO
    i2c_write_blocking(i2c_default, SSD1306_I2C_ADDR, temp_buf, kBufLen + 1, false);
#else
    // fill out dev buffer
    // for (int x = 0; x < SSD1306_WIDTH; x++)
    // {
    //     for (int y = 0; y < SSD1306_HEIGHT; y++)
    //     {
    //         int byte_idx = (y / 8) * SSD1306_WIDTH + x;
    //         sDevDisplayBuffer[x][y] = sDisplayBuffer[byte_idx];
    //     }
    // }
#endif
}

void SSD1306_init()
{
    uint8_t cmds[] = {
        SSD1306_SET_DISP, // set display off
        /* memory mapping */
        SSD1306_SET_MEM_MODE, // set memory address mode 0 = horizontal, 1 = vertical, 2 = page
        0x00,                 // horizontal addressing mode
        /* resolution and layout */
        SSD1306_SET_DISP_START_LINE,    // set display start line to 0
        SSD1306_SET_SEG_REMAP | 0x01,   // set segment re-map, column address 127 is mapped to SEG0
        SSD1306_SET_MUX_RATIO,          // set multiplex ratio
        SSD1306_HEIGHT - 1,             // Display height - 1
        SSD1306_SET_COM_OUT_DIR | 0x08, // set COM (common) output scan direction. Scan from bottom up, COM[N-1] to COM0
        SSD1306_SET_DISP_OFFSET,        // set display offset
        0x00,                           // no offset
        SSD1306_SET_COM_PIN_CFG,        // set COM (common) pins hardware configuration. Board specific magic number.
                                        // 0x02 Works for 128x32, 0x12 Possibly works for 128x64. Other options 0x22, 0x32
        0x02,
        /* timing and driving scheme */
        SSD1306_SET_DISP_CLK_DIV, // set display clock divide ratio
        0x80,                     // div ratio of 1, standard freq
        SSD1306_SET_PRECHARGE,    // set pre-charge period
        0xF1,                     // Vcc internally generated on our board
        SSD1306_SET_VCOM_DESEL,   // set VCOMH deselect level
        0x30,                     // 0.83xVcc
        /* display */
        SSD1306_SET_CONTRAST, // set contrast control
        0xFF,
        SSD1306_SET_ENTIRE_ON,     // set entire display on to follow RAM content
        SSD1306_SET_NORM_DISP,     // set normal (not inverted) display
        SSD1306_SET_CHARGE_PUMP,   // set charge pump
        0x14,                      // Vcc internally generated on our board
        SSD1306_SET_SCROLL | 0x00, // deactivate horizontal scrolling if set. This is necessary as memory writes will corrupt if scrolling was enabled
        SSD1306_SET_DISP | 0x01,   // turn display on
    };

    SSD1306_send_cmd_list(cmds, sizeof(cmds));
}

void Render()
{
    // update a portion of the display with a render area
    uint8_t cmds[6] = {
        SSD1306_SET_COL_ADDR,
        kStartCol,
        kEndCol,
        SSD1306_SET_PAGE_ADDR,
        kStartPage,
        kEndPage};

    SSD1306_send_cmd_list(cmds, 6);
    SSD1306_send_buf();
}

void SetPixel(int x, int y)
{
    // exit if pixel not existing
    if (x < 0 || x >= SSD1306_WIDTH || y < 0 || y > SSD1306_HEIGHT)
        return;
    const int BytesPerRow = SSD1306_WIDTH;
    int byte_idx = (y / 8) * BytesPerRow + x;
    uint8_t byte = sDisplayBuffer[byte_idx];
    uint8_t shift = 1 << (y % 8);
    byte |= shift;
    sDisplayBuffer[byte_idx] = byte;
    // Render();
    // sleep_ms(50);
}

void Clear()
{
    std::memset(sDisplayBuffer, 0, kBufLen);
}

void Fill()
{
    std::memset(sDisplayBuffer, 255, kBufLen);
}

void AddTunerOutline()
{
    // middle line
    for (int i = 0; i < 100; i++)
    {
        SetPixel(i, 16);
    }
    // left outer
    for (int i = 8; i < 24; i++)
    {
        SetPixel(0, i);
    }

    // right outer
    for (int i = 8; i < 24; i++)
    {
        SetPixel(100, i);
    }
    // left inner
    for (int i = 12; i < 20; i++)
    {
        SetPixel(40, i);
    }
    // right inner
    for (int i = 12; i < 20; i++)
    {
        SetPixel(60, i);
    }
}
void AddTunerLocator(float f)
{
    constexpr int height = 12;
    constexpr int width = 2;

    int position = (int)(f * 100);
    for (int x = position - width; x < position + width; x++)
    {
        for (int y = 16 - height; y < 16 + height; y++)
            SetPixel(x, y);
    }
}
void AddLabel(Note note)
{
    auto letter_bitmap = LetterBitmapFromNote(note);
    ProcessBitmap(letter_bitmap, 103);
    switch (note)
    {
    case Note::A_sharp:
    case Note::C_sharp:
    case Note::D_sharp:
    case Note::F_sharp:
    case Note::G_sharp:
    {
        std::memcpy(letter_bitmap.data, letter_hash, kLetterSize);
        ProcessBitmap(letter_bitmap, 115);
        break;
    }
    default:
        break;
    }
}

int getBit(uint8_t byte, int idx)
{
    return (byte >> idx) & 1;
}

int getBit(const uint8_t *bytes, int idx)
{
    int array_fist_idx = idx / 8;
    int array_second_idx = idx % 8;
    return getBit(bytes[array_second_idx], array_fist_idx);
}

void ProcessBitmap(const letter_data &ld, int start_pos)
{
    int bitmap_counter = 0;
    for (int x = 0; x < kLetterHeight; x++)
    {
        for (int y = 0; y < kLetterWidth; y++)
        {
            auto idx = 0;
            uint8_t color = ld.data[x][y];
            if (color != 0U)
            {
                SetPixel(y + start_pos, x);
            }
        }
    }
}

letter_data LetterBitmapFromNote(Note note)
{
    letter_data ld;

    switch (note)
    {
    case Note::A:
    case Note::A_sharp:
        std::memcpy(ld.data, letter_a, kLetterSize);
        break;
    case Note::B:
        std::memcpy(ld.data, letter_b, kLetterSize);
        break;
    case Note::C:
    case Note::C_sharp:
        std::memcpy(ld.data, letter_c, kLetterSize);
        break;
    case Note::D:
    case Note::D_sharp:
        std::memcpy(ld.data, letter_d, kLetterSize);
        break;
    case Note::E:
        std::memcpy(ld.data, letter_e, kLetterSize);
        break;
    case Note::F:
    case Note::F_sharp:
        std::memcpy(ld.data, letter_f, kLetterSize);
        break;
    case Note::G:
    case Note::G_sharp:
        std::memcpy(ld.data, letter_g, kLetterSize);
        break;
    default:
        break;
    }
    return ld;
}

void setup_display()
{
#ifdef PICO
    i2c_init(i2c_default, SSD1306_I2C_CLK * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
#endif
    // init
    SSD1306_init();
    Clear();
    Render();
}
