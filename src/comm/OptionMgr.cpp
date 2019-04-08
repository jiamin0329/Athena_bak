/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena option manager
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *================================================================================
 */
/* Athena headers */
#include "OptionMgr.hpp"

/* c++ headers */
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>

/* External headers */
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

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
OptionMgr *OptionMgr::d_instance(nullptr);

OptionMgr *
OptionMgr::GetOptionMgr()
{
    if (!d_instance)
    {
        d_instance = new OptionMgr;
    }
    return d_instance;
}

OptionMgr::OptionMgr() : d_isInitialized(false), d_numOptions(0) {}

OptionMgr::~OptionMgr() {}

Status_t
OptionMgr::ReadOptionFile()
{
    static bool isDebug = false;
    Status_t    status  = Status_OK;

    if (isDebug)
        ATHENA_DEBUG(ATHENA_CONTROL_FILE);

    boost::property_tree::ptree pt, section;
    read_ini(ATHENA_CONTROL_FILE, pt);

    // loop all the sections in athena.ini
    for (boost::property_tree::ptree::iterator iter = pt.begin(); iter != pt.end(); iter++)
    {
        if (isDebug)
            ATHENA_DEBUG(iter->first);

        section = iter->second;
        // loop the current section
        for (boost::property_tree::ptree::iterator itemIter = section.begin(); itemIter != section.end(); itemIter++)
        {
            string  value  = section.get<string>(itemIter->first, "");
            Option *option = GetOption(itemIter->first);

            if (option != nullptr)
            {
                if (option->GetType() == OptionType_double)
                {
                    DoubleOption *currOption = dynamic_cast<DoubleOption *>(option);
                    currOption->SetValue(atof(value.c_str()));
                }
                else if (option->GetType() == OptionType_int)
                {
                    IntOption *currOption = dynamic_cast<IntOption *>(option);
                    currOption->SetValue(atoi(value.c_str()));
                }
                else if (option->GetType() == OptionType_string)
                {
                    StringOption *currOption = dynamic_cast<StringOption *>(option);
                    currOption->SetValue(value);
                }
            }
            else
            {
            }
        }
    }

    if (isDebug)
    {
        for (vector<Option *>::iterator iter = d_optionSet.begin(); iter != d_optionSet.end(); iter++)
        {
            ATHENA_DEBUG((*iter)->GetOptionName());
            if ((*iter)->GetType() == OptionType_double)
                ATHENA_DEBUG((dynamic_cast<DoubleOption *>(*iter))->GetValue());
            if ((*iter)->GetType() == OptionType_string)
                ATHENA_DEBUG((dynamic_cast<StringOption *>(*iter))->GetValue());
            if ((*iter)->GetType() == OptionType_int)
                ATHENA_DEBUG((dynamic_cast<IntOption *>(*iter))->GetValue());
        }
    }

    return status;
}

Option *
OptionMgr::GetOption(string optionName)
{
    Option *option = nullptr;

    for (vector<Option *>::iterator iter = d_optionSet.begin(); iter != d_optionSet.end(); iter++)
    {
        if ((*iter)->GetOptionName() == optionName)
        {
            option = *iter;
            break;
        }
    }
    return option;
}

void
OptionMgr::Initialize()
{
    Option::CreateOptionSet(d_optionSet);
    d_numOptions = d_optionSet.size();

    d_isInitialized = true;
}

string
OptionMgr::GetOptionString(int OptionIndex, bool &isFound)
{
    string value;
    isFound = false;
    for (vector<Option *>::iterator iter = d_optionSet.begin(); iter != d_optionSet.end(); iter++)
    {
        if ((*iter)->GetOptionIndex() == OptionIndex && (*iter)->GetType() == OptionType_string)
        {
            StringOption *option = dynamic_cast<StringOption *>(*iter);
            value                = option->GetValue();
            isFound              = true;
            return value;
        }
    }
    return value;
}

double
OptionMgr::GetOptionDouble(int OptionIndex, bool &isFound)
{
    double value = 0.0;
    isFound      = false;
    for (vector<Option *>::iterator iter = d_optionSet.begin(); iter != d_optionSet.end(); iter++)
    {
        if ((*iter)->GetOptionIndex() == OptionIndex && (*iter)->GetType() == OptionType_double)
        {
            DoubleOption *option = dynamic_cast<DoubleOption *>(*iter);
            value                = option->GetValue();
            isFound              = true;
            return value;
        }
    }
    return value;
}

int
OptionMgr::GetOptionInt(int OptionIndex, bool &isFound)
{
    int value = 0;
    isFound   = false;
    for (vector<Option *>::iterator iter = d_optionSet.begin(); iter != d_optionSet.end(); iter++)
    {
        if ((*iter)->GetOptionIndex() == OptionIndex && (*iter)->GetType() == OptionType_int)
        {
            IntOption *option = dynamic_cast<IntOption *>(*iter);
            value             = option->GetValue();
            isFound           = true;
            return value;
        }
    }
    return value;
}

}  // namespace ATHENA
