#include <iostream>

#include "GameType.hh"
#include "SuccessfulHit.hh"
#include "Mode.hh"
#include "Difficulty.hh"
#include "Randomness.hh"
#include "Placement.hh"
#include "TileState.hh"
#include "validate_input.hh"
#include "map_creation.hh"
#include "player.hh"
#include "gameplay.hh"

#pragma once

void start_game(ship_t *ships_to_place, int ships_count, int map_size, GameType gameType,
                SuccessfulHit successfulHit, Mode mode, Difficulty difficulty, Randomness randomness);