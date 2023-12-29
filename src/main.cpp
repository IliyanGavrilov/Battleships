#include "input_handling/get_input.hh"

int main() {
  return get_input();
}
// TODO make player wait until random generates map with any amount of ships that can fit on it
// TODO Fix passing whole player struct instead of separate parameters
// TODO "const" (TileState ** const map, const int size, const ship_t end_points)
// TODO space between for () if () while () etc.