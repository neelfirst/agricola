#include "player.h"

Player::Farm::Farm()
{
	for (uint8_t i = 0; i < 3; i++) {
		for (uint8_t j = 0; j < 5; j++) {
			squares[i][j] = UNUSED;
			lines[i][j] = EMPTY;
			lines[i][j+1] = EMPTY;
		}
	}
	squares[0][0] = ROOM_W;
	squares[1][0] = ROOM_W;
	lines[0][0] = ILLEGAL;
	lines[1][0] = ILLEGAL;
}

Player::Player(uint8_t t, std::string n)
{
	name = n; turn_order = t;
	fences = 15; stables = 4;
	peoples = 2; score = -14;
}

int8_t Player::getMove(const Game game)
{
	/* step 1 - identify player and provide turn order */
	std::cout << "Player: " << this.name 
			  << "Position: " << this.turn_order
			  << " of " << game.player_count << std::endl;

	/* step 2 - 
	/* what is the game state
	 * 1. N_PLAYERS * IS_FAMILY --> Q-table per combo
	 * 2. ROUND * MOVE # * N_MOVES
	 * 3. turn order
	 * 4. game.resources super-struct or game.spaces.resources list
	 * 5. player.resources & player.farm struct
	 */
}