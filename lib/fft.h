#pragma once

#include <cstdint>

#ifdef PICO
#include "hardware/sync.h"
#endif

#include "common.h"

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
    void Add(FFT_SCALAR data);
    void PushIntoBuffer();

    float GetFrequency();

    void Perform();
    float GetHzFromIdx(int idx) const;
    int FindMaxIdx() const;
    int GetCpxInSize() const;

private:
    int add_pos_buffer_{0};
    int cpx_in_pos_{0};
    // exchange
    kiss_fftr_cfg cfgr_;
    kiss_fft_scalar sc_buffer_[FFTParams::kAnalogReadBufferSize];
    kiss_fft_scalar sc_in_[FFTParams::kFFTBufferSize];
    kiss_fft_cpx cpx_out_[FFTParams::kFFTBufferSize];
    float freq_magnitude_[FFTParams::kAreaOfInterestSize];
// lock for cpx_in shared interaction
#ifdef PICO
    int spin_lock_id_ = spin_lock_claim_unused(true);
#endif
};

namespace Instance
{
    FFTProcessor *GetProcessor();
}