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

/* c++ headers */
#include <fstream>
#include <iostream>

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

ConnPoint::ConnPoint() : d_isInner(false), d_isSearched(false), d_color(0) {}

ConnFace::ConnFace() {}

ConnectivityProc::ConnectivityProc()
{
    d_isInitialized = false;
}

void
ConnectivityProc::Initialize()
{
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

    for (auto iter = d_blockVec.begin(); iter != d_blockVec.end(); iter++)
    {

    }

    output.close();
}

}  // namespace ATHENA