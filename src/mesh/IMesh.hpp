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