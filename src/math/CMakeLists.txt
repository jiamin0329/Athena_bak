##================================================================================
## Copyright (c) 2018 Ultra-Aero, All Rights Reserved
##================================================================================
## File description:
## Main CMake file for libmath
##
##================================================================================
##    Date            Name                    Description of Change
##    22-Aug-2018     Jiamin Xu               Creation
##================================================================================

## set path to output library
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

## add include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

## set src file list
set(MATH_SRC 
AVector.cpp)

## produce libcomm
add_library(math SHARED ${MATH_SRC})
set_target_properties(math PROPERTIES OUTPUT_NAME "math")
set_target_properties(math PROPERTIES VERSION 1.0 SOVERSION 1.0)
