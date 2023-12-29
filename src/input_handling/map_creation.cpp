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
      // Not enough space on map to place ship, so we exit the game
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
      char filename[FILENAME_MAX];
      std::cout << "Filename: ";
      std::cin >> filename;

      // Load map and ships into player struct
      int error_code = load_game_from_file(FileHandling::PlayerInfo, filename, &player);
      if(!error_code) {
        print_file_errors(error_code);
        return -1;
      }
    }break;
    case Placement::Random: {
      std::cout << "Generating random map. Please wait . . .\n";
      if(!create_random_map(player)) {
        return -1;
      }
    }break;
  }
  // TODO ask player to save map to file
  player.print_map();

  int iSaveToFile;
  std::cout << "Do you want to save this map to a file? (1, 2)";
  std::cin >> iSaveToFile;
  SaveToFile eSaveToFile = static_cast<SaveToFile>(iSaveToFile);

  char filename[FILENAME_MAX];
  std::cout << "Filename: ";
  std::cin >> filename;

  // Write map to file
  if(eSaveToFile == SaveToFile::Save) {
    int error_code = save_game_to_file(FileHandling::PlayerInfo, filename, &player);
    if(!error_code) {
      print_file_errors(error_code);
      return -1;
    }
  }

  // TODO TEMP
  // Clear terminal so other player doesn't see coordinates entered
  // system("@cls||clear");;

  return 0;
}

void set_ship_coords_on_map(TileState **map, ship_t ship) {
  point_t start = ship.end_coords[0], end = ship.end_coords[1];

  for (int i = start.x; i <= end.x; ++i) {
    for (int j = start.y; j <= end.y; ++j) {
      map[i][j] = TileState::Unhit;
    }
  }
}