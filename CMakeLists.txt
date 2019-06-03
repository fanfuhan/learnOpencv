cmake_minimum_required(VERSION 3.13)
project(learnOpencv)

set(CMAKE_CXX_STANDARD 11)

# Where to find CMake modules and OpenCV
set(OpenCV_DIR "D:\\software\\opencv4\\MinGW64_build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(learnOpencv 139.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs opencv_photo opencv_calib3d
        opencv_video)
# linking
target_link_libraries(learnOpencv ${OpenCV_LIBS})


