# Software License Agreement (BSD License)
#
# Copyright (C) 2012, Jack O'Quin
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of the author nor of other contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

"""
.. module:: unique_id

Generate universally unique identifiers and messages.

Various ROS components use universally unique identifiers
(UUID_). This module provides functions for working with a common
`uuid_msgs/UniqueID`_ message definition, with a thin ROS
wrapper using the standard Python :py:class:`uuid.UUID` class.

.. _`uuid_msgs/UniqueID`: http://ros.org/doc/api/uuid_msgs/html/msg/UniqueID.html
.. _`RFC 4122`: http://tools.ietf.org/html/rfc4122.html
.. _UUID: http://en.wikipedia.org/wiki/Uuid

"""

PKG='unique_id'
import roslib; roslib.load_manifest(PKG)
from uuid_msgs.msg import UniqueID

import uuid

def fromMsg(msg):
    """Create UUID object from UniqueID message.

    :param msg: `uuid_msgs/UniqueID`_ message.
    :returns: standard Python :class:`uuid.UUID` object.
    """
    return uuid.UUID(bytes = msg.uuid)

def generate(url, id=None):
    """ Generate UUID_ from URL.

    Matching features within each name space must yield the same UUID.
    The method used is `RFC 4122`_ variant 5, computing the SHA-1 hash
    of a URL encoded using the map source.

    For example, Open Street Map identifiers are encoded like this::

        generate('http://openstreetmap.org/node/' + str(node_id))
        generate('http://openstreetmap.org/way/' + str(way_id))
        generate('http://openstreetmap.org/relation/ + str(rel_id))

    Decimal representations of the integer OSM node, way, or relation
    identifiers are appended to the URL.

    :param url: URL indicating generating source
    :param id: (optional) identifier, unique within URL name space
    :type  id: int or string convertible to int

    :returns: standard Python :class:`uuid.UUID` object.
    :raises: :exc:`ValueError` if *id* not convertible to int.
"""
    if id is not None:
        url += str(int(id))
    return uuid.uuid5(uuid.NAMESPACE_URL, url)

def makeUniqueID(url, id=None):
    """Create a UniqueID message for *id* number in name space *ns*.

    .. deprecated:: 0.2.0
       Use :py:func:`toMsg`, instead.

    :param url: URL indicating generating source
    :param id: (optional) identifier, unique within URL name space
    :type  id: int or string convertible to int
    :returns: `uuid_msgs/UniqueID`_ message
    :raises: :exc:`ValueError` if *id* not convertible to int.
    """
    return UniqueID(uuid = str(generate(url, id)))

def random():
    """Create a random UUID object.

    :returns: standard type 4 Python :class:`uuid.UUID` object.
    """
    return uuid.uuid4()

def toMsg(uuid_obj):
    """Create a UniqueID message from a UUID object.

    :param uuid_obj: standard Python :class:`uuid.UUID` object.
    :returns: `uuid_msgs/UniqueID`_ message
    """
    return UniqueID(uuid = uuid_obj.bytes)

def toString(msg):
    """Create the canonical string representation for a UniqueID message.

    :param msg: `uuid_msgs/UniqueID`_ message.
    :returns: canonical UUID hex string: '01234567-89ab-cdef-0123-456789abcdef'
    """
    return str(uuid.UUID(bytes = msg.uuid))
