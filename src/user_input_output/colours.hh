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
// * <header file with ANSI escape code colours in terminal/console>
// *
// *
//

#pragma once

// ANSI code colours

// Bold High-Intensity Text colours
#define WHITE_T "\033[1;38;5;231m"
#define MAGENTA_T "\033[1;38;5;127m" // Hit tile border highlight
#define BLUE_T "\033[1;38;5;21m" // Unhit/Water
#define RED_T "\033[1;38;5;196m" // Miss
#define ORANGE_T "\033[1;38;5;214m" // Hit
#define GREEN_T "\033[1;38;5;113m" // Sunken

// High-Intensity Background colours
#define WHITE_B "\033[48;5;231m"

// Reset
#define RESET "\033[0m"