# wished for accuracy: 0.001
# calc of resolution
def calc_resolution(sample_rate, buffer_size):
    return float(sample_rate) / buffer_size

# for i in range(1000, 100000, 1000):
#     print(calc_resolution(i, i))
    

print(calc_resolution(1000, 10000))