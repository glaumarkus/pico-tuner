#pragma once

#include <cstdint>

#define FFT_SCALAR int16_t

#ifdef PICO
#define ENABLE_LOGGING
#include "pico/stdlib.h"
#include "hardware/uart.h"
#ifdef ENABLE_LOGGING
#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1
void setup_uart();
void uart_print(const char *str);
#endif
#endif

constexpr uint32_t kCoreStarted = 0x00000000;
constexpr uint32_t kNewMeasurement = 0x00000001;
constexpr uint32_t kFFTDone = 0x00000002;

namespace FFTParams
{
    // since area of interest really only begins at 500hz sampleing at higher freq than 1000hz makes no sense
    constexpr int kSamplePerSec = 1000;
    constexpr int kRecordTaskus = 1000000 / kSamplePerSec;
    constexpr int kScreenUpdatesPerSecond = 10;
    constexpr int kScreenUpdateEveryUs = 1000000 / kScreenUpdatesPerSecond;
    constexpr int kAnalogBlocksPerFFT = 4;
    constexpr int kAnalogReadBufferSize = static_cast<double>(kSamplePerSec) / kScreenUpdatesPerSecond;
    constexpr int kFFTCounter = kAnalogBlocksPerFFT * kAnalogReadBufferSize;
    constexpr int kMemcpyHelper = kFFTCounter - kAnalogReadBufferSize;
    // 9 zero pads to increase accuracy to around 0.1
    constexpr int kNumZeroPads = 9;
    constexpr int kFFTBufferSize = kSamplePerSec + kNumZeroPads * kSamplePerSec;
    constexpr double kFFTResolution = static_cast<double>(kSamplePerSec) / static_cast<double>(kFFTBufferSize);

    constexpr double kAreaOfInterestBegin = 20.0;
    constexpr double kAreaOfInterestEnd = 500.0;
    constexpr int kAreaOfInterestBeginIdx = kAreaOfInterestBegin / kFFTResolution;
    constexpr int kAreaOfInterestEndIdx = kAreaOfInterestEnd / kFFTResolution;
    constexpr int kAreaOfInterestSize = kAreaOfInterestEndIdx - kAreaOfInterestBeginIdx;

    constexpr int kMagnitudeCutoff = 4000;
};
