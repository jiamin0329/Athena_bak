/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena connectivity proceoosr
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    17-Oct-2018     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_CONNECTIVITYPROC_HPP
#define ATHENA_CONNECTIVITYPROC_HPP

/* Athena headers */
#include "IBlock.hpp"

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
class IMesh;
}

/*
 *================================================================================
 *    Class namespaces
 *================================================================================
 */
namespace ATHENA
{
class ConnectivityProc
{
public:
    ConnectivityProc(IMesh* mesh);
    ~ConnectivityProc(){};

    void Initialize();
    void SearchConnectivity();
    void WriteBCInfo();

private:
    IMesh* d_mesh;

    bool d_isInitialized;
    int  d_numSplit;

    int d_maxLinks;
    int d_maxSubface;
};
}  // namespace ATHENA

#endif