#include "validate_input.hh"

bool validate_game_type(int gameType) {
  // Check game type
  if ((GameType) gameType != GameType::Load && (GameType) gameType != GameType::New) {
    return false;
  }

  return true;
}

bool validate_map_size(int size) {
  // Check map size
  if (size < MIN_SIZE || size > MAX_SIZE) {
    return false;
  }

  return true;
}

bool validate_successful_hit(int successfulHit) {
  // Check to repeat turn or not after a successful ship hit
  if ((SuccessfulHit) successfulHit != SuccessfulHit::RepeatTurn && (SuccessfulHit) successfulHit != SuccessfulHit::SwitchTurn) {
    return false;
  }

  return true;
}

bool validate_mode(int mode) {
  // Check game mode
  if ((Mode) mode != Mode::Singleplayer && (Mode) mode != Mode::Multiplayer) {
    return false;
  }

  return true;
}

bool validate_difficulty(int difficulty) {
  // Check difficulty of bot
  if ((Difficulty) difficulty != Difficulty::Easy && (Difficulty) difficulty != Difficulty::Medium &&
      (Difficulty) difficulty != Difficulty::Hard && (Difficulty) difficulty != Difficulty::Impossible) {
    return false;
  }

  return true;
}

bool validate_randomness(int randomness) {
  // Check if bot can cheat/if randomness is rigged
  if ((Randomness) randomness != Randomness::Normal && (Randomness) randomness != Randomness::Rigged) {
    return false;
  }

  return true;
}

bool validate_ship_placement(Placement ship_placement) {
  // Check ship placement
  if (ship_placement != Placement::CreateCustom && ship_placement != Placement::LoadFromFile && ship_placement != Placement::Random) {
    return false;
  }

  return true;
}

// Validate placement input
Placement get_placement() {
  int iPlacement;
  Placement ePlacement;

  bool correct_input;
  do {
    // Ship placement (Map type)
    std::cout << "Select option:\n1. Create custom map\n2. Load map from file\n3. Random generation\n";
    std::cin >> iPlacement;

    // Input isn't of type int (less than 4 bytes written error handling)
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    ePlacement = (Placement) iPlacement;

    correct_input = validate_ship_placement(ePlacement);
    if (!correct_input) {
      clear_screen();
      std::cerr << "Invalid input!\n";
    }
  } while (!correct_input);

  return ePlacement;
}

int validate_ship_coords(const std::vector<std::vector<TileState>> &map, int map_size, int ship_size, const point_t &p1,
                         const point_t &p2) {
  // Coordinates are outside of map
  if (p1.x < 0 || p1.x >= map_size || p2.x < 0 || p2.x >= map_size || p1.y < 0 || p1.y >= map_size || p2.y < 0 || p2.y >= map_size) {
    return 1;
  }

  // Coordinates not on same row/column
  if (p1.x != p2.x && p1.y != p2.y) {
    return 2;
  }

  // Coordinates don't correspond to size a.k.a. coordinates can't fit ship perfectly
  // Horizontal OR vertical cases
  if ((p1.x == p2.x && p2.y - p1.y + 1 != ship_size) || (p1.y == p2.y && p2.x - p1.x + 1 != ship_size)) {
    return 3;
  }

  // Custom amount of ships - if player can't fit any more of this type of ships end inputting
  if (!can_ship_fit_on_map(map, map_size, ship_size)) {
    return 4;
  }

  // Another ship between given points
  for (int i = p1.y; i <= p2.y; i++) {
    for (int j = p1.x; j <= p2.x; j++) {
      if (map[i][j] != TileState::Water) {
        return 5;
      }
    }
  }

  return 0;
}

bool can_ship_fit_on_map(const std::vector<std::vector<TileState>> &map, int map_size, int ship_size) {
  int count_horizontal_tiles, count_vertical_tiles;

  for (int i = 0; i < map_size; i++) {
    for (int j = 0; j < map_size; j++) {
      count_horizontal_tiles = 1;
      count_vertical_tiles = 1;

      // Check for adjacent free spaces(water) on the same row
      for (int l = j + 1; l < map_size; l++) {
        if (count_horizontal_tiles >= ship_size) {
          return true;
        }

        if (map[i][j] == TileState::Water && map[i][l] == map[i][j]) {
          count_horizontal_tiles++;
        }
        else {
          break;
        }
      }

      // Check for adjacent free spaces(water) on the same column
      for (int l = i + 1; l < map_size; l++) {
        if (count_vertical_tiles >= ship_size) {
          return true;
        }

        if (map[i][j] == TileState::Water && map[l][j] == map[i][j]) {
          count_vertical_tiles++;
        }
        else {
          break;
        }
      }

      if (count_horizontal_tiles >= ship_size || count_vertical_tiles >= ship_size) {
        return true;
      }
    }
  }

  return false;
}

// Flag is used in the computer's sinking the hit ship logic so that the
// loop continues when the tile is hit
int validate_shot_coords(const player_t &player, const point_t &shot, bool flag) {
  // Coordinates are outside of map
  if (shot.x < 0 || shot.x >= player.map_size || shot.y < 0 || shot.y >= player.map_size) {
    return 1;
  }

  // Already hit tile
  if ((player.map[shot.y][shot.x] == TileState::Hit && flag) || player.map[shot.y][shot.x] == TileState::Miss ||
     player.map[shot.y][shot.x] == TileState::Sunken) {
    return 6;
  }

  return 0;
}

void print_invalid_coords_error_code(int error_code) {
  std::cerr << "Invalid coordinates - ";
  switch (error_code) {
    case 1: std::cerr << "Coordinates are outside of the map!\n";break;
    case 2: std::cerr << "Coordinates not lying on same row/column!\n";break;
    case 3: std::cerr << "Coordinates do not match ship size!\n";break;
    case 4: std::cerr << "Ship cannot fit anywhere on the map! Add less ships next time! Exiting game!\n";break;
    case 5: std::cerr << "There is a ship lying between the given points!\n";break;
    default: std::cerr << "You have already hit that tile! Please choose another point!\n";break; // case 6
  }
}

void print_file_errors(int error_code) {
  switch (error_code) {
    case 1: std::cerr << "File with given name does not exist!\n";break;
    case 2: std::cerr << "File is empty!\n";break;
    case 3: std::cerr << "File is not empty!\n";break;
    case 4: std::cerr << "Invalid file information! Given input and file information might not be matching!\n";break;
    default: std::cerr << "Error while opening file!\n";break; // case 5
  }
}

// Clear terminal
void clear_screen() {
  system("@cls||clear");
}

unsigned char to_lower(char c)
{
  if (c >= 'A' && c <= 'Z')
    return c | 0x20;
  return c;
}