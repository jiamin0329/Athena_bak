/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Interface for output manager
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_IOUTPUTMGR_HPP
#define ATHENA_IOUTPUTMGR_HPP

/* Athena headers */

/* c++ headers */
#include <string>

/*
 *================================================================================
 *    Forward declarations
 *================================================================================
 */
namespace ATHENA
{
class IMesh;
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
    OutputFileType_none = 0,
    OutputFileType_cgns = 1
} OutputFileType_t;

class IOutputMgr
{
public:
    virtual ~IOutputMgr(){};
    virtual void OutputDomain(IMesh *mesh) const = 0;

protected:
    explicit IOutputMgr(){};
};
}  // namespace ATHENA

#endif
