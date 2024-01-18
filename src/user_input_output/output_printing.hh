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
// * <header file with functions related to printing to console/terminal output and formatting>
// *
// *
//

#include <iostream>
#include <vector>
#include <iomanip>
#include "../structs/ship.hh"
#include "../enums/TileState.hh"
#include "../enums/ShipTypes.hh"

#pragma once

void print_grid_line(int map_size, point_t *shot, bool highlight);

void print_x_axis_numbers(int map_size);

void print_map(const std::vector<std::vector<TileState>> &map_before, int map_size, bool flag, point_t *shot = nullptr);

void print_ship_sizes_left(const std::vector<ship_t> &ships);