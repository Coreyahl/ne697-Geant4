cmake_minimum_required(VERSION 3.10)
project(mc1d)
#to avoid listing all .cpp files in executable, make function that adds them all
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp) #grab every .cpp file
include_directories(${PROJECT_SOURCE_DIR}/include) #grab all .hpp files

add_executable(mc1d ${SOURCES}) #to something that contains a main function
