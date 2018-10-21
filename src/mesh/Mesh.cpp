/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena mesh object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *================================================================================
 */

/* Athena headers */
#include "Mesh.hpp"
#include "Athena.hpp"
#include "StrBlock.hpp"

/* c++ headers */

/* External headers */
#include "boost/filesystem.hpp"
#include "cgnslib.h"

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
Mesh::Mesh(string meshFile, string bocoFile) : d_meshFile(meshFile), d_bocoFile(bocoFile)
{
    d_name = meshFile;
}

Mesh::~Mesh() {}

MeshFileType_t
Mesh::GetMeshFileType() const
{
    MeshFileType_t          meshFileType = MeshFileType_none;
    boost::filesystem::path meshFile(d_meshFile);

    if (boost::filesystem::is_regular_file(meshFile))
    {
        if (meshFile.extension() == ".cgns")
            meshFileType = MeshFileType_cgns;
        else if (meshFile.extension() == ".grd")
            meshFileType = meshFileType_plt3d;
    }

    return meshFileType;
}

Status_t
Mesh::Process()
{
    static bool isDebug = true;
    Status_t    status  = Status_OK;

    if (this->GetMeshFileType() == MeshFileType_cgns)
    {
        int fileType;
        int iFile;         // File index
        int numBases = 0;  // Number of databases in cgns file

        status = (Status_t) cg_is_cgns(d_meshFile.c_str(), &fileType);

        if (status != CG_OK)
            return status;

        if (cg_open(d_meshFile.c_str(), CG_MODE_READ, &iFile))
        {
            cg_error_exit();
            return Status_ERROR;
        }

        // Get the number of databases. This is the highest node
        // in the CGNS heirarchy.
        if (cg_nbases(iFile, &numBases))
            cg_error_exit();

        // Only single database is supported in ATHENA
        if (numBases != 1)
            return Status_ERROR;

        // loop all the databases
        for (int iDataBase = 1; iDataBase <= numBases; ++iDataBase)
        {
            int  cellDim;
            int  physDim;
            char baseName[MAX_STRING_SIZE];

            if (cg_base_read(iFile, iDataBase, baseName, &cellDim, &physDim))
                cg_error_exit();

            d_cellDim = cellDim;
            d_physDim = physDim;

            if (isDebug)
            {
                DEBUG(baseName);
                DEBUG(cellDim);
                DEBUG(physDim);
            }

            int numZones;
            if (cg_nzones(iFile, iDataBase, &numZones))
                cg_error_exit();

            d_numZones = numZones;
            // loop all the zones
            for (int iZone = 1; iZone <= numZones; ++iZone)
            {
                int idim, jdim, kdim;
                CGNS_ENUMT(ZoneType_t)
                zoneType;
                if (cg_zone_type(iFile, iDataBase, iZone, &zoneType))
                    cg_error_exit();

                char     zoneName[MAX_STRING_SIZE];
                cgsize_t cgSize[3][3];

                if (cg_zone_read(iFile, iDataBase, iZone, zoneName, *cgSize))
                    cg_error_exit();

                // get number of nodes in 3 dimensions
                if (this->GetCellDim() == 2)
                {
                    idim = cgSize[0][0];
                    jdim = cgSize[0][1];
                    kdim = 1;
                }
                else if (this->GetCellDim() == 3)
                {
                    idim = cgSize[0][0];
                    jdim = cgSize[0][1];
                    kdim = cgSize[0][2];
                }

                // Create block for current zone
                IBlock *currBlk = new StrBlock(zoneName, idim, jdim, kdim);
                currBlk->SetDimType(this->GetCellDim() == 2 ? BlockDimType_2D : BlockDimType_3D);

                int numCoords;
                if (cg_ncoords(iFile, iDataBase, iZone, &numCoords))
                    cg_error_exit();

                // loop all the coords
                for (int iCoord = 1; iCoord <= numCoords; ++iCoord)
                {
                    char       coordName[500];
                    DataType_t dataType;
                    if (cg_coord_info(iFile, iDataBase, iZone, iCoord, &dataType, coordName))
                        cg_error_exit();

                    cgsize_t minRange[3], maxRange[3];

                    minRange[0] = (cgsize_t) 1;
                    minRange[1] = (cgsize_t) 1;
                    minRange[2] = (cgsize_t) 1;

                    maxRange[0] = idim;  // i-dim of nodes
                    maxRange[1] = jdim;  // j-dim of nodes
                    maxRange[2] = kdim;  // k-dim of nodes

                    // load x/y/z coords
                    double *val = new double[maxRange[0] * maxRange[1] * maxRange[2]];
                    if (cg_coord_read(iFile, iDataBase, iZone, coordName, dataType, minRange, maxRange, val))
                        cg_error_exit();

                    for (int k = 0; k <= maxRange[2] - 1; k++)
                        for (int j = 0; j <= maxRange[1] - 1; j++)
                            for (int i = 0; i <= maxRange[0] - 1; i++)
                            {
                                int index = k * maxRange[1] * maxRange[0] + j * maxRange[0] + i;
                                if (iCoord == 1)
                                    currBlk->AddCoordX(val[index]);
                                else if (iCoord == 2)
                                    currBlk->AddCoordY(val[index]);
                                else if (iCoord == 3)
                                    currBlk->AddCoordZ(val[index]);
                            }
                }  // end loop all the coords
                d_blockVec.push_back(currBlk);
            }  // end loop all the zones

            if (isDebug)
                DEBUG(d_blockVec.size());
        }  // end loop all the databases
    }
    return status;
}

}  // namespace ATHENA
