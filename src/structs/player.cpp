#include "player.hh"

player_t::player_t() {
  this->map_size = 0;
  this->ships_count = 0;
}

player_t::player_t(int map_size, const std::vector<ship_t> &ships, int ships_count) {
  this->map_size = map_size;
  this->set_map();
  this->ships = ships;
  this->ships_count = ships_count;
}

void player_t::set_map() {
  for (int i = 0; i < map_size; i++) {
    std::vector<TileState> row;
    for (int j = 0; j < map_size; j++) {
      row.emplace_back(TileState::Water);
    }
    this->map.emplace_back(row);
  }
}

void player_t::clear_map() {
  for (int i = 0; i < map_size; i++) {
    for (int j = 0; j < map_size; j++) {
      map[i][j] = TileState::Water;
    }
  }
}

ship_t *player_t::get_hit_ship(const point_t &shot) {
  for (int i = 0; i < ships_count; i++) {
    if (shot.is_between_points(ships[i].end_coords[0], ships[i].end_coords[1])) {
      return &ships[i];
    }
  }
  return nullptr;
}

int player_t::get_hit_ship_index(const ship_t &ship) const {
  for (int i = 0; i < ships_count; i++) {
    if (ships[i].size == ship.size && ships[i].end_coords[0].x == ship.end_coords[0].x &&
        ships[i].end_coords[0].y == ship.end_coords[0].y) {
      return i;
    }
  }
  return 0;
}

bool player_t::shoot_at(const point_t &shot) {
  bool successful_hit = false;

  switch (map[shot.y][shot.x]) {
    case Water: {
      map[shot.y][shot.x] = TileState::Miss;
      std::cout << "Missed!";
    }break;
    case Unhit: {
      successful_hit = true;

      ship_t *hit_ship = get_hit_ship(shot);
      int hit_ship_tiles_count = 0;

      point_t start = (*hit_ship).end_coords[0], end = (*hit_ship).end_coords[1];

      // Count how many ship tiles have been hit
      for (int i = start.y; i <= end.y; i++) {
        for (int j = start.x; j <= end.x; j++) {
          if (map[i][j] == TileState::Hit) {
            hit_ship_tiles_count++;
          }
        }
      }

      // Check if ship is fully sunken or just hit
      if (hit_ship_tiles_count == (*hit_ship).size - 1) {
        // Set ship as sunken and print ship type
        for (int i = start.y; i <= end.y; i++) {
          for (int j = start.x; j <= end.x; j++) {
            map[i][j] = TileState::Sunken;
          }
        }
        // Remove hit ship from player ships
        ships.erase(ships.begin() + get_hit_ship_index((*hit_ship)));
        ships_count--;

        std::cout << "Sunk enemy's " << valueToEnumName((ShipTypes) (*hit_ship).size) <<
                     " (size " << (*hit_ship).size << ")!";
      }
      else {
        map[shot.y][shot.x] = TileState::Hit;
        std::cout << "Hit enemy ship!";
      }
    }break;
    default: break; // Hit, Miss or Sunken case
  }

  // Print shot coords
  std::cout << " [" << char('A' + shot.y) << shot.x + 1 << "]\n";

  return successful_hit;
}

point_t *player_t::get_unhit_ship_coords() const {
  point_t *ship_coords = new point_t[get_ship_coords_count(TileState::Unhit)];
  int l = 0;

  for (int i = 0; i < map_size; i++) {
    for (int j = 0; j < map_size; j++) {
      if (map[i][j] == TileState::Unhit) {
        ship_coords[l] = point_t(j, i);
        l++;
      }
    }
  }

  return ship_coords;
}

int player_t::get_ship_coords_count(TileState ship_state) const {
  int count = 0;

  for (int i = 0; i < map_size; i++) {
    for (int j = 0; j < map_size; j++) {
      // Hit or Unhit ships
      if (map[i][j] == ship_state) {
        count++;
      }
    }
  }

  return count;
}

int player_t::get_smallest_ship_size() const {
  int min = ShipTypes::Carrier;

  for (int i = 0; i < ships_count; i++) {
    point_t start = ships[i].end_coords[0], end = ships[i].end_coords[1];

    // Get ships that are still not sunk
    for (int j = start.x; j <= end.x; j++) {
      for (int l = start.y; l <= end.y; l++) {
        if (map[j][l] == TileState::Sunken) {
          continue;
        }
      }
    }

    if (ships[i].size < min) {
      min = ships[i].size;
    }
  }

  return min;
}