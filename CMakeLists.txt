cmake_minimum_required(VERSION 3.16)
project(21f_final_proj_template)

set(CMAKE_CXX_STANDARD 17)

add_executable(21f_final_proj_template main.cpp DocumentParser.cpp IndexEntry.cpp IndexHandler.cpp porter2_stemmer.cpp FileHandler.cpp QueryEngine.cpp)
