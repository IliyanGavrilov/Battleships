#include "gameplay.hh"

bool check_win(player_t *p1, player_t *p2) {
  if(p2->get_ship_coords_count() <= 0) {
    std::cout << "Player 1 wins!\n";
    return true;
  }
  if(p1->get_ship_coords_count() <= 0) {
    std::cout << "Player 2 wins!\n";
    return true;
  }

  return false;
}

void game_loop(player_t p1, player_t p2, Mode mode, SuccessfulHit successfulHit, Difficulty difficulty, Randomness randomness) {
  while(true) {
    // TODO Ask to save game

    while(play_turn(&p2) && successfulHit == SuccessfulHit::RepeatTurn);

    if(check_win(&p1, &p2)) {
      break;
    }

    if (mode == Mode::Singleplayer) {
      while(play_turn(&p1, &difficulty, &randomness) && successfulHit == SuccessfulHit::RepeatTurn);
    }
    else {
      while(play_turn(&p1) && successfulHit == SuccessfulHit::RepeatTurn);
    }

    if(check_win(&p1, &p2)) {
      break;
    }
  }
}

// Returns true upon a successful ship hit
bool play_turn(player_t *opponent, Difficulty *difficulty, Randomness *randomness) {
  bool return_val;

  // Formula: (rand() % (ub - lb + 1)) + lb
  // 10% chance for bot to *cheat* and hit ship directly (increases by 15% each time it misses a ship)
  static int chance_to_cheat = 10;
  static bool successful_last_shot = false;

  opponent->print_map();

  // Make a move
  point_t shot = get_shot_coords(opponent, difficulty, randomness, chance_to_cheat, successful_last_shot);

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

  // If a ship is found try to sink it fully (Bot difficulties Medium & Hard)
  successful_last_shot = return_val;

  opponent->print_map();

  // End game if all ships have been hit
  if(return_val && opponent->get_ship_coords_count() == 0) {
    return false;
  }

  return return_val;
}

point_t get_shot_coords(player_t *opponent, Difficulty *difficulty, Randomness *randomness, int chance_to_cheat, bool successful_last_shot) {
  point_t shot;

  // Bot move
  if(difficulty != nullptr && randomness != nullptr) {
    switch(*difficulty) {
      case Easy: { // Random shot
        shot = get_shot_from_easy_or_hard_bot(opponent, randomness, difficulty, chance_to_cheat);
      }break;
      case Medium: { // If last shot was hit then try sinking the ship fully, otherwise random shot
        if(successful_last_shot) {
          // TODO
        }
        else {
          shot = get_shot_from_easy_or_hard_bot(opponent, randomness, difficulty, chance_to_cheat);
        }
      }break;
      case Hard: { // Medium bot, but instead of random shot it shoots every n tiles (n is the smallest ship size left)
        if(successful_last_shot) {
          // TODO
        }
        else {
          get_shot_from_easy_or_hard_bot(opponent, randomness, difficulty, chance_to_cheat);
        }
      }break;
      case Impossible: { // Cheats every shot
        point_t *all_ship_coords = opponent->get_unhit_ship_coords();
        shot = get_random_ship_tile_coords(opponent, all_ship_coords);
      }break;
    }
  }
  // Player move
  else {
    int error_code;

    do {
      std::cout << "Shoot at (x, y): ";
      std::cin >> shot.x >> shot.y;
      error_code = validate_shot_coords(opponent, shot);
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

    error_code = validate_shot_coords(opponent, shot);
  } while (error_code);

  return shot;
}

// Shoot every n tiles instead of randomly (where n is the size of the smallest ship that is still unhit)
point_t get_parity_shot(player_t *opponent) {
  point_t shot;
  bool flag = false;
  int smallestShipSize = opponent->get_smallest_ship_size();

  for (int x = 0; x < opponent->map_size; x += 1) {
    for (int y = x % smallestShipSize; y < opponent->map_size; y += smallestShipSize) {
      if(opponent->map[x][y] == TileState::Water) {
        shot = point_t(x, y);
        flag = true;
        break;
      }
    }
    if(flag) {
      break;
    }
  }

  return shot;
}

point_t get_random_ship_tile_coords(player_t *opponent, point_t *all_ship_coords) {
  int error_code;
  point_t shot;

  do {
    shot = all_ship_coords[rand() % opponent->get_ship_coords_count()];
    error_code = validate_shot_coords(opponent, shot);
  } while(error_code);

  return shot;
}