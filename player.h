#ifndef __BAH_PLAYER_H
#define __BAH_PLAYER_H

#include "common.h"

// Farm square states
enum FarmSquareState {EMPTY, ROOM_W, ROOM_C, ROOM_S, 
		FIELD, FIELD_1G, FIELD_2G, FIELD_3G, FIELD_1V, FIELD_2V, 
		STABLE, PASTURE, PASTABLE};
// Farm fence states
enum FarmFenceState {ILLEGAL, EMPTY, FENCE}; // Farm fence states

struct Farm {
	uint8_t squares[3][5]; // enumerate {empty, w/c/s room, field, unf stable, pasture, p+stable}
	int8_t lines[4][6]; // enumerate {illegal, empty, fence}
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