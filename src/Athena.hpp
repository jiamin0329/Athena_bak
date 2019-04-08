/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Main header file for Athena
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *    07-Apr-2019     Jiamin Xu               Add NULL_USE
 *================================================================================
 */
#ifndef ATHENA_HPP
#define ATHENA_HPP

/* c++ headers */
#include <iostream>

/*
 *================================================================================
 *    Athena declarations
 *================================================================================
 */
// Athena return codes
typedef enum
{
    Status_OK    = 0,
    Status_ERROR = 1
} Status_t;

// Used for parallel coding
#define MASTER_NODE 0
#define SINGLE_NODE 1

// Minimum double in Athena system
#define EPS 1.0E-16

// Default defined maximum string size
#define MAX_STRING_SIZE 500

/*****************************************************************************
 * Default filenames used in Athena
 ****************************************************************************/
// Default config file for Athena
#define ATHENA_CONTROL_FILE "athena.ini"
#define ATHENA_LOG_FILE "athena.log"

/*****************************************************************************
 * Definitions for degree/radian
 ****************************************************************************/
#define PI 3.1415926535897932
#define DEG_TO_RAD(deg) deg *PI / 180.0

/*****************************************************************************
 * A null use of a variable, use to avoid GNU compiler
 * warnings about unused variables.
 ****************************************************************************/
#define NULL_USE(variable)                                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        if (0)                                                                                                         \
        {                                                                                                              \
            char *temp = (char *) &variable;                                                                           \
            ++temp;                                                                                                    \
        }                                                                                                              \
    } while (0)

// end of athena.hpp
#endif