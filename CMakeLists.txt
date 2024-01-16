cmake_minimum_required(VERSION 3.27)
project(test C)

set(CMAKE_C_STANDARD 11)

add_executable(test
        test.c
        testwithcmd.c
        ContactMgmt.c
        lecture-test.c
        studentReg.c)
