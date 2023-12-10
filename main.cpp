#include <iostream>

#define MIN_SIZE 5
#define MAX_SIZE 20

using namespace std;

enum Mode {Singleplayer = 's', Multiplayer = 'm'};
enum Difficulty {Easy = 1, Medium = 2, Hard = 3};
enum Randomness {Normal = 'n', Rigged = 'y'};
enum Placement {CreateCustom = 1, LoadFromFile = 2, Random = 3};

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
  if(difficulty != Difficulty::Easy && difficulty != Difficulty::Medium && difficulty != Difficulty::Hard) {
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

void generate_map(int size, Mode mode, Placement ship_placement) {
  switch (ship_placement) {
    case Placement::CreateCustom: {

    }break;
    case Placement::LoadFromFile: {

    }break;
    case Placement::Random: {//

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
    cout << "Select difficulty: 1. Easy 2. Medium 3. Hard";
    cin >> iDifficulty;
    eDifficulty = static_cast<Difficulty>(iDifficulty);

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
    cout << "Invalid input!";
    return;
  }

  generate_map(map_size, eMode, ePlacement);
}

int main() {
  start_game();

  return 0;
}
