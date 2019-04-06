/*
 *================================================================================
 * Copyright (c) 2019 Agi-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena grid zone object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    03-Apr-2019     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_ZONE_HPP
#define ATHENA_ZONE_HPP

/* Athena headers */
#include "IZone.hpp"

/* c++ headers */
#include <string>
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
class Zone : public IZone
{
public:
    Zone(char* zoneName, IZone::ZoneType_t zoneType, int numCoords);
    ~Zone();

    virtual string     GetName() const { return d_name; };
    virtual ZoneType_t GetType() const { return d_type; };

    virtual int      GetNumCoords() const { return d_numCoords; };
    virtual int      GetNumVertices() const = 0;
    virtual int      GetNumCells() const    = 0;
    virtual Vertice* GetVertice(int index)  = 0;

protected:
    string     d_name;
    ZoneType_t d_type;
    int        d_dim;
    int        d_numCoords;
};
}  // namespace ATHENA

#endif