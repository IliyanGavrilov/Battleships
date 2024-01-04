#include "get_input.hh"

int get_input() {
  // Get input as int or char to convert it to enum afterwards
  int map_size, iDifficulty, iGameType, total_ships_count, iMode, iRandomness, iSuccessfulHit;
  SuccessfulHit eSuccessfulHit;
  Mode eMode;
  Difficulty eDifficulty = Difficulty::Easy;
  Randomness eRandomness = Randomness::Normal;

  std::cout << "Select game type:\n1. New game\n2. Load game from file\n";
  std::cin >> iGameType;
  GameType eGameType = static_cast<GameType>(iGameType);

  if (!validate_input(eGameType)) {
    std::cerr << "Invalid input!\n";
    return -1;
  }

  clear_screen();

  // Load new game
  if (eGameType == GameType::New) {
    std::cout << "Does player repeat his turn (go again) after a successful hit (hitting a ship)?\n1. Yes\n2. No\n";
    std::cin >> iSuccessfulHit;
    eSuccessfulHit = static_cast<SuccessfulHit>(iSuccessfulHit);

    clear_screen();

    // Map size
    std::cout << "Field size [" << MIN_SIZE << ", " << MAX_SIZE << "]:\n";
    std::cin >> map_size;

    clear_screen();

    // Amount of ships to place
    std::vector<ship_t> ships;
    total_ships_count = get_amount_of_ships_to_place(ships, map_size);

    if (total_ships_count <= 0) {
      return -1;
    }

    clear_screen();

    // Game mode
    std::cout << "Select mode:\n1. Singleplayer\n2. Multiplayer\n";
    std::cin >> iMode;
    eMode = static_cast<Mode>(iMode);

    clear_screen();

    // Singleplayer computer options
    if (eMode == Mode::Singleplayer) {
      // Difficulty
      std::cout << "Select difficulty:\n1. Easy\n2. Medium\n3. Hard\n4. Impossible\n";
      std::cin >> iDifficulty;
      eDifficulty = static_cast<Difficulty>(iDifficulty);

      clear_screen();

      if (eDifficulty != Difficulty::Impossible) {
        // Rigged computer randomness
        std::cout << "Can computer *cheat*?\n1. Yes\n2. No\n";
        std::cin >> iRandomness;
        eRandomness = static_cast<Randomness>(iRandomness);

        clear_screen();
      }
    }

    if (!validate_input(eGameType, map_size, eSuccessfulHit,
                        eMode, eDifficulty, eRandomness)) {
      std::cerr << "Invalid input!\n";
      return -1;
    }

    clear_screen();

    if (start_game(ships, total_ships_count, map_size, eSuccessfulHit,
               eMode, eDifficulty, eRandomness)) {
      return -1;
    }
  }
  // Load ongoing game from file
  else {
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
  int curr_ship_index = 0;
  int total_spaces_occupied_by_ships = 0;
  int total_ships_count = 0;

  for (int boat_type = ShipTypes::Destroyer; boat_type != ShipTypes::Last; boat_type++) {
    int count = 0;
    std::cout << "How many " << valueToEnumName(static_cast<ShipTypes>(boat_type)) <<
                 "s (size " << boat_type << ") do you want each player to have?\n";
    std::cin >> count;

    if (count < 0) {
      std::cerr << "Can't place negative amount of ships!\n";
      return -1;
    }

    total_ships_count += count;
    total_spaces_occupied_by_ships += count * boat_type;

    if (total_spaces_occupied_by_ships > 0.85 * (map_size * map_size)) {
      std::cerr << "You've entered too many ships! Ships must occupy less than 85% of the map!\n";
      return -1;
    }

    // Save inputted ships
    count += curr_ship_index;
    for (; curr_ship_index < count; curr_ship_index++) {
      ships.emplace_back(boat_type);
    }
  }

  return total_ships_count;
}