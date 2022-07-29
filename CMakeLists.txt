cmake_minimum_required(VERSION 3.16)


project(search_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(search_engine src/main.cpp src/DocumentParser.cpp src/IndexEntry.cpp src/IndexHandler.cpp src/porter2_stemmer.cpp src/FileHandler.cpp src/QueryEngine.cpp)
