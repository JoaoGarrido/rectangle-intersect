#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <vector>

struct rectangle
{
  rectangle(uint _idx, uint _h, uint _w, uint _x, uint _y)
      : idx {_idx}
      , h {_h}
      , w {_w}
      , x {_x}
      , y {_y}
  {
  }
  void print() const
  {
    std::cout << "\t" << idx << ": Rectangle at (" << x << "," << y
              << "), w=" << w << ", h=" << h << ".\n";
  }
  const uint idx;
  const uint h;
  const uint w;
  const uint x;
  const uint y;
};

struct intersect_rectangle
{
  intersect_rectangle(rectangle&& rect, std::vector<uint> ids)
      : intersectRect {std::move(rect)}
      , intersectionRectIds {std::move(ids)}
  {
  }
  const rectangle intersectRect;
  const std::vector<uint> intersectionRectIds;
  void print() const
  {
    std::cout << "\t" << "Between rectangle " << intersectionRectIds.at(0);
    for (uint i = 1; i < intersectionRectIds.size() - 1; i++) {
      std::cout << ", " << intersectionRectIds.at(i);
    }
    std::cout << "and " << intersectionRectIds.back() << "at ";
    std::cout << "(" << intersectRect.x << "," << intersectRect.y
              << "), w=" << intersectRect.w << ", h=" << intersectRect.h
              << ".\n";
  }
};

auto intersectRectangles(const std::vector<rectangle>& rectangles)
    -> std::vector<intersect_rectangle>;
