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
  player_t(int, std::vector<ship_t> , int);
  void setMap();
  void clear_map();
  ship_t *get_hit_ship(point_t shot);
  int get_hit_ship_index(ship_t ship);
  bool shoot_at(point_t shot);
  point_t *get_unhit_ship_coords();
  int get_ship_coords_count(TileState ship_state);
  int get_smallest_ship_size();
};