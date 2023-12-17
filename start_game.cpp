#include "start_game.hh"

void start_game(ship_t *ships_to_place, int ships_count, int map_size, GameType gameType,
                SuccessfulHit successfulHit, Mode mode, Difficulty difficulty, Randomness randomness) {
  // Set random seed
  srand(time(nullptr));

  // Create players and their ships
  player_t player1 = player_t(map_size, ships_to_place, ships_count);
  player_t player2 = player_t(map_size, ships_to_place, ships_count);

  // Create both maps
  Placement placement = get_placement();
  std::cout << "Player 1 map:\n";
  generate_map(player1, placement);

  if(mode == Mode::Singleplayer) {
    generate_map(player2, Placement::Random);
  }
  else {
    placement = get_placement();
    std::cout << "Player 2 map:\n";
    generate_map(player2, placement);
  }

  std::cout << "\n";

  // Start game
  game_loop(player1, player2, successfulHit, difficulty, randomness);

  // Free map memory by calling the players' destructors
  player1.player_t::~player_t();
  player2.player_t::~player_t();
}