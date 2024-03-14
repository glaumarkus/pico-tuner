import os
import numpy as np
from scipy.fft import fft
from scipy import signal
import matplotlib.pyplot as plt
from string import Template

test_templ = Template("""
{.result = $freq, .expected = $exp, .data = {$list}},""")

data_templ = Template("""
#pragma once

#include <vector>
#include <cstdint>

struct testcase
{
    float result;
    float expected;
    std::vector<uint16_t> data{};
};

std::vector<testcase> cases{
    $cases
};

""")

hw = np.hamming(100)

fs = 1000
sample_size = 100
T = 1.0 / 1000
zero_pads = 4
L = fs * zero_pads + fs
take_first_n = 300
target_start = 40.0
target_end = 350.0
num_pts = L
resolution = fs / L
peak_width = 5 / resolution


start_idx = int(target_start / resolution)
end_idx = int(target_end / resolution)

def samples_as_header(samples):
    pass

def prepare_samples(data: str):
    cleaned_samples = []
    # split samples
    samples = data.split("bufferend\n\n")[1:-1]
    for sample in samples:
        cleaned_samples.append(
            [int(i) for i in sample.split("\n")[:-1]]
        )
    return cleaned_samples 
    # hw reduces accuracy

def freq_from_result1(xf, yf):
    max_idx = np.argmax(yf)
    return xf[max_idx]

def freq_from_result2(xf, yf):
    max_idx = np.argmax(yf)
    max_magnitude = yf[max_idx]
    filter_mag = max_magnitude * 0.6
    avg = np.mean(yf)
    
    peak_idxs = []
    peak_max = 0
    
    # print(max_idx)
    for idx, x in enumerate(yf):
        if x < avg:
            if peak_max > 0:
                if yf[peak_max] >= filter_mag:
                    peak_idxs.append(peak_max)
                peak_max = 0
            continue
        
        if x > yf[peak_max]:
            peak_max = idx
        
    if len(peak_idxs) > 1:
        # filter for duplicate frequencies, e.g. 40, 80, 160
        tmp_freqs = [xf[i] for i in peak_idxs]
        # print(tmp_freqs)
        # [24, 74] [44, 54]
        # [40, 80, 160]
        filtered_idxs = []
        duplicates = []
        for xidx, x in enumerate(tmp_freqs):
            accepted_diff = x * 0.05
            found_duplicate = False
            for yidx, y in enumerate(tmp_freqs[xidx + 1:]):
                r = y % x
                if r < accepted_diff:
                    duplicates.append([xidx, yidx + 1])
        
        # multiple duplicates, take highest
        if len(duplicates) > 1:
            return xf[max_idx]
        
        # only one duplicate, take highest freq in sample
        elif len(duplicates) == 1:
            peak_idx = duplicates[0][-1]
            peak_idx = peak_idxs[peak_idx]
            return xf[peak_idx]
        
        # no duplicate, just return highest
        return xf[max_idx]
        
    return xf[max_idx]
    
# b.socrative.com/login/student 21434DAY1

test_cases = []
test_case_notes = {
    "1.cap": [],
    "2.cap": [],
    "3.cap": [],
    "4.cap": [],
    "5.cap": [],
    "6.cap": [],
}

def to_header(name, data, result, exp):
    header = test_templ.safe_substitute(dict(
        # id=name,
        list=','.join([str(i) for i in data]),
        exp=exp,
        freq=result
    ))
    test_cases.append(header)
    # with open("captures/validation/headers/" + str(name) + ".hpp", 'w') as f:
    #     f.write(header)
    

def to_png(name, xf, yf, freq):
    fig, ax = plt.subplots()
    ax.plot(xf, yf)
    ax.set_xscale('log')  
    ax.get_xaxis().set_major_formatter(plt.ScalarFormatter())  
    ax.set_xticks([10, 100, 500]) 
    plt.title(f'{str(freq)}')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Amplitude')
    plt.grid()
    plt.savefig(f'{name}.png')
    plt.close()

def FFTWithSample(sample):
    # apply padding
    padded = np.pad(sample, (0, zero_pads * fs + fs - sample_size), 'constant')
    yf = fft(padded)
    xf = np.linspace(0.0, 1.0/(2.0*T), L//2)
    yf = yf[:len(yf)//2]
    yf = np.abs(yf)
    return xf, yf

def FFTFilter(xf, yf):
    xf = xf[start_idx:end_idx]
    yf = yf[start_idx:end_idx]
    return xf, yf

# reference points
reference_points = {
    "1.cap": 293.665,
    "2.cap": 220.00,
    "3.cap": 174.614,
    "4.cap": 130.813,
    "5.cap": 97.998,
    "6.cap": 48.999,
}

def in_general_range(freq, target):
    if abs(freq - target) < 10:
        return True
    return False
    # return True

def get_target_note(freq, target):
    for key in target.keys():
        if abs(freq - target[key]) < 10:
            return target[key]
    return 0.0


def test_freq(xf, yf, exp):
    print("Expected: ", exp)
    print("Actual: ", freq_from_result(xf, yf))

def main():
    # with open("captures/validation/2.cap") as f:
    #     data = f.read()
    # samples = prepare_samples(data)
    # xf, yf = FFTWithSample(samples[0])
    # xf, yf = FFTFilter(xf, yf)
    # test_freq(xf, yf, reference_points["2.cap"])
        
    samples_in_range1 = 0
    samples_in_range2 = 0
    num_samples = 0
    file_counter = 0
    captures = os.listdir("captures/validation")
    test_cases = []
    for file in captures:
        if file.endswith(".cap"):
            # valid file
            with open(f"captures/validation/{file}") as f:
                data = f.read()
            samples = prepare_samples(data)
            num_these_samples = 0
            for sample in samples:
                xf, yf = FFTWithSample(sample)
                capture_num = file.split(".")[0]
                xf, yf = FFTFilter(xf, yf)
                if num_samples == 150:
                    print("")

                freq1 = freq_from_result1(xf, yf)
                target_note = get_target_note(freq1, reference_points)
                if target_note > 1:
                    if in_general_range(freq1, target_note):
                        # samples_in_range1 += 1
                        sample_templ = test_templ.safe_substitute(
                            dict(
                                list=','.join([str(i) for i in sample]),
                                freq=freq1,
                                exp=target_note,
                            )
                        )
                        test_cases.append(
                            sample_templ
                        )
            # print(file)
            # print(float(samples_in_range1) / num_these_samples)
            # print(float(samples_in_range2) / num_these_samples)
            # samples_in_range1 = 0
            # samples_in_range2 = 0
            # num_these_samples = 0
            # break
    
    # create test cases
    with open("captures/validation/headers/testcases.hpp", 'w') as f:
        f.write(data_templ.safe_substitute(dict(
            cases=''.join(test_cases),
        )))
    
           
if __name__ == '__main__' :
    main()
            
        
            