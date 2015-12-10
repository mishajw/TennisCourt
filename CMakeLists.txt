cmake_minimum_required(VERSION 3.3)
project(tenniscourt)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/KMeans.cpp src/KMeans.h src/LineDetector.cpp src/LineDetector.h src/LineIdentifier.cpp src/LineIdentifier.h src/CourtLine.cpp src/CourtLine.h src/Line.cpp src/Line.h src/SimpleLineIdentifier.cpp src/SimpleLineIdentifier.h src/CSVExporter.cpp src/CSVExporter.h)
add_executable(tenniscourt ${SOURCE_FILES})
target_link_libraries(tenniscourt ${OpenCV_LIBS})
