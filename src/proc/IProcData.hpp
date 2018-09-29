/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Interface for processor data
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_IPROCDATA_HPP
#define ATHENA_IPROCDATA_HPP

/* Athena headers */

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
class IProcData
{
public:
    virtual ~IProcData(){};

protected:
    explicit IProcData(){};
};
}  // namespace ATHENA

#endif