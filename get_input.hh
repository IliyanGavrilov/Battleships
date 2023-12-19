#include <iostream>

#include "GameType.hh"
#include "SuccessfulHit.hh"
#include "Mode.hh"
#include "Difficulty.hh"
#include "Randomness.hh"
#include "Placement.hh"
#include "BoatTypes.hh"
#include "start_game.hh"
#include "file_handling.hh"

#pragma once

int get_input();

int get_amount_of_ships_to_place(ship_t *ships, int map_size);