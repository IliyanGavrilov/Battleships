#include "ShipTypes.hh"

std::string valueToEnumName(ShipTypes size) {
  switch (size) {
    default: return "Destroyer"; // 2
    case 3: return "Submarine";
    case 4: return "Battleship";
    case 5: return "Carrier";
  }
}