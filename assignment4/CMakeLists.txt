cmake_minimum_required(VERSION 3.10)
project(mc2d)
#to avoid listing all .cpp files in executable, make function that adds them all
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp) #grab every .cpp file
include_directories(${PROJECT_SOURCE_DIR}/include) #grab all .hpp files

add_executable(mc2d ${SOURCES}) #to something that contains a main function
