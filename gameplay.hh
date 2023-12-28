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

point_t get_shot_coords(player_t *opponent, Difficulty *difficulty, Randomness *randomness, int chance_to_cheat, bool successful_last_shot);

point_t get_shot_from_easy_or_hard_bot(player_t *opponent, Randomness *randomness, Difficulty *difficulty, int chance_to_cheat);

point_t get_random_coords_for_shot(player_t *opponent);

point_t get_random_ship_tile_coords(player_t *opponent, point_t *all_ship_coords);