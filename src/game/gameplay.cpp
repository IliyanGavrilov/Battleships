#include "gameplay.hh"

bool check_win(player_t *p1, player_t *p2) {
  if(p2->get_ship_coords_count(TileState::Unhit) <= 0) {
    std::cout << "Player 1 wins!\n";
    return true;
  }
  if(p1->get_ship_coords_count(TileState::Unhit) <= 0) {
    std::cout << "Player 2 wins!\n";
    return true;
  }

  return false;
}

int game_loop(player_t p1, player_t p2, Mode mode, SuccessfulHit successfulHit, Difficulty difficulty, Randomness randomness) {
  while(true) {
    // Player 1's turn
    while(play_turn(&p2) && successfulHit == SuccessfulHit::RepeatTurn);

    if(check_win(&p1, &p2)) {
      break;
    }

    // Player 2's turn
    if (mode == Mode::Singleplayer) {
      while(play_turn(&p1, &difficulty, &randomness) && successfulHit == SuccessfulHit::RepeatTurn);
    }
    else {
      while(play_turn(&p1) && successfulHit == SuccessfulHit::RepeatTurn);
    }

    if(check_win(&p1, &p2)) {
      break;
    }

    // Ask to save game
    int iSaveToFile;
    std::cout << "Do you want to save the correct game state to a file? (1, 2)";
    std::cin >> iSaveToFile;
    SaveToFile eSaveToFile = static_cast<SaveToFile>(iSaveToFile);

    // Write map to file
    if(eSaveToFile == SaveToFile::Save) {
      char filename[FILENAME_MAX];
      std::cout << "Filename: ";
      std::cin >> filename;

      int error_code = save_game_to_file(FileHandling::All, filename, &p1, &p2, &mode,
                                         &successfulHit, &difficulty, &randomness);
      if(!error_code) {
        print_file_errors(error_code);
        return -1;
      }
    }
  }

  return 0;
}

// Returns true upon a successful ship hit
bool play_turn(player_t *opponent, Difficulty *difficulty, Randomness *randomness) {
  bool return_val;

  // Formula: (rand() % (ub - lb + 1)) + lb
  // 10% chance for bot to *cheat* and hit ship directly (increases by 15% each time it misses a ship)
  static int chance_to_cheat = 10;

  opponent->print_map();

  // Make a move
  point_t shot = get_shot_coords(opponent, difficulty, randomness, chance_to_cheat);

  // Update board and if shot hit or missed
  return_val = opponent->shoot_at(shot);

  // Increase or reset chance to cheat
  if(*randomness == Randomness::Rigged) {
    // If shot missed increase chance by 15%
    if (!return_val) {
      chance_to_cheat += 15;
    }
    // If shot successfully hit a ship reset chance back to 10%
    else {
      chance_to_cheat = 10;
    }
  }

  opponent->print_map();

  // End game if all ships have been hit
  if(return_val && opponent->get_ship_coords_count(TileState::Unhit) == 0) {
    return false;
  }

  return return_val;
}

point_t get_shot_coords(player_t *opponent, Difficulty *difficulty, Randomness *randomness, int chance_to_cheat) {
  point_t shot;

  // Bot move
  if(difficulty != nullptr && randomness != nullptr) {
    switch(*difficulty) {
      case Easy: { // Random shot
        shot = get_shot_from_easy_or_hard_bot(opponent, randomness, difficulty, chance_to_cheat);
      }break;
      case Medium: { // If last shot was hit then try sinking the ship fully, otherwise random shot
        if(opponent->get_ship_coords_count(TileState::Hit) > 0) {
          shot = sink_found_ships(opponent);
        }
        else {
          shot = get_shot_from_easy_or_hard_bot(opponent, randomness, difficulty, chance_to_cheat);
        }
      }break;
      case Hard: { // Medium bot, but instead of random shot it shoots every n tiles (n is the smallest ship size left)
        if(opponent->get_ship_coords_count(TileState::Hit) > 0) {
          shot = sink_found_ships(opponent);
        }
        else {
          get_shot_from_easy_or_hard_bot(opponent, randomness, difficulty, chance_to_cheat);
        }
      }break;
      case Impossible: { // Cheats every shot
        point_t *all_unhit_ship_coords = opponent->get_unhit_ship_coords();
        shot = get_random_ship_tile_coords(opponent, all_unhit_ship_coords);
      }break;
    }
  }
  // Player move
  else {
    int error_code;

    do {
      std::cout << "Shoot at (x, y): ";
      std::cin >> shot.x >> shot.y;
      error_code = validate_shot_coords(opponent, shot, true);
      if(!error_code) {
        print_invalid_coords_error_code(error_code);
      }
    } while (error_code);
  }

  return shot;
}

point_t get_shot_from_easy_or_hard_bot(player_t *opponent, Randomness *randomness, Difficulty *difficulty, int chance_to_cheat) {
  point_t shot;

  if(*randomness == Randomness::Rigged) {
    point_t *all_ship_coords = opponent->get_unhit_ship_coords();

    if(rand() % 100 < chance_to_cheat) { // Random ship coordinate (cheat)
      shot = get_random_ship_tile_coords(opponent, all_ship_coords);
    }
    else { // Random shot (EASY & MEDIUM) or every n tile shot (HARD)
      if(*difficulty != Difficulty::Hard) {
        shot = get_random_coords_for_shot(opponent);
      }
      else {
        shot = get_parity_shot(opponent);
      }
    }
  }
  else { // Random shot (EASY & MEDIUM) or every n tile shot (HARD)
    if(*difficulty != Difficulty::Hard) {
      shot = get_random_coords_for_shot(opponent);
    }
    else {
      shot = get_parity_shot(opponent);
    }
  }

  return shot;
}

point_t get_random_coords_for_shot(player_t *opponent) {
  int error_code;
  point_t shot;

  do {
    int x = rand() % opponent->map_size;
    int y = rand() % opponent->map_size;
    shot = point_t(x, y);

    error_code = validate_shot_coords(opponent, shot, true);
  } while (error_code);

  return shot;
}

// Shoot every n tiles instead of randomly (where n is the size of the smallest ship that is still unhit)
point_t get_parity_shot(player_t *opponent) {
  point_t shot;
  bool found = false;
  int smallestShipSize = opponent->get_smallest_ship_size();

  for (int x = 0; x < opponent->map_size; x += 1) {
    for (int y = x % smallestShipSize; y < opponent->map_size; y += smallestShipSize) {
      if(opponent->map[x][y] == TileState::Water) {
        shot = point_t(x, y);
        found = true;
        break;
      }
    }
    if(found) {
      break;
    }
  }

  return shot;
}

point_t get_random_ship_tile_coords(player_t *opponent, point_t *all_unhit_ship_coords) {
  int error_code;
  point_t shot;

  do {
    shot = all_unhit_ship_coords[rand() % opponent->get_ship_coords_count(TileState::Unhit)];
    error_code = validate_shot_coords(opponent, shot, true);
  } while(error_code);

  return shot;
}

point_t sink_found_ships(player_t *opponent) {
  point_t shot, unhit_tile;
  bool found = false;

  // Get first hit ship tile
  for(int i = 0; i < opponent->map_size; i++) {
    for(int j = 0; j < opponent->map_size; j++) {
      if(opponent->map[i][j] == TileState::Hit) {
        unhit_tile = point_t(i, j);
        found = true;
        break;
      }
    }
    if(found) {
      break;
    }
  }

  // Try going every direction (top, down, right, left) until miss
  int dx[] = {0, 0, 1, -1};
  int dy[] = {1, -1, 0, 0};

  for(int i = 0; i < DIRECTIONS_COUNT; i++) {
    int newX = unhit_tile.x + dx[i];
    int newY = unhit_tile.y + dy[i];

    // Stop going that direction and try next one if the tile is sunken or missed or out of map
    while (!validate_shot_coords(opponent, point_t(newX, newY), false)) {
      // Shoot if space is available
      if (opponent->map[newX][newY] == TileState::Unhit || opponent->map[newX][newY] == TileState::Water) {
        return {newX, newY};
      }

      newX += dx[i];
      newY += dy[i];
    }
  }

  return shot;
}