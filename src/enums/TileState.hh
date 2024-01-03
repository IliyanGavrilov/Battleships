#pragma once

enum TileState {Water = '~', Unhit = 's', Hit = 'X', Miss = 'O', Sunken = '@'};

TileState charToTileState(char c);