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
#ifndef ATHENA_OPTIONMGR_HPP
#define ATHENA_OPTIONMGR_HPP

/* Athena headers */
#include "../Athena.hpp"
#include "Option.hpp"

/* c++ headers */
#include <map>
#include <string>
#include <vector>

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
class OptionMgr
{
public:
    static OptionMgr *GetOptionMgr();
    OptionMgr();
    ~OptionMgr();

    Status_t ReadOptionFile();
    void     Initialize();

    int GetNumOptions() const { return d_numOptions; };

    Option *GetOption(string optionName);

    string GetOptionString(int OptionIndex, bool &isFound);
    double GetOptionDouble(int OptionIndex, bool &isFound);
    int    GetOptionInt(int OptionIndex, bool &isFound);

private:
    static OptionMgr *d_instance;

    bool             d_isInitialized;
    vector<Option *> d_optionSet;
    int              d_numOptions;
};
}  // namespace ATHENA

#endif