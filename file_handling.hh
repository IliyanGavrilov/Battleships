#pragma once
#include <fstream>
#include <string>
#include <vector>

#include "SuccessfulHit.hh"
#include "Mode.hh"
#include "Difficulty.hh"
#include "Randomness.hh"
#include "TileState.hh"
#include "ship.hh"
#include "player.hh"
#include "FileHandling.hh"

int load_game_from_file(FileHandling load_type, char *filename, player_t *player1, player_t *player2 = nullptr, Mode *eMode = nullptr,
                        SuccessfulHit *eSuccessfulHit = nullptr, Difficulty *eDifficulty = nullptr, Randomness *eRandomness = nullptr);

void load_player_info_from_file(std::ifstream &file, player_t &player);

int save_game_to_file(FileHandling save_type, char *filename, player_t *player1, player_t *player2 = nullptr, Mode *eMode = nullptr,
                      SuccessfulHit *eSuccessfulHit = nullptr, Difficulty *eDifficulty = nullptr, Randomness *eRandomness = nullptr);

void save_player_info_to_file(std::ofstream &file, player_t &player);

std::vector<std::string> split_string(const char *str, char delimiter = ' ');