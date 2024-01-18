#include "../user_input_output/colours.hh"
#include <string>

#pragma once

enum TileState {Water = '~', Unhit = 's', Hit = 'X', Miss = 'O', Sunken = '@'};

TileState charToTileState(char c);

std::string getTileColour(char tile);