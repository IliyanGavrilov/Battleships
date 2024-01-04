#include "map_creation.hh"

int create_custom_map(player_t &player) {
  for (int i = 0; i < player.ships_count;) {
    point_t p1, p2;
    std::cout << "Place ship with size " << player.ships[i].size << " (x1 y1 x2 y2) [1, " << player.map_size << "]\n";
    std::cin >> p1.x >> p1.y >> p2.x >> p2.y;

    // Fix coords to start from 0
    p1.x--;
    p1.y--;
    p2.x--;
    p2.y--;

    ship_t::fix_start_end_coords(p1, p2);

    int error_code = validate_ship_coords(player.map, player.map_size, player.ships[i].size, p1, p2);

    if (!error_code) {
      player.ships[i] = ship_t(player.ships[i].size, p1, p2);
      set_ship_coords_on_map(player.map, player.ships[i]);
      print_map(player.map, player.map_size, false);
      i++;
    }
    else {
      print_invalid_coords_error_code(error_code);
      // Not enough space on map to place ship, so we exit the game
      if (error_code == 4) {
        return -1;
      }
    }
  }

  return 0;
}

int create_random_map(player_t &player) {
  for (int i = 0; i < player.ships_count;) {
    point_t p1, p2;

    // Formula: (rand() % (ub - lb + 1)) + lb
    int x = rand() % player.map_size;
    int y = rand() % player.map_size;

    p1 = point_t(x, y);
    // Horizontal or vertical ship
    if (rand() % 2) { // Same y - horizontal ship
      // Going left or right from first point
      x += (rand() % 2) ? (-player.ships[i].size - 1) : (player.ships[i].size - 1);
    }
    else { // Same x - vertical ship
      // Going down or up from first point
      y += (rand() % 2) ? (-player.ships[i].size - 1) : (player.ships[i].size - 1);
    }
    p2 = point_t(x, y);

    ship_t::fix_start_end_coords(p1, p2);

    int error_code = validate_ship_coords(player.map, player.map_size, player.ships[i].size, p1, p2);

    if (!error_code) {
      player.ships[i] = ship_t(player.ships[i].size, p1, p2);
      set_ship_coords_on_map(player.map, player.ships[i]);
      i++;
    }
    else if (error_code == 4) {
      i = 0;
      player.clear_map();
    }
  }

  return 0;
}

int generate_map(player_t &player, Placement ship_placement, Mode mode) {
  switch (ship_placement) {
    case Placement::CreateCustom: {
      if (create_custom_map(player)) {
        return -1;
      }
    }break;
    case Placement::LoadFromFile: {
      while (true) {
        char filename[FILENAME_MAX];
        std::cout << "Filename: ";
        std::cin >> filename;

        // Load map and ships into player struct
        int error_code = load_game_from_file(FileHandling::PlayerInfo, filename, player);
        if (error_code) {
          print_file_errors(error_code);
          if (error_code == 4) {
            return -1;
          }
        } else {
          std::cout << "Loaded map:\n";
          print_map(player.map, player.map_size, false);
          break;
        }
      }
    }break;
    case Placement::Random: {
      std::cout << "Generating random map. Please wait . . .\n";
      create_random_map(player);
    }break;
  }

  if (mode == Mode::Multiplayer && ship_placement != Placement::LoadFromFile) {
    // Saving map to file
    print_map(player.map, player.map_size, false);

    int iSaveToFile;
    std::cout << "Do you want to save this map to a file?\n1. Yes\n2. No\n";
    std::cin >> iSaveToFile;
    SaveToFile eSaveToFile = static_cast<SaveToFile>(iSaveToFile);

    // Write map to file
    if (eSaveToFile == SaveToFile::Save) {
      while (true) {
        char filename[FILENAME_MAX];
        std::cout << "Filename: ";
        std::cin >> filename;

        int error_code = save_game_to_file(FileHandling::PlayerInfo, filename, player);

        if (error_code) {
          print_file_errors(error_code);
        } else {
          std::cout << "Saved map to file successfully!\n";
          break;
        }
      }
    }
  }

  return 0;
}

void set_ship_coords_on_map(std::vector<std::vector<TileState>> &map, ship_t &ship) {
  point_t start = ship.end_coords[0], end = ship.end_coords[1];

  for (int i = start.y; i <= end.y; i++) {
    for (int j = start.x; j <= end.x; j++) {
      map[i][j] = TileState::Unhit;
    }
  }
}