cmake_minimum_required(VERSION 3.24)
project(battleships/src)

set(CMAKE_CXX_STANDARD 17)

add_executable(battleships src/main.cpp src/structs/point.hh src/structs/point.cpp src/structs/ship.hh src/structs/ship.cpp
               src/structs/player.hh src/structs/player.cpp src/enums/GameType.hh src/enums/SuccessfulHit.hh src/enums/Mode.hh
               src/enums/Difficulty.hh src/enums/Randomness.hh src/enums/Placement.hh src/enums/TileState.hh src/enums/ShipTypes.hh
               src/user_input_output/get_input.cpp src/user_input_output/get_input.hh src/game/start_game.hh src/game/start_game.cpp
               src/user_input_output/validate_input.hh src/user_input_output/validate_input.cpp src/user_input_output/map_creation.hh
               src/user_input_output/map_creation.cpp src/game/gameplay.cpp src/game/gameplay.hh src/user_input_output/file_handling.hh
               src/user_input_output/file_handling.cpp src/enums/TileState.cpp src/enums/SaveToFile.hh src/enums/FileHandling.hh
               src/user_input_output/validate_input.cpp src/user_input_output/output_printing.cpp  src/user_input_output/output_printing.hh
               src/enums/ShipTypes.cpp src/user_input_output/colours.hh src/structs/game_settings.hh)
