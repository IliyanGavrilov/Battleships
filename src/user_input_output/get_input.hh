#include <iostream>

#include "../enums/GameType.hh"
#include "../enums/SuccessfulHit.hh"
#include "../enums/Mode.hh"
#include "../enums/Difficulty.hh"
#include "../enums/Randomness.hh"
#include "../enums/Placement.hh"
#include "../enums/ShipTypes.hh"
#include "../game/start_game.hh"
#include "../structs/game_settings.hh"
#include "file_handling.hh"

#define MAX_SHIP_COVERAGE 0.85

#pragma once

int get_input();

int get_amount_of_ships_to_place(std::vector<ship_t> &ships, int map_size);