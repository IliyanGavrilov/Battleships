#pragma once

enum TileState {Water = '~', Unhit = '!', Hit = 'X', Miss = 'O', Sunken = '*'};

TileState charToTileState(char c);