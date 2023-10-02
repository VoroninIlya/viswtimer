cmake_minimum_required(VERSION 3.22)

project(viswtimer)

# Debug message
message("Entering ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")

# Register core library
add_library(viswtimer INTERFACE)
target_sources(viswtimer PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/viswtimer.c)
target_include_directories(viswtimer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/inc)

# Debug message
message("Exiting ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")