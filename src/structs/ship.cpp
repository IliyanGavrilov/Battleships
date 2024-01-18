// /**
// *
// * Solution to course project # 1
// * Introduction to programming course
// * Faculty of Mathematics and Informatics of Sofia University
// * Winter semester 2023/2024
// *
// * @author Iliyan Gavrilov
// * @idnumber 6MI0600293
// * @compiler GCC
// *
// * <file with ship constructors implementations>
// *
// *
//

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