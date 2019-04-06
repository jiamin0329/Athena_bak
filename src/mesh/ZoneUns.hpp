/*
 *================================================================================
 * Copyright (c) 2019 Agi-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena unstructure grid zone object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    03-Apr-2019     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_ZONEUNS_HPP
#define ATHENA_ZONEUNS_HPP

/* Athena headers */
#include "Zone.hpp"

#include "Vertice.hpp"

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
class ZoneUns : public Zone
{
public:
    ZoneUns(char*             zoneName,
            IZone::ZoneType_t zoneType,
            int               numVertices,
            int               numCells,
            int               numBoundaryVerts,
            int               numCoords);
    ~ZoneUns();

    virtual int      GetNumVertices() const { return d_numVertices; };
    virtual int      GetNumCells() const { return d_numCells; };
    virtual Vertice* GetVertice(int index) { return d_verticeContainer[index]; };

private:
    vector<Vertice*> d_verticeContainer;

    int d_numVertices;
    int d_numCells;
    int d_numBoundaryVerts;
};
}  // namespace ATHENA

#endif