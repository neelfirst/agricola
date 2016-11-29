#ifndef __BAH_COMMON_H
#define __BAH_COMMON_H

// define action codes

#define UNAVAILABLE 0
#define ROOM_STABLE 1
#define SP_FOOD_1 2
#define SP_FOOD_2 3
//...
#define GRAIN 16
#define PLOW 17
#define STABLES 18
#define DAY_LABORER 19
#define WOOD_2 20
//...
#define CLAY_1 34
//...
#define REED_1 48
//...
#define FISH_1 62
//...
#define SHEEP_1 76
//...
#define FENCES 90
#define SOW_BAKE 91
#define IMPROVEMENT 92
#define STONE_1 93 // multiple items in the action list can be STONE_1
//...
#define FGMI 103
#define RENOVATE_IMP 104
#define BOAR_1 105
//...
#define VEGGIE 112
#define CATTLE_1 113
#define CATTLE_2 114
#define CATTLE_3 115
#define CATTLE_4 116
#define CATTLE_5 117
#define FGWR 118
#define PLOW_SOW 119
#define RENOVATE_FENCE 120

struct Action {
	uint8_t round;
	uint8_t move_number;
	uint8_t action_code;
};

#endif