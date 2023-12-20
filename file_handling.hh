#pragma once
#include <fstream>
#include <string> // TODO
#include <vector> // TODO

#include "SuccessfulHit.hh"
#include "Mode.hh"
#include "Difficulty.hh"
#include "Randomness.hh"
#include "TileState.hh"
#include "ship.hh"
#include "player.hh"

std::ifstream open_file_for_reading(char *filename);

std::ofstream open_file_for_writing(char * filename);

int load_game_from_file(char *filename, player_t &player1, player_t &player2, SuccessfulHit &eSuccessfulHit, Difficulty &eDifficulty, Randomness &eRandomness);

int load_map_from_file(std::ifstream &file, player_t &player);

void load_player_info_from_file(std::ifstream &file, player_t &player);

std::vector<std::string> split_string(const char *str, char delimiter = ' ');