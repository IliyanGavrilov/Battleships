#include <iostream>
#include <vector>
#include <iomanip>
#include "../structs/ship.hh"
#include "../enums/TileState.hh"
#include "../enums/ShipTypes.hh"

#pragma once

void print_grid_line(int map_size);

void print_x_axis_numbers(int map_size);

void print_map(const std::vector<std::vector<TileState>> &map_before, int map_size, bool flag,
               const std::vector<std::vector<TileState>> *map_after = nullptr);

void print_ship_sizes_left(const std::vector<ship_t> &ships);