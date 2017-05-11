cmake_minimum_required(VERSION 3.7)
project(lab_3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        "other files/frequency_table.txt"
        "other files/test1_out.txt"
        "other files/test2_out.txt"
        "other files/test3_out.txt"
        "other files/words.txt"
        BinarySearchTree.h
        dsexceptions.h
        test4.cpp
        )

add_executable(lab_3 ${SOURCE_FILES})