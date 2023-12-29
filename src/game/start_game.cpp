#include "start_game.hh"

int start_game(ship_t *ships_to_place, int ships_count, int map_size, SuccessfulHit successfulHit,
                Mode mode, Difficulty difficulty, Randomness randomness) {
  // Set random seed
  srand(time(nullptr));

  // Create players and their ships
  player_t player1 = player_t(map_size, ships_to_place, ships_count);
  player_t player2 = player_t(map_size, ships_to_place, ships_count);

  // Create both maps
  Placement placement = get_placement();
  std::cout << "Player 1 map:\n";
  if(!generate_map(player1, placement)) {
    return -1;
  }

  if(mode == Mode::Singleplayer) {
    if(!generate_map(player2, Placement::Random)) {
      return -1;
    }
  }
  else {
    placement = get_placement();
    std::cout << "Player 2 map:\n";
    if(!generate_map(player2, placement)) {
      return -1;
    }
  }

  std::cout << "\n";

  // Start game
  game_loop(player1, player2, mode, successfulHit, difficulty, randomness);

  // Free map memory by calling the players' destructors
  player1.player_t::~player_t();
  player2.player_t::~player_t();

  return 0;
}