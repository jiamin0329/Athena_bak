/*
 *================================================================================
 * Copyright (c) 2019 Agi-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena zone object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    03-Apr-2019     Jiamin Xu               Creation
 *================================================================================
 */

/* Athena headers */
#include "Zone.hpp"

/* c++ headers */

/* External headers */

/*
 *================================================================================
 *    Forward declarations
 *================================================================================
 */

/*
 *================================================================================
 *    Class namespaces
 *================================================================================
 */
namespace ATHENA
{
Zone::Zone(char* zoneName, IZone::ZoneType_t zoneType, int numCoords)
    : d_name(zoneName), d_type(zoneType), d_numCoords(numCoords)
{
}

Zone::~Zone() {}

}  // namespace ATHENA
