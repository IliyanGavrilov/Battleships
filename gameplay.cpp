#include "gameplay.hh"

void game_loop(player_t p1, player_t p2, Mode mode, SuccessfulHit successfulHit, Difficulty difficulty, Randomness randomness) {
  while(1) {
    // TODO Ask to save game

    while(play_turn(&p2) && successfulHit == SuccessfulHit::RepeatTurn);
    if (mode == Mode::Singleplayer) {
      while(play_turn(&p1, &difficulty, &randomness) && successfulHit == SuccessfulHit::RepeatTurn);
    } else {
      while(play_turn(&p1) && successfulHit == SuccessfulHit::RepeatTurn);
    }
  }
}

// Returns true upon a successful ship hit
bool play_turn(player_t *opponent, Difficulty *difficulty, Randomness *randomness) {
  bool return_val;
  point_t shot;

  // Formula: (rand() % (ub - lb + 1)) + lb
  // 10% chance for bot to *cheat* and hit ship directly (increases by 15% each time it misses a ship)
  static int chance_to_cheat = 10;

  static bool successful_last_hit = false;

  opponent->print_map();

  // Bot move
  if(difficulty != nullptr && randomness != nullptr) {
    if(!successful_last_hit && *randomness == Randomness::Rigged) {
      point_t *all_ship_coords = opponent->get_unhit_ship_coords();

      if(rand() % 100 < chance_to_cheat) { // Random ship coordinate
        shot = all_ship_coords[rand() % opponent->get_ship_coords_count()];
      }
      else { // Random shot
        shot = get_random_coords_for_shot(opponent);
      }
    }

    switch(*difficulty) {
      case Easy: // Random shot
        break;
      case Medium: // Random shot, but if last shot was hit then try sinking the ship fully
        break;
      case Hard: // Medium bot, but instead of random shot it shoots every n tiles (n is the smallest ship size left)
        break;
      case Impossible: // Cheats every shot
        break;
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
  if(*difficulty == Difficulty::Medium || *difficulty == Difficulty::Hard) {
    successful_last_hit = return_val;
  }

  opponent->print_map();

  return return_val;
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