#include <Rectangle.hpp>
#include <gtest/gtest.h>

TEST(RectangleTest, Create)
{
  ASSERT_NO_THROW(rectangle(0, 1, 2, 3, 4));
}

TEST(RectangleTest, Print)
{
  ASSERT_NO_THROW(rectangle(0, 1, 2, 3, 4).print());
}

TEST(RectangleTest, TwoRectanglesWithDifferentIdsAreTheSame)
{
  const auto rectA = rectangle(1, 1, 2, 3, 4);
  const auto rectB = rectangle(2, 1, 2, 3, 4);
  EXPECT_EQ(rectA, rectB);
}

TEST(IntersectRectangleTest, Create)
{
  ASSERT_NO_THROW(intersect_rectangle(rectangle(0, 1, 2, 3, 4), {1, 2}));
  const auto iRect = intersect_rectangle(rectangle(0, 1, 2, 3, 4), {1, 2});
  ASSERT_EQ(iRect.intersectionRectIds.front(), 1);
  ASSERT_EQ(iRect.intersectionRectIds.back(), 2);
}

TEST(IntersectRectangleTest, Print)
{
  ASSERT_NO_THROW(intersect_rectangle(rectangle(0, 1, 2, 3, 4), {1, 2}).print());
}

TEST(IntersectRectangleTest, IntersectEqualRectangles)
{
  const auto rectA = rectangle(1, 1, 2, 3, 4);
  const auto rectB = rectangle(2, 1, 2, 3, 4);
  const auto intersectionRects = intersectRectangles({rectA, rectB});
  ASSERT_EQ(intersectionRects.size(), 1);
  EXPECT_EQ(rectA, intersectionRects.front().intersectRect);
}

TEST(IntersectRectangleTest, IntersectRectangleHasIdZero)
{
  const auto rectA = rectangle(1, 1, 2, 3, 4);
  const auto rectB = rectangle(2, 1, 2, 3, 4);
  const auto intersectionRects = intersectRectangles({rectA, rectB});
  ASSERT_EQ(intersectionRects.front().intersectRect.idx, 0);
}
