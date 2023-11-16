cmake_minimum_required(VERSION 3.26)
project(MiniProjetC C)

set(CMAKE_C_STANDARD 11)

include_directories(actions)
include_directories(application)
include_directories(utils)

add_executable(MiniProjetC
    actions/actions.c
    actions/actions.h
    application/main.c
    utils/conio.c
    utils/conio.h
    utils/tools.c
    utils/tools.h)
