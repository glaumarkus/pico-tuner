# math_lib
add_library(fft_lib STATIC 
    fft.cpp
    timer.cpp
    frequency_map.cpp
    display.cpp
    )
target_link_libraries(fft_lib PRIVATE kissfft)
target_include_directories(fft_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
