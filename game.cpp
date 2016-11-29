#include "game.h"
#include <stdlib> // std::srand, std::rand
#include <time> // std::time
#include <vector> // std::vector
#include <algorithm> // std::random_shuffle

Game::Game(void)
{
	std::srand(std::time(NULL));
	/* 1. generate action set
	 * std01-std10 are the standard 10 actions
	 * available at the start of any game
	 * round actions are selected randomly from
	 * their respective stages */
	actions["std1"] = "room+stable";
	actions["std2"] = "sp+food_1";
	actions["std3"] = "grain";
	actions["std4"] = "plow";
	actions["std5"] = "stables";
	actions["std6"] = "daylaborer";
	actions["std7"] = "wood_2";
	actions["std8"] = "clay_1";
	actions["std9"] = "reed_1";
	actions["std10"] = "fish_1";
	actions["round14"] = "renovate+fences";

	std::vector<std::string> stage1;
	stage1.push_back("sheep_1");
	stage1.push_back("sow+bake");
	stage1.push_back("fences");
	stage1.push_back("improvement");
	std::random_shuffle(stage1.begin(), stage1.end());
	actions["round1"] = stage1[0];
	actions["round2"] = stage1[1];
	actions["round3"] = stage1[2];
	actions["round4"] = stage1[3];

	std::vector<std::string> stage2;
	stage2.push_back("stone_1");
	stage2.push_back("renovate+improvement");
	stage2.push_back("familygrowth")
	std::random_shuffle(stage2.begin(), stage2.end());
	actions["round5"] = stage1[0];
	actions["round6"] = stage1[1];
	actions["round7"] = stage1[2];

	std::vector<std::string> stage3;
	stage3.push_back("boar_1");
	stage3.push_back("veggie");
	std::random_shuffle(stage3.begin(), stage3.end());
	actions["round8"] = stage3[0];
	actions["round9"] = stage3[1];

	std::vector<std::string> stage4;
	stage4.push_back("cattle_1");
	stage4.push_back("stone_1");
	std::random_shuffle(stage4.begin(), stage4.end());
	actions["round10"] = stage4[0];
	actions["round11"] = stage4[1];

	std::vector<std::string> stage5;
	stage5.push_back("plow+sow");
	stage5.push_back("familygrowth+withoutroom");
	std::random_shuffle(stage5.begin(), stage5.end());
	actions["round12"] = stage1[0];
	actions["round13"] = stage1[1];
}