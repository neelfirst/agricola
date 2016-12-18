#ifndef __BAH_COMMON_H
#define __BAH_COMMON_H

enum Round {
	INVALID = -1,
	ROUND_0 = 0,
	ROUND_1 = 1,
	ROUND_2 = 2,
	ROUND_3 = 3,
	ROUND_4 = 4,
	HARVEST_1 = 5,
	ROUND_5 = 6,
	ROUND_6 = 7,
	ROUND_7 = 8,
	HARVEST_2 = 9,
	ROUND_8 = 10,
	ROUND_9 = 11,
	HARVEST_3 = 12,
	ROUND_10 = 13,
	ROUND_11 = 14,
	HARVEST_4 = 15,
	ROUND_12 = 16,
	ROUND_13 = 17,
	HARVEST_5 = 18,
	ROUND_14 = 19,
	HARVEST_6 = 20,
	END_GAME = 21,
};

enum MajorImprovement {
	FIREPLACE_2,
	FIREPLACE_3,
	COOKINGHEARTH_4,
	COOKINGHEARTH_5,
	WELL,
	CLAY_OVEN,
	STONE_OVEN,
	JOINERY,
	POTTERY,
	BASKETMAKERS,
};

struct Resource {
	uint8_t wood, clay, reed, stone, sheep, boar, cattle, grain, veggie, food;
	Resource();
};

Resource::Resource() {
	wood = 0; clay = 0; reed = 0; stone = 0;
	sheep = 0; boar = 0; cattle = 0;
	grain = 0; veggie = 0; food = 0;
}

struct ActionData {
	uint8_t round;
	uint8_t count;
	uint8_t max_count;
	uint8_t action_code;
};

#endif