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
