cmake_minimum_required(VERSION 3.13)
project(augment_camera)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message(" ")
    message("CMAKE IN DEBUG MODE")
    message(" ")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message(" ")
    message("CMAKE IN RELEASE MODE")
    message(" ")
endif ()

find_package( OpenCV REQUIRED )
find_package( Qt5 COMPONENTS Core Gui Widgets REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(augment_camera main.cpp widget.cpp VirtualCamera.cpp VirtualCamera.hpp SimpleFaceDetector.hpp CameraAugment.cpp CameraAugment.hpp)
target_link_libraries( augment_camera ${OpenCV_LIBS} Qt5::Widgets Qt5::Gui Qt5::Core)