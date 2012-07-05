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

#include <string>

#include <ros/ros.h>
#include <uuid_msgs/UniqueID.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace unique_id
{

/** @brief Create UUID object from UniqueID message.
 *
 *  @param msg uuid_msgs/UniqueID message.
 *  @returns boost::uuids::uuid object.
 */
boost::uuids::uuid fromMsg(uuid_msgs::UniqueID const &msg)
{
  boost::uuids::uuid uu;
  std::copy(msg.uuid.begin(), msg.uuid.end(), uu.begin());
  return uu;
}

/** @brief Generate a random UUID object.
 *
 *  @returns type 4 boost::uuids::uuid` object.
 */
boost::uuids::uuid fromRandom(void)
{
  static boost::uuids::random_generator rand;
  return rand();
}

/** @brief Generate UUID from Uniform Resource Locator.
 *
 *  @param url URL for identifier creation.
 *  @returns type 5 boost::uuids::uuid` object.
 *
 *  Matching @a url strings must yield the same UUID. Different @a url
 *  strings will almost certainly generate different UUIDs. The method
 *  used is `RFC 4122`_ variant 5, computing the SHA-1 hash of the @a
 *  url.
 *
 *  For example, Open Street Map identifiers are encoded like this:
 *
 *    fromURL("http://openstreetmap.org/node/" + str(node_id))
 *    fromURL("http://openstreetmap.org/way/" + str(way_id))
 *    fromURL("http://openstreetmap.org/relation/" + str(rel_id))
 *
 *  Decimal representations of the integer OSM node, way, or relation
 *  identifiers are appended to the URL.
 */
boost::uuids::uuid fromURL(std::string const &url)
{
  // initialize to {6ba7b810-9dad-11d1-80b4-00c04fd430c8}?
  static boost::uuids::uuid url_namespace_uuid;
  static boost::uuids::name_generator gen(url_namespace_uuid);
  return gen(url);
}

/** @brief Create a UniqueID message from a UUID object.
 *
 *  @param uu boost::uuids::uuid object.
 *  @returns uuid_msgs/UniqueID message.
 */
uuid_msgs::UniqueID toMsg(boost::uuids::uuid const &uu)
{
  uuid_msgs::UniqueID msg;
  std::copy(uu.begin(), uu.end(), msg.uuid.begin());
  return msg;
}

/** @brief Create the canonical string representation for a UniqueID message.
 *
 *  @param msg uuid_msgs/UniqueID message.
 *  @returns canonical UUID hex string: '01234567-89ab-cdef-0123-456789abcdef'.
 *
 *  A @c boost::uuids::uuid object yields the same representation via
 *  its @c << operator or @c to_string() function.
 */
std::string toString(uuid_msgs::UniqueID const &msg)
{
  return boost::uuids::to_string(fromMsg(msg));
}

} // end namespace unique_id

#endif // _UNIQUE_ID_H_
