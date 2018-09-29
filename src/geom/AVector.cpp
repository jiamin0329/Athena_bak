/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena vector object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    22-Aug-2018     Jiamin Xu               Creation
 *================================================================================
 */

/* Athena headers */
#include "AVector.hpp"

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
AVector::AVector() : d_x(0.0), d_y(0.0), d_z(0.0) {}

AVector::AVector(double x, double y, double z) : d_x(x), d_y(y), d_z(z) {}

AVector::AVector(double x, double y) : d_x(x), d_y(y), d_z(0.0) {}

void
AVector::Normalize()
{
    double norm = sqrt(d_x * d_x + d_y * d_y + d_z * d_z);

    d_x = d_x / norm;
    d_y = d_y / norm;
    d_z = d_z / norm;
}

}  // namespace ATHENA
