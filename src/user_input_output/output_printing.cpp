#include "output_printing.hh"

void print_grid_line(int map_size, point_t *shot, bool highlight) {
  std::cout << "   "; // 3
  for (int i = 0; i < map_size; i++) {
    if (shot != nullptr && highlight && (*shot).x == i) {
      std::cout << "+" << MAGENTA_T << "---" << RESET;
    }
    else {
      std::cout << "+---";
    }
  }

  std::cout << "+";
}

// Print row of numbers (x-axis coordinates)
void print_x_axis_numbers(int map_size) {
  std::cout << "  "; // 2
  for (int i = 0; i < map_size; i++) {
    std::cout << std::setw(4) << i + 1;
  }
}

// Flag is to tell where function is called from
// If it is called before the game starts ship locations are displayed, but during the game they're hidden
void print_map(const std::vector<std::vector<TileState>> &map, int map_size, bool flag, point_t *shot) {
  std::cout << "\n";

  print_x_axis_numbers(map_size);

  std::cout << "\n";

  bool highlight = false;
  if (shot != nullptr) {
    highlight = ((*shot).y == map_size - 1);
  }

  print_grid_line(map_size, shot, highlight);

  std::cout << "\n";

  for (int i = map_size - 1; i >= 0; i--) {
    // Print first column of letters (y-axis coordinates)
    if (shot != nullptr && (((*shot).x == 0 && (*shot).y == i))) {
      std::cout << " " << (char)('A' + i) << MAGENTA_T << " |" << RESET;
    }
    else {
      std::cout << " " << (char)('A' + i) << " |";
    }

    // Print rows of map
    for (int j = 0; j < map_size; j++) {
      char tile = (map[i][j] == TileState::Unhit && flag) ? TileState::Water : map[i][j];
      // If previous tile from shot or current tile is shot we highlight the vertical borders
      if (shot != nullptr && (((*shot).x - 1 == j && (*shot).y == i) || ((*shot).x == j && (*shot).y == i))) {
        std::cout << " " << getTileColour(tile) << tile << RESET << MAGENTA_T << " |" << RESET;
      }
      else {
        std::cout << " " << getTileColour(tile) << tile << RESET << " |";
      }
    }

    // Print last column of letters (y-axis coordinates)
    std::cout << " " << (char)('A' + i);

    std::cout << "\n";

    if (shot != nullptr) {
      highlight = ((*shot).y + 1 == i) || ((*shot).y == i);
    }

    print_grid_line(map_size, shot, highlight);

    std::cout << "\n";
  }

  print_x_axis_numbers(map_size);

  std::cout << "\n\n";
}

void print_ship_sizes_left(const std::vector<ship_t> &ships) {
  if (!ships.empty()) {
    std::cout << WHITE_T << "Opponent ships left: ";

    int count_ship_types[SHIP_TYPES];
    for (int &count_ship_type : count_ship_types) {
      count_ship_type = 0;
    }

    // Count each type of ship
    for (const ship_t &ship : ships) {
      count_ship_types[ship.size - ShipTypes::Destroyer]++;
    }

    bool firstTypePrinted = false;
    for (int i = 0; i < SHIP_TYPES; i++) {
      if (count_ship_types[i] > 0) {
        // Print comma before each ship type count except the first one
        if (firstTypePrinted) {
          std::cout << ", ";
        }
        std::cout << valueToEnumName((ShipTypes) (i + ShipTypes::Destroyer)) << " (size " << i + ShipTypes::Destroyer << ") x "
                  << count_ship_types[i];
        firstTypePrinted = true;
      }
    }
    std::cout << RESET << "\n";
  }
}