cmake_minimum_required(VERSION 3.9)
project(MyOpenCVApp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(myapp main.cpp)
target_link_libraries(myapp ${OpenCV_LIBS})