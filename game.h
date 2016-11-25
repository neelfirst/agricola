#ifndef __BAH_GAME_H
#define __BAH_GAME_H

class Game {
	public:
		uint8_t round;
		bool is_harvest;
		list actions[26]; // 127?
		list resources[10]; // roll in?
	private:
		void update(Action); // executes after valid move
};

#endif