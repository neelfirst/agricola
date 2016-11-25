#ifndef __BAH_PLAYER_H
#define __BAH_PLAYER_H

struct Farm {
	uint8_t squares[3][5]; // enumerate {empty, w/c/s room, field, unf stable, pasture, p+stable}
	int8_t lines[4][6]; // enumerate {illegal, empty, fence}
};

struct Resource {
	uint8_t wood, clay, reed, stone, sheep, boar, cow, grain, veg, food;
};

class Player {
	public:
		Resource resources;
		Farm farm_board;
		uint8_t fences, stables; // finite
		uint8_t peoples; // 2-5
		int8_t score; // starts negative!
	private:
		int8_t move(Action); // validity checks
};

#endif