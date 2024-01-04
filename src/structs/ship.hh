#include <iostream>
#include "point.hh"

#pragma once

struct ship_t {
  int size;
  point_t end_coords[2];

  ship_t();
  ship_t(int);
  ship_t(int, point_t, point_t);
};

