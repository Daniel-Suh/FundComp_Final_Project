
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
# Above line indicates to Cmake that minimum version 2.8 is required.
# As you may have noted all lines beginning with hash symbol are treated as comments by Cmake.
project(circleGame)
SET(sampleName MyApp)
include_directories(-L/opt/X11/lib/)
include_directories(-I/opt/X11/include/)
include_directories(-lX11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(My_Project Threads::Threads)

target_link_libraries(My_Project X11)

add_executable (circleGame circleBoard.cpp circleBoard.h project.cpp gfx.h gfx_mac.o)
