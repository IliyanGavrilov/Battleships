#include "get_input.hh"

int get_input() {
  // Get input as int or char to convert it to enum afterwards
  int map_size, iDifficulty, iGameType, total_ships_count, iMode, iRandomness, iSuccessfulHit;
  SuccessfulHit eSuccessfulHit;
  Mode eMode;
  Difficulty eDifficulty = Difficulty::Easy;
  Randomness eRandomness = Randomness::Normal;

  std::cout << "New game (1) or load game from file (2)? \n";
  std::cin >> iGameType;
  GameType eGameType = static_cast<GameType>(iGameType);

  if (!validate_input(eGameType)) {
    std::cerr << "Invalid input!\n";
    return -1;
  }

  // Load new game
  if(eGameType == GameType::New) {
    std::cout << "Does player repeat his turn (go again) after a successful hit (hitting a ship)? (1, 2) ";
    std::cin >> iSuccessfulHit;
    eSuccessfulHit = static_cast<SuccessfulHit>(iSuccessfulHit);

    // Map size
    std::cout << "Field size (5, 20): ";
    std::cin >> map_size;

    // Amount of ships to place
    ship_t *ships = new ship_t[(map_size * map_size) / 2];
    total_ships_count = get_amount_of_ships_to_place(ships, map_size);

    // Game mode
    std::cout << "Singleplayer(1) or multiplayer(2)? ";
    std::cin >> iMode;
    eMode = static_cast<Mode>(iMode);

    // Singleplayer computer options
    if (eMode == Mode::Singleplayer) {
      // Difficulty
      std::cout << "Select difficulty: 1. Easy 2. Medium 3. Hard 4. Impossible ";
      std::cin >> iDifficulty;
      eDifficulty = static_cast<Difficulty>(iDifficulty);

      if (eDifficulty != Difficulty::Impossible) {
        // Rigged computer randomness
        std::cout << "Can computer *cheat*? (1, 2) ";
        std::cin >> iRandomness;
        eRandomness = static_cast<Randomness>(iRandomness);
      }
    }

    if (!validate_input(eGameType, map_size, eSuccessfulHit,
                        eMode, eDifficulty, eRandomness)) {
      std::cerr << "Invalid input!\n";
      return -1;
    }

    start_game(ships, total_ships_count, map_size, eSuccessfulHit,
               eMode, eDifficulty, eRandomness);
  }
  else { // Load ongoing game from file
    player_t player1, player2;

    char filename[FILENAME_MAX];
    std::cout << "Filename: ";
    std::cin >> filename;

    int error_code = load_game_from_file(FileHandling::All, filename, &player1, &player2,
                                         &eMode, &eSuccessfulHit, &eDifficulty, &eRandomness);

    if(!error_code) {
      game_loop(player1, player2, eMode, eSuccessfulHit, eDifficulty, eRandomness);
    }
    else {
      print_file_errors(error_code);
      return -1;
    }
  }

  return 0;
}

int get_amount_of_ships_to_place(ship_t *ships, int map_size) {
  int curr_ship_index = 0;
  int total_spaces_occupied_by_ships = 0;
  int total_ships_count = 0;

  for (int boat_type = BoatTypes::Destroyer; boat_type != BoatTypes::Last; boat_type++) {
    int count = 0;
    std::cout << "How many ships with size " << boat_type << " do you want each player to have?";
    std::cin >> count;

    total_ships_count += count;
    total_spaces_occupied_by_ships += count * boat_type;

    if (total_spaces_occupied_by_ships > map_size * map_size) {
      std::cerr << "You've entered too many ships to fit on the map!\n";
      return -1;
    }

    // Save inputted ships
    count += curr_ship_index;
    for (; curr_ship_index < count; curr_ship_index++) {
      ships[curr_ship_index].size = boat_type;
    }
  }

  return total_ships_count;
}