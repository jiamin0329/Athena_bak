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
#ifndef ATHENA_OPTION_HPP
#define ATHENA_OPTION_HPP

/* Athena headers */
#include "../Athena.hpp"
#include "OptionIndex.hpp"

/* c++ headers */
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
typedef enum
{
    OptionType_none   = 0,
    OptionType_int    = 1,
    OptionType_double = 2,
    OptionType_string = 3
} OptionType_t;

class Option
{
public:
    Option(string optName, int optionIndex);
    ~Option(){};

    static void CreateOptionSet(vector<Option *> &optionSet);

    string               GetOptionName() { return d_optionName; };
    int                  GetOptionIndex() { return d_optIndex; };
    virtual OptionType_t GetType() const = 0;

protected:
    string d_optionName;
    int    d_optIndex;
};

class DoubleOption : public Option
{
public:
    DoubleOption(string optName, int optionIndex, double defVal);
    DoubleOption(string optName, int optionIndex, double defVal, double val);
    ~DoubleOption(){};

    void                 SetValue(double value) { d_value = value; };
    double               GetValue() { return d_value; };
    virtual OptionType_t GetType() const { return OptionType_double; }

private:
    double d_defValue;
    double d_value;
};

class IntOption : public Option
{
public:
    IntOption(string optName, int optionIndex, int defVal);
    IntOption(string optName, int optionIndex, int defVal, int val);
    ~IntOption(){};

    void                 SetValue(int value) { d_value = value; };
    int                  GetValue() { return d_value; };
    virtual OptionType_t GetType() const { return OptionType_int; }

private:
    int d_defValue;
    int d_value;
};

class StringOption : public Option
{
public:
    StringOption(string optName, int optionIndex, string defVal);
    StringOption(string optName, int optionIndex, string defVal, string val);
    ~StringOption(){};

    void                 SetValue(string value) { d_value = value; };
    string               GetValue() { return d_value; };
    virtual OptionType_t GetType() const { return OptionType_string; }

private:
    string d_defValue;
    string d_value;
};

typedef Option *(*CreateOptionCallback)(int OptionIndex);

struct OptionCreator
{
    int                  optionIndex;
    CreateOptionCallback creatorCallback;
};

}  // namespace ATHENA

#endif