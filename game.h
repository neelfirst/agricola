#ifndef __BAH_GAME_H
#define __BAH_GAME_H

#include "common.h"
#include <unordered_map>
#include <string>

class Game {
	public:
		uint8_t round;
		bool is_harvest;
		std::unordered_map<std::string, uint8_t> actions; // available actions, max is 26
		Game();
	private:
		void update(Action); // executes after valid move
};

#endif