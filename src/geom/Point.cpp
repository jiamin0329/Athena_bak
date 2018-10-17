/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena point object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    17-Oct-2018     Jiamin Xu               Creation
 *================================================================================
 */

/* Athena headers */
#include "Point.hpp"

/* c++ headers */
#include <cmath>

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

Point::Point() : d_x(0.0), d_y(0.0), d_z(0.0) {}
Point::Point(double x, double y, double z) : d_x(x), d_y(y), d_z(z) {}
Point::Point(double x, double y) : d_x(x), d_y(y), d_z(0.0) {}
Point::~Point() {}

}  // namespace ATHENA