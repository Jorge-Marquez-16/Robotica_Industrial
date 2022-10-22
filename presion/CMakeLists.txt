cmake_minimum_required(VERSION 3.0)
project(presion)


#incluir headers o prototipos
include_directories(include)


add_executable(
    presion_exe #binario
    src/main.cpp 
    src/presion.cpp

)