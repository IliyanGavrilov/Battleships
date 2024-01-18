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
// * <header file with player struct>
// *
// *
//

#include <iostream>
#include <vector>
#include "ship.hh"
#include "../enums/TileState.hh"
#include "../enums/ShipTypes.hh"

#pragma once

struct player_t {
  std::vector<std::vector<TileState>> map;
  int map_size;
  std::vector<ship_t> ships;
  int ships_count;

  player_t();
  player_t(int, const std::vector<ship_t> &, int);
  void set_map();
  void clear_map();
  ship_t *get_hit_ship(const point_t &shot);
  int get_hit_ship_index(const ship_t &ship) const;
  bool shoot_at(const point_t &shot);
  point_t *get_unhit_ship_coords() const;
  int get_ship_coords_count(TileState ship_state) const;
  int get_smallest_ship_size() const;
};