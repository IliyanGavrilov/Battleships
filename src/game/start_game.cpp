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
// * <file with function to prepare the start of the game - create players and maps>
// *
// *
//

#include "start_game.hh"

int start_game(const std::vector<ship_t> &ships_to_place, int ships_count, int map_size, SuccessfulHit successfulHit,
                Mode mode, Difficulty difficulty, Randomness randomness) {
  // Set random seed
  srand(time(nullptr));

  // Create players and their ships
  player_t player1 = player_t(map_size, ships_to_place, ships_count);
  player_t player2 = player1;

  // Create both maps
  std::cout << "Player 1:\n";
  Placement placement = get_placement();
  if (generate_map(player1, placement, Mode::Multiplayer)) {
    return -1;
  }

  std::cout << "Player 2:\n";
  if (mode == Mode::Singleplayer) {
    if (generate_map(player2, Placement::Random, Mode::Singleplayer)) {
      return -1;
    }
  }
  else {
    placement = get_placement();
    if (generate_map(player2, placement, Mode::Multiplayer)) {
      return -1;
    }
  }

  std::cout << "\nStarting game!\n\n";

  // Start game
  game_loop(player1, player2, mode, successfulHit, &difficulty, &randomness);

  return 0;
}