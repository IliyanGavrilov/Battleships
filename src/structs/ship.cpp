#include "ship.hh"

ship_t::ship_t() {
  this->size = 0;
  this->end_coords[0] = point_t();
  this->end_coords[1] = point_t();
}

ship_t::ship_t(int size) {
  this->size = size;
}

ship_t::ship_t(int size, point_t p1, point_t p2) {
  this->size = size;
  this->end_coords[0] = p1;
  this->end_coords[1] = p2;
}