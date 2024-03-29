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
// * <header file with function to prepare the start of the game>
// *
// *
//

#include <iostream>

#include "../enums/SuccessfulHit.hh"
#include "../enums/Mode.hh"
#include "../enums/Difficulty.hh"
#include "../enums/Randomness.hh"
#include "../enums/Placement.hh"
#include "../enums/TileState.hh"
#include "../user_input_output/validate_input.hh"
#include "../user_input_output/map_creation.hh"
#include "../structs/player.hh"
#include "gameplay.hh"

#pragma once

int start_game(const std::vector<ship_t> &ships_to_place, int ships_count, int map_size, SuccessfulHit successfulHit,
                Mode mode, Difficulty difficulty, Randomness randomness);