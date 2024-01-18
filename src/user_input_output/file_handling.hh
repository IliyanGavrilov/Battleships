// /**
// *
// * Solution to course project # 1
// * Introduction to programming course
// * Faculty of Mathematics and Informatics of Sofia University
// * Winter semester 2023/2024
// *
// * @author Iliyan Gavrilov
// * @idnumber 6MI0600293
// * @compiler GCC
// *
// * <header file with functions for loading and saving information to files>
// *
// *
//

#pragma once
#include <fstream>
#include <string>
#include <vector>

#include "../enums/SuccessfulHit.hh"
#include "../enums/Mode.hh"
#include "../enums/Difficulty.hh"
#include "../enums/Randomness.hh"
#include "../enums/TileState.hh"
#include "../structs/ship.hh"
#include "../structs/player.hh"
#include "../enums/FileHandling.hh"

int load_game_from_file(FileHandling load_type, char *filename, player_t &player1, player_t *player2 = nullptr, Mode *eMode = nullptr,
                        SuccessfulHit *eSuccessfulHit = nullptr, Difficulty *eDifficulty = nullptr, Randomness *eRandomness = nullptr);

int load_player_info_from_file(FileHandling load_type, std::ifstream &file, player_t &player);

int save_game_to_file(FileHandling save_type, char *filename, const player_t &player1, const player_t *player2 = nullptr,
                      const Mode *eMode = nullptr, const SuccessfulHit *eSuccessfulHit = nullptr, const Difficulty *eDifficulty = nullptr,
                      const Randomness *eRandomness = nullptr);

void save_player_info_to_file(std::ofstream &file, const player_t &player);

std::vector<std::string> split_string(const char *str, char delimiter = ' ');