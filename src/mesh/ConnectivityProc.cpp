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

/* Athena headers */
#include "ConnectivityProc.hpp"

#include "IMesh.hpp"
#include "IBlock.hpp"

/* c++ headers */
#include <fstream>
#include <iostream>

using namespace std;
/*
 *================================================================================
 *    Forward declarations
 *================================================================================
 */
namespace
{
int
Compare()
{
    int flag = 0;

    return flag;
}

void
FindSubfaceBoundary()
{
}

void
FindConerPoint()
{
}
}  // namespace

/*
 *================================================================================
 *    Class namespaces
 *================================================================================
 */
namespace ATHENA
{
ConnectivityProc::ConnectivityProc(IMesh* mesh) : d_mesh(mesh)
{
    d_isInitialized = false;
}

void
ConnectivityProc::Initialize()
{
    d_numSplit   = 7;
    d_maxLinks   = 50;   // could be deleted later
    d_maxSubface = 100;  // could be deleted later

    // setup points/faces
    vector<IBlock*>* blockVec = d_mesh->GetBlockVector();
    for (auto iter = blockVec->begin(); iter != blockVec->end(); iter++)
    {
    }
}

void
ConnectivityProc::SearchConnectivity()
{

    // Mark inner vertices

    // Create subfaces
}

void
ConnectivityProc::WriteBCInfo()
{
    std::ofstream output("bcinfo.in", std::ios::out);
    if (!output)
    {
        std::cerr << "Open output file error!" << std::endl;
        exit(-1);
    }
    output << "***************************************************************************" << std::endl;
    output << "This is a block connectivity info file.                                    " << std::endl;
    output << "This file is generated automatically by Athena, DO NOT do any modification." << std::endl;
    output << "***************************************************************************" << std::endl;

    output.close();
}

}  // namespace ATHENA