#include "Mode.hh"
#include "SuccessfulHit.hh"
#include "Difficulty.hh"
#include "Randomness.hh"
#include "TileState.hh"
#include "player.hh"
#include "validate_input.hh"

#pragma once

void game_loop(player_t p1, player_t p2, Mode mode, SuccessfulHit successfulHit, Difficulty difficulty, Randomness randomness);

bool play_turn(player_t *opponent, Difficulty *difficulty = nullptr, Randomness *randomness = nullptr);

point_t get_random_coords_for_shot(player_t *opponent);