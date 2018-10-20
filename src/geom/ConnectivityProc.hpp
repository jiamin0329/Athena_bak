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
#include "Face.hpp"
#include "Point.hpp"

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
class ConnPoint : public Point
{
public:
    ConnPoint();
    ~ConnPoint(){};

private:
    bool d_isInner;
    bool d_isSearched;
    int  d_color;

    vector<int> d_linkedBlock;
    vector<int> d_linkedFace;
    vector<int> d_linkedVertice;
};

class ConnFace : public Face
{
public:
    ConnFace();
    ~ConnFace(){};

private:
    double d_radius;
    Point  d_centroid;
};

class ConnectivityProc
{
public:
    ConnectivityProc();
    ~ConnectivityProc(){};

    void Initialize();
    void SearchConnectivity();
    void WriteBCInfo();

private:
    bool d_isInitialized;
    int  d_numSplit;

    int d_maxLinks;
    int d_maxSubface;

    vector<IBlock*> d_blockVec;
};
}  // namespace ATHENA

#endif