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
 *    07-Apr-2019     Jiamin Xu               Add macros
 *    08-Apr-2019     Jiamin Xu               Update macros
 *    08-Apr-2019     Jiamin Xu               Add ATHENA_DEBUG
 *================================================================================
 */
#ifndef ATHENA_LOGGER_HPP
#define ATHENA_LOGGER_HPP

/* Athena headers */
#include "../Athena.hpp"

/* c++ headers */
#include <iostream>
#include <sstream>
#include <string>

/* External headers */
#include <glog/logging.h>

using namespace std;
/*
 *================================================================================
 *    Forward declarations
 *================================================================================
 */
#define ATHENA_DEBUG(X)                                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        std::ostringstream athenaos;                                                                                   \
        athenaos << X << std::ends;                                                                                    \
        ATHENA::Logger::GetLogger()->Log(                                                                              \
            __FILE__, __FUNCTION__, __LINE__, ATHENA::Logger::SeverityType_debug, athenaos.str());                     \
    } while (0)

#define ATHENA_INFO(X)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        std::ostringstream athenaos;                                                                                   \
        athenaos << X << std::ends;                                                                                    \
        ATHENA::Logger::GetLogger()->Log(                                                                              \
            __FILE__, __FUNCTION__, __LINE__, ATHENA::Logger::SeverityType_info, athenaos.str());                      \
    } while (0)

#define ATHENA_WARNING(X)                                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        std::ostringstream athenaos;                                                                                   \
        athenaos << X << std::ends;                                                                                    \
        ATHENA::Logger::GetLogger()->Log(                                                                              \
            __FILE__, __FUNCTION__, __LINE__, ATHENA::Logger::SeverityType_warning, athenaos.str());                   \
    } while (0)

#define ATHENA_ERROR(X)                                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        std::ostringstream athenaos;                                                                                   \
        athenaos << X << std::ends;                                                                                    \
        ATHENA::Logger::GetLogger()->Log(                                                                              \
            __FILE__, __FUNCTION__, __LINE__, ATHENA::Logger::SeverityType_error, athenaos.str());                     \
    } while (0)

#define ATHENA_FATAL(X)                                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        std::ostringstream athenaos;                                                                                   \
        athenaos << X << std::ends;                                                                                    \
        ATHENA::Logger::GetLogger()->Log(                                                                              \
            __FILE__, __FUNCTION__, __LINE__, ATHENA::Logger::SeverityType_fatal, athenaos.str());                     \
    } while (0)
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
        SeverityType_fatal   = 3,
        SeverityType_debug   = 4
    } SeverityType_t;

    static Logger *GetLogger();
    Logger();
    ~Logger();

    void StartupLogger(string workingDir, string filename);
    void ShutdownLogger();
    void Log(string filename, string function, int line, SeverityType_t severityType, string text);

private:
    static Logger *d_instance;     // ths
    string         d_logFilename;  // file
    string         d_outputDir;    // dir
};
}  // namespace ATHENA
#endif