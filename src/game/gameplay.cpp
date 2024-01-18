// /**
// *
// * Solution to course project # 1
// * Introduction to programming course
// * Faculty of Mathematics and Informatics of Sofia University
// * Winter semester 2023/2024
// *
// * @author Iliyan Gavrilov
// * @idnumber 6MI0600293
// * @compiler GCC
// *
// * <file with functions executed during gameplay>
// *
// *
//

#include "gameplay.hh"

bool check_win(const player_t &p1, const player_t &p2) {
  if (p2.ships_count <= 0) {
    std::cout << WHITE_T << "Player 1 wins!\n" << RESET;
    return true;
  }
  if (p1.ships_count <= 0) {
    std::cout << WHITE_T << "Player 2 wins!\n" << RESET;
    return true;
  }

  return false;
}

void game_loop(player_t &p1, player_t &p2, Mode mode, SuccessfulHit successfulHit, const Difficulty *difficulty,
               const Randomness *randomness) {
  if (mode == Mode::Multiplayer) {
    difficulty = nullptr;
    randomness = nullptr;
  }

  while (true) {
    // Player 1's turn
    do {
      // clear_screen();
      std::cout << WHITE_B << RED_T << "Player 1's turn:\n" << RESET;

      // If player hit a ship AND option is on then player repeats his turn
    } while (play_turn(p2) && successfulHit == SuccessfulHit::RepeatTurn);


    if (check_win(p1, p2)) {
      break;
    }

    // Player 2's turn
    do {
      // clear_screen();
      std::cout << WHITE_B << RED_T <<  "Player 2's turn:\n" << RESET;

      // If player hit a ship AND option is on then player repeats his turn
    } while (play_turn(p1, difficulty, randomness) && successfulHit == SuccessfulHit::RepeatTurn);

    if (check_win(p1, p2)) {
      break;
    }

    // Ask to save game
    int iSaveToFile;
    std::cout << "Do you want to save the current game state to a file?\n1. Yes\n2. No\n";
    std::cin >> iSaveToFile;
    SaveToFile eSaveToFile = (SaveToFile) iSaveToFile;

    // Write map to file
    if (eSaveToFile == SaveToFile::Save) {
      while (true) {
        char filename[FILENAME_MAX];
        std::cout << "Filename: ";
        std::cin >> filename;

        int error_code = save_game_to_file(FileHandling::All, filename, p1, &p2, &mode,
                                           &successfulHit, difficulty, randomness);
        if (error_code) {
          print_file_errors(error_code);
        } else {
          std::cout << "Saved game state to file successfully!\n";
          return;
        }
      }
    }
  }
}

// Returns true upon a successful ship hit
bool play_turn(player_t &opponent, const Difficulty *difficulty, const Randomness *randomness) {
  bool return_val;

  // Formula: (rand() % (ub - lb + 1)) + lb
  // 10% chance for bot to *cheat* and hit ship directly (increases by 15% each time it misses a ship)
  // Static so that it saves the chance on each call
  static int chance_to_cheat = 10;

  print_map(opponent.map, opponent.map_size, true);
  print_ship_sizes_left(opponent.ships);

  // Make a move
  point_t shot = get_shot_coords(opponent, difficulty, randomness, chance_to_cheat);

  // clear_screen(); // !!!

  // Update board and if shot hit or missed
  return_val = opponent.shoot_at(shot);

  // Increase or reset chance to cheat
  if (randomness != nullptr && *randomness == Randomness::Rigged) {
    // If shot missed increase chance by 15%
    if (!return_val) {
      chance_to_cheat += 15;
    }
    // If shot successfully hit a ship reset chance back to 10%
    else {
      chance_to_cheat = 10;
    }
  }

  print_map(opponent.map, opponent.map_size, true, &shot);
  print_ship_sizes_left(opponent.ships);

  // End game if all ships have been hit
  if (return_val && opponent.get_ship_coords_count(TileState::Unhit) == 0) {
    return false;
  }

  return return_val;
}

point_t get_shot_coords(const player_t &opponent, const Difficulty *difficulty, const Randomness *randomness, int chance_to_cheat) {
  point_t shot;

  // Bot move
  if (difficulty != nullptr && randomness != nullptr) {
    switch (*difficulty) {
      case Difficulty::Easy: { // Random shot
        shot = get_shot_from_easy_or_hard_bot(opponent, *randomness, *difficulty, chance_to_cheat);
      }break;
      // Medium (try sinking the ship fully) and hard (medium but instead of random shoots every n tiles (n is the smallest ship size)) bot
      default: {
        if (opponent.get_ship_coords_count(TileState::Hit) > 0) {
          shot = sink_found_ships(opponent);
        }
        else {
          shot = get_shot_from_easy_or_hard_bot(opponent, *randomness, *difficulty, chance_to_cheat);
        }
      }break;
      case Difficulty::Impossible: { // Cheats every shot
        point_t *all_unhit_ship_coords = opponent.get_unhit_ship_coords();
        shot = get_random_ship_tile_coords(opponent, all_unhit_ship_coords);
      }break;
    }
  }
  // Player move
  else {
    int error_code;

    do {
      char y;
      std::cout << "Shoot at (letter, number): [A, " << (char) ('A' + opponent.map_size - 1) << "], [1, " << opponent.map_size << "]\n";
      std::cin >> y >> shot.x;

      // Input isn't of type int (less than 4 bytes written error handling)
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }

      // Fix coords to start from 0 and letters to numbers
      shot.y = to_lower(y) - 'a';
      shot.x--;

      error_code = validate_shot_coords(opponent, shot, true);
      if (error_code) {
        print_invalid_coords_error_code(error_code);
      }
    } while (error_code);
  }

  return shot;
}

point_t get_shot_from_easy_or_hard_bot(const player_t &opponent, Randomness randomness, Difficulty difficulty, int chance_to_cheat) {
  point_t shot;

  if (randomness == Randomness::Rigged) {
    point_t *all_ship_coords = opponent.get_unhit_ship_coords();

    // Random ship coordinate (cheat)
    if (rand() % 100 < chance_to_cheat) {
      shot = get_random_ship_tile_coords(opponent, all_ship_coords);
    }
    // Random shot (EASY & MEDIUM) or every n tile shot (HARD)
    else {
      if (difficulty != Difficulty::Hard) {
        shot = get_random_coords_for_shot(opponent);
      }
      else {
        shot = get_parity_shot(opponent);
      }
    }
  }
  // Random shot (EASY & MEDIUM) or every n tile shot (HARD)
  else {
    if (difficulty != Difficulty::Hard) {
      shot = get_random_coords_for_shot(opponent);
    }
    else {
      shot = get_parity_shot(opponent);
    }
  }

  return shot;
}

point_t get_random_coords_for_shot(const player_t &opponent) {
  int error_code;
  point_t shot;

  do {
    int x = rand() % opponent.map_size;
    int y = rand() % opponent.map_size;
    shot = point_t(x, y);

    error_code = validate_shot_coords(opponent, shot, true);
  } while (error_code);

  return shot;
}

// Shoot every n tiles instead of randomly (where n is the size of the smallest ship that is still unhit)
point_t get_parity_shot(const player_t &opponent) {
  point_t shot;
  bool found = false;
  int smallestShipSize = opponent.get_smallest_ship_size();

  for (int x = 0; x < opponent.map_size; x++) {
    for (int y = x % smallestShipSize; y < opponent.map_size; y += smallestShipSize) {
      if (!validate_shot_coords(opponent, point_t(x, y), true)) {
        shot = point_t(x, y);
        found = true;
        break;
      }
    }
    if (found) {
      break;
    }
  }

  return shot;
}

point_t get_random_ship_tile_coords(const player_t &opponent, const point_t *all_unhit_ship_coords) {
  int error_code;
  point_t shot;

  do {
    shot = all_unhit_ship_coords[rand() % opponent.get_ship_coords_count(TileState::Unhit)];
    error_code = validate_shot_coords(opponent, shot, true);
  } while (error_code);

  return shot;
}

point_t sink_found_ships(const player_t &opponent) {
  point_t shot, hit_tile;
  bool found = false;

  // Get first hit ship tile
  for (int i = 0; i < opponent.map_size; i++) {
    for (int j = 0; j < opponent.map_size; j++) {
      if (opponent.map[i][j] == TileState::Hit) {
        hit_tile = point_t(j, i);
        found = true;
        break;
      }
    }
    if (found) {
      break;
    }
  }

  // Try going every direction (top, down, right, left) until miss
  int dx[] = {0, 0, 1, -1};
  int dy[] = {1, -1, 0, 0};

  for (int i = 0; i < DIRECTIONS_COUNT; i++) {
    int newX = hit_tile.x + dx[i];
    int newY = hit_tile.y + dy[i];

    // Stop going that direction and try next one if the tile is sunken or missed or out of map
    while (!validate_shot_coords(opponent, point_t(newX, newY), false)) {
      // Shoot if space is available
      if (opponent.map[newY][newX] == TileState::Unhit || opponent.map[newY][newX] == TileState::Water) {
        return {newX, newY};
      }

      // Continue iteration if tile is Hit
      newX += dx[i];
      newY += dy[i];
    }
  }

  return shot;
}