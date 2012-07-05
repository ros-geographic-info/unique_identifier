//
// C++ unit tests for unique_id interface.
//

#include <gtest/gtest.h>

#include <unique_id/unique_id.h>
using namespace unique_id;
typedef boost::uuids::uuid uuid;

///////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////

// Test random generator
TEST(UniqueID, fromRandom)
{
  uuid x = fromRandom();
  EXPECT_EQ(x, x);
  uuid y = fromRandom();
  EXPECT_NE(x, y);
}

// Run all the tests that were declared with TEST()
int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
