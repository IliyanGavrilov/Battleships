#include <iostream>
#include <fstream>

#define MIN_SIZE 5
#define MAX_SIZE 20

using namespace std;

enum Mode {Singleplayer = 's', Multiplayer = 'm'};
enum Difficulty {Easy = 1, Medium = 2, Hard = 3, Impossible = 4};
enum Randomness {Normal = 'n', Rigged = 'y'};
enum Placement {CreateCustom = 1, LoadFromFile = 2, Random = 3};
enum TileState {Water = '~', Unhit = '~', Hit = 'X', Miss = 'O', Sunken = '*'};

struct point_t {
  int x;
  int y;
};

struct ship_t {
  point_t end_coords[2];
};

// Check input
bool invalid_input(int size, Mode mode, Placement ship_placement, Difficulty difficulty, Randomness randomness) {
  // Check map size
  if(size < MIN_SIZE || size > MAX_SIZE) {
    return true;
  }

  // Check game mode
  if(mode != Mode::Singleplayer && mode != Mode::Multiplayer) {
    return true;
  }

  // Check difficulty of bot
  if(difficulty != Difficulty::Easy && difficulty != Difficulty::Medium && difficulty != Difficulty::Hard && difficulty != Difficulty::Impossible) {
    return true;
  }

  // Check if bot can cheat/if randomness is rigged
  if(randomness != Randomness::Normal && randomness != Randomness::Rigged) {
    return true;
  }

  // Check ship placement
  if(ship_placement != Placement::CreateCustom && ship_placement != Placement::LoadFromFile && ship_placement != Placement::Random) {
    return true;
  }

  return false;
}

void fix_start_end_coords(int &x1, int &x2, int &y1, int &y2) {
  if(x1 > x2 || y1 > y2) {
    swap(x1, x2);
    swap(y1, y2);
  }
}

// TODO "const" TileState ** const map, const int size, const ship_t end_points
bool valid_coords(TileState ** map, int map_size, int ship_size, int x1, int x2, int y1, int y2) {
  // Coordinates are outside of map
  if(x1 < 0 || x1 >= map_size || x2 < 0 || x2 >= map_size || y1 < 0 || y1 >= map_size || y2 < 0 || y2 >= map_size) {
    cout << "Invalid coordinates - Given coordinates are bigger than map size!\n";
    return false;
  }

  // Coordinates not on same row/column
  if(x1 != x2 && y1 != y2) {
    cout << "Invalid coordinates - Given coordinates not lying on same row/column!\n";
    return false;
  }

  // Vertical ship
  if(x1 == x2) {
    // If given coordinates can fit ship perfectly
    if(y2 - y1 + 1 != ship_size) {
      cout << "Invalid coordinates - Given coordinates do not match ship size!\n";
      return false;
    }

    for(int i = y1; i <= y2; i++) {
      if(map[i][x1] != TileState::Water) {
        cout << "Invalid coordinates - There is a ship lying between the given points!\n";
        return false;
      }
    }
  }
  // Horizontal ship (y1 == y2)
  else {
    // If given coordinates can fit ship perfectly
    if(x2 - x1 + 1 != ship_size) {
      cout << "Invalid coordinates - Given coordinates do not match ship size!\n";
      return false;
    }

    for(int i = x1; i <= x2; i++) {
      if(map[y1][i] != TileState::Water) {
        cout << "Invalid coordinates - There is a ship lying between the given points!\n";
        return false;
      }
    }
  }

  return true;
}

void set_ship_coords_on_map(TileState **map, ship_t ships) {

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
    int x1, y1, x2, y2;
    cout << "Place ship with size " << ships_to_place[i] << "(x1 y1 x2 y2)\n";
    cin >> x1 >> y1 >> x2 >> y2;

    fix_start_end_coords(x1, x2, y1, y2);

    if(valid_coords(map, size, ships_to_place[i], x1, x2, y1, y2)) {
      ships[i] = ship_t{point_t{x1, y1}, point_t{x2, y2}};
      set_ship_coords_on_map(map, ships[i]);
      i++;
    }
  }

  return map;
}

void generate_map(int size, Mode mode, Placement ship_placement) {
  TileState **map = nullptr;
  int ships_to_place[5] = {5, 4, 3, 3, 2};
  ship_t ships[5];

  switch (ship_placement) {
    case Placement::CreateCustom: {
      map = create_custom_map(size, ships_to_place, ships);
    }break;
    case Placement::LoadFromFile: {

    }break;
    case Placement::Random: {

    }break;
  }
}

void start_game() {
// Get input as int or char
  int map_size, iDifficulty;
  char cMode, cRandomness, cPlacement;
  Difficulty eDifficulty = Difficulty::Easy;
  Randomness eRandomness = Randomness::Normal;

  // Map size
  cout << "Field size (5, 20):";
  cin >> map_size;

  // Game mode
  cout << "Singleplayer(S) or multiplayer(M)?";
  cin >> cMode;
  Mode eMode = static_cast<Mode>(tolower(cMode));

  // Singleplayer computer options
  if(eMode == Mode::Singleplayer) {
    // Difficulty
    cout << "Select difficulty: 1. Easy 2. Medium 3. Hard 4. Impossible";
    cin >> iDifficulty;
    eDifficulty = static_cast<Difficulty>(iDifficulty);
    if(eDifficulty != Difficulty::Impossible)
    // Rigged computer randomness
    cout << "Can computer *cheat*? (y, n)";
    cin >> cRandomness;
    eRandomness = static_cast<Randomness>(cRandomness);
  }

  // Ship placement
  cout << "Create custom(1), load from file (2) or random placement(3)?";
  cin >> cPlacement;
  Placement ePlacement = static_cast<Placement>(cPlacement);

  cout << "\n";
  cout << "";

  if(!invalid_input(map_size, eMode, ePlacement, eDifficulty, eRandomness)) {
    cout << "Invalid input!\n";
    return;
  }

  generate_map(map_size, eMode, ePlacement);
}

int main() {
  start_game();

  return 0;
}
