#include <algorithm>

#include "Rectangle.hpp"

namespace details
{

auto intersectLineInTheSameAxis(const line a,
                                const line b) -> std::optional<line>
{
  // No intersection
  if (b.first >= a.second || a.first >= b.second) {
    return std::nullopt;
  }
  // Same coordinate
  else if (a == b)
  {
    return a;
  }
  // B contained in A
  else if (b.first >= a.first && b.second <= a.second)
  {
    return b;
  }
  // A contained in B
  else if (a.first >= b.first && a.second <= b.second)
  {
    return a;
  }
  // Intersection starts in a ends in b
  else if (a.first >= b.first && a.second >= b.second)
  {
    return line {a.first, b.second};
  }
  // Intersection starts in b ends in a
  else if (b.first >= a.first && b.second >= a.second)
  {
    return line {b.first, a.second};
  }
  std::cerr << "IMPOSSIBLE!" << std::endl;
  return std::nullopt;
}

}  // namespace details

auto toRect(const std::optional<details::line> x,
            const std::optional<details::line> y) -> std::optional<rectangle>
{
  if (!x || !y) {
    return std::nullopt;
  }
  const auto w = x.value().second - x.value().first;
  const auto h = y.value().second - y.value().first;
  return rectangle {0, h, w, x.value().first, y.value().first};
}

auto createFamilyRectanglesList(const rectangle& a,
                                const rectangle& b) -> std::set<uint>
{
  std::set<uint> intersectionIds;
  intersectionIds.emplace(a.idx);
  intersectionIds.emplace(b.idx);
  return intersectionIds;
}

auto intersectRectangle(const rectangle& a, const rectangle& b)
    -> std::optional<intersect_rectangle>
{
  auto familyRectIdList = createFamilyRectanglesList(a, b);
  // One over the other
  if (a == b) {
    return intersect_rectangle {rectangle {a.h, a.w, a.x, a.y},
                                familyRectIdList};
  }
  const auto xIntersect =
      details::intersectLineInTheSameAxis({a.x, a.x + a.w}, {b.x, b.x + b.w});
  const auto yIntersect =
      details::intersectLineInTheSameAxis({a.y, a.y + a.h}, {b.y, b.y + b.h});
  const auto intersectionRect = toRect(xIntersect, yIntersect);
  if (!intersectionRect) {
    return std::nullopt;
  }
  return intersect_rectangle {intersectionRect.value(), familyRectIdList};
}

auto createFamilyRectanglesList(const intersect_rectangle& a,
                                const intersect_rectangle& b) -> std::set<uint>
{
  std::set<uint> intersectionIds;
  std::merge(a.intersectionRectIds.cbegin(),
             a.intersectionRectIds.cend(),
             b.intersectionRectIds.cbegin(),
             b.intersectionRectIds.cend(),
             std::inserter(intersectionIds, intersectionIds.begin()));
  return intersectionIds;
}

auto intersectRectangle(const intersect_rectangle& a,
                        const intersect_rectangle& b)
    -> std::optional<intersect_rectangle>
{
  auto familyRectIdList = createFamilyRectanglesList(a, b);
  if (a == b) {
    return std::nullopt;
  } else if (a.intersectRect == b.intersectRect) {
    return intersect_rectangle {rectangle {a.intersectRect.h,
                                           a.intersectRect.w,
                                           a.intersectRect.x,
                                           a.intersectRect.y},
                                familyRectIdList};
  }
  const auto& rectA = a.intersectRect;
  const auto& rectB = b.intersectRect;
  const auto xIntersect = details::intersectLineInTheSameAxis(
      {rectA.x, rectA.x + rectA.w}, {rectB.x, rectB.x + rectB.w});
  const auto yIntersect = details::intersectLineInTheSameAxis(
      {rectA.y, rectA.y + rectA.h}, {rectB.y, rectB.y + rectB.h});
  const auto intersectionRect = toRect(xIntersect, yIntersect);
  if (!intersectionRect) {
    return std::nullopt;
  }
  return intersect_rectangle {intersectionRect.value(), familyRectIdList};
}

auto addInternalIntersection(std::vector<intersect_rectangle>& rectangles)
    -> bool
{
  bool addedMoreIntersection = false;
  const uint n_rectangles = rectangles.size();
  const uint n_rectagles_except_last = n_rectangles - 1;
  for (uint i = 0; i < n_rectagles_except_last; i++) {
    for (uint j = i + 1; j < n_rectangles; j++) {
      const auto intersectionRect =
          intersectRectangle(rectangles.at(i), rectangles.at(j));
      if (intersectionRect
          && std::find(
                 rectangles.begin(), rectangles.end(), intersectionRect.value())
              == rectangles.end())
      {
        rectangles.emplace_back(intersectionRect.value());
        (*intersectionRect).print();
        addedMoreIntersection = true;
      }
    }
  }
  return addedMoreIntersection;
}

auto intersectRectangles(const std::vector<rectangle>& rectangles)
    -> std::vector<intersect_rectangle>
{
  std::vector<intersect_rectangle> intersectRects;
  const uint n_rectangles = rectangles.size();
  const uint n_rectagles_except_last = n_rectangles - 1;
  for (uint i = 0; i < n_rectagles_except_last; i++) {
    for (uint j = i + 1; j < n_rectangles; j++) {
      const auto intersectionRect =
          intersectRectangle(rectangles.at(i), rectangles.at(j));
      if (intersectionRect) {
        intersectRects.emplace_back(intersectionRect.value());
        (*intersectionRect).print();
      }
    }
  }
  if (!intersectRects.empty()) {
    while (addInternalIntersection(intersectRects)) {
    }
  }
  return intersectRects;
}
