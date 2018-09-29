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

## set src file list
set(OPUT_SRC 
OutputMgr.cpp)

## produce liboput
add_library(oput SHARED ${OPUT_SRC})
set_target_properties(oput PROPERTIES OUTPUT_NAME "oput")
sET_TARGET_PROPERTIES (oput PROPERTIES VERSION 1.0 SOVERSION 1.0)

## link boost
target_link_libraries(oput ${Boost_LIBRARIES})

## link cgns
target_link_libraries(oput cgns)
