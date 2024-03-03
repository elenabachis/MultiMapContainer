cmake_minimum_required(VERSION 3.24)
project(Lab4dsa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab4dsa
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        MultiMap.cpp
        MultiMap.h
        MultiMapIterator.cpp
        MultiMapIterator.h
        ShortTest.cpp
        ShortTest.h)
