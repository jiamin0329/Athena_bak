/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena output manager class
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_OUTPUTMGR_HPP
#define ATHENA_OUTPUTMGR_HPP

/* Athena headers */
#include "IOutputMgr.hpp"

/* c++ headers */

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
class OutputMgr : public IOutputMgr
{
public:
    OutputMgr();
    ~OutputMgr();

    virtual void OutputDomain(IMesh* mesh) const;

private:
    OutputFileType_t d_outputFileType;
};
}  // namespace ATHENA

#endif
