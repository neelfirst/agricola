#ifndef __BAH_ENV_H
#define __BAH_ENV_H

#include "common.h"
#include "game.h"
#include "player.h"
#include <vector> // std::vector

class Env {
	public:
		Game game_board;
		Player player_board;
		std::vector<Action> history;
};

#endif