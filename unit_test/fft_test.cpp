#include "fft.h"
#include "frequency_map.h"
#include "timer.hpp"
#include "display.h"
#include <cstring>
#include <gtest/gtest.h>
#include <iostream>

#include <cmath>
#include <iostream>
#include <vector>
#include "headers/testcases.hpp"

std::vector<uint16_t> generateSineWave(int n, double fs, double targetFrequency)
{
    constexpr uint16_t MAX_AMPLITUDE = 65535;
    double amplitude = MAX_AMPLITUDE / 2.0;

    std::vector<uint16_t> samples;
    samples.reserve(n);
    double samplePeriod = 1.0 / fs;

    for (int i = 0; i < n; ++i)
    {
        // Generate the sine wave value
        double time = static_cast<double>(i) / static_cast<double>(fs);
        double sineValue = std::sin(2.0 * M_PI * targetFrequency * time);

        // Scale and shift the sine value to fit the uint16_t range
        uint16_t sample = static_cast<uint16_t>((sineValue + 1.0) * amplitude);
        samples.emplace_back(sample);
    }

    return samples;
}

bool equal_freq(float first, float second)
{
    return std::abs(first - second) <= 2.5;
}

bool equal_freq_exact(float first, float second)
{
    if (std::abs(first - second) <= 5.0)
        return true;
    std::cout << first << ":" << second << std::endl;
    return false;
}

// suggestions
// input has no imaginary, use kiss_fftr
// create hardcoded kiss_fft_state

// TEST(fft_test, auto_fft_test)
// {
//     // set up processor
//     FFTProcessor p;
//     p.Init();
//     for (const auto &val : data_0)
//     {
//         p.Add(val);
//     }
//     p.Perform();
//     auto max_idx = p.FindMaxIdx();
//     auto freq = p.GetHzFromIdx(max_idx);
//     EXPECT_TRUE(equal_freq_exact(freq, result_0));
// }

TEST(fft_test, auto_fft_test2)
{
    float negative_cases = 0;

    // set up processor
    FFTProcessor p;
    p.Init();

    for (int i = 0; i < cases.size(); i++)
    {
        for (const auto &val : cases[i].data)
        {
            p.Add(val);
        }
        Timer t;
        p.Perform();
        auto measurement = t.MeasureMs();
        auto max_idx = p.FindMaxIdx();
        auto freq = p.GetHzFromIdx(max_idx);
        if (!equal_freq_exact(freq, cases[i].result))
        {
            negative_cases += 1;
            std::cout << "i: " << i << "\n";
        }
    }
    std::cout << "Failed cases: " << (int)negative_cases << " of " << cases.size() << "\n";
    EXPECT_TRUE(negative_cases / cases.size() < 0.5);
}

// TEST(fft_test, test_memory_management)
// {
//     FFTProcessor p;
//     p.Init();
//     EXPECT_EQ(p.GetCpxInSize(), 0);
//     p.Add(0);
//     EXPECT_EQ(p.GetCpxInSize(), 0);
//     for (int i = 0; i < FFTParams::kAnalogReadBufferSize; i++)
//         p.Add(0);
//     EXPECT_EQ(p.GetCpxInSize(), FFTParams::kAnalogReadBufferSize);
//     for (int k = 0; k < FFTParams::kAnalogBlocksPerFFT + 1; k++)
//         for (int i = 0; i < FFTParams::kAnalogReadBufferSize; i++)
//             p.Add(0);
//     EXPECT_EQ(p.GetCpxInSize(), FFTParams::kAnalogReadBufferSize * FFTParams::kAnalogBlocksPerFFT);
// }

// TEST(fft_test, fft_test)
// {
//     // set up processor
//     FFTProcessor p;

//     for (int i = 200; i < 460; i++)
//     {
//         p.Init();
//         // mock sine wave
//         auto sine_wave = generateSineWave(FFTParams::kAnalogReadBufferSize, FFTParams::kSamplePerSec, i);
//         for (const auto sample : sine_wave)
//         {
//             p.Add(sample);
//         }
//         if (!equal_freq(p.GetFrequency(), i))
//         {
//             EXPECT_TRUE(false);
//             std::cout << p.GetFrequency() << " vs " << i << std::endl;
//         }
//     }
// }

// TEST(fft_test, fft_test_performance)
// {
//     // set up processor
//     FFTProcessor p;

//     for (int i = 0; i < 10; i++)
//     {
//         p.Init();
//         // mock sine wave
//         auto sine_wave = generateSineWave(FFTParams::kAnalogReadBufferSize, FFTParams::kSamplePerSec, 440);
//         for (const auto sample : sine_wave)
//         {
//             p.Add(sample);
//         }
//         Timer t;
//         auto freq = p.GetFrequency();
//         auto measurement = t.MeasureMs();
//         if (measurement < (1000.0 / FFTParams::kScreenUpdatesPerSecond))
//         {
//         }
//         else
//         {
//             std::cout << measurement << "\n";
//             FAIL();
//         }
//     }
// }

// TEST(fft_test, test_note_mapping)
// {
//     EXPECT_EQ(CurrentNote(65).note, Note::C);
//     EXPECT_EQ(CurrentNote(65).octave, 2);
//     EXPECT_EQ(CurrentNote(69).note, Note::C_sharp);
//     EXPECT_EQ(CurrentNote(69).octave, 2);
//     EXPECT_EQ(CurrentNote(73).note, Note::D);
//     EXPECT_EQ(CurrentNote(77).note, Note::D_sharp);
//     EXPECT_EQ(CurrentNote(82).note, Note::E);
//     EXPECT_EQ(CurrentNote(87).note, Note::F);
//     EXPECT_EQ(CurrentNote(92).note, Note::F_sharp);
//     EXPECT_EQ(CurrentNote(97).note, Note::G);
//     EXPECT_EQ(CurrentNote(103).note, Note::G_sharp);
//     EXPECT_EQ(CurrentNote(110).note, Note::A);
//     EXPECT_EQ(CurrentNote(116).note, Note::A_sharp);
//     EXPECT_EQ(CurrentNote(123).note, Note::B);

//     EXPECT_EQ(CurrentNote(130).note, Note::C);
//     EXPECT_EQ(CurrentNote(130).octave, 3);
//     EXPECT_EQ(CurrentNote(138).note, Note::C_sharp);
//     EXPECT_EQ(CurrentNote(138).octave, 3);
//     EXPECT_EQ(CurrentNote(146).note, Note::D);
//     EXPECT_EQ(CurrentNote(155).note, Note::D_sharp);
//     EXPECT_EQ(CurrentNote(164).note, Note::E);
//     EXPECT_EQ(CurrentNote(174).note, Note::F);
//     EXPECT_EQ(CurrentNote(184).note, Note::F_sharp);
//     EXPECT_EQ(CurrentNote(195).note, Note::G);
//     EXPECT_EQ(CurrentNote(207).note, Note::G_sharp);
//     EXPECT_EQ(CurrentNote(220).note, Note::A);
//     EXPECT_EQ(CurrentNote(233).note, Note::A_sharp);
//     EXPECT_EQ(CurrentNote(246).note, Note::B);

//     EXPECT_EQ(CurrentNote(261).note, Note::C);
//     EXPECT_EQ(CurrentNote(261).octave, 4);
//     EXPECT_EQ(CurrentNote(277).note, Note::C_sharp);
//     EXPECT_EQ(CurrentNote(277).octave, 5);
//     EXPECT_EQ(CurrentNote(293).note, Note::D);
//     EXPECT_EQ(CurrentNote(311).note, Note::D_sharp);
//     EXPECT_EQ(CurrentNote(329).note, Note::E);
//     EXPECT_EQ(CurrentNote(349).note, Note::F);
//     EXPECT_EQ(CurrentNote(369).note, Note::F_sharp);
//     EXPECT_EQ(CurrentNote(391).note, Note::G);
//     EXPECT_EQ(CurrentNote(415).note, Note::G_sharp);
//     EXPECT_EQ(CurrentNote(440).note, Note::A);
//     EXPECT_EQ(CurrentNote(466).note, Note::A_sharp);
//     EXPECT_EQ(CurrentNote(493).note, Note::B);
// }

// TEST(fft_test, test_note_boundaries)
// {
//     // 440 hz -> lower
//     auto limits = GetNoteLimits(NoteIdx{
//         .note = Note::A,
//         .octave = 4,
//         .freq = 427.5,
//     });
//     // 440 hz -> upper
//     EXPECT_TRUE(limits.scalar < 0.01 && limits.scalar >= 0);
//     limits = GetNoteLimits(NoteIdx{
//         .note = Note::A,
//         .octave = 4,
//         .freq = 452.8,
//     });
//     EXPECT_TRUE(limits.scalar > 0.99 && limits.scalar >= 0 && limits.scalar <= 1.0);

//     // 440 hz -> lower
//     limits = GetNoteLimits(NoteIdx{
//         .note = Note::E,
//         .octave = 3,
//         .freq = 160.2,
//     });
//     EXPECT_TRUE(limits.scalar < 0.01 && limits.scalar >= 0);
//     // 440 hz -> upper
//     limits = GetNoteLimits(NoteIdx{
//         .note = Note::G,
//         .octave = 2,
//         .freq = 100.8,
//     });
//     EXPECT_TRUE(limits.scalar > 0.99 && limits.scalar >= 0 && limits.scalar <= 1.0);
// }

// int GetIdxFromContinousBuffer(int x, int y)
// {
//     int byte_idx = (y / 8) * SSD1306_WIDTH + x;
//     return byte_idx;
// }

// TEST(fft_test, test_display_update)
// {
//     SSD1306_init();
//     Clear();
//     Render();
//     EXPECT_EQ(GetDisplayBuffer()[0], 0x00);
//     Fill();
//     Render();
//     EXPECT_EQ(GetDisplayBuffer()[0], 0xFF);
// }

// TEST(fft_test, test_ui)
// {
//     SSD1306_init();
//     Clear();
//     Render();
//     AddTunerOutline();
//     EXPECT_EQ(GetDisplayBuffer()[GetIdxFromContinousBuffer(0, 0)], 0x80);
// }

// TEST(fft_test, test_letter)
// {
//     SSD1306_init();
//     Clear();
//     Render();
//     AddLabel(Note::A);
// }

// TEST(fft_test, test_letter_conversion)
// {
//     SSD1306_init();
//     Clear();
//     Render();
//     AddLabel(Note::A);
//     const uint8_t *bm = LetterBitmapFromNote(Note::A);
//     int bit;
//     for (int i = 0; i < 100; i++)
//     {
//         bit = getBit(bm, i);
//         std::cout << i << ": " << (int)bit << std::endl;
//     }

//     bit = getBit(bm, 35);
//     EXPECT_NE(bit, 0);
//     bit = getBit(bm, 0);
//     EXPECT_EQ(bit, 0);
//     bit = getBit(bm, 29);
//     EXPECT_EQ(bit, 0);
// }
