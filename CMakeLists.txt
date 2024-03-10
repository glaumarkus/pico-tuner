cmake_minimum_required(VERSION 3.15.0)

# include(pico_sdk_import.cmake)
# project(pico-tuner C CXX ASM)
# set(CMAKE_C_STANDARD 11)
# set(CMAKE_CXX_STANDARD 17)
# pico_sdk_init()
# add_subdirectory(external/kissfft-131.1.0)
# include_directories(${PROJECT_SOURCE_DIR}/external/kissfft-131.1.0)


# Check if the C compiler is set to arm-none-eabi-gcc
if("${CMAKE_C_COMPILER}" STREQUAL "/usr/bin/arm-none-eabi-gcc")
    set(PICO_COMPILE ON)
    add_definitions(-DPICO=1)
    message(STATUS "Using arm-none-eabi-gcc for C")
else()
    set(PICO_COMPILE OFF)
    message(WARNING "Not using arm-none-eabi-gcc for C")
endif()

# import pico sdk 
if (PICO_COMPILE)
    include(pico_sdk_import.cmake)
endif()

project(pico-tuner C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
if (PICO_COMPILE)
    pico_sdk_init()
endif()


# add subdirectories
set(KISSFFT_DATATYPE "int16_t")
add_subdirectory(external/kissfft-131.1.0)
include_directories(${PROJECT_SOURCE_DIR}/external/kissfft-131.1.0)

# add testing
if (!PICO_COMPILE)
    include(CTest)
    enable_testing()
    # add GTest
    add_subdirectory(external/googletest-release-1.11.0)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif()

# add lib
add_subdirectory(lib)

if (CMAKE_CROSSCOMPILING)
    # add bins
    add_subdirectory(hw_test)
else()
    # add UTs
    include(CTest)
    enable_testing()
    # add GTest
    add_subdirectory(external/googletest-release-1.11.0)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    add_subdirectory(unit_test)
    set(CPACK_PROJECT_NAME ${PROJECT_NAME})
    set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
    include(CPack)
endif()




