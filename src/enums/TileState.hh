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
// * <header file with TileState enum>
// *
// *
//



#include "../user_input_output/colours.hh"
#include <string>

#pragma once

enum TileState {Water = '~', Unhit = 's', Hit = 'X', Miss = 'O', Sunken = '@'};

TileState charToTileState(char c);

std::string getTileColour(char tile);