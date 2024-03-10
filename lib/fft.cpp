#include "fft.h"
#include <cmath>
#include <complex>
#include <cstring>
#ifdef PICO
#include <pico/multicore.h>
#endif

namespace Instance
{
    static FFTProcessor processor;
    FFTProcessor *GetProcessor()
    {
        return &processor;
    }
}

bool FFTProcessor::Init()
{

    // set all buffers to 0
    memset(cpx_in_, 0, FFTParams::kFFTBufferSize * sizeof(kiss_fft_cpx));
    memset(cpx_out_, 0, FFTParams::kFFTBufferSize * sizeof(kiss_fft_cpx));
    memset(cpx_buffer_, 0, FFTParams::kAnalogReadBufferSize * sizeof(kiss_fft_cpx));
    memset(freq_magnitude_, 0, FFTParams::kAreaOfInterestSize * sizeof(float));

    // reset counters
    add_pos_buffer_ = 0;
    cpx_in_pos_ = 0;

    // init kiss fft
    cfg_ = kiss_fft_alloc(FFTParams::kFFTBufferSize, 0, nullptr, nullptr);
    if (cfg_ == nullptr)
        return false;
    return true;
}

int FFTProcessor::FindMaxIdx() const
{
    int idx = -FFTParams::kAreaOfInterestBeginIdx;

    // iterate from the back to find first valid freq
    for (int i = sizeof(freq_magnitude_) - 1; i <= 0; i--)
    {
        if (freq_magnitude_[i] > 0)
        {
            // uart_print()
            idx = i;
            break;
        }
    }

    return idx;
    // float max_value = 0.0f;
    // int last_idx = 0;
    // for (int i = 0; i < FFTParams::kAreaOfInterestSize; i++)
    // {
    //     if (freq_magnitude_[i] > max_value)
    //     {
    //         max_value = freq_magnitude_[i];
    //         last_idx = i;
    //     }
    // }
    // if (max_value < 10.0)
    //     last_idx = -FFTParams::kAreaOfInterestBeginIdx;
    // return last_idx;
}

void FFTProcessor::Perform()
{

#ifdef PICO
    uint32_t irq = spin_lock_blocking(spin_lock_instance(spin_lock_id_));
    // print all values
    uint16_t v = 0;
    char buffer[6];
    for (int i = 0; i < 100; i++)
    {
        snprintf(buffer, sizeof(buffer), "%u", cpx_in_[i].r);
        uart_print(buffer);
    }
    char msg[] = "bufferend\n";
    uart_print(msg);
    spin_unlock(spin_lock_instance(spin_lock_id_), irq);

#endif

    //     kiss_fft(cfg_, cpx_in_, cpx_out_);
    // #ifdef PICO
    //     spin_unlock(spin_lock_instance(spin_lock_id_), irq);
    // #endif
    //     // set freq_magnitude to 0
    //     memset(freq_magnitude_, 0, sizeof(freq_magnitude_));
    //     // perform and then return the idx
    //     float max_v = 0.0;
    //     for (int i = FFTParams::kAreaOfInterestBeginIdx;
    //          i < FFTParams::kAreaOfInterestEndIdx; i++)
    //     {
    //         auto magnitude = std::sqrt(cpx_out_[i].r * cpx_out_[i].r + cpx_out_[i].i * cpx_out_[i].i);
    //         if (magnitude > max_v)
    //             max_v = magnitude;
    //         // if (magnitude >= FFTParams::kMagnitudeCutoff)
    //         // {
    //         freq_magnitude_[i - FFTParams::kAreaOfInterestBeginIdx] = magnitude;
    //         // }
    //     }
    //     // char buffer[8];
    //     // snprintf(buffer, sizeof(buffer), "%.2f", max_v);
    //     // uart_print(buffer);
}

float FFTProcessor::GetFrequency()
{
    Perform();
    return GetHzFromIdx(FindMaxIdx());
}

void FFTProcessor::PushIntoBuffer()
{
    std::memcpy(&cpx_in_[0], cpx_buffer_, FFTParams::kAnalogReadBufferSize * sizeof(kiss_fft_cpx));
    // // check current position
    // auto delta = FFTParams::kFFTCounter - cpx_in_pos_;
    // if (delta >= FFTParams::kAnalogReadBufferSize)
    // {
    //     // just copy at current position
    //     std::memcpy(&cpx_in_[cpx_in_pos_], cpx_buffer_,
    //                 FFTParams::kAnalogReadBufferSize * sizeof(kiss_fft_cpx));
    //     cpx_in_pos_ += FFTParams::kAnalogReadBufferSize;
    // }
    // else
    // {
    //     // copy everything back a sample
    //     std::memcpy(&cpx_in_[0], &cpx_in_[FFTParams::kAnalogReadBufferSize], FFTParams::kMemcpyHelper);
    //     // emplace new
    //     std::memcpy(&cpx_in_[FFTParams::kMemcpyHelper], cpx_buffer_, FFTParams::kAnalogReadBufferSize);
    // }
}

int FFTProcessor::GetCpxInSize() const
{
    return cpx_in_pos_;
}

void FFTProcessor::Add(FFT_SCALAR data)
{
    // in case buffer is not already filled completely
    auto delta = FFTParams::kAnalogReadBufferSize - add_pos_buffer_;
    cpx_buffer_[add_pos_buffer_].r = data;
    if (delta > 1)
    {
        add_pos_buffer_++;
    }
    // push everything a sample forward and append at end
    else
    {
        add_pos_buffer_ = 0;

        // // print highest value
        // uint16_t v = 0;
        // for (int i = 0; i < 100; i++)
        // {
        //     if (v < cpx_buffer_[i].r)
        //     {
        //         v = cpx_buffer_[i].r;
        //     }
        // }
        // char buffer[6];
        // snprintf(buffer, sizeof(buffer), "%u", v);
        // uart_print(buffer);
// add sample to shared memory
#ifdef PICO
        uint32_t irq = spin_lock_blocking(spin_lock_instance(spin_lock_id_));
#endif
        PushIntoBuffer();
#ifdef PICO
        spin_unlock(spin_lock_instance(spin_lock_id_), irq);
        // notify a new reading is available
        multicore_fifo_push_blocking(kNewMeasurement);

#endif
    }
}