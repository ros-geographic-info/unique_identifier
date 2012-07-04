#!/usr/bin/env python

PKG='unique_id'
import roslib; roslib.load_manifest(PKG)

import sys
import unittest

import uuid                     # standard Python module

from uuid_msgs.msg import UniqueID
from unique_id.unique_id import *

class TestPythonUUID(unittest.TestCase):
    """Unit tests for Python UUID generation.
    """

    # random UUID generation tests
    def test_random_uuids(self):
        x = random()
        self.assertEqual(type(x), uuid.UUID)
        self.assertEqual(x, x)
        y = random()
        self.assertEqual(type(y), uuid.UUID)
        self.assertNotEqual(x, y)

    # UUID generation from URL tests
    def test_int_with_leading_zeros(self):
        x = generate('http://openstreetmap.org/node/', 1)
        self.assertEqual(type(x), uuid.UUID)
        y = generate('http://openstreetmap.org/node/', 0001)
        self.assertEqual(type(y), uuid.UUID)
        self.assertEqual(x, y)
        self.assertEqual(str(x), 'ef362ac8-9659-5481-b954-88e9b741c8f9')

    def test_int_in_a_string(self):
        x = generate('http://openstreetmap.org/node/', 1)
        y = generate('http://openstreetmap.org/node/', '0001')
        self.assertEqual(x, y)
        self.assertEqual(str(y), 'ef362ac8-9659-5481-b954-88e9b741c8f9')
        
    def test_same_id_different_namespace(self):
        x = generate('http://openstreetmap.org/node/', 1)
        y = generate('http://openstreetmap.org/way/', 1)
        self.assertNotEqual(x, y)
        self.assertEqual(str(y), 'b3180681-b125-5e41-bd04-3c8b046175b4')
        
    def test_actual_osm_node_id(self):
        x = generate('http://openstreetmap.org/node/', 1)
        y = generate('http://openstreetmap.org/node/', 152370223)
        self.assertNotEqual(x, y)
        self.assertEqual(str(y), '8e0b7d8a-c433-5c42-be2e-fbd97ddff9ac')

    def test_route_segment(self):
        start = 'da7c242f-2efe-5175-9961-49cc621b80b9'
        end = '812f1c08-a34b-5a21-92b9-18b2b0cf4950'
        x = generate('http://ros.org/wiki/road_network/' + start + '/' + end)
        y = generate('http://ros.org/wiki/road_network/' + end + '/' + start)
        self.assertNotEqual(x, y)
        self.assertEqual(str(x), 'acaa906e-8411-5b45-a446-ccdc2fc39f29')

    def test_invalid_id_value(self):
        self.assertRaises(ValueError, generate,
                          'http://openstreetmap.org/way/', 'xxx')

    # UniqueID message generation tests
    def test_msg_creation(self):
        msg = makeUniqueID('http://openstreetmap.org/node/', 152370223)
        self.assertEqual(msg.uuid, '8e0b7d8a-c433-5c42-be2e-fbd97ddff9ac')
        
    def test_msg_same_id_different_namespace(self):
        x = makeUniqueID('http://openstreetmap.org/node/', 1)
        y = makeUniqueID('http://openstreetmap.org/way/', 1)
        self.assertNotEqual(x, y)
        self.assertEqual(y.uuid, 'b3180681-b125-5e41-bd04-3c8b046175b4')

    def test_msg_route_segment(self):
        start = 'da7c242f-2efe-5175-9961-49cc621b80b9'
        end = '812f1c08-a34b-5a21-92b9-18b2b0cf4950'
        x = makeUniqueID('http://ros.org/wiki/road_network/'
                         + start + '/' + end)
        y = makeUniqueID('http://ros.org/wiki/road_network/'
                         + end + '/' + start)
        self.assertNotEqual(x, y)
        self.assertEqual(x.uuid, 'acaa906e-8411-5b45-a446-ccdc2fc39f29')

    def test_msg_invalid_value(self):
        self.assertRaises(ValueError, makeUniqueID,
                          'http://openstreetmap.org/way/', 'xxx')

    def test_nil_msg(self):
        x = UniqueID()
        y = toMsg(uuid.UUID('00000000-0000-0000-0000-000000000000'))
        self.assertEqual(x, y)

    def test_random_msg(self):
        x = UniqueID()
        y = toMsg(random())
        self.assertNotEqual(x, y)

    def test_equivalent_msgs(self):
        s = 'da7c242f-2efe-5175-9961-49cc621b80b9'
        x = toMsg(uuid.UUID(s))
        y = toMsg(uuid.UUID(s))
        self.assertEqual(x, y)
        self.assertEqual(s, toString(y))

    def test_to_and_from_msg(self):
        x = uuid.UUID('da7c242f-2efe-5175-9961-49cc621b80b9')
        y = (fromMsg(toMsg(x)))
        self.assertEqual(x, y)
        self.assertEqual(type(y), uuid.UUID)

    def test_msg_to_string(self):
        s = 'da7c242f-2efe-5175-9961-49cc621b80b9'
        x = toMsg(uuid.UUID(s))
        y = toString(x)
        self.assertEqual(s, y)
        self.assertEqual(type(y), str)

if __name__ == '__main__':
    import rosunit
    rosunit.unitrun(PKG, 'test_uuid_py', TestPythonUUID) 
