##================================================================================
## Copyright (c) 2018 Ultra-Aero, All Rights Reserved
##================================================================================
## File description:
## Main CMake file for libcomm
##
##================================================================================
##    Date            Name                    Description of Change
##    20-Aug-2018     Jiamin Xu               Creation
##================================================================================

## set path to output library
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

## add include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

## add link directories
set(PROC_DATA 
ProcData.cpp )

## produce libproc
add_library(proc SHARED ${PROC_DATA})
set_target_properties(proc PROPERTIES OUTPUT_NAME "proc")
set_target_properties(proc PROPERTIES VERSION 1.0 SOVERSION 1.0)