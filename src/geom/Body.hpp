/*
 *================================================================================
 * Copyright (c) 2018 Ultra-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena body object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    22-Oct-2018     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_BODY_HPP
#define ATHENA_BODY_HPP

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
class Body
{
public:
    typedef enum
    {
        BodyType_none  = 0,
        BodyType_cubic = 1,
    } BodyType_t;

    Body();
    ~Body(){};

private:
    BodyType_t d_type;
};
}  // namespace ATHENA

#endif