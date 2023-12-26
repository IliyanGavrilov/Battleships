#include "Mode.hh"
#include "SuccessfulHit.hh"
#include "Difficulty.hh"
#include "Randomness.hh"
#include "TileState.hh"
#include "player.hh"

#pragma once

void game_loop(player_t p1, player_t p2, Mode mode, SuccessfulHit successfulHit, Difficulty difficulty, Randomness randomness);