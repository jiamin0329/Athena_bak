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
##    27-Sep-2018     Jiamin Xu               Add -wall in debug mode
##================================================================================

##================================================================================
## Enforce an out-of-source builds before anything else
##================================================================================
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(STATUS "ATHENA requires an out-of-source build.")
  message(FATAL_ERROR "in-source build detected")
endif()

##================================================================================
## Define CMake requirements and override make rules as needed
##================================================================================
## minimum version required
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

## to override CMP0042 issue
## MACOSX_RPATH is enabled by default, turn it off
set(CMAKE_MACOSX_RPATH 0)

##================================================================================
## General info
##================================================================================
## project name
project(ATHENA)

## version number
set(ATHENA_VERSION 0.1)
message(STATUS "Current ATHENA version: " ${ATHENA_VERSION})

##================================================================================
## Complier settings
##================================================================================
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_BUILD_TYPE "Debug")
message(STATUS "Build Type: " ${CMAKE_BUILD_TYPE})
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_definitions(-DDEBUG)
endif()

##================================================================================
## Setting up dependencies
##================================================================================
## set up boost
find_package(Boost REQUIRED COMPONENTS filesystem system date_time)
if(NOT Boost_FOUND)
  message(FATAL_ERROR "Can NOT find boost in system!")
endif()

##================================================================================
## Main cmake procedures
##================================================================================
add_subdirectory("${PROJECT_SOURCE_DIR}/src/comm")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/geom")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/mesh")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/proc")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/oput")
add_subdirectory("${PROJECT_SOURCE_DIR}/src")
