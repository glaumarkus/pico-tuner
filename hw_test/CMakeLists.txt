add_executable(test_label
        test_label.cpp
        )

# pull in common dependencies and additional i2c hardware support
target_link_libraries(test_label tuner_lib pico_stdlib hardware_i2c)

# create map/bin/hex file etc.
pico_add_extra_outputs(test_label)


add_executable(test_multicore
        test_multicore.cpp
        )

# Add pico_multicore which is required for multicore functionality
target_link_libraries(test_multicore
        pico_stdlib
        pico_multicore
        tuner_lib
        hardware_i2c 
        hardware_adc 
        hardware_sync
)
pico_enable_stdio_uart(test_multicore 1)
# create map/bin/hex file etc.
pico_add_extra_outputs(test_multicore)


add_executable(test_recording
test_recording.cpp
        )

# Add pico_multicore which is required for multicore functionality
target_link_libraries(test_recording
        pico_stdlib
        pico_multicore
        tuner_lib
        hardware_i2c 
        hardware_adc 
        hardware_sync
)
pico_enable_stdio_uart(test_recording 1)
# create map/bin/hex file etc.
pico_add_extra_outputs(test_recording)
