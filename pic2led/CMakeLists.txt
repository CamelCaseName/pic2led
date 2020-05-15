# CMakeList.txt : CMake project for pic2led, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("pic2led")

# Add source to this project's executable.
add_executable (pic2led "pic2led.cpp" "pic2led.h")

# TODO: Add tests and install targets if needed.
