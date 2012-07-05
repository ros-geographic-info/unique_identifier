/* -*- mode: C++ -*- */
/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (C) 2011 Jack O'Quin
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the author nor other contributors may be
*     used to endorse or promote products derived from this software
*     without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

#ifndef _UNIQUE_ID_H_
#define _UNIQUE_ID_H_ 1

/** @file

    @brief Generate universally unique identifiers and messages.

    Various ROS components use universally unique identifiers. This
    header provides functions for working with a common @c
    uuid_msgs/UniqueID message, and the @c boost::uuid class.

    Programmers are free to create UUID objects using any approved RFC
    4122 method. The boost uuid module supports them all.

    Many ROS applications need either a random (@c fromRandom()) or a
    name-based UUID. The @c fromURL() function generates a name-based
    UUID from a URL string.

    @author Jack O'Quin
 */

#include <ros/ros.h>
#include <uuid_msgs/UniqueID.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace unique_id
{

boost::uuids::uuid fromRandom(void)
{
  static boost::uuids::random_generator rand;
  return rand();
}

} // end namespace unique_id

#endif // _UNIQUE_ID_H_
