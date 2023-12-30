#include <iostream>
#include "ship.hh"
#include "../enums/TileState.hh"
#include "../enums/BoatTypes.hh"

#pragma once

struct player_t {
  TileState **map;
  int map_size;
  ship_t *ships;
  int ships_count;

  player_t();
  player_t(int, ship_t *, int);
  ~player_t();
  void print_map();
  ship_t *get_hit_ship(point_t shot);
  bool shoot_at(point_t shot);
  point_t *get_unhit_ship_coords();
  int get_ship_coords_count(TileState ship_state);
  int get_smallest_ship_size();
};