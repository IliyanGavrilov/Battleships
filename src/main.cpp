#include "user_input_output/get_input.hh"

int main() {
  return get_input();
}

// TODO Fix settings input
// TODO Fix passing whole player struct instead of separate parameters AND passing by reference instead of copying
// TODO "const" (TileState ** const map, const int size, const ship_t end_points)