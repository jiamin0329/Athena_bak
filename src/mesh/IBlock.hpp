/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Interface for block class
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_IBLOCK_HPP
#define ATHENA_IBLOCK_HPP

/* Athena headers */

/* c++ headers */
#include <string>

using namespace std;
/*
 *================================================================================
 *    Forward declarations
 *================================================================================
 */
namespace ATHENA
{
class AVector;
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
    BlockDimType_none = 0,
    BlockDimType_2D   = 1,
    BlockDimType_3D   = 2
} BlockDimType_t;

class IBlock
{
public:
    virtual ~IBlock(){};

    virtual void AddCoordX(double val) = 0;
    virtual void AddCoordY(double val) = 0;
    virtual void AddCoordZ(double val) = 0;

    virtual double GetCoordX(int index) const = 0;
    virtual double GetCoordY(int index) const = 0;
    virtual double GetCoordZ(int index) const = 0;

    virtual void SetDimType(BlockDimType_t dimType) = 0;

    virtual bool IsDimType2D() const = 0;
    virtual bool IsDimType3D() const = 0;

    virtual string GetName() const = 0;

    virtual int GetIDim() const = 0;
    virtual int GetJDim() const = 0;
    virtual int GetKDim() const = 0;

    virtual int GetNumNodes() const = 0;

    virtual void GridTransformation() = 0;

    virtual double GetVolume(int index) const = 0;

    virtual AVector GetISurfNormal(int index) const = 0;
    virtual AVector GetJSurfNormal(int index) const = 0;
    virtual AVector GetKSurfNormal(int index) const = 0;

protected:
    explicit IBlock(){};
};
}  // namespace ATHENA

#endif
