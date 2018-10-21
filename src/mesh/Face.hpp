/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena Face object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    17-Oct-2018     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_FACE_HPP
#define ATHENA_FACE_HPP

/* Athena headers */
#include "IFace.hpp"

/* c++ headers */

/*
 *================================================================================
 *    Forward declarations
 *================================================================================
 */
namespace ATHENA
{
class Point;
}
/*
 *================================================================================
 *    Class namespaces
 *================================================================================
 */
namespace ATHENA
{
class Face : public IFace
{
public:
    Face(Point* pnt1, Point* pnt2, Point* pnt3, Point* pnt4);
    Face();
    ~Face(){};

private:
    int d_ni, d_nj, d_nk;
};
}  // namespace ATHENA

#endif