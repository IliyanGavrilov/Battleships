#include <iostream>
#include <ctime> // for random
// #include <cstdlib> // for random // TODO fix

#include "Placement.hh"
#include "TileState.hh"
#include "ship.hh"
#include "player.hh"
#include "validate_input.hh"

#pragma once

void create_custom_map(player_t player);

void create_random_map(player_t player);

void generate_map(player_t player, Placement ship_placement);

void print_invalid_coords_error_code(int error_code);

void set_ship_coords_on_map(TileState **map, ship_t ship);