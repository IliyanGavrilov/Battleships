#include <string>

#pragma once

struct game_settings_t {
  int *game_setting;
  std::string message;
  bool (*input_validation_func) (int);

  game_settings_t(int *game_setting, std::string message, bool (*input_validation_func) (int)) :
    game_setting(game_setting), message(message), input_validation_func(input_validation_func) {}
};