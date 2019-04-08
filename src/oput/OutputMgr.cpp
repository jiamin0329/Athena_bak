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
/* Athena headers */
#include "OutputMgr.hpp"
#include "AVector.hpp"
#include "mesh/IBlock.hpp"
#include "mesh/IMesh.hpp"

/* c++ headers */
#include <sstream>

/* External headers */
#include "boost/filesystem.hpp"
#include "cgnslib.h"

using namespace std;
/*
 *================================================================================
 *    Forward declarations
 *================================================================================
 */
namespace
{
string
GetZoneName(int iZone)
{
    string zoneName = "zone ";

    stringstream stream;
    stream << iZone;
    string zoneId = stream.str();
    zoneName.append(zoneId);
    return zoneName;
}
}  // namespace

/*
 *================================================================================
 *    Class namespaces
 *================================================================================
 */
namespace ATHENA
{
OutputMgr::OutputMgr() {}

OutputMgr::~OutputMgr() {}

void
OutputMgr::OutputDomain(IMesh *mesh) const
{
    static bool isDebug  = true;
    string      filename = "debug.cgns";
    int         iFile    = 1;
    /* open CGNS file for write */
    if (cg_open(filename.c_str(), CG_MODE_WRITE, &iFile))
        cg_error_exit();

    int    iDataBase = 1;
    int    cellDim   = mesh->GetCellDim();
    int    physDim   = mesh->GetPhysDim();
    string baseName  = mesh->GetName();

    ATHENA_DEBUG(cellDim);
    ATHENA_DEBUG(physDim);
    // Write database info into cgns file
    cg_base_write(iFile, baseName.c_str(), cellDim, physDim, &iDataBase);

    // Write zones into cgns file
    int numZones = mesh->GetNumZones();

    int index;
    for (int iZone = 1; iZone <= numZones; ++iZone)
    {
        // define zone name (user can give any name)
        IBlock *currBlock = mesh->GetBlock(iZone - 1);
        string  zoneName  = currBlock->GetName();

        cgsize_t cgSize[3][3];
        if (cellDim == 2)
        {
            // vertex size
            cgSize[0][0] = currBlock->GetIDim();
            cgSize[0][1] = currBlock->GetJDim();
            cgSize[0][2] = cgSize[0][0] - 1;
            cgSize[1][0] = cgSize[0][1] - 1;
            cgSize[1][1] = 0;
            cgSize[1][2] = 0;
            cgSize[2][0] = 0;
            cgSize[2][1] = 0;
            cgSize[2][2] = 0;
        }
        else if (cellDim == 3)
        {
            // vertex size
            cgSize[0][0] = currBlock->GetIDim();
            cgSize[0][1] = currBlock->GetJDim();
            cgSize[0][2] = currBlock->GetKDim();
            // cell size
            cgSize[1][0] = cgSize[0][0] - 1;
            cgSize[1][1] = cgSize[0][1] - 1;
            cgSize[1][2] = cgSize[0][2] - 1;
            // boundary vertex size (always zero for structured grids)
            cgSize[2][0] = 0;
            cgSize[2][1] = 0;
            cgSize[2][2] = 0;
        }

        // create zone
        if (cg_zone_write(iFile, iDataBase, zoneName.c_str(), *cgSize, CGNS_ENUMV(Structured), &index))
            cg_error_exit();

        int idim = currBlock->GetIDim();
        int jdim = currBlock->GetJDim();
        int kdim = currBlock->GetKDim();

        int     numNodes = currBlock->GetNumNodes();
        double *valx     = new double[numNodes];
        double *valy     = new double[numNodes];
        double *valz     = new double[numNodes];

        for (int k = 0; k < kdim; ++k)
            for (int j = 0; j < jdim; ++j)
                for (int i = 0; i < idim; ++i)
                {
                    int ind   = k * jdim * idim + j * idim + i;
                    valx[ind] = currBlock->GetCoordX(ind);
                    valy[ind] = currBlock->GetCoordY(ind);
                    valz[ind] = currBlock->GetCoordZ(ind);
                }

        // write grid coordinates (user must use SIDS-standard names here) */
        int iCoordBuffer;
        if (cg_coord_write(iFile, iDataBase, iZone, CGNS_ENUMV(RealDouble), "Coordinate X", valx, &iCoordBuffer))
            cg_error_exit();
        if (cg_coord_write(iFile, iDataBase, iZone, CGNS_ENUMV(RealDouble), "Coordinate Y", valy, &iCoordBuffer))
            cg_error_exit();
        if (cg_coord_write(iFile, iDataBase, iZone, CGNS_ENUMV(RealDouble), "Coordinate Z", valz, &iCoordBuffer))
            cg_error_exit();

        delete[] valx;
        delete[] valy;
        delete[] valz;

        ATHENA_DEBUG("start === output geom info")
        char solname[33];
        int  iFlow, iField;

        double *volume = new double[numNodes];

        if (cellDim == 2)
        {
            for (int j = 0; j < jdim - 1; ++j)
                for (int i = 0; i < idim - 1; ++i)
                {
                    int ind     = j * (idim - 1) + i;
                    volume[ind] = currBlock->GetVolume(ind);
                }
        }
        else if (cellDim == 3)
        {
            for (int k = 0; k < kdim - 1; ++k)
                for (int j = 0; j < jdim - 1; ++j)
                    for (int i = 0; i < idim - 1; ++i)
                    {
                        int ind     = k * (jdim - 1) * (idim - 1) + j * (idim - 1) + i;
                        volume[ind] = currBlock->GetVolume(ind);
                    }
        }

        /* define flow solution node name (user can give any name) */
        strcpy(solname, "GeomInfo1");
        /* create flow solution node (NOTE USE OF CGNS_ENUMV(CellCenter) HERE) */
        cg_sol_write(iFile, iDataBase, iZone, solname, CGNS_ENUMV(CellCenter), &iFlow);
        /* write flow solution (user must use SIDS-standard names here) */
        cg_field_write(iFile, iDataBase, iZone, iFlow, CGNS_ENUMV(RealDouble), "Volume", volume, &iField);

        double *nix = new double[numNodes];
        double *niy = new double[numNodes];

        if (cellDim == 2)
        {
            for (int j = 0; j < jdim; ++j)
                for (int i = 0; i < idim; ++i)
                {
                    int ind = j * idim + i;

                    AVector surfNormal = currBlock->GetISurfNormal(ind);

                    nix[ind] = surfNormal[0];
                    niy[ind] = surfNormal[1];
                }
        }

        /* define flow solution node name (user can give any name) */
        strcpy(solname, "GeomInfo2");
        /* create flow solution node (NOTE USE OF CGNS_ENUMV(CellCenter) HERE) */
        cg_sol_write(iFile, iDataBase, iZone, solname, CGNS_ENUMV(Vertex), &iFlow);
        /* write flow solution (user must use SIDS-standard names here) */
        cg_field_write(iFile, iDataBase, iZone, iFlow, CGNS_ENUMV(RealDouble), "nix", nix, &iField);
        cg_field_write(iFile, iDataBase, iZone, iFlow, CGNS_ENUMV(RealDouble), "niy", niy, &iField);

        delete[] nix, niy;
        delete[] volume;
        ATHENA_DEBUG("end === output geom info")
    }

    ATHENA_DEBUG("successed!");
    /* close CGNS file */
    cg_close(iFile);
}
}  // namespace ATHENA
