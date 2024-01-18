// /**
// *
// * Solution to course project # 1
// * Introduction to programming course
// * Faculty of Mathematics and Informatics of Sofia University
// * Winter semester 2023/2024
// *
// * @author Iliyan Gavrilov
// * @idnumber 6MI0600293
// * @compiler GCC
// *
// * <file with ShipTypes enum function implementation>
// *
// *
//

#include "ShipTypes.hh"

std::string valueToEnumName(ShipTypes size) {
  switch (size) {
    default: return "Destroyer"; // 2
    case 3: return "Submarine";
    case 4: return "Battleship";
    case 5: return "Carrier";
  }
}