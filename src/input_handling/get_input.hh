#include <iostream>

#include "../enums/GameType.hh"
#include "../enums/SuccessfulHit.hh"
#include "../enums/Mode.hh"
#include "../enums/Difficulty.hh"
#include "../enums/Randomness.hh"
#include "../enums/Placement.hh"
#include "../enums/BoatTypes.hh"
#include "../game/start_game.hh"
#include "file_handling.hh"

#pragma once

int get_input();

int get_amount_of_ships_to_place(ship_t *ships, int map_size);