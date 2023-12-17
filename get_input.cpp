#include "get_input.hh"

int get_input() {
  // Get input as int or char to convert it to enum afterwards
  int map_size, iDifficulty, iGameType;
  char cMode, cRandomness, cSuccessfulHit;

  Difficulty eDifficulty = Difficulty::Easy;
  Randomness eRandomness = Randomness::Normal;

  std::cout << "New game (1) or load game from file (2)? \n";
  std::cin >> iGameType;
  GameType eGameType = static_cast<GameType>(iGameType);

  std::cout << "Does player repeat his turn (go again) after a successful hit (hitting a ship)? (y, n) ";
  std::cin >> cSuccessfulHit;
  SuccessfulHit eSuccessfulHit = static_cast<SuccessfulHit>(tolower(cSuccessfulHit));

  // Map size
  std::cout << "Field size (5, 20): ";
  std::cin >> map_size;

  // Amount of ships to place
  ship_t *ships = new ship_t[(map_size * map_size) / 2];
  int total_ships_count = 0;
  int curr_ship_index = 0;
  int total_spaces_occupied_by_ships = 0;

  for(int boat_type = BoatTypes::Destroyer; boat_type != BoatTypes::Last; boat_type++) {
    int count = 0;
    std::cout << "How many ships with size " << boat_type << " do you want each player to have?";
    std::cin >> count;

    total_ships_count += count;
    total_spaces_occupied_by_ships += count * boat_type;

    if(total_spaces_occupied_by_ships > map_size * map_size) {
      std::cout << "You've entered too many ships to fit on the map!\n";
      return -1;
    }

    // Save inputted ships
    count += curr_ship_index;
    for(;curr_ship_index < count; curr_ship_index++) {
      ships[curr_ship_index].size = boat_type;
    }
  }

  // Game mode
  std::cout << "Singleplayer(S) or multiplayer(M)? ";
  std::cin >> cMode;
  Mode eMode = static_cast<Mode>(tolower(cMode));

  // Singleplayer computer options
  if(eMode == Mode::Singleplayer) {
    // Difficulty
    std::cout << "Select difficulty: 1. Easy 2. Medium 3. Hard 4. Impossible ";
    std::cin >> iDifficulty;
    eDifficulty = static_cast<Difficulty>(iDifficulty);

    if(eDifficulty != Difficulty::Impossible) {
      // Rigged computer randomness
      std::cout << "Can computer *cheat*? (y, n) ";
      std::cin >> cRandomness;
      eRandomness = static_cast<Randomness>(cRandomness);
    }
  }

  if(!validate_input(map_size, eGameType, eSuccessfulHit,
                     eMode, eDifficulty, eRandomness)) {
    std::cout << "Invalid input!\n";
    return -1;
  }

  start_game(ships, total_ships_count, map_size, eGameType,
             eSuccessfulHit, eMode, eDifficulty, eRandomness);

  return 0;
}