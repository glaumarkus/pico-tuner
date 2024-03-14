# add lib
if (PICO_COMPILE)
    add_library(tuner_lib STATIC 
        fft.cpp
        common.cpp
        frequency_map.cpp
        display.cpp
        adc_record.cpp
        ${KISSFFT_SRC}
        )
    target_link_libraries(tuner_lib PRIVATE pico_stdlib hardware_i2c pico_multicore hardware_adc hardware_sync)
    target_include_directories(tuner_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
else()
    add_library(tuner_lib STATIC 
        fft.cpp
        frequency_map.cpp
        display.cpp
        timer.cpp
        ${KISSFFT_SRC}
        )
    target_link_libraries(tuner_lib PRIVATE)
    target_include_directories(tuner_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()
