#include <Rectangle.hpp>
#include <gtest/gtest.h>

using namespace details;

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
  ASSERT_NO_THROW(
      intersect_rectangle(rectangle(0, 1, 2, 3, 4), {1, 2}).print());
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

TEST(IntersectLine, SameLine)
{
  const auto lineA = line {1, 2};
  const auto intersectLine = intersectLineInTheSameAxis(lineA, lineA);
  ASSERT_EQ(intersectLine.value_or(line {0, 0}), lineA);
}

TEST(IntersectLine, DoNotTouch)
{
  ASSERT_FALSE(intersectLineInTheSameAxis(line {1, 2}, line {2, 3}).has_value());
}

TEST(IntersectLine, OneLineContainedOnAnother)
{
  const auto lineA = line {1, 5};
  const auto lineB = line {2, 3};
  ASSERT_EQ(intersectLineInTheSameAxis(lineA, lineB), lineB);
  ASSERT_EQ(intersectLineInTheSameAxis(lineB, lineA), lineB);
}

TEST(IntersectLine, StartsInOneEndsInTheOther)
{
  const auto lineA = line {1, 5};
  const auto lineB = line {3, 7};
  const auto intersectionLine = line {3, 5};
  ASSERT_EQ(intersectLineInTheSameAxis(lineA, lineB), intersectionLine);
  ASSERT_EQ(intersectLineInTheSameAxis(lineB, lineA), intersectionLine);
}
