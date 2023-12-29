#include "file_handling.hh"

int load_game_from_file(FileHandling load_type, char *filename, player_t *player1, player_t *player2, Mode *eMode,
                        SuccessfulHit *eSuccessfulHit, Difficulty *eDifficulty, Randomness *eRandomness) {
  std::ifstream file(filename);

  // Check if file exists
  if(file.fail()) {
    return 1;
  }

  // Check if file is empty
  if(file.peek() == std::ifstream::traits_type::eof())
  {
    return 2;
  }

  // Check if file opened successfully
  if(file.is_open()) {
    std::string line;

    if(load_type == FileHandling::All) {
      // Get first line containing game settings (a.k.a. map_size, ship_count, enums)
      std::getline(file, line);
      const char *str = line.c_str();

      // Split line/string by delimiter
      std::vector<std::string> result = split_string(str);
      int index = 0;

      // Read the game settings from first row, convert them from string to int using stoi() and
      // Then cast them to enum
      int map_size = stoi(result[index++]);
      int total_ships_count = stoi(result[index++]);
      *eSuccessfulHit = static_cast<SuccessfulHit>(stoi(result[index++]));
      *eMode = static_cast<Mode>(stoi(result[index++]));
      *eDifficulty = static_cast<Difficulty>(stoi(result[index++]));
      *eRandomness = static_cast<Randomness>(stoi(result[index]));


      (*player1).map_size = map_size;
      (*player1).ships_count = total_ships_count;
      (*player2).map_size = map_size;
      (*player2).ships_count = total_ships_count;

      // Skip empty line before loading Player 1 information (map and ships)
      std::getline(file, line);

    }

    // Load Player 1 information
    load_player_info_from_file(file, *player1);

    if(load_type == FileHandling::All) {
      // Skip empty line before loading Player 2 information (map and ships)
      std::getline(file, line);

      // Loading Player 2 information
      load_player_info_from_file(file, *player2);
    }

    file.close();
  }
    // Error while opening file
  else {
    return 3;
  }

  return 0;
}

void load_player_info_from_file(std::ifstream &file, player_t &player) {
  std::string line;

  // Allocate memory for map
  player.map = new TileState *[player.map_size]; // TODO prevent fragmentation of memory
  for(int i = 0; i < player.map_size; i++) {
    player.map[i] = new TileState[player.map_size];
    for(int j = 0; j < player.map_size; j++) {
      player.map[i][j] = TileState::Water;
    }
  }

  // Read player map (matrix) line by line
  for(int i = 0; i < player.map_size; i++) {
    std::getline(file, line);
    std::vector <std::string> v = split_string(line.c_str());

    for(int j = 0; j < player.map_size; j++) {
      player.map[i][j] = charToTileState(*v[j].c_str());
    }
  }

  // Skip empty line before loading player ships
  std::getline(file, line);

  // Read player ships line by line
  for(int i = 0; i < player.ships_count; i++) {
    std::getline(file, line);
    std::vector <std::string> v = split_string(line.c_str());

    player.ships[i] = ship_t(stoi(v[0]),
                             point_t(stoi(v[1]), stoi(v[2])),
                             point_t(stoi(v[3]), stoi(v[4])));
  }
}

int save_game_to_file(FileHandling save_type, char *filename, player_t *player1, player_t *player2, Mode *eMode,
                      SuccessfulHit *eSuccessfulHit, Difficulty *eDifficulty, Randomness *eRandomness) {
  std::ofstream file(filename); // TODO

  // Check if file exists
  if(file.fail()) {
    return 1;
  }

  // Check if file opened successfully
  if(file.is_open()) {
    std::string line;

    if(save_type == FileHandling::All) {
      // Save game settings (a.k.a. map_size, ship_count, enums) to the first line
      file << player1->map_size << " " << player1->ships_count << " " <<
      eSuccessfulHit << " " << eMode << " " << eDifficulty << " " << eRandomness << "\n";

      // Skip empty line before saving Player 1 information (map and ships)
      file << "\n";
    }

    save_player_info_to_file(file, *player1);

    if(save_type == FileHandling::All) {
      // Skip empty line before saving Player 2 information (map and ships)
      file << "\n";

      save_player_info_to_file(file, *player2);
    }

    file.close();
  }
    // Error while opening file
  else {
    return 3;
  }

  return 0;
}

void save_player_info_to_file(std::ofstream &file, player_t &player) {
  // Save player map (matrix)
  for(int i = 0; i < player.map_size; i++) {
    for(int j = 0; j < player.map_size; j++) {
      file << player.map[i][j] << " ";
    }
    file << "\n";
  }

  // Skip empty line before saving player ships
  file << "\n";

  // Save player ships
  for(int i = 0; i < player.ships_count; i++) {
    file << player.ships[i].size << " " << player.ships[i].end_coords[0].x << " " << player.ships[i].end_coords[0].y << " " <<
                                           player.ships[i].end_coords[1].x << " " << player.ships[i].end_coords[1].y << "\n";
  }
}

std::vector<std::string> split_string(const char *str, char delimiter)
{
  // Vector to store different parts
  std::vector<std::string> result;

  do
  {
    const char *begin = str;

    // Find end of part before delimiter
    while(*str != delimiter && *str != '\0') {
      str++;
    }

    result.emplace_back(begin, str);
  } while (*str++ != '\0');

  return result;
}