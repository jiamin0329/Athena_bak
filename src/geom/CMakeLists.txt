##================================================================================
## Copyright (c) 2018 Ultra-Aero, All Rights Reserved
##================================================================================
## File description:
## Main CMake file for libgeom
##
##================================================================================
##    Date            Name                    Description of Change
##    22-Aug-2018     Jiamin Xu               Creation
##    22-Oct-2018     Jiamin Xu               Move ConnectivityProc to mesh lib
##                                            Add Volume.cpp
##================================================================================

## set path to output library
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

## add include directories
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/mesh)

## set src file list
set(GEOM_SRC 
Point.cpp 
Face.cpp 
Volume.cpp)

## produce libcomm
add_library(geom SHARED ${GEOM_SRC})
set_target_properties(geom PROPERTIES OUTPUT_NAME "geom")
set_target_properties(geom PROPERTIES VERSION 1.0 SOVERSION 1.0)
