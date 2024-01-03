#include <string>
#define SHIP_TYPES 4
#pragma once

// 'Last' is added so that we can iterate through the enums
enum ShipTypes {Destroyer = 2, Submarine = 3 , Battleship = 4, Carrier = 5, Last};

std::string valueToEnumName(ShipTypes size);