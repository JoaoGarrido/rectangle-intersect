#include "Rectangle.hpp"

auto intersectRectangle(const rectangle& a,
                        const rectangle& b) -> std::optional<intersect_rectangle>
{
  // One over the other
  if (a == b) {
    return intersect_rectangle{rectangle{a.h, a.w, a.x, a.y}, {a.idx, b.idx}};
  }
  // TODO: Intersect when not one over the other
  return std::nullopt;
}

auto intersectRectangles(const std::vector<rectangle>& rectangles)
    -> std::vector<intersect_rectangle>
{
  std::vector<intersect_rectangle> intersectRects;
  const uint n_rectangles = rectangles.size();
  const uint n_rectagles_except_last = n_rectangles - 1;
  // TODO: Intersect more than 2
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
  return intersectRects;
}
