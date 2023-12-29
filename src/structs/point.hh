#pragma once

struct point_t {
  int x;
  int y;

  point_t();
  point_t(int, int);
  bool is_between_points(point_t p1, point_t p2);
};
