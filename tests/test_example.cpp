#include <gtest/gtest.h>

class FooTest : public testing::Test
{
  protected:
    FooTest()
    {
    }

    ~FooTest() override
    {
    }

    void
    SetUp() override
    {
    }

    void
    TearDown() override
    {
    }
};

TEST_F(FooTest, BasicAddition)
{
    ASSERT_EQ(1 + 1, 2);
}