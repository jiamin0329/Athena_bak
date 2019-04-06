/*
 *================================================================================
 * Copyright (c) 2019 Agi-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Interface for zone class
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    03-Apr-2019     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_IZONE_HPP
#define ATHENA_IZONE_HPP

/* Athena headers */
#include "../Athena.hpp"

#include "Vertice.hpp"

/* c++ headers */
#include <vector>

using namespace std;

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
class IZone
{
public:
    typedef enum
    {
        ZoneType_none         = 0,
        ZoneType_structured   = 1,
        ZoneType_unstructured = 2

    } ZoneType_t;

    virtual ~IZone(){};

    virtual string     GetName() const        = 0;
    virtual ZoneType_t GetType() const        = 0;
    virtual int        GetNumCoords() const   = 0;
    virtual int        GetNumVertices() const = 0;
    virtual Vertice*   GetVertice(int index)  = 0;

protected:
    explicit IZone(){};
};
}  // namespace ATHENA

#endif