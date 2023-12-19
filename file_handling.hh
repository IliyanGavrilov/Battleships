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

int load_game_from_file(char *filename, player_t &player1, player_t &player2, SuccessfulHit &eSuccessfulHit, Difficulty &eDifficulty, Randomness &eRandomness);

void load_player_info_from_file(std::ifstream &file, player_t &player);

std::vector<std::string> split_string(const char *str, char delimiter = ' ');