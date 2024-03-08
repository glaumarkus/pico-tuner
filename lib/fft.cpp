#include "fft.h"
#include <cmath>
#include <complex>
#include <cstring>

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
    float max_value = 0.0f;
    int last_idx = 0;
    for (int i = 0; i < FFTParams::kAreaOfInterestSize; i++)
    {
        if (freq_magnitude_[i] > max_value)
        {
            max_value = freq_magnitude_[i];
            last_idx = i;
        }
    }
    return last_idx;
}

void FFTProcessor::Perform()
{
    kiss_fft(cfg_, cpx_in_, cpx_out_);
    // perform and then return the idx
    for (int i = FFTParams::kAreaOfInterestBeginIdx;
         i < FFTParams::kAreaOfInterestEndIdx; i++)
    {
        freq_magnitude_[i - FFTParams::kAreaOfInterestBeginIdx] =

            std::sqrt(cpx_out_[i].r * cpx_out_[i].r + cpx_out_[i].i * cpx_out_[i].i);
    }
}

float FFTProcessor::GetFrequency()
{
    Perform();
    return GetHzFromIdx(FindMaxIdx());
}

void FFTProcessor::PushIntoBuffer()
{
    // check current position
    auto delta = FFTParams::kFFTCounter - cpx_in_pos_;
    if (delta >= FFTParams::kAnalogReadBufferSize)
    {
        // just copy at current position
        std::memcpy(&cpx_in_[cpx_in_pos_], cpx_buffer_,
                    FFTParams::kAnalogReadBufferSize * sizeof(kiss_fft_cpx));
        cpx_in_pos_ += FFTParams::kAnalogReadBufferSize;
    }
    else
    {
        // copy everything back a sample
        std::memcpy(&cpx_in_[0], &cpx_in_[FFTParams::kAnalogReadBufferSize], FFTParams::kMemcpyHelper);
        // emplace new
        std::memcpy(&cpx_in_[FFTParams::kMemcpyHelper], cpx_buffer_, FFTParams::kAnalogReadBufferSize);
    }
}

int FFTProcessor::GetCpxInSize() const
{
    return cpx_in_pos_;
}

void FFTProcessor::Add(float data)
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
        PushIntoBuffer();
    }
}