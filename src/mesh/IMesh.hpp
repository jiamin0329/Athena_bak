/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Interface for mesh class
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *    09-Apr-2019     Jiamin Xu               Add more macro definitions
 *================================================================================
 */
#ifndef ATHENA_IMESH_HPP
#define ATHENA_IMESH_HPP

/* Athena headers */
#include "../Athena.hpp"

/* c++ headers */
#include <vector>

using namespace std;

/*
 *================================================================================
 *    Forward declarations
 *================================================================================
 */
#define VTK_TYPE_VERTEX 1        // VTK nomenclature for defining a vertex element.
#define VTK_TYPE_LINE 3          // VTK nomenclature for defining a line element.
#define VTK_TYPE_TRIANGLE 5      // VTK nomenclature for defining a triangle element.
#define VTK_TYPE_RECTANGLE 9     // VTK nomenclature for defining a rectangle element.
#define VTK_TYPE_TETRAHEDRON 10  // VTK nomenclature for defining a tetrahedron element.
#define VTK_TYPE_HEXAHEDRON 12   // VTK nomenclature for defining a hexahedron element.
#define VTK_TYPE_PRISM 13        // VTK nomenclature for defining a prism element.
#define VTK_TYPE_PYRAMID 14      // VTK nomenclature for defining a pyramid element.

#define NUM_ELEM_TYPES 7

#define NUM_VERTICES_LINE 2
#define NUM_VERTICES_TRIANGLE 3
#define NUM_VERTICES_QUADRILATERAL 4
#define NUM_VERTICES_TETRAHEDRON 4
#define NUM_VERTICES_HEXAHEDRON 8
#define NUM_VERTICES_PYRAMID 5
#define NUM_VERTICES_PRISM 6

namespace ATHENA
{
class IBlock;
}
/*
 *================================================================================
 *    Class namespaces
 *================================================================================
 */
namespace ATHENA
{
typedef enum
{
    MeshType_none         = 0,
    MeshType_structured   = 1,
    MeshType_unstructured = 2
} MeshType_t;

typedef enum
{
    MeshFileType_none  = 0,
    MeshFileType_cgns  = 1,
    meshFileType_plt3d = 2
} MeshFileType_t;



class IMesh
{
public:
    virtual ~IMesh(){};
    virtual MeshType_t     GetMeshType() const     = 0;
    virtual MeshFileType_t GetMeshFileType() const = 0;

    virtual string GetName() const = 0;

    virtual int GetCellDim() const = 0;
    virtual int GetPhysDim() const = 0;

    virtual int GetNumZones() const = 0;

    virtual IBlock *GetBlock(int index) const = 0;

    virtual Status_t Process() = 0;

    virtual vector<IBlock *> *GetBlockVector() = 0;

protected:
    explicit IMesh(){};
};
}  // namespace ATHENA

#endif