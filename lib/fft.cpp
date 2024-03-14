#include "fft.h"
#include "common.h"
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

float FFTProcessor::GetHzFromIdx(int idx) const { return (idx + FFTParams::kAreaOfInterestBeginIdx) * FFTParams::kFFTResolution; }

bool FFTProcessor::Init()
{

    // set all buffers to 0
    memset(cpx_out_, 0, FFTParams::kFFTBufferSize * sizeof(kiss_fft_cpx));
    memset(freq_magnitude_, 0, FFTParams::kAreaOfInterestSize * sizeof(float));
    memset(sc_buffer_, 0, FFTParams::kAnalogReadBufferSize * sizeof(kiss_fft_scalar));
    memset(sc_in_, 0, FFTParams::kFFTBufferSize * sizeof(kiss_fft_scalar));

    // reset counters
    add_pos_buffer_ = 0;
    cpx_in_pos_ = 0;

    // init kiss fft
    cfgr_ = kiss_fftr_alloc(FFTParams::kFFTBufferSize, 0, nullptr, nullptr);
    if (cfgr_ == nullptr)
        return false;
    return true;
}

int FFTProcessor::FindMaxIdx() const
{
    int idx = -FFTParams::kAreaOfInterestBeginIdx;
    float max_value = 0;

    for (int i = 0; i < FFTParams::kAreaOfInterestSize; i++)
    {
        if (freq_magnitude_[i] > max_value)
        {
            idx = i;
            max_value = freq_magnitude_[i];
        }
    }

    return idx;
}

void FFTProcessor::Perform()
{

#ifdef PICO
    // uint32_t irq = spin_lock_blocking(spin_lock_instance(spin_lock_id_));
#endif
    kiss_fftr(cfgr_, sc_in_, cpx_out_);
#ifdef PICO
    spin_unlock(spin_lock_instance(spin_lock_id_), irq);
#endif
    // set freq_magnitude to 0
    memset(freq_magnitude_, 0, sizeof(freq_magnitude_));
    // perform and then return the idx
    float max_v = 0.0;
    for (int i = FFTParams::kAreaOfInterestBeginIdx;
         i < FFTParams::kAreaOfInterestEndIdx; i++)
    {
        auto magnitude = std::sqrt(cpx_out_[i].r * cpx_out_[i].r + cpx_out_[i].i * cpx_out_[i].i);
        if (magnitude > max_v)
            max_v = magnitude;
        freq_magnitude_[i - FFTParams::kAreaOfInterestBeginIdx] = magnitude;
    }
#ifdef PICO
    // char buffer[8];
    // snprintf(buffer, sizeof(buffer), "%.2f", max_v);
    // uart_print(buffer);
#endif
}

float FFTProcessor::GetFrequency()
{
    Perform();
    return GetHzFromIdx(FindMaxIdx());
}

void FFTProcessor::PushIntoBuffer()
{
    auto delta = FFTParams::kFFTCounter - cpx_in_pos_;
    if (delta >= FFTParams::kAnalogReadBufferSize)
    {
        // just copy at current position
        std::memcpy(&sc_in_[cpx_in_pos_], sc_buffer_,
                    FFTParams::kAnalogReadBufferSize * sizeof(kiss_fft_scalar));
        cpx_in_pos_ += FFTParams::kAnalogReadBufferSize;
    }
    else
    {
        // copy everything back a sample
        std::memcpy(&sc_in_[0], &sc_in_[FFTParams::kAnalogReadBufferSize], FFTParams::kMemcpyHelper * sizeof(kiss_fft_scalar));
        // emplace new
        std::memcpy(&sc_in_[FFTParams::kMemcpyHelper], sc_buffer_, FFTParams::kAnalogReadBufferSize * sizeof(kiss_fft_scalar));
    }
    std::memset(sc_buffer_, 0, FFTParams::kAnalogReadBufferSize * sizeof(kiss_fft_scalar));
}

int FFTProcessor::GetCpxInSize() const
{
    return cpx_in_pos_;
}

void FFTProcessor::Add(FFT_SCALAR data)
{
    // in case buffer is not already filled completely
    auto delta = FFTParams::kAnalogReadBufferSize - add_pos_buffer_;
    // cpx_buffer_[add_pos_buffer_].r = data;
    sc_buffer_[add_pos_buffer_] = data;
    if (delta > 1)
    {
        add_pos_buffer_++;
    }
    // push everything a sample forward and append at end
    else
    {
        add_pos_buffer_ = 0;
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