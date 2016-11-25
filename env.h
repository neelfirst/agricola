#ifndef __BAH_ENV_H
#define __BAH_ENV_H

#include "game.h"
#include "player.h"

class Env {
	public:
		Game game_board;
		Player player_board;
		list <Action> history;
};

#endif