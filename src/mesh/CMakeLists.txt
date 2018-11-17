##================================================================================
## Copyright (c) 2018 Ultra-Aero, All Rights Reserved
##================================================================================
## File description:
## Main CMake file for libmesh
##
##================================================================================
##    Date            Name                    Description of Change
##    20-Aug-2018     Jiamin Xu               Creation
##    22-Oct-2018     Jiamin Xu               Add ConnectivityProc
##================================================================================

## set path to output library
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

## add include directories
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/geom)
include_directories(${PROJECT_SOURCE_DIR}/src/math)

## add lib directory
link_directories("${PROJECT_SOURCE_DIR}/lib")

## set src file list
set(MESH_SRC 
Vertice.hpp 
Mesh.cpp 
StrBlock.cpp 
ConnectivityProc.cpp ) 

## produce libmesh
add_library(mesh SHARED ${MESH_SRC})
set_target_properties(mesh PROPERTIES OUTPUT_NAME "mesh")
set_target_properties(mesh PROPERTIES VERSION 1.0 SOVERSION 1.0)

## link geom
target_link_libraries(mesh geom)

## link boost
target_link_libraries(mesh ${Boost_LIBRARIES})

## link cgns
target_link_libraries(mesh cgns)
