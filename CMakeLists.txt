cmake_minimum_required(VERSION 3.3)
project(tenniscourt)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp KMeans.cpp KMeans.h LineDetector.cpp LineDetector.h LineIdentifier.cpp LineIdentifier.h)
add_executable(tenniscourt ${SOURCE_FILES})
target_link_libraries(tenniscourt ${OpenCV_LIBS})
