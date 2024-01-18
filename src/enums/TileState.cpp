#include "TileState.hh"

TileState charToTileState(char c) {
  switch (c) {
    default: return TileState::Water; // ~
    case 's': return TileState::Unhit;
    case 'X': return TileState::Hit;
    case 'O': return TileState::Miss;
    case '@': return TileState::Sunken;
  }
}

std::string getTileColour(char tile) {
  switch (tile) {
    default: return BLUE_T; // ~
    case 's': return RED_T;
    case 'X': return ORANGE_T;
    case 'O': return RED_T;
    case '@': return GREEN_T;
  }
}