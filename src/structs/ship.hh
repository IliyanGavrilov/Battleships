#include <iostream>
#include "point.hh"

#pragma once

struct ship_t {
  int size;
  point_t end_coords[2];

  ship_t();
  ship_t(int);
  ship_t(int, point_t, point_t);
  // Static so it can be called without an object created
  static void fix_start_end_coords(point_t &p1, point_t &p2);
};

