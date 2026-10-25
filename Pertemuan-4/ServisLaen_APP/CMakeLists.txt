cmake_minimum_required(VERSION 3.10)
project(servis_laen LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
# Default ke Release kalau tidak ditentukan
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
 
add_executable(servis_laen app.cpp)
 
# json.hpp ada di folder yang sama dengan app.cpp
target_include_directories(servis_laen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
 
target_compile_options(servis_laen PRIVATE -Wall -Wextra)