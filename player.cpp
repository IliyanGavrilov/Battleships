#include "player.hh"

player_t::player_t(int map_size, ship_t *ships, int ships_count) {
  this->map = nullptr;
  this->map_size = map_size;
  this->ships = ships;
  this->ships_count = ships_count;
}

player_t::~player_t() {
  // Free map memory

  // Free each column (sub-array)
  for(int i = 0; i < map_size; i++) {
    delete[] map[i];
  }

  // Free each row (array of pointers)
  delete[] map;
  map = nullptr;
  map_size = 0;

  ships = nullptr;
  ships_count = 0;
}

void player_t::print_map() {
  for(int i = map_size - 1; i >= 0; i--) {
    for(int j = 0; j < map_size; j++) {
      std::cout << (char)map[i][j] << " ";
    }
    std::cout << "\n";
  }
}