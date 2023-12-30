#include <iostream>
#include <ctime> // for random
#include <cstdlib> // for random

#include "../enums/Placement.hh"
#include "../enums/TileState.hh"
#include "../enums/SaveToFile.hh"
#include "../structs/ship.hh"
#include "../structs/player.hh"
#include "validate_input.hh"
#include "file_handling.hh"

#pragma once

int create_custom_map(player_t &player);

int create_random_map(player_t &player);

int generate_map(player_t &player, Placement ship_placement);

void set_ship_coords_on_map(TileState **map, ship_t ship);