cmake_minimum_required(VERSION 4.3)
project(NHF C)

set(CMAKE_C_STANDARD 11)

add_executable(NHF main.c
        jatekAlgoritmus.c
        jatekAlgoritmus.h
        tabellaOlvasas.c
        tabellaOlvasas.h)
