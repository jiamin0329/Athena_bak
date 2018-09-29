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

/* Athena headers */
#include "Logger.hpp"

/* c++ headers */
#include <cstddef>
#include <string>

/* External headers */
#include <glog/logging.h>

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
Logger *Logger::d_instance(nullptr);

Logger *
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
    FLAGS_log_dir = workingDir + "/";
    google::InitGoogleLogging(filename.c_str());
    LOG(INFO) << "Log file started!";
}

void
Logger::ShutdownLogger()
{
    google::ShutdownGoogleLogging();
}

void
Logger::Log(SeverityType_t severityType, string text)
{
    switch (severityType)
    {
    case SeverityType_info:
        LOG(INFO) << text;
    case SeverityType_warning:
        LOG(WARNING) << text;
    case SeverityType_error:
        LOG(ERROR) << text;
    case SeverityType_fatal:
        LOG(FATAL) << text;
    default:
        LOG(INFO) << text;
    }
}

}  // namespace ATHENA
