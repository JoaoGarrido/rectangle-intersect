#include <Rectangle.hpp>
#include <gtest/gtest.h>

using namespace details;

TEST(IntersectLine, SameLine)
{
  const auto lineA = line {1, 2};
  const auto intersectLine = intersectLineInTheSameAxis(lineA, lineA);
  ASSERT_EQ(intersectLine.value_or(line {0, 0}), lineA);
}

TEST(IntersectLine, DoNotTouch)
{
  ASSERT_FALSE(
      intersectLineInTheSameAxis(line {1, 2}, line {2, 3}).has_value());
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
  ASSERT_EQ(*iRect.intersectionRectIds.cbegin(), 1);
  ASSERT_EQ(*iRect.intersectionRectIds.cend(), 2);
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

TEST(IntersectRectangleTest, IntersectRectanglesThatDoNotIntersect)
{
  const auto rectA = rectangle(1, 1, 1, 0, 0);
  const auto rectB = rectangle(2, 1, 1, 2, 2);
  ASSERT_EQ(intersectRectangles({rectA, rectB}).size(), 0);
}

TEST(IntersectRectangleTest, IntersectRectanglePartOnePartOther)
{
  const auto rectA = rectangle(1, 1, 2, 2, 1);  // 2->4 in x and 1->2 in y
  const auto rectB = rectangle(2, 4, 2, 3, 0);  // 3->5 in x and 0->4 in y
  const auto intersectionRects = intersectRectangles({rectA, rectB});
  ASSERT_EQ(intersectionRects.size(), 1);
  EXPECT_EQ(rectangle(1, 1, 3, 1), intersectionRects.front().intersectRect);
}

TEST(IntersectRectangleTest, IntersectRectangleContainedInTheOther)
{
  const auto rectA = rectangle(1, 4, 6, 0, 1);  // 0->6 in x and 1->5 in y
  const auto rectB = rectangle(2, 2, 2, 3, 2);  // 3->5 in x and 2->4 in y
  const auto intersectionRects = intersectRectangles({rectA, rectB});
  ASSERT_EQ(intersectionRects.size(), 1);
  EXPECT_EQ(rectB, intersectionRects.front().intersectRect);
}

TEST(IntersectRectangleTest, IntersectFourRectangles)
{
  std::vector<rectangle> testRectangles;
  testRectangles.emplace_back(rectangle {1, 80, 250, 100, 100});
  testRectangles.emplace_back(rectangle {2, 150, 250, 120, 200});
  testRectangles.emplace_back(rectangle {3, 100, 250, 140, 160});
  testRectangles.emplace_back(rectangle {4, 190, 350, 160, 140});
  const auto intersectionRects = intersectRectangles(testRectangles);
  ASSERT_EQ(intersectionRects.size(), 7);
  ASSERT_EQ(intersectionRects.at(0),
            intersect_rectangle(rectangle(20, 210, 140, 160),
                                std::set<uint>({1, 3})));
  ASSERT_EQ(intersectionRects.at(1),
            intersect_rectangle(rectangle(40, 190, 160, 140),
                                std::set<uint>({1, 4})));
  ASSERT_EQ(intersectionRects.at(2),
            intersect_rectangle(rectangle(60, 230, 140, 200),
                                std::set<uint>({2, 3})));
}

TEST(IntersectRectangleTest, IntersectThreeEqualRectangles)
{
  const auto rectA = rectangle(1, 1, 2, 3, 4);
  const auto rectB = rectangle(2, 1, 2, 3, 4);
  const auto rectC = rectangle(3, 1, 2, 3, 4);
  const auto intersectionRects = intersectRectangles({rectA, rectB, rectC});
  ASSERT_EQ(intersectionRects.size(), 4);
  for(const auto &iRect : intersectionRects){
    EXPECT_EQ(rectA, iRect.intersectRect);
  }
}

TEST(IntersectRectangleTest, IntersectSixEqualRectangles)
{
  const auto rectA = rectangle(1, 1, 2, 3, 4);
  const auto rectB = rectangle(2, 1, 2, 3, 4);
  const auto rectC = rectangle(3, 1, 2, 3, 4);
  const auto rectD = rectangle(4, 1, 2, 3, 4);
  const auto rectE = rectangle(5, 1, 2, 3, 4);
  const auto rectF = rectangle(6, 1, 2, 3, 4);
  const auto intersectionRects = intersectRectangles({rectA, rectB, rectC, rectD, rectE, rectF});
  ASSERT_EQ(intersectionRects.size(), 57);
  for(const auto &iRect : intersectionRects){
    EXPECT_EQ(rectA, iRect.intersectRect);
  }
}
