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
 *    08-Apr-2019     Jiamin Xu               Refine Log()
 *================================================================================
 */

/* Athena headers */
#include "Logger.hpp"

/* c++ headers */
#include <cstddef>
#include <string>

/* External headers */

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
static bool isDebug = true;

Logger* Logger::d_instance(nullptr);

Logger*
Logger::GetLogger()
{
    if (!d_instance)
    {
        d_instance = new Logger;
    }
    return d_instance;
}

Logger::Logger() {}

Logger::~Logger() {}

void
Logger::StartupLogger(string workingDir, string filename)
{
    FLAGS_log_dir                   = workingDir + "/";
    FLAGS_log_prefix                = false;  // include the time and thread id
    FLAGS_logbufsecs                = 0;      // flush log to file frequency
    FLAGS_stop_logging_if_full_disk = true;   // if log is full stop write log
    FLAGS_colorlogtostderr          = true;

    google::InitGoogleLogging("Athena");
    LOG(INFO) << "Log file started!";
}

void
Logger::ShutdownLogger()
{
    google::ShutdownGoogleLogging();
}

void
Logger::Log(string filename, string function, int line, SeverityType_t severityType, string text)
{
    std::ostringstream output;
    output << "[" << filename.c_str() << ":" << function.c_str() << ":Line" << line << "] " << text.c_str()
           << std::ends;

    switch (severityType)
    {
    case SeverityType_info:
        LOG(INFO) << output.str().c_str();
        break;
    case SeverityType_warning:
        LOG(WARNING) << output.str().c_str();
        break;
    case SeverityType_error:
        LOG(ERROR) << output.str().c_str();
        break;
    case SeverityType_fatal:
        LOG(FATAL) << output.str().c_str();
        break;
    default:
        LOG(INFO) << output.str().c_str();
        break;
    }
}

}  // namespace ATHENA
