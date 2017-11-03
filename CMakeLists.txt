cmake_minimum_required(VERSION 3.8)
project(GeneralList)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c GeneralListOperate.h)
add_executable(GeneralList ${SOURCE_FILES} GeneralListOperate.h)