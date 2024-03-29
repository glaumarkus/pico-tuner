#include <cstdint>

constexpr int kLetterHeight = 32;
constexpr int kLetterWidth = 13;
constexpr int kLetterSize = kLetterHeight*kLetterWidth;
constexpr uint8_t letter_d[32][13] =
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,0,0,},
{0,1,1,1,1,1,1,1,1,1,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},

};


constexpr uint8_t letter_c[32][13] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},

};


constexpr uint8_t letter_f[32][13] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},

};


constexpr uint8_t letter_b[32][13] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,0,0,},
{0,1,1,1,1,1,1,1,1,1,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,0,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,0,0,},
{0,1,1,1,1,1,1,1,1,1,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},

};


constexpr uint8_t letter_hash[32][13] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,1,1,0,0,0,1,1,0,0,0,},
{0,0,0,1,1,0,0,0,1,1,0,0,0,},
{0,0,0,1,1,0,0,0,1,1,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,0,0,1,1,0,0,0,1,1,0,0,0,},
{0,0,0,1,1,0,0,0,1,1,0,0,0,},
{0,0,0,1,1,0,0,0,1,1,0,0,0,},
{0,0,0,1,1,0,0,0,1,1,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,0,0,1,1,0,0,0,1,1,0,0,0,},
{0,0,0,1,1,0,0,0,1,1,0,0,0,},
{0,0,0,1,1,0,0,0,1,1,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},

};


constexpr uint8_t letter_g[32][13] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},

};


constexpr uint8_t letter_a[32][13] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,1,1,1,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},

};


constexpr uint8_t letter_e[32][13] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,0,0,0,0,0,0,0,0,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,1,1,1,1,1,1,1,1,1,1,1,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,},

};