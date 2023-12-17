#include <iostream>

#include "GameType.hh"
#include "SuccessfulHit.hh"
#include "Mode.hh"
#include "Difficulty.hh"
#include "Randomness.hh"
#include "Placement.hh"
#include "TileState.hh"
#include "point.hh"

#define MIN_SIZE 5
#define MAX_SIZE 20

#pragma once

bool validate_input(int size, GameType gameType, SuccessfulHit successfulHit, Mode mode, Difficulty difficulty, Randomness randomness);

bool validate_ship_placement(Placement ship_placement);

Placement get_placement();

int validate_ship_coords(TileState ** map, int map_size, int ship_size, point_t p1, point_t p2);