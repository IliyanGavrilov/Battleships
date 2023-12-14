#include <iostream>
#include <fstream>

#define MIN_SIZE 5
#define MAX_SIZE 20

using namespace std;

enum GameType {New = 1, Load = 2};
enum SuccessfulHit {RepeatTurn = 'y', SwitchTurn = 'n'};
enum Mode {Singleplayer = 's', Multiplayer = 'm'};
enum Difficulty {Easy = 1, Medium = 2, Hard = 3, Impossible = 4};
enum Randomness {Normal = 'n', Rigged = 'y'};
enum Placement {CreateCustom = 1, LoadFromFile = 2, Random = 3};
enum TileState {Water = '~', Unhit = '!', Hit = 'X', Miss = 'O', Sunken = '*'};

struct point_t {
  int x;
  int y;
};

struct ship_t {
  int size;
  point_t end_coords[2];
};

// Check input
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

void fix_start_end_coords(point_t &p1, point_t &p2) {
  if(p1.x > p2.x || p1.y > p2.y) {
    swap(p1.x, p2.x);
    swap(p1.y, p2.y);
  }
}

// TODO "const" TileState ** const map, const int size, const ship_t end_points
// TODO space between for () if () while () etc.
bool valid_coords(TileState ** map, int map_size, int ship_size, point_t p1, point_t p2) {
  // Coordinates are outside of map
  if(p1.x < 0 || p1.x >= map_size || p2.x < 0 || p2.x >= map_size || p1.y < 0 || p1.y >= map_size || p2.y < 0 || p2.y >= map_size) {
    cout << "Invalid coordinates - Given coordinates are outside of the map!\n";
    return false;
  }

  // Coordinates not on same row/column
  if(p1.x != p2.x && p1.y != p2.y) {
    cout << "Invalid coordinates - Given coordinates not lying on same row/column!\n";
    return false;
  }

  // Vertical ship
  if(p1.x == p2.x) {
    // If given coordinates can fit ship perfectly
    if(p2.y - p1.y + 1 != ship_size) {
      cout << "Invalid coordinates - Given coordinates do not match ship size!\n";
      return false;
    }

    for(int i = p1.y; i <= p2.y; i++) {
      if(map[i][p1.x] != TileState::Water) {
        cout << "Invalid coordinates - There is a ship lying between the given points!\n";
        return false;
      }
    }
  }
  // Horizontal ship (y1 == y2)
  else {
    // If given coordinates can fit ship perfectly
    if(p2.x - p1.x + 1 != ship_size) {
      cout << "Invalid coordinates - Given coordinates do not match ship size!\n";
      return false;
    }

    for(int i = p1.x; i <= p2.x; i++) {
      if(map[p1.y][i] != TileState::Water) {
        cout << "Invalid coordinates - There is a ship lying between the given points!\n";
        return false;
      }
    }
  }

  return true;
}

void set_ship_coords_on_map(TileState **map, ship_t ship) {
  point_t p1 = ship.end_coords[0], p2 = ship.end_coords[1];

  // Vertical ship
  if(p1.x == p2.x) {
    for(int i = p1.y; i <= p2.y; i++) {
      map[i][p1.x] = TileState::Unhit;
    }
  }
    // Horizontal ship (y1 == y2)
  else {
    for(int i = p1.x; i <= p2.x; i++) {
      map[p1.y][i] = TileState::Unhit;
    }
  }
}

void print_map(TileState **map, int size) {
  for(int i = size - 1; i >= 0; i--) {
    for(int j = 0; j < size; j++) {
      cout << (char)map[i][j] << " ";
    }
    cout << "\n";
  }
}

TileState **create_custom_map(int size, int *ships_to_place, ship_t *ships) {
  TileState **map = new TileState *[size];
  for(int i = 0; i < size; i++) {
    map[i] = new TileState[size];
    for(int j = 0; j < size; j++) {
      map[i][j] = TileState::Water;
    }
  }

  for(int i = 0; i < 5;) {
    point_t p1 = {}, p2 = {};
    cout << "Place ship with size " << ships_to_place[i] << "(x1 y1 x2 y2)\n";
    cin >> p1.x >> p1.y >> p2.x >> p2.y;

    fix_start_end_coords(p1, p2);

    if(valid_coords(map, size, ships_to_place[i], p1, p2)) {
      ships[i] = ship_t{ships_to_place[i], p1, p2};
      set_ship_coords_on_map(map, ships[i]);
      i++;
    }
  }

  return map;
}

TileState **create_random_map(int size, int *ships_to_place, ship_t *ships) {
  TileState **map = new TileState *[size];
  for(int i = 0; i < size; i++) {
    map[i] = new TileState[size];
    for(int j = 0; j < size; j++) {
      map[i][j] = TileState::Water;
    }
  }

  for(int i = 0; i < 5;) {
    point_t p1 = {}, p2 = {};

    fix_start_end_coords(p1, p2);

    if(valid_coords(map, size, ships_to_place[i], p1, p2)) {
      ships[i] = ship_t{ships_to_place[i], p1, p2};
      set_ship_coords_on_map(map, ships[i]);
      i++;
    }
  }

  return map;
}

TileState **generate_map(int size, Placement ship_placement) {
  TileState **map = nullptr;
  int ships_to_place[5] = {5, 4, 3, 3, 2};
  ship_t ships[5];

  switch (ship_placement) {
    case Placement::CreateCustom: {
      map = create_custom_map(size, ships_to_place, ships);
    }break;
    case Placement::LoadFromFile: {
      //map = load_map_from_file();
    }break;
    case Placement::Random: {
      map = create_random_map(size, ships_to_place, ships);
    }break;
  }

  // print_map(map, size); // TODO TEMP
  // Clear terminal so other player doesn't see coordinates entered
  // system("@cls||clear");; // TODO ASK IF ALLOWED

  return map;
}

void game_loop(TileState **map1, TileState **map2) {

}

Placement get_placement() {
  int iPlacement;
  Placement ePlacement;
  do {
    // Ship placement
    cout << "Create custom(1), load from file (2) or random placement(3)? ";
    cin >> iPlacement;
    ePlacement = static_cast<Placement>(iPlacement);
  } while(!validate_ship_placement(ePlacement));

  return ePlacement;
}

void free_map_memory(TileState **map, int size) {
  // Free each column (sub-array)
  for(int i = 0; i < size; i++) {
    delete[] map[i];
  }

  // Free each row (array of pointers)
  delete[] map;
  map = nullptr;
}

void start_game(int map_size, GameType gameType, SuccessfulHit successfulHit, Mode mode, Difficulty difficulty, Randomness randomness) {
  // Create both maps
  Placement placement = get_placement();
  TileState **map1 = generate_map(map_size, placement);

  TileState **map2;
  if(mode == Mode::Singleplayer) {
    map2 = generate_map(map_size, Placement::Random);
  }
  else {
    placement = get_placement();
    map2 = generate_map(map_size, placement);
  }

  cout << "\n";

  // Start game
  game_loop(map1, map2);

  free_map_memory(map1, map_size);
  free_map_memory(map2, map_size);
}

int main() {
  // Get input as int or char to convert it to enum afterwards
  int map_size, iDifficulty, iGameType;
  char cMode, cRandomness, cSuccessfulHit;

  Difficulty eDifficulty = Difficulty::Easy;
  Randomness eRandomness = Randomness::Normal;

  cout << "New game (1) or load game from file (2)? \n"; // TODO
  cin >> iGameType;
  GameType eGameType = static_cast<GameType>(iGameType);

  cout << "Does player go again after a successful hit? (y, n) "; // TODO
  cin >> cSuccessfulHit;
  SuccessfulHit eSuccessfulHit = static_cast<SuccessfulHit>(tolower(cSuccessfulHit));

  // Map size
  cout << "Field size (5, 20): ";
  cin >> map_size;

  // Game mode
  cout << "Singleplayer(S) or multiplayer(M)? ";
  cin >> cMode;
  Mode eMode = static_cast<Mode>(tolower(cMode));

  // Singleplayer computer options
  if(eMode == Mode::Singleplayer) {
    // Difficulty
    cout << "Select difficulty: 1. Easy 2. Medium 3. Hard 4. Impossible ";
    cin >> iDifficulty;
    eDifficulty = static_cast<Difficulty>(iDifficulty);

    if(eDifficulty != Difficulty::Impossible) {
      // Rigged computer randomness
      cout << "Can computer *cheat*? (y, n) ";
      cin >> cRandomness;
      eRandomness = static_cast<Randomness>(cRandomness);
    }
  }

  if(!validate_input(map_size, eGameType, eSuccessfulHit, eMode, eDifficulty, eRandomness)) {
    cout << "Invalid input!\n";
    return -1;
  }

  start_game(map_size, eGameType, eSuccessfulHit, eMode, eDifficulty, eRandomness);

  return 0;
}
