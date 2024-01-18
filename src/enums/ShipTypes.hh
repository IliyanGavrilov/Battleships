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
// * <header file with ShipTypes enum>
// *
// *
//


#include <string>
#define SHIP_TYPES 4
#pragma once

// 'Last' is added so that we can iterate through the enums
enum ShipTypes {Destroyer = 2, Submarine = 3 , Battleship = 4, Carrier = 5, Last};

std::string valueToEnumName(ShipTypes size);