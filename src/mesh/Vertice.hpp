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
 *    07-Apr-2019     Jiamin Xu               Add SetCoord/GetX/GetY/GetZ
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

    double GetX() const { return d_x; };
    double GetY() const { return d_y; };
    double GetZ() const { return d_z; };

    void SetCoord(int coord, double value);

private:
    int    d_index;
    double d_x;
    double d_y;
    double d_z;
};
}  // namespace ATHENA

#endif