/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena processor data class
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_PROCDATA_HPP
#define ATHENA_PROCDATA_HPP

/* Athena headers */
#include "IProcData.hpp"

/* c++ headers */
#include <string>

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
class ProcData : public IProcData
{
public:
    ProcData();
    ~ProcData();

private:
};
}  // namespace ATHENA

#endif