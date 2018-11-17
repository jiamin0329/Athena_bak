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
 *    22-Aug-2018     Jiamin Xu               Calculate ni/nj for 2D cases
 *================================================================================
 */
/* Athena headers */
#include "StrBlock.hpp"
#include "AVector.hpp"
#include "Athena.hpp"

/* c++ headers */
#include <cmath>

using namespace std;

#define NEGATIVE_VOLUME 1.0e-16
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
StrBlock::StrBlock() {}

StrBlock::StrBlock(char *name, int idimNode, int jdimNode, int kdimNode)
    : d_idimNode(idimNode), d_jdimNode(jdimNode), d_kdimNode(kdimNode), d_numNodes(idimNode * jdimNode * kdimNode)
{
    d_name     = name;
    d_idimCell = d_idimNode - 1;
    d_jdimCell = d_jdimNode - 1;
    d_kdimCell = d_kdimNode - 1;
    d_numCells = d_idimCell * d_jdimCell * d_kdimCell;
}

StrBlock::~StrBlock() {}

void
StrBlock::Initialize()
{



    
}

void
StrBlock::GridTransformation()
{
    double volume = 0.0;
    double maxVol = 0.0;
    double minVol = 1.0e10;
    if (this->IsDimType2D())
    {
        for (int j = 0; j < d_jdimNode - 1; ++j)
            for (int i = 0; i < d_idimNode - 1; ++i)
            {
                int index         = j * d_idimNode + i;
                int index_ip1     = j * d_idimNode + i + 1;
                int index_jp1     = (j + 1) * d_idimNode + i;
                int index_ip1_jp1 = (j + 1) * d_idimNode + i + 1;

                double x1 = this->GetCoordX(index);
                double x2 = this->GetCoordX(index_ip1);
                double x3 = this->GetCoordX(index_ip1_jp1);
                double x4 = this->GetCoordX(index_jp1);

                double y1 = this->GetCoordY(index);
                double y2 = this->GetCoordY(index_ip1);
                double y3 = this->GetCoordY(index_ip1_jp1);
                double y4 = this->GetCoordY(index_jp1);

                volume = abs((x1 - x3) * (y2 - y4) - (x2 - x4) * (y1 - y3)) * 0.50;
                d_volume.push_back(volume);
            }

        for (int j = 0; j < d_jdimNode; ++j)
            for (int i = 0; i < d_idimNode; ++i)
            {
                if (i < d_idimNode - 1)
                {
                    int index     = j * d_idimNode + i;
                    int index_ip1 = j * d_idimNode + i + 1;

                    double x1 = this->GetCoordX(index);
                    double x2 = this->GetCoordX(index_ip1);

                    double y1 = this->GetCoordY(index);
                    double y2 = this->GetCoordY(index_ip1);

                    AVector vec(y2 - y1, x1 - x2);
                    vec.Normalize();
                    d_ni.push_back(vec);
                }
                else
                {
                    AVector vec(0.0, 0.0);
                    d_ni.push_back(vec);
                }
            }

        for (int j = 0; j < d_jdimNode; ++j)
            for (int i = 0; i < d_idimNode; ++i)
            {
                if (j < d_jdimNode - 1)
                {
                    int index     = j * d_idimNode + i;
                    int index_jp1 = (j + 1) * d_idimNode + i;

                    double x1 = this->GetCoordX(index);
                    double x2 = this->GetCoordX(index_jp1);

                    double y1 = this->GetCoordY(index);
                    double y2 = this->GetCoordY(index_jp1);

                    AVector vec(y1 - y2, x2 - x1);
                    vec.Normalize();
                    d_nj.push_back(vec);
                }
                else
                {
                    AVector vec(0.0, 0.0);
                    d_nj.push_back(vec);
                }
            }
    }
    else if (this->IsDimType3D())
    {
        for (int k = 0; k < d_kdimCell; ++k)
            for (int j = 0; j < d_jdimCell; ++j)
                for (int i = 0; i < d_idimCell; ++i)
                {
                    volume = 0.0;
                    for (int iFace = 1; iFace < 6; ++iFace)
                    {
                        double x1, x2, x3, x4;
                        double y1, y2, y3, y4;
                        double z1, z2, z3, z4;

                        // if (iFace == 0)
                        // else if (iFace == 1)
                        // else if (iFace == 1)

                        double sx, sy, sz;
                        double rx, ry, rz;

                        double vec1[3], vec2[3];
                        vec1[0] = x3 - x1;
                        vec1[1] = y3 - y1;
                        vec1[2] = z3 - z1;

                        vec2[0] = x4 - x2;
                        vec2[1] = y4 - y2;
                        vec2[2] = z4 - z2;

                        sx = 0.50 * (vec1[1] * vec2[2] - vec1[2] * vec2[1]);
                        sy = 0.50 * (vec1[2] * vec2[0] - vec1[0] * vec2[2]);
                        sz = 0.50 * (vec1[0] * vec2[1] - vec1[1] * vec2[0]);

                        rx = 0.25 * (x1 + x2 + x3 + x4);
                        ry = 0.25 * (y1 + y2 + y3 + y4);
                        rz = 0.25 * (z1 + z2 + z3 + z4);

                        volume = volume + (sx * rx + sy * ry + sz * rz) / 3.0;
                    }

                    // Check negative volume
                    if (volume < NEGATIVE_VOLUME)
                        cout << "negative volume found !" << endl;

                    if (volume > maxVol)
                        maxVol = volume;
                    if (volume < minVol)
                        minVol = volume;

                    d_volume.push_back(volume);
                }
    }
}

}  // namespace ATHENA
