/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena structured block class
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *    22-Aug-2018     Jiamin Xu               Add d_ni, d_nj, d_nk
 *================================================================================
 */
#ifndef ATHENA_STRBLOCK_HPP
#define ATHENA_STRBLOCK_HPP

/* Athena headers */
#include "AVector.hpp"
#include "IBlock.hpp"

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
class StrBlock : public IBlock
{
public:
    StrBlock();
    StrBlock(char *name, int idimNode, int jdimNode, int kdimNode);
    ~StrBlock();

    void AddCoordX(double val) { d_coordX.push_back(val); }
    void AddCoordY(double val) { d_coordY.push_back(val); }
    void AddCoordZ(double val) { d_coordZ.push_back(val); }

    double GetCoordX(int index) const { return d_coordX[index]; }
    double GetCoordY(int index) const { return d_coordY[index]; }
    double GetCoordZ(int index) const { return d_coordZ[index]; }

    // void AddBoco(IBoco* boco) { d_bocoList.push_back(boco); }

    virtual void GridTransformation();

    virtual void SetDimType(BlockDimType_t dimType) { d_dimType = dimType; };
    virtual bool IsDimType2D() const { return d_dimType == BlockDimType_2D; };
    virtual bool IsDimType3D() const { return d_dimType == BlockDimType_3D; };

    virtual string GetName() const { return d_name; };
    virtual int    GetIDim() const { return d_idimNode; };
    virtual int    GetJDim() const { return d_jdimNode; };
    virtual int    GetKDim() const { return d_kdimNode; };
    virtual int    GetNumNodes() const { return d_numNodes; };

    virtual double GetVolume(int index) const { return d_volume[index]; }

    virtual AVector GetISurfNormal(int index) const { return d_ni[index]; };
    virtual AVector GetJSurfNormal(int index) const { return d_nj[index]; };
    virtual AVector GetKSurfNormal(int index) const { return d_nk[index]; };

private:
    BlockDimType_t d_dimType;
    string         d_name;

    int d_numNodes;
    int d_numCells;
    int d_idimNode, d_jdimNode, d_kdimNode;
    int d_idimCell, d_jdimCell, d_kdimCell;

    // vector<Cell*> d_cells;

    vector<double> d_coordX;
    vector<double> d_coordY;
    vector<double> d_coordZ;

    vector<double>  d_volume;
    vector<AVector> d_ni;
    vector<AVector> d_nj;
    vector<AVector> d_nk;
};
}  // namespace ATHENA
#endif
