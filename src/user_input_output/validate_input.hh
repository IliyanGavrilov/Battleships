#include <iostream>

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

bool validate_input(GameType gameType = GameType::New, int size = MIN_SIZE,
                    SuccessfulHit successfulHit = SuccessfulHit::SwitchTurn, Mode mode = Mode::Singleplayer,
                    Difficulty difficulty = Difficulty::Impossible, Randomness randomness = Randomness::Normal);

bool validate_ship_placement(Placement ship_placement);

Placement get_placement();

int validate_ship_coords(std::vector<std::vector<TileState>> map, int map_size, int ship_size, point_t p1, point_t p2);

bool can_ship_fit_on_map(std::vector<std::vector<TileState>> map, int map_size, int ship_size);

int validate_shot_coords(player_t *player, point_t shot, bool flag);

void print_invalid_coords_error_code(int error_code);

void print_file_errors(int error_code);

void clear_screen();

unsigned char to_lower(char c);