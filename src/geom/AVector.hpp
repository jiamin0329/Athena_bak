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
#ifndef ATHENA_AVECTOR_HPP
#define ATHENA_AVECTOR_HPP

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
class AVector
{
public:
    AVector();
    AVector(double x, double y, double z);
    AVector(double x, double y);
    ~AVector(){};

    void Normalize();

    double operator[](int i)
    {
        if (i == 0)
            return d_x;
        else if (i == 1)
            return d_y;
        else if (i == 2)
            return d_z;
    }

private:
    double d_x, d_y, d_z;
};
}  // namespace ATHENA

#endif
