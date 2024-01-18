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
// * <header file with point structure>
// *
// *
//

#pragma once

struct point_t {
  int x;
  int y;

  point_t();
  point_t(int, int);
  bool is_between_points(const point_t &p1, const point_t &p2) const;
  void swap(point_t &other);
};

void fix_start_end_coords(point_t &p1, point_t &p2);