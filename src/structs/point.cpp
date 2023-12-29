#include "point.hh"

point_t::point_t() {
  this->x = 0;
  this->y = 0;
}

point_t::point_t(int x, int y) {
  this->x = x;
  this->y = y;
}

bool point_t::is_between_points(point_t p1, point_t p2) {
  // Horizontal or vertical cases
  if((p1.x == x && p2.x == x && y > p1.y && y < p2.y) ||
     (p1.y == y && p2.y == x && x > p1.x && x < p2.x)) {
    return true;
  }
  return false;
}