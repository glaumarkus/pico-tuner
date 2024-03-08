cmake_minimum_required(VERSION 3.15.0)
project(raytracer VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD "17")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")

include(CTest)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

# add GTest
add_subdirectory(external/googletest-release-1.11.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# add subdirectories
add_subdirectory(external/kissfft-131.1.0)
include_directories(${PROJECT_SOURCE_DIR}/external/kissfft-131.1.0)

add_subdirectory(lib)
add_subdirectory(unit_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

