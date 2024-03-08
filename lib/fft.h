#pragma once

#include <cstdint>
#include <kiss_fft.h>

namespace FFTParams
{
    constexpr int kSamplePerSec = 44000;
    constexpr int kScreenUpdatesPerSecond = 20;
    constexpr int kAnalogBlocksPerFFT = 4;
    constexpr int kAnalogReadBufferSize = static_cast<double>(kSamplePerSec) / kScreenUpdatesPerSecond;
    constexpr int kFFTCounter = kAnalogBlocksPerFFT * kAnalogReadBufferSize;
    constexpr int kMemcpyHelper = kFFTCounter - kAnalogReadBufferSize;
    constexpr int kNumZeroPads = 1;
    constexpr int kFFTBufferSize = kSamplePerSec + kNumZeroPads * kSamplePerSec;
    constexpr double kFFTResolution = static_cast<double>(kSamplePerSec) / static_cast<double>(kFFTBufferSize);

    constexpr double kAreaOfInterestBegin = 20.0;
    constexpr double kAreaOfInterestEnd = 500.0;
    constexpr int kAreaOfInterestBeginIdx = kAreaOfInterestBegin / kFFTResolution;
    constexpr int kAreaOfInterestEndIdx = kAreaOfInterestEnd / kFFTResolution;
    constexpr int kAreaOfInterestSize = kAreaOfInterestEndIdx - kAreaOfInterestBeginIdx;

};

struct fp
{
    float start;
    float end;
};

class FFTProcessor
{
public:
    FFTProcessor() = default;
    ~FFTProcessor() = default;
    bool Init();
    void Add(float data);
    void PushIntoBuffer();

    float GetFrequency();

    void Perform();
    constexpr float GetHzFromIdx(int idx) const { return (idx + FFTParams::kAreaOfInterestBeginIdx) * FFTParams::kFFTResolution; }
    int FindMaxIdx() const;
    int GetCpxInSize() const;

private:
    kiss_fft_cfg cfg_;
    int add_pos_buffer_{0};
    int cpx_in_pos_{0};
    kiss_fft_cpx cpx_buffer_[FFTParams::kAnalogReadBufferSize];
    kiss_fft_cpx cpx_in_[FFTParams::kFFTBufferSize];
    kiss_fft_cpx cpx_out_[FFTParams::kFFTBufferSize];
    float freq_magnitude_[FFTParams::kAreaOfInterestSize];
};
