#include "player.hh"

player_t::player_t() {
  this->map = nullptr;
  this->map_size = 0;
  this->ships = nullptr;
  this->ships_count = 0;
}

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

  delete[] ships;
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

ship_t *player_t::get_hit_ship(point_t shot) {
  for(int i = 0; i < ships_count; i++) {
    if(shot.is_between_points(ships[i].end_coords[0], ships[i].end_coords[1])) {
      return &ships[i];
    }
  }
  return nullptr;
}

bool player_t::shoot_at(point_t shot) {
  bool successful_hit = false;

  switch(map[shot.x][shot.y]) {
    case Water: {
      map[shot.x][shot.y] = TileState::Miss;
      std::cout << "Missed!\n";
    }break;
    case Unhit: {
      successful_hit = true;

      ship_t hit_ship = *get_hit_ship(shot);
      int hit_ship_tiles_count = 0;

      // Count how many ship tiles have been hit
      for(int i = 0; i < hit_ship.size; i++) {
        // Vertical ship
        if(hit_ship.end_coords[0].x == hit_ship.end_coords[1].x) {
          if(map[i][shot.x] == TileState::Unhit) {
            hit_ship_tiles_count++;
          }
        }

        // Horizontal ship (y1 == y2)
        if(hit_ship.end_coords[0].y == hit_ship.end_coords[1].y) {
          if (map[shot.y][i] == TileState::Unhit) {
            hit_ship_tiles_count++;
          }
        }
      }

      // Check if ship is fully sunken or just hit
      if(hit_ship_tiles_count == 0) {
        // Print ship type
        map[shot.x][shot.y] = TileState::Sunken;
        std::cout << "You sunk the enemy's ship!\n";
      }
      else {
        map[shot.x][shot.y] = TileState::Hit;
        std::cout << "Hit enemy ship!\n";
      }
    }break;
    default: break; // Hit, Miss or Sunken case
  }

  return successful_hit;
}

point_t *player_t::get_unhit_ship_coords() {
  point_t *ship_coords = new point_t[get_ship_coords_count()];
  int l = 0;

  for(int i = 0; i < map_size; i++) {
    for(int j = 0; j < map_size; j++) {
      if(map[i][j] == TileState::Unhit) {
        ship_coords[l] = point_t(j, i);
        l++;
      }
    }
  }

  return ship_coords;
}

int player_t::get_ship_coords_count() {
  int count = 0;

  for(int i = 0; i < ships_count; i++) {
    count += ships[i].size;
  }

  return count;
}