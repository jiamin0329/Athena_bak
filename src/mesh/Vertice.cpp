/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena Vertice object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    17-Oct-2018     Jiamin Xu               Creation
 *================================================================================
 */

/* Athena headers */
#include "Vertice.hpp"

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

Vertice::Vertice() : d_x(0.0), d_y(0.0), d_z(0.0) {}
Vertice::Vertice(double x, double y, double z) : d_x(x), d_y(y), d_z(z) {}
Vertice::Vertice(double x, double y) : d_x(x), d_y(y), d_z(0.0) {}
Vertice::~Vertice() {}

}  // namespace ATHENA