##================================================================================
## Copyright (c) 2018 Ultra-Aero, All Rights Reserved
##================================================================================
## File description:
## Main CMake file for libcomm
##
##================================================================================
##    Date            Name                    Description of Change
##    20-Aug-2018     Jiamin Xu               Creation
##    28-Sep-2018     Jiamin Xu               Remove external include/link directory
##================================================================================

## set path to output library
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

## add include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

## set src file list
set(COMM_SRC 
OptionMgr.cpp 
Logger.cpp 
Option.cpp)

## produce libcomm
add_library(comm SHARED ${COMM_SRC})
set_target_properties(comm PROPERTIES OUTPUT_NAME "comm")
set_target_properties(comm PROPERTIES VERSION 1.0 SOVERSION 1.0)

## link glog
target_link_libraries(comm glog)