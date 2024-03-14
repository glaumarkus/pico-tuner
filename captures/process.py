import numpy as np
from scipy.fft import fft
import matplotlib.pyplot as plt

with open("captures/minicom_a.cap") as f:
    data = f.read()
    
samples = data.split("Sample\n")
sample_id = 0
for i in range(1, len(samples) - 1):
    i_samples = [int(i) for i in samples[i].split("\n")[:-1]] 
    valid = False
    for sample in i_samples:
        if sample > 30:
            valid = True
            break
    if valid:
        
        fs = 1000
        T = 1.0 / 1000
        zero_pads = 9
        L = fs * zero_pads + fs
        take_first_n = 300
        target_start = 20.0
        target_end = 500.0
        
        num_pts = L
        resolution = fs / L
        
        start_idx = int(target_start / resolution)
        end_idx = int(target_end / resolution)
        
        i_samples = i_samples[:take_first_n]
        # apply 0 padding
        padded = np.pad(i_samples, (0, zero_pads * fs + fs - take_first_n), 'constant')
        # print(len(padded))
        yf = fft(padded)
        xf = np.linspace(0.0, 1.0/(2.0*T), L//2)
        
        # cutoff everything before 20hz and everything after 500hz
        yf = yf[start_idx:start_idx + 4800]
        xf = xf[start_idx:]
        
        # get peak
        idx_peak = np.argmax(np.abs(yf))
        
        amplitude = np.abs(yf)
        
        # Set the values of 'yf' to 0 where the amplitude is less than 10        
        # yf = 2.0/L * np.abs(yf)
        amplitude = np.where(amplitude < 4000, 0, amplitude)
        

        # Plot
        fig, ax = plt.subplots()
        ax.plot(xf, amplitude)
        ax.set_xscale('log')  # Set logarithmic scale
        ax.get_xaxis().set_major_formatter(plt.ScalarFormatter())  # Use scalar formatting
        ax.set_xticks([10, 100, 500])  # Define x-ticks to improve readability
        plt.title('Fast Fourier Transform')
        plt.xlabel('Frequency (Hz)')
        plt.ylabel('Amplitude')
        plt.grid()

        # Save the plot to the filesystem
        plt.savefig(f'{sample_id}.png')
        sample_id += 1
    
    # break
# print(samples[1])

# reference points
# 6 -> 48,9995
# 5 -> 97,9989
# 4 -> 130,813
# 3 -> 174,614
# 2 -> 220
# 1 -> 293,665