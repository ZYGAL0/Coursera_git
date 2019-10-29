cmake_minimum_required(VERSION 3.15)
project(DataBaseClass)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataBaseClass
        token.h
        condition_parser.h
        database.h
        date.h
        node.h
        test_runner.h
        main.cpp
        token.cpp
        condition_parser.cpp
        database.cpp
        date.cpp
        node.cpp
        test_runner.cpp
        )