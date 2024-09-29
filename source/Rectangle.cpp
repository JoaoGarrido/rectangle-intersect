#include "Rectangle.hpp"

inline bool operator==(const rectangle& lhs, const rectangle& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.h == rhs.h && lhs.w == rhs.w;
}

auto intersectRectangle(const rectangle& a,
                        const rectangle& b) -> std::optional<rectangle>
{
  // One over the other
  if (a == b) {
    return a;
  }
  // TODO: Intersect when not one over the other
  return std::nullopt;
}

auto intersectRectangles(const std::vector<rectangle>& rectangles)
    -> std::vector<intersect_rectangle>
{
  std::vector<intersect_rectangle> intersectRect;
  const uint n_rectangles = rectangles.size();
  const uint n_rectagles_except_last = n_rectangles - 1;
  // TODO: Intersect more than 2
  for (uint i = 0; i < n_rectagles_except_last; i++) {
    for (uint j = i + 1; j < n_rectangles; j++) {
      const auto intersectionRect =
          intersectRectangle(rectangles.at(i), rectangles.at(j));
      if (intersectionRect) {
        (*intersectionRect).print();
      }
    }
  }
  return intersectRect;
}
