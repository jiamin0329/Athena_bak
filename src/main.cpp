/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Main entrance for Athena
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *================================================================================
 */
/* Athena headers */
#include "Athena.hpp"
#include "IMesh.hpp"
#include "IOutputMgr.hpp"
#include "Logger.hpp"
#include "Mesh.hpp"
#include "OptionMgr.hpp"
#include "OutputMgr.hpp"

/* c++ headers */
#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/* External headers */
#include "boost/filesystem.hpp"

using namespace std;
/*
 *================================================================================
 *    Forward declarations
 *================================================================================
 */
namespace
{
void
PrintAthenaHeader()
{
    cout << "************************************************************" << endl;
    cout << "* Welcome to Athena                                        *" << endl;
    cout << "************************************************************" << endl;
}
}  // namespace

/*
 *================================================================================
 *    Main function
 *================================================================================
 */
int
main(int argc, char *argv[])
{
    static bool isDebug = true;

    PrintAthenaHeader();
    // Check the command line input.
    std::string userDefinedDir;
    if (argc < 2)
    {
        cerr << "ATHENA ERROR: No input file specified ... " << endl;
        return -1;
    }
    else
    {
        userDefinedDir = argv[1];
    }
    static const std::string workingDir = userDefinedDir;

    // Check if working dir exists
    boost::filesystem::path workingDirPath(workingDir);
    if (!(boost::filesystem::exists(workingDirPath) && boost::filesystem::is_directory(workingDirPath)))
    {
        cerr << "ATHENA ERROR: working dir does not exist." << endl;
        return -1;
    }

    // Go to the working dir
    boost::filesystem::current_path(workingDirPath);
    if (isDebug)
    {
        boost::filesystem::path currPath = boost::filesystem::current_path();
        DEBUG(currPath);
    }

    // Setup logger
    // Given it is already switched into working directory, log file
    // will be created in current directory.
    ATHENA::Logger *logger = ATHENA::Logger::GetLogger();
    logger->StartupLogger("./", ATHENA_LOG_FILE);

    // Setup option manager
    ATHENA::OptionMgr *optMgr = ATHENA::OptionMgr::GetOptionMgr();
    optMgr->Initialize();
    optMgr->ReadOptionFile();

    // ProcData* procData = new ProcData(optMgr);
    // ISolver* solver = SolverFactory::CreateSolver();

    bool isMeshFileDefined = false;
    bool isBocoFileDefined = false;

    string meshFile = optMgr->GetOptionString(ATHENA_OPTION_INDEX_MESH_FILE, isMeshFileDefined);
    string bocoFile = optMgr->GetOptionString(ATHENA_OPTION_INDEX_BOUNDARY_INFO_FILE, isBocoFileDefined);

    ATHENA::IMesh *mesh = new ATHENA::Mesh(meshFile, bocoFile);
    mesh->Process();

    vector<ATHENA::IBlock *> *blockVec = mesh->GetBlockVector();
    for (auto blkIter : *blockVec)
    {
        blkIter->GridTransformation();
    }

    ATHENA::IOutputMgr *outputMgr = new ATHENA::OutputMgr();
    outputMgr->OutputDomain(mesh);

    return 0;
}
