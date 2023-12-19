#include <iostream>
#include "ship.hh"
#include "TileState.hh"

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
};