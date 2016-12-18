#ifndef __BAH_PLAYER_H
#define __BAH_PLAYER_H

#include "common.h"

// best design for player is to accept inputs from generic stream
// and have that stream defined elsewhere as std::cin or AI stream



class Player {
	public:
		// Farm square states
		enum FarmSquareState {UNUSED, ROOM_W, ROOM_C, ROOM_S, 
				FIELD, FIELD_1G, FIELD_2G, FIELD_3G, FIELD_1V, FIELD_2V, 
				STABLE, PASTURE, PASTABLE};
		// Farm fence states
		enum FarmFenceState {ILLEGAL, EMPTY, FENCE}; 

		/* Farm squares map:
			2,0	2,1	2,2	2,3	2,4
			1,0	1,1	1,2	1,3	1,4
			0,0	0,1	0,2	0,3	0,4
		   Farm fences map:
			2,0	2,1 2,2 2,3 2,4 2,5
				1,1 1,2 1,3 1,4 1,5
				0,1 0,2 0,3 0,4 0,5
		*/

		struct Farm {
			uint8_t squares[3][5];
			uint8_t lines[3][6];
			Farm();
		};
		Resource resources;
		Farm farm_board;
		uint8_t turn_order;
		std::string name; // for identification purposes
		uint8_t fences, stables; // finite
		uint8_t peoples; // 2-5
		int8_t score; // starts negative!
		std::list<Major> cards_in_play; // cards in play
		Player(uint8_t, std::string); // game assigns turn order
	private:
		int8_t getMove(Action); // validity checks
		// hand
};

#endif