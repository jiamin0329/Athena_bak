/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena vertice object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    13-Nov-2018     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_VERTICE_HPP
#define ATHENA_VERTICE_HPP

/* Athena headers */

/* c++ headers */

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
class Vertice
{
public:
    Vertice(double x, double y, double z);
    Vertice(double x, double y);
    Vertice();
    ~Vertice();

private:
    int    d_index;
    double d_x;
    double d_y;
    double d_z;
};
}  // namespace ATHENA

#endif