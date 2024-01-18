#include <iostream>
#include <limits>

#include "../enums/GameType.hh"
#include "../enums/SuccessfulHit.hh"
#include "../enums/Mode.hh"
#include "../enums/Difficulty.hh"
#include "../enums/Randomness.hh"
#include "../enums/Placement.hh"
#include "../enums/TileState.hh"
#include "../structs/point.hh"
#include "../structs/player.hh"

#define MIN_SIZE 5
#define MAX_SIZE 20

#pragma once

bool validate_game_type(int gameType);

bool validate_map_size(int size);

bool validate_successful_hit(int successfulHit);

bool validate_mode(int mode);

bool validate_difficulty(int difficulty);

bool validate_randomness(int randomness);

bool validate_ship_placement(Placement ship_placement);

Placement get_placement();

int validate_ship_coords(const std::vector<std::vector<TileState>> &map, int map_size, int ship_size, const point_t &p1, const point_t &p2);

bool can_ship_fit_on_map(const std::vector<std::vector<TileState>> &map, int map_size, int ship_size);

int validate_shot_coords(const player_t &player, const point_t &shot, bool flag);

void print_invalid_coords_error_code(int error_code);

void print_file_errors(int error_code);

void clear_screen();

unsigned char to_lower(char c);