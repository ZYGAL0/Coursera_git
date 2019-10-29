cmake_minimum_required(VERSION 3.15)
project(Framework)

set(CMAKE_CXX_STANDARD 17)

add_executable(Framework
#        test_equation.cpp
#        test_person.cpp
        test_rational.cpp
#        test_palindrome.cpp
        Test_runner.h Rational.h Tests.h)
