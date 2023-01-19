cmake_minimum_required(VERSION 3.23)
project(Archive)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Archive
        BSM_Part2.cpp
        BSM_Part2.h
        main.cpp
        Option.cpp
        Option.h
        Option_Price.cpp
        Option_Price.h
        Simulated_Price.cpp
        Simulated_Price.h
        Stock.cpp
        Stock.h
        Unit_Test.cpp
        Unit_Test.h)
