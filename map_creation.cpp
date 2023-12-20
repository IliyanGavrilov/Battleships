#include "map_creation.hh"

int create_custom_map(player_t &player) {
  player.map = new TileState *[player.map_size]; // TODO prevent fragmentation of memory
  for(int i = 0; i < player.map_size; i++) {
    player.map[i] = new TileState[player.map_size];
    for(int j = 0; j < player.map_size; j++) {
      player.map[i][j] = TileState::Water;
    }
  }

  for(int i = 0; i < player.ships_count;) {
    point_t p1, p2;
    std::cout << "Place ship with size " << player.ships[i].size << "(x1 y1 x2 y2) [0, " << player.map_size - 1 << "]\n";
    std::cin >> p1.x >> p1.y >> p2.x >> p2.y;

    ship_t::fix_start_end_coords(p1, p2);

    int error_code = validate_ship_coords(player.map, player.map_size, player.ships[i].size, p1, p2);

    if(!error_code) {
      player.ships[i] = ship_t(player.ships[i].size, p1, p2);
      set_ship_coords_on_map(player.map, player.ships[i]);
      i++;
    }
    else {
      print_invalid_coords_error_code(error_code);
      if(error_code == 3) {
        return -1;
      }
    }
  }

  return 0;
}

int create_random_map(player_t &player) {
  player.map = new TileState *[player.map_size]; // TODO prevent fragmentation of memory
  for(int i = 0; i < player.map_size; i++) {
    player.map[i] = new TileState[player.map_size];
    for(int j = 0; j < player.map_size; j++) {
      player.map[i][j] = TileState::Water;
    }
  }

  for(int i = 0; i < player.ships_count;) {
    point_t p1, p2;

    // Formula: (rand() % (ub - lb + 1)) + lb
    int x = rand() % player.map_size;
    int y = rand() % player.map_size;

    p1 = point_t(x, y);
    // Horizontal or vertical ship
    if(rand() % 2) { // Same y - horizontal ship
      // Going left or right from first point
      x = (rand() % 2) ? (x - player.ships[i].size - 1) : (x + player.ships[i].size - 1);
    }
    else { // Same x - vertical ship
      // Going down or up from first point
      y = (rand() % 2) ? (x - player.ships[i].size - 1) : (x + player.ships[i].size - 1);
    }
    p2 = point_t(x, y);

    std::cout << "Random points: " << p1.x << " " << p1.y << ", " << p2.x << " " << p2.y << "\n";

    ship_t::fix_start_end_coords(p1, p2);

    int error_code = validate_ship_coords(player.map, player.map_size, player.ships[i].size, p1, p2);

    if(!error_code) {
      player.ships[i] = ship_t(player.ships[i].size, p1, p2);
      set_ship_coords_on_map(player.map, player.ships[i]);
      i++;
    }
    else if(error_code == 3) {
      print_invalid_coords_error_code(error_code);
      return -1;
    }
  }

  return 0;
}

int generate_map(player_t &player, Placement ship_placement) {
  switch (ship_placement) {
    case Placement::CreateCustom: {
      if(!create_custom_map(player)) {
        return -1;
      }
    }break;
    case Placement::LoadFromFile: {
//      if(!load_map_from_file()) {
//        return -1;
//      }
    }break;
    case Placement::Random: {
      if(!create_random_map(player)) {
        return -1;
      }
    }break;

    // TODO ask player to save map to file
  }

  // print_map(map, size); // TODO TEMP
  // Clear terminal so other player doesn't see coordinates entered
  // system("@cls||clear");;

  return 0;
}

void set_ship_coords_on_map(TileState **map, ship_t ship) {
  point_t p1 = ship.end_coords[0], p2 = ship.end_coords[1];

  // Vertical ship
  if(p1.x == p2.x) {
    for(int i = p1.y; i <= p2.y; i++) {
      map[i][p1.x] = TileState::Unhit;
    }
  }
    // Horizontal ship (y1 == y2)
  else {
    for(int i = p1.x; i <= p2.x; i++) {
      map[p1.y][i] = TileState::Unhit;
    }
  }
}