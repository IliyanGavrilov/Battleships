#include "get_input.hh"

int get_input() {
  int total_ships_count;
  int gameType = 0, map_size = 0, successfulHit = 0, mode = 0, difficulty = 1,  randomness = 1;

  game_settings_t settings[] = {
    game_settings_t(&gameType, "Select game type:\n1. New game\n2. Load game from file\n", validate_game_type),
    game_settings_t(&map_size, "Field size [" + std::to_string(MIN_SIZE) + ", " + std::to_string(MAX_SIZE) + "]:\n", validate_map_size),
    game_settings_t(&successfulHit, "Does player repeat his turn (go again) after a successful hit (hitting a ship)?\n1. Yes\n2. No\n",
                      validate_successful_hit),
    game_settings_t(&mode, "Select mode:\n1. Singleplayer\n2. Multiplayer\n", validate_mode),
    game_settings_t(&difficulty, "Select difficulty:\n1. Easy\n2. Medium\n3. Hard\n4. Impossible\n", validate_difficulty),
    game_settings_t(&randomness, "Can computer *cheat*?\n1. Yes\n2. No\n", validate_randomness)};


  for (game_settings_t &setting : settings) {
    // If GameType is load from file OR
    // If Multiplayer mode is selected skip Difficulty and Randomness settings OR
    // If Difficulty selected is Impossible skip bot cheating option
    if ((GameType) gameType == GameType::Load || (Mode) mode == Mode::Multiplayer || (Difficulty) difficulty == Difficulty::Impossible) {
      break;
    }

    bool correct_input;
    do {
      std::cout << setting.message;
      std::cin >> *setting.game_setting;

      // Input isn't of type int (less than 4 bytes written error handling)
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }

      correct_input = setting.input_validation_func(*setting.game_setting);
      if (!correct_input) {
        clear_screen();
        std::cerr << "Invalid input!\n";
      }
    } while (!correct_input);

    clear_screen();
  }

  // Load new game
  if ((GameType) gameType == GameType::New) {
    // Amount of ships to place
    std::vector<ship_t> ships;
    total_ships_count = get_amount_of_ships_to_place(ships, map_size);

    if (start_game(ships, total_ships_count, map_size, (SuccessfulHit) successfulHit,
                   (Mode) mode, (Difficulty) difficulty, (Randomness) randomness)) {
      return -1;
    }
  }
  // Load ongoing game from file
  else {
    Mode eMode;
    SuccessfulHit eSuccessfulHit;
    Difficulty eDifficulty;
    Randomness eRandomness;

    player_t player1, player2;

    char filename[FILENAME_MAX];
    std::cout << "Filename: ";
    std::cin >> filename;

    int error_code = load_game_from_file(FileHandling::All, filename, player1, &player2,
                                         &eMode, &eSuccessfulHit, &eDifficulty, &eRandomness);

    if (!error_code) {
      game_loop(player1, player2, eMode, eSuccessfulHit, &eDifficulty, &eRandomness);
    }
    else {
      print_file_errors(error_code);
      return -1;
    }
  }

  return 0;
}

int get_amount_of_ships_to_place(std::vector<ship_t> &ships, int map_size) {
  int curr_ship_index, total_spaces_occupied_by_ships, total_ships_count;

  while (true) {
    curr_ship_index = 0;
    total_spaces_occupied_by_ships = 0;
    total_ships_count = 0;

    for (int boat_type = ShipTypes::Destroyer; boat_type != ShipTypes::Last;) {
      int count = 0;
      std::cout << "How many " << valueToEnumName((ShipTypes) boat_type) <<
                "s (size " << boat_type << ") do you want each player to have?\n";
      std::cin >> count;

      // Input isn't of type int (less than 4 bytes written error handling)
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }

      if (count < 0) {
        std::cerr << "Can't place negative amount of ships!\n";
        continue;
      }

      total_ships_count += count;
      total_spaces_occupied_by_ships += count * boat_type;

      if (total_spaces_occupied_by_ships > MAX_SHIP_COVERAGE * (map_size * map_size)) {
        clear_screen();
        std::cerr << "You've entered too many ships! Ships must occupy less than 85% of the map!\n";

        // Reset and continue
        ships.clear();
        curr_ship_index = 0;
        total_spaces_occupied_by_ships = 0;
        total_ships_count = 0;
        boat_type = ShipTypes::Destroyer;

        continue;
      }

      // Save inputted ships
      count += curr_ship_index;
      for (; curr_ship_index < count; curr_ship_index++) {
        ships.emplace_back(boat_type);
      }
      boat_type++;
    }

    // Input ships again if no ships have been entered
    if (total_ships_count <= 0) {
      std::cerr << "Must have at least 1 ship to start the game!\n";
      ships.clear();
      clear_screen();
    }
    else {
      break;
    }
  }

  return total_ships_count;
}