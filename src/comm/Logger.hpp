/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena logger object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_LOGGER_HPP
#define ATHENA_LOGGER_HPP

/* Athena headers */

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
class Logger
{
public:
    typedef enum
    {
        SeverityType_info    = 0,
        SeverityType_warning = 1,
        SeverityType_error   = 2,
        SeverityType_fatal   = 3
    } SeverityType_t;

    static Logger *GetLogger();
    Logger();
    ~Logger();

    void StartupLogger(string workingDir, string filename);
    void ShutdownLogger();
    void Log(SeverityType_t severityType, string text);

private:
    static Logger *d_instance;     // ths
    string         d_logFilename;  // file
    string         d_outputDir;    // dir
};
}  // namespace ATHENA

#endif