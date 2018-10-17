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
#ifndef ATHENA_POINT_HPP
#define ATHENA_POINT_HPP

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
class Point
{
public:
    Point(double x, double y, double z);
    Point(double x, double y);
    Point();
    ~Point();

private:
    double d_x;
    double d_y;
    double d_z;

    bool d_inner;
};
}  // namespace ATHENA

#endif