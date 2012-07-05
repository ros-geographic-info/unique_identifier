//
// C++ unit tests for unique_id interface.
//

#include <gtest/gtest.h>

#include <unique_id/unique_id.h>
using namespace unique_id;
typedef boost::uuids::uuid uuid;
typedef uuid_msgs::UniqueID UniqueID;

///////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////

// Test random generator
TEST(BoostUUID, fromRandom)
{
  static const int N = 1000;
  uuid uu[N];
  for (int i = 0; i < N; ++i)
    {
      uu[i] = fromRandom();
      for (int j = i-1; j >= 0; --j)
        {
          EXPECT_NE(uu[i], uu[j]);
        }
    }
}

TEST(BoostUUID, sameURL)
{
  std::string s("http://openstreetmap.org/node/1");
  uuid x = fromURL(s);
  uuid y = fromURL(s);
  EXPECT_EQ(x, y);
#if 0
  // Currently broken (requires correct namespace)...
  // MUST yield same result as Python fromURL() function:
  EXPECT_EQ(boost::uuids::to_string(x),
            "ef362ac8-9659-5481-b954-88e9b741c8f9");
#endif
}

TEST(BoostUUID, actualOsmNode)
{
  uuid x = fromURL("http://openstreetmap.org/node/1");
  uuid y = fromURL("http://openstreetmap.org/node/152370223");
  EXPECT_NE(x, y);
#if 0
  // Currently broken (requires correct namespace)...
  // MUST yield same result as Python fromURL() function:
  EXPECT_EQ(boost::uuids::to_string(y),
            "8e0b7d8a-c433-5c42-be2e-fbd97ddff9ac");
#endif
}

TEST(UniqueID, nilMessage)
{
  UniqueID x;
  UniqueID y = toMsg(uuid());
  EXPECT_EQ(x.uuid, y.uuid);
}

TEST(UniqueID, randomMessage)
{
  UniqueID x;
  UniqueID y = toMsg(fromRandom());
  EXPECT_NE(x.uuid, y.uuid);
}

TEST(UniqueID, equivalentMessages)
{
  std::string s("da7c242f-2efe-5175-9961-49cc621b80b9");
  boost::uuids::string_generator gen;
  UniqueID x = toMsg(uuid(gen(s)));
  UniqueID y = toMsg(uuid(gen(s)));
  EXPECT_EQ(x.uuid, y.uuid);
  EXPECT_EQ(s, toString(y));
}

TEST(UniqueID, toAndFromMessage)
{
  std::string s("da7c242f-2efe-5175-9961-49cc621b80b9");
  boost::uuids::string_generator gen;
  uuid x = uuid(gen(s));
  uuid y = fromMsg(toMsg(x));
  EXPECT_EQ(x, y);
}

TEST(UniqueID, messageToString)
{
  std::string s("da7c242f-2efe-5175-9961-49cc621b80b9");
  boost::uuids::string_generator gen;
  UniqueID x = toMsg(uuid(gen(s)));
  std::string y = toString(x);
  EXPECT_EQ(s, y);
}

// Run all the tests that were declared with TEST()
int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
