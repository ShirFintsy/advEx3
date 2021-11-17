cmake_minimum_required(VERSION 3.20)
project(advEx3)

set(CMAKE_CXX_STANDARD 14)

add_executable(advEx3 anomaly_detection_util.h anomaly_detection_util.cpp MainTrain.cpp minCircle.cpp minCircle.h)
