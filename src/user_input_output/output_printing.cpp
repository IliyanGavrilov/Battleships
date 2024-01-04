#include "output_printing.hh"

void print_grid_line(int map_size) {
  std::cout << "   "; // 3
  for (int i = 0; i < map_size; i++) {
    std::cout << "+---";
  }

  std::cout << "+";
}

// Print row of numbers (x-axis coordinates)
void print_x_axis_numbers(int map_size) {
  std::cout << "  ";
  for (int i = 0; i < map_size; i++) {
    std::cout << std::setw(4) << i + 1;
  }
}

// Flag is to tell where function is called from
// If it is before the game starts ship locations are displayed, but during the game they're hidden
void print_map(const std::vector<std::vector<TileState>> &map_before, int map_size, bool flag,
               const std::vector<std::vector<TileState>> *map_after) {
  std::cout << "\n";

  print_x_axis_numbers(map_size);

  if (map_after != nullptr) {
    std::cout << "        "; // 8
    print_x_axis_numbers(map_size);
  }

  std::cout << "\n";
  print_grid_line(map_size);

  if (map_after != nullptr) {
    std::cout << "      "; // 6
    print_grid_line(map_size);
  }

  std::cout << "\n";

  for (int i = map_size - 1; i >= 0; i--) {
    // Print first column of letters (y-axis coordinates) [BEFORE MAP]
    std::cout << " " << (char)('A' + i) << " |";

    // Print rows of map [BEFORE MAP]
    for (int j = 0; j < map_size; j++) {
      char tile = (map_before[i][j] == TileState::Unhit && flag) ? TileState::Water : map_before[i][j];
      std::cout << " " << tile  << " |";
    }

    // Print last column of letters (y-axis coordinates) [BEFORE MAP]
    std::cout << " " << (char)('A' + i);

    if (map_after != nullptr) {
      std::cout << "    "; // 4

      // Print first column of letters (y-axis coordinates) [AFTER MAP]
      std::cout << " " << (char) ('A' + i) << " |";

      // Print rows of map [AFTER MAP]
      for (int j = 0; j < map_size; j++) {
        char tile = ((*map_after)[i][j] == TileState::Unhit && flag) ? TileState::Water : (*map_after)[i][j];
        std::cout << " " << tile << " |";
      }

      // Print last column of letters (y-axis coordinates) [AFTER MAP]
      std::cout << " " << (char) ('A' + i);
    }

    std::cout << "\n";

    print_grid_line(map_size);

    if (map_after != nullptr) {
      std::cout << "      "; // 6
      print_grid_line(map_size);
    }

    std::cout << "\n";
  }

  print_x_axis_numbers(map_size);

  if (map_after != nullptr) {
    std::cout << "        "; // 8
    print_x_axis_numbers(map_size);
  }

  std::cout << "\n\n";
}

void print_ship_sizes_left(const std::vector<ship_t> &ships) {
  if (!ships.empty()) {
    std::cout << "Opponent ships left: ";

    int count_ship_types[SHIP_TYPES];
    for (int &count_ship_type : count_ship_types) {
      count_ship_type = 0;
    }

    // Count each type of ship
    for (const ship_t &ship : ships) {
      count_ship_types[ship.size - ShipTypes::Destroyer]++;
    }


    for (int i = 0; i < SHIP_TYPES; i++) {
      if (count_ship_types[i] > 0) {
        std::cout << valueToEnumName((ShipTypes) (i + ShipTypes::Destroyer)) << " (size " << i + ShipTypes::Destroyer << ") x "
                  << count_ship_types[i] << " ";
      }
    }
    std::cout << "\n";
  }
}