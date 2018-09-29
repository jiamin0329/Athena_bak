/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena option object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    28-Jul-2018     Jiamin Xu               Creation
 *================================================================================
 */

/* Athena headers */
#include "Option.hpp"

/* c++ headers */

using namespace ATHENA;
/*
 *================================================================================
 *    Forward declarations
 *================================================================================
 */
namespace
{
Option *
CreateAttackAngleOptionCB(int OptionIndex)
{
    Option *optionAttackAngle = new DoubleOption("Alpha", OptionIndex, 0.0);
    return optionAttackAngle;
}

Option *
CreateSlideAngleOptionCB(int OptionIndex)
{
    Option *optionSlideAngle = new DoubleOption("Beta", OptionIndex, 0.0);
    return optionSlideAngle;
}

Option *
CreateReynoldsNumberOptionCB(int OptionIndex)
{
    Option *optionRe = new DoubleOption("Reynolds", OptionIndex, 0.0);
    return optionRe;
}

Option *
CreateMachNumberOptionCB(int OptionIndex)
{
    Option *optionMa = new DoubleOption("Mach", OptionIndex, 0.0);
    return optionMa;
}

Option *
CreateTemperatureOptionCB(int OptionIndex)
{
    Option *optionTemperature = new DoubleOption("Temperature", OptionIndex, 0.0);
    return optionTemperature;
}
Option *
CreateMeshFileOptionCB(int OptionIndex)
{
    Option *optionMeshFile = new StringOption("MeshFile", OptionIndex, "");
    return optionMeshFile;
}

Option *
CreateBocoFileOptionCB(int OptionIndex)
{
    Option *optionBocoFile = new StringOption("BoundaryInfo", OptionIndex, "");
    return optionBocoFile;
}

typedef enum
{
    InviscidFluxType_none = 0,
    InviscidFluxType_roe  = 1
} InviscidFluxType_t;

Option *
CreateInviscidFluxOptionCB(int OptionIndex)
{
    Option *optionBocoFile = new StringOption("FluxMethod", OptionIndex, "none");
    return optionBocoFile;
}

Option *
CreateInviscidSchemeOptionCB(int OptionIndex)
{
    Option *optionBocoFile = new StringOption("InviscidScheme", OptionIndex, "none");
    return optionBocoFile;
}

Option *
CreateTurbulenceModelOptionCB(int OptionIndex)
{
    Option *optionBocoFile = new StringOption("TurbulenceModel", OptionIndex, "none");
    return optionBocoFile;
}

static OptionCreator optionTable[] = {{ATHENA_OPTION_INDEX_ATTACK_ANGLE, &CreateAttackAngleOptionCB},
                                      {ATHENA_OPTION_INDEX_SLIDE_ANGLE, &CreateSlideAngleOptionCB},
                                      {ATHENA_OPTION_INDEX_REYNOLDS_NUMBER, &CreateReynoldsNumberOptionCB},
                                      {ATHENA_OPTION_INDEX_MACH_NUMBER, &CreateMachNumberOptionCB},
                                      {ATHENA_OPTION_INDEX_TEMPERATURE, &CreateTemperatureOptionCB},

                                      {ATHENA_OPTION_INDEX_MESH_FILE, &CreateMeshFileOptionCB},
                                      {ATHENA_OPTION_INDEX_BOUNDARY_INFO_FILE, &CreateBocoFileOptionCB},

                                      {ATHENA_OPTION_INDEX_INVISCID_FLUX, &CreateInviscidFluxOptionCB},
                                      {ATHENA_OPTION_INDEX_INVISCID_SCHEME, &CreateInviscidSchemeOptionCB},
                                      {ATHENA_OPTION_INDEX_TURBULENCE_MODEL, &CreateTurbulenceModelOptionCB},

                                      {ATHENA_OPTION_INDEX_END, nullptr}};
}  // namespace

/*
 *================================================================================
 *    Class namespaces
 *================================================================================
 */
namespace ATHENA
{
Option::Option(string optName, int optionIndex) : d_optionName(optName), d_optIndex(optionIndex) {}

void
Option::CreateOptionSet(vector<Option *> &optionSet)
{
    static bool isDebug = true;
    int         i       = 0;
    while (optionTable[i].optionIndex != ATHENA_OPTION_INDEX_END)
    {
        Option *option = optionTable[i].creatorCallback(optionTable[i].optionIndex);
        optionSet.push_back(option);
        i++;
        if (isDebug)
            DEBUG(option->GetOptionName());
    }
}

DoubleOption::DoubleOption(string optName, int optionIndex, double defVal)
    : Option(optName, optionIndex), d_defValue(defVal), d_value(defVal)
{
}

DoubleOption::DoubleOption(string optName, int optionIndex, double defVal, double val)
    : Option(optName, optionIndex), d_defValue(defVal), d_value(val)
{
}

IntOption::IntOption(string optName, int optionIndex, int defVal)
    : Option(optName, optionIndex), d_defValue(defVal), d_value(defVal)
{
}

IntOption::IntOption(string optName, int optionIndex, int defVal, int val)
    : Option(optName, optionIndex), d_defValue(defVal), d_value(val)
{
}

StringOption::StringOption(string optName, int optionIndex, string defVal)
    : Option(optName, optionIndex), d_defValue(defVal), d_value(defVal)
{
}

StringOption::StringOption(string optName, int optionIndex, string defVal, string val)
    : Option(optName, optionIndex), d_defValue(defVal), d_value(val)
{
}

}  // namespace ATHENA
