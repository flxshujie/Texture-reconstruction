cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Texture C CXX)
SET(CMAKE_BUILD_TYPE Debug)

#OPENCV
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIRS} )
link_directories(${OPENCV_LIBRARY_DIRS})
add_definitions(${OPENCV_DEFINITIONS})


#OpenMP
find_package(OpenMP REQUIRED)
SET(CMAKE CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

INCLUDE_DIRECTORIES(io)


add_subdirectory(io)
add_subdirectory(apps)
add_subdirectory(modules)


link_directories(./io)
