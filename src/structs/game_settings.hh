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
// * <header file with game settings structure>
// *
// *
//

#include <string>

#pragma once

struct game_settings_t {
  int *game_setting;
  std::string message;
  bool (*input_validation_func) (int);

  game_settings_t(int *game_setting, std::string message, bool (*input_validation_func) (int)) :
    game_setting(game_setting), message(message), input_validation_func(input_validation_func) {}
};