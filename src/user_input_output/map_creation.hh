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
// * <header file with functions for creating player maps>
// *
// *
//

#include <iostream>
#include <ctime> // for random
#include <cstdlib> // for random
#include <limits>

#include "../enums/Placement.hh"
#include "../enums/TileState.hh"
#include "../enums/SaveToFile.hh"
#include "../structs/ship.hh"
#include "../structs/player.hh"
#include "validate_input.hh"
#include "file_handling.hh"
#include "output_printing.hh"

#pragma once

int create_custom_map(player_t &player);

int create_random_map(player_t &player);

int generate_map(player_t &player, Placement ship_placement, Mode mode);

void set_ship_coords_on_map(std::vector<std::vector<TileState>> &map, const ship_t &ship);