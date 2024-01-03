all:
	gcc -Wall -pedantic src/main.cpp src/game/start_game.cpp src/game/gameplay.cpp src/structs/player.cpp src/structs/ship.cpp \
	src/structs/point.cpp src/enums/TileState.cpp src/enums/ShipTypes.cpp src/user_input_output/file_handling.cpp \
	src/user_input_output/get_input.cpp src/user_input_output/validate_input.cpp src/user_input_output/map_creation.cpp \
	src/user_input_output/output_printing.cpp -o battleships -lstdc++
	./battleships