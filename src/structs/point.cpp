#include "point.hh"

point_t::point_t() {
  this->x = 0;
  this->y = 0;
}

point_t::point_t(int x, int y) {
  this->x = x;
  this->y = y;
}

bool point_t::is_between_points(const point_t &p1, const point_t &p2) const {
  // Horizontal or vertical cases
  if ((p1.x == x && p2.x == x && y >= p1.y && y <= p2.y) ||
     (p1.y == y && p2.y == y && x >= p1.x && x <= p2.x)) {
    return true;
  }
  return false;
}

void fix_start_end_coords(point_t &p1, point_t &p2) {
  if (p1.x > p2.x || p1.y > p2.y) {
    p1.swap(p2);
  }
}

void point_t::swap(point_t &other) {
  int temp = this->x;
  this->x = other.x;
  other.x = temp;

  temp = this->y;
  this->y = other.y;
  other.y = temp;
}