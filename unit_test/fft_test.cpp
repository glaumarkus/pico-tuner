#include "fft.h"
#include "frequency_map.h"
#include "timer.hpp"
#include "display.h"
#include <gtest/gtest.h>
#include <iostream>

#include <cmath>
#include <iostream>
#include <vector>

std::vector<double> generateSineWave(int n, double fs, double targetFrequency)
{
    std::vector<double> samples(n);
    double samplePeriod = 1.0 / fs;

    for (int i = 0; i < n; ++i)
    {
        double t = i * samplePeriod;
        samples[i] = sin(2.0 * M_PI * targetFrequency * t);
    }

    return samples;
}

bool equal_freq(float first, float second)
{
    return std::abs(first - second) <= 2.5;
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

//     for (int i = 20; i < 500; i++)
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

//     for (int i = 0; i < 100; i++)
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
//         EXPECT_TRUE(measurement < (1000.0 / FFTParams::kScreenUpdatesPerSecond));
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

int GetIdxFromContinousBuffer(int x, int y)
{
    int byte_idx = (y / 8) * SSD1306_WIDTH + x;
    return byte_idx;
}

TEST(fft_test, test_display_update)
{
    SSD1306_init();
    Clear();
    Render();
    EXPECT_EQ(GetDisplayBuffer()[0], 0x00);
    Fill();
    Render();
    EXPECT_EQ(GetDisplayBuffer()[0], 0xFF);
}

TEST(fft_test, test_ui)
{
    SSD1306_init();
    Clear();
    Render();
    AddTunerOutline();
    EXPECT_EQ(GetDisplayBuffer()[GetIdxFromContinousBuffer(0, 0)], 0x80);
}

TEST(fft_test, test_letter)
{
    SSD1306_init();
    Clear();
    Render();
    AddLabel(Note::A);
}
