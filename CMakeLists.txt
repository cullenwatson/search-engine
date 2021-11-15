cmake_minimum_required(VERSION 3.16)
project(21f_final_proj_template)

set(CMAKE_CXX_STANDARD 17)
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()
add_executable(21f_final_proj_template main.cpp catch_setup.cpp DocumentParser.cpp IndexEntry.cpp IndexHandler.cpp porter2_stemmer.cpp FileHandler.cpp QueryEngine.cpp)
