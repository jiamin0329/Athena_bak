/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena mesh object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_MESH_HPP
#define ATHENA_MESH_HPP

/* Athena headers */
#include "IBlock.hpp"
#include "IMesh.hpp"

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
class Mesh : public IMesh
{
public:
    Mesh(string meshFile, string bocoFile);
    ~Mesh();
    virtual MeshType_t     GetMeshType() const { return d_type; };
    virtual MeshFileType_t GetMeshFileType() const;

    virtual Status_t Process();

    virtual string  GetName() const { return d_name; };
    virtual int     GetCellDim() const { return d_cellDim; };
    virtual int     GetPhysDim() const { return d_physDim; };
    virtual int     GetNumZones() const { return d_numZones; };
    virtual IBlock *GetBlock(int index) const { return d_blockVec[index]; };

    virtual vector<IBlock *> *GetBlockVector() { return &d_blockVec; };

private:
    string d_name;
    int    d_cellDim;
    int    d_physDim;

    int d_numZones;

    MeshType_t d_type;

    string d_meshFile;
    string d_bocoFile;

    vector<IBlock *> d_blockVec;
};
}  // namespace ATHENA

#endif