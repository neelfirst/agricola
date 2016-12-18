#ifndef __BAH_GAME_H
#define __BAH_GAME_H

#include "common.h"
#include <unordered_map>
#include <vector>
#include <string>

class Game {
	public:
		enum UseState {LOCKED, OCCUPIED, OPEN};
		enum Action {
			ROOM_STABLE,
			SP_FOOD_1,
			GRAIN,
			PLOW,
			STABLES,
			OCCUPATION,
			DAY_LABORER,
			WOOD_2,
			WOOD_3,
			CLAY_1,
			REED_1,
			FISH_1,
			SHEEP_1,
			FENCES,
			SOW_BAKE,
			IMPROVEMENT,
			STONE_1, // multiple items in the action list can be STONE_1
			FGMI,
			RENOVATE_IMP,
			BOAR_1,
			VEGGIE,
			CATTLE_1,
			FGWR,
			PLOW_SOW,
			RENOVATE_FENCE,
			CLAY_2,
			CLAY_3,
			WOOD_1,
			WOOD_4,
			OCCUPATION3,
			OCCUPATION4,
			OCC4_R5FG,
			ANY1,
			RSF,
			RSW,
			TRAVEL_1,
			BUILD_TRAVEL,
			MULTI_ANIMAL,
		};

		struct Space {
			UseState status;
			Action action;
			Resource resources;
			Space(UseState, Action);
		};

		// just an idea for Major implementation
		// should they be passable objects
		// or should different classes track them separately
		// this would be part of the latter solution
		struct Major {
			Resource cost;
			UseState status;
			std::string name;
			MajorImprovement mcode;
			uint8_t points;
			Major(MajorImprovement);
		};

		Game(uint8_t, bool); // player_count, is_family_game
		bool start(); // deals cards, 10-7/drafts? and moves to round 1
		bool update(Action); // executes after valid move
		void unlock(Space &); // changes Space UseState from LOCKED-->OPEN
	private:
		uint8_t player_count;
		bool is_family_game;
		uint8_t current_round; // index to rounds vector
		std::list<Player> players;

		std::vector<Major> improvements;
		std::vector<std::string> rounds; // vector of round/harvest strings, rounds match action map
		std::unordered_map<std::string, Space> action_set; // round-based current action list
};

#endif