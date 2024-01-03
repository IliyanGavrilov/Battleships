#include "TileState.hh"

TileState charToTileState(char c) {
  switch (c) {
    default: return TileState::Water; // ~
    case 's': return TileState::Unhit;
    case 'X': return TileState::Hit;
    case 'O': return TileState::Miss;
    case '*': return TileState::Sunken;
  }
}