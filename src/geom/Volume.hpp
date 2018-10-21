/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena Volume object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    22-Oct-2018     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_VOLUME_HPP
#define ATHENA_VOLUME_HPP

/* Athena headers */

/* c++ headers */

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
class Volume
{
public:
    typedef enum
    {
        VolumeType_none  = 0,
        VolumeType_cubic = 1,
    } VolumeType_t;

    Volume();
    ~Volume(){};

private:
    VolumeType_t d_type;
};
}  // namespace ATHENA

#endif