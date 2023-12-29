#include "ship.hh"

ship_t::ship_t() {
  this->size = 0;
  this->end_coords[2] = {};
}

ship_t::ship_t(int size, point_t p1, point_t p2){
  this->size = size;
  this->end_coords[0] = p1;
  this->end_coords[1] = p2;
}

void ship_t::fix_start_end_coords(point_t &p1, point_t &p2) {
  if(p1.x > p2.x || p1.y > p2.y) {
    std::swap(p1.x, p2.x);
    std::swap(p1.y, p2.y);
  }
}