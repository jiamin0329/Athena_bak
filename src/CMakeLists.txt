##================================================================================
## Copyright (c) 2018 Ultra-Aero, All Rights Reserved
##================================================================================
## File description:
## Main CMake file for Athena.
##
##================================================================================
##    Date            Name                    Description of Change
##    20-Aug-2018     Jiamin Xu               Creation
##    22-Aug-2018     Jiamin Xu               Add geom
##================================================================================

## set path to output executable file
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

## add lib directory
link_directories("${PROJECT_SOURCE_DIR}/lib")

## add include directories
include_directories(${PROJECT_SOURCE_DIR}/src/geom)
include_directories(${PROJECT_SOURCE_DIR}/src/mesh)
include_directories(${PROJECT_SOURCE_DIR}/src/comm)
include_directories(${PROJECT_SOURCE_DIR}/src/proc)
include_directories(${PROJECT_SOURCE_DIR}/src/oput)

## compile executable file
add_executable(ATHENA ${PROJECT_SOURCE_DIR}/src/main.cpp)

## set link directory
target_link_libraries(ATHENA mesh comm proc oput geom ${Boost_LIBRARIES})
