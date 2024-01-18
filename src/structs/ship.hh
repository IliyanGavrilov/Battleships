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
// * <header file with ship structure>
// *
// *
//

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

