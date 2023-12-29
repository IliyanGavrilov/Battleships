#include "TileState.hh"

TileState charToTileState(char c) {
  switch(c) {
    default: return TileState::Water; // ~
    case '!': return TileState::Unhit;
    case 'X': return TileState::Hit;
    case '0': return TileState::Miss;
    case '*': return TileState::Sunken;
  }
}