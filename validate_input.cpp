#include "validate_input.hh"

bool validate_input(int size, GameType gameType, SuccessfulHit successfulHit, Mode mode, Difficulty difficulty, Randomness randomness) {
  // Check game type
  if(gameType != GameType::Load && gameType != GameType::New) {
    return false;
  }

  // Check to repeat turn or not after a successful ship hit
  if(successfulHit != SuccessfulHit::RepeatTurn && successfulHit != SuccessfulHit::SwitchTurn) {
    return false;
  }

  // Check map size
  if(size < MIN_SIZE || size > MAX_SIZE) {
    return false;
  }

  // Check game mode
  if(mode != Mode::Singleplayer && mode != Mode::Multiplayer) {
    return false;
  }

  // Check difficulty of bot
  if(difficulty != Difficulty::Easy && difficulty != Difficulty::Medium && difficulty != Difficulty::Hard && difficulty != Difficulty::Impossible) {
    return false;
  }

  // Check if bot can cheat/if randomness is rigged
  if(randomness != Randomness::Normal && randomness != Randomness::Rigged) {
    return false;
  }

  return true;
}

bool validate_ship_placement(Placement ship_placement) {
  // Check ship placement
  if(ship_placement != Placement::CreateCustom && ship_placement != Placement::LoadFromFile && ship_placement != Placement::Random) {
    return false;
  }

  return true;
}

// Validate placement input
Placement get_placement() {
  int iPlacement;
  Placement ePlacement;
  do {
    // Ship placement
    std::cout << "Create custom(1), load from file (2) or random placement(3)? ";
    std::cin >> iPlacement;
    ePlacement = static_cast<Placement>(iPlacement);
  } while(!validate_ship_placement(ePlacement));

  return ePlacement;
}

int validate_ship_coords(TileState ** map, int map_size, int ship_size, point_t p1, point_t p2) {
  // Coordinates are outside of map
  if(p1.x < 0 || p1.x >= map_size || p2.x < 0 || p2.x >= map_size || p1.y < 0 || p1.y >= map_size || p2.y < 0 || p2.y >= map_size) {
    return 1;
  }

  // Coordinates not on same row/column
  if(p1.x != p2.x && p1.y != p2.y) {
    return 2;
  }

  // Vertical ship
  if(p1.x == p2.x) {
    // If given coordinates can fit ship perfectly
    if(p2.y - p1.y + 1 != ship_size) {
      return 3;
    }

    for(int i = p1.y; i <= p2.y; i++) {
      if(map[i][p1.x] != TileState::Water) {
        return 4;
      }
    }
  }
    // Horizontal ship (y1 == y2)
  else {
    // If given coordinates can fit ship perfectly
    if(p2.x - p1.x + 1 != ship_size) {
      return 3;
    }

    for(int i = p1.x; i <= p2.x; i++) {
      if(map[p1.y][i] != TileState::Water) {
        return 4;
      }
    }
  }

  return 0;
}