# Enable testing with CTest
enable_testing()

# Define test executable
add_executable(fft_test fft_test.cpp) 

# Link the test executable with GoogleTest and your libraries
target_link_libraries(fft_test gtest gtest_main tuner_lib)

# Register the executable as a test
add_test(NAME fft_test COMMAND fft_test)
