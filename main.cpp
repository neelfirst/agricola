/* main.cpp - what does a main file look like
 * main basically needs to execute a game
 * main needs also to ask what kind of game
 * but maybe for now we stick to solo family */

#include <iostream>
#include <string>
#include <list>

int main (int argc, char **argv)
{
	/* I guess we need a block to parse game type. But ignore because
	 * we're just going to do solo family for now */
	uint8_t player_count = 0;
	bool is_family_game = false;
	if (argc != 3 || argc != 4) {
		std::cout << "usage: agricola -n [1-5] [--family]" << std::endl;
		exit(1);
	}
	else {
		if (argv[1] == "-n" || argv[1] == "-N") {
			player_count = (int)argv[2];
			if (player_count < 1 || player_count > 5) {
				std::cout << "usage: agricola -n [1-5] [--family]" << std::endl;
				exit(2);
			}
		}
		if (argv[3] != NULL && argv[3] == "--family") {
			is_family_game = true;
		}
	}

	/* step 1. setup the game */
	std::cout << "Initializing game: # players = " << player_count
			  << " & family == " << is_family_game << std::endl;
	Game game(player_count, is_family_game);
	/* 2. start the game - is this necessary */
	game.start();
	/* step 3. ask player for move */
	while (!game.isComplete()) {
		for (Player player : game.players) {
			do { 
				move = player.getMove(game); 
			}
			while (!game.update(move, player));	
		}
	}
	// this should be more flexible for n players and shit
	game.printResult(players);
}