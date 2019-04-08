/*
 *================================================================================
 * Copyright (c) 2019 Agi-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena unstructured grid zone object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    03-Apr-2019     Jiamin Xu               Creation
 *================================================================================
 */

/* Athena headers */
#include "ZoneUns.hpp"

#include "comm/Logger.hpp"
/* c++ headers */

/* External headers */

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
ZoneUns::ZoneUns(char*             zoneName,
                 IZone::ZoneType_t zoneType,
                 int               numVertices,
                 int               numCells,
                 int               numBoundaryVerts,
                 int               numCoords)
    : Zone(zoneName, zoneType, numCoords),
      d_numVertices(numVertices),
      d_numCells(numCells),
      d_numBoundaryVerts(numBoundaryVerts)
{
    ATHENA_DEBUG(d_numVertices);
    ATHENA_DEBUG(d_numCells);
    ATHENA_DEBUG(d_numBoundaryVerts);
    ATHENA_DEBUG(d_numCoords);

    for (int iVert = 0; iVert < d_numVertices; ++iVert)
    {
        Vertice* vertice = new Vertice;
        d_verticeContainer.push_back(vertice);
    }
}

ZoneUns::~ZoneUns()
{
    for (int iVert = 0; iVert < d_numVertices; ++iVert)
    {
        Vertice* vertice = d_verticeContainer[iVert];
        delete vertice;
    }
}

}  // namespace ATHENA
