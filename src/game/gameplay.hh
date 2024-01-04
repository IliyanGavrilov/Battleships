#include <limits>
#include "../enums/Mode.hh"
#include "../enums/SuccessfulHit.hh"
#include "../enums/Difficulty.hh"
#include "../enums/Randomness.hh"
#include "../enums/TileState.hh"
#include "../structs/player.hh"
#include "../user_input_output/validate_input.hh"
#include "../enums/SaveToFile.hh"
#include "../enums/FileHandling.hh"
#include "../user_input_output/file_handling.hh"
#include "../user_input_output/output_printing.hh"

#define DIRECTIONS_COUNT 4

#pragma once

bool check_win(player_t &p1, player_t &p2);

void game_loop(player_t &p1, player_t &p2, Mode mode, SuccessfulHit successfulHit, Difficulty *difficulty, Randomness *randomness);

bool play_turn(player_t &opponent, Difficulty *difficulty = nullptr, Randomness *randomness = nullptr);

point_t get_shot_coords(player_t &opponent, Difficulty *difficulty, Randomness *randomness, int chance_to_cheat);

point_t get_shot_from_easy_or_hard_bot(player_t &opponent, Randomness randomness, Difficulty difficulty, int chance_to_cheat);

point_t get_random_coords_for_shot(player_t &opponent);

point_t get_parity_shot(player_t &opponent);

point_t get_random_ship_tile_coords(player_t &opponent, point_t *all_ship_coords);

point_t sink_found_ships(player_t &opponent);