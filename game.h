#ifndef __BAH_GAME_H
 __BAH_GAME_H

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
			DAY_LABORER,
			WOOD_2,
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
			// future - add other spots
		}

		struct Space {
			UseState status;
			Action action;
			Resource resources;
			Space(SpaceState, Action);
		};

		// just an idea for Major implementation
		// should they be passable objects
		// or should different classes track them separately
		// this would be part of the latter solution
		struct Major {
			Resource cost;
			UseState status;
			std::string name;
			Major(MajorImprovement);
		};

		std::vector<Major> improvements;
		std::vector<std::string> rounds; // vector of round/harvest strings, rounds match action map
		std::unordered_map<std::string, Space> action_set; // round-based current action list

		Game();
	private:
		bool update(Action); // executes after valid move
};

#endif