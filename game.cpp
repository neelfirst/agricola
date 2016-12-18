#include "game.h"
#include <string> // std::string
#include <stdlib> // std::srand, std::rand
#include <time> // std::time
#include <vector> // std::vector
#include <algorithm> // std::random_shuffle
#include <iostream> // std::cout, std::cerr

std::string getName(uint8_t i) // fun little name bank
{
	switch (i)
	{
		case 1: return "Neel"; break;
		case 2: return "Dave"; break;
		case 3: return "Simon"; break;
		case 4: return "Thomas"; break;
		case 5: return "Rick"; break;
		default: return "???"; break;
	}
	return "???"; break;
}

Game::Space::Space(Game::UseState s, Game::Action a)
{
	status = s; action = a;
	resources = Resource(); // all zeroes
	switch (action)
	{
		case SP_FOOD_1:	resources.food += 1;	break;
		case WOOD_1:	resources.wood += 1;	break;
		case WOOD_2:	resources.wood += 2;	break;
		case WOOD_3:	resources.wood += 3;	break;
		case WOOD_4:	resources.wood += 4;	break;
		case CLAY_1:	resources.clay += 1;	break;
		case CLAY_2:	resources.clay += 2;	break;
		case CLAY_3:	resources.clay += 3;	break;
		case RSW:		resources.reed += 1;	break;
		case TRAVEL_1:	resources.food += 1;	break;
		case BUILD_TRAVEL: resources.food += 1;	break;
		case REED_1:	resources.reed += 1;	break;
		case FISH_1:	resources.food += 1;	break;
		case SHEEP_1:	resources.sheep += 1;	break;
		case STONE_1:	resources.stone += 1;	break;
		case BOAR_1:	resources.boar += 1;	break;
		case CATTLE_1:	resources.cattle += 1;	break;
		default:								break;
	}
}

Game::Major::Major(MajorImprovement m)
{
	cost = Resource();
	mcode = m;
	status = Game::UseState::OPEN;
	switch (mcode)
	{
		case FIREPLACE_2:
			name = "Fireplace";
			cost.clay += 2;
			points = 1;
			break;
		case FIREPLACE_3:
			name = "Fireplace";
			cost.clay += 3;
			points = 1;
			break;
		case COOKINGHEARTH_4:
			name = "Cooking Hearth";
			cost.clay += 4;
			points = 1;
			break;
		case COOKINGHEARTH_5:
			name = "Cooking Hearth";
			cost.clay += 5;
			points = 1;
			break;
		case WELL:
			name = "Well";
			cost.wood += 1;
			cost.stone += 3;
			points = 4;
			break;
		case CLAY_OVEN:
			name = "Clay Oven";
			cost.clay += 3;
			cost.stone += 1;
			points = 2;
			break;
		case STONE_OVEN:
			name = "Stone Oven";
			cost.clay += 1;
			cost.stone += 3;
			points = 3;
			break;
		case JOINERY:
			name = "Joinery";
			cost.wood += 2;
			cost.stone += 2;
			points = 2;
			break;
		case POTTERY:
			name = "Pottery";
			cost.clay += 2;
			cost.stone += 2;
			points = 2;
			break;
		case BASKETMAKERS:
			name = "Basketmaker's Workshop";
			cost.reed += 2;
			cost.stone += 2;
			points = 2;
			break;
		default: assert(false); break;
	}
}

Game::Game(uint8_t p, bool f)
{
	player_count = p;
	is_family_game = f;
	current_round = 0;
	std::srand(std::time(NULL));

	/* 1. generate action set
	 * std01-std10 are the standard 10 actions
	 * available at the start of any game
	 * round actions are selected randomly from
	 * their respective stages */
	action_set["std1"] = Space(OPEN, ROOM_STABLE);
	action_set["std2"] = Space(OPEN, SP_FOOD_1);
	action_set["std3"] = Space(OPEN, GRAIN);
	action_set["std4"] = Space(OPEN, PLOW);
	if (is_family_game)	action_set["std5"] = Space(OPEN, STABLES);
	else 				action_set["std5"] = Space(OPEN, OCCUPATION);
	action_set["std6"] = Space(OPEN, DAY_LABORER);
	if (player_count == 1)	action_set["std7"] = Space(OPEN, WOOD_2);
	else					action_set["std7"] = Space(OPEN, WOOD_3);
	action_set["std8"] = Space(OPEN, CLAY_1);
	action_set["std9"] = Space(OPEN, REED_1);
	action_set["std10"] = Space(OPEN, FISH_1);
	action_set["round14"] = Space(LOCKED, RENOVATE_FENCES);

	if (player_count == 3) {
		action_set["ext1"] = Space(OPEN, WOOD_2);
		action_set["ext2"] = Space(OPEN, CLAY_1);
		action_set["ext3"] = Space(OPEN, OCCUPATION3);
		action_set["ext4"] = Space(OPEN, ANY1);
		action_set["ext5"] = NULL;
		action_set["ext6"] = NULL;
	}
	else if (player_count == 4) {
		action_set["ext1"] = Space(OPEN, WOOD_2);
		action_set["ext2"] = Space(OPEN, WOOD_1);
		action_set["ext3"] = Space(OPEN, OCCUPATION4);
		action_set["ext4"] = Space(OPEN, CLAY_2);
		action_set["ext5"] = Space(OPEN, RSF);
		action_set["ext6"] = Space(OPEN, TRAVELING_1);
	}
	else if (player_count == 5) {
		action_set["ext1"] = Space(OPEN, WOOD_4);
		action_set["ext2"] = Space(OPEN, CLAY_3);
		action_set["ext3"] = Space(OPEN, RSW);
		action_set["ext4"] = Space(OPEN, BUILD_TRAVELING_1);
		action_set["ext5"] = Space(OPEN, OCC4_R5FG);
		action_set["ext6"] = Space(OPEN, MULTI_ANIMAL);
	}

	std::vector<Space> stage1;
	stage1.push_back(Space(LOCKED, SHEEP_1));
	stage1.push_back(Space(LOCKED, SOW_BAKE));
	stage1.push_back(Space(LOCKED, FENCES));
	stage1.push_back(Space(LOCKED, IMPROVEMENT));
	std::random_shuffle(stage1.begin(), stage1.end());
	action_set["round1"] = stage1[0];
	action_set["round2"] = stage1[1];
	action_set["round3"] = stage1[2];
	action_set["round4"] = stage1[3];

	std::vector<Space> stage2;
	stage2.push_back(Space(LOCKED, STONE_1));
	stage2.push_back(Space(LOCKED, RENOVATE_IMP));
	stage2.push_back(Space(LOCKED, FGMI));
	std::random_shuffle(stage2.begin(), stage2.end());
	action_set["round5"] = stage2[0];
	action_set["round6"] = stage2[1];
	action_set["round7"] = stage2[2];

	std::vector<Space> stage3;
	stage3.push_back(Space(LOCKED, BOAR_1));
	stage3.push_back(Space(LOCKED, VEGGIE));
	std::random_shuffle(stage3.begin(), stage3.end());
	action_set["round8"] = stage3[0];
	action_set["round9"] = stage3[1];

	std::vector<Space> stage4;
	stage4.push_back(Space(LOCKED, CATTLE_1));
	stage4.push_back(Space(LOCKED, STONE_1));
	std::random_shuffle(stage4.begin(), stage4.end());
	action_set["round10"] = stage4[0];
	action_set["round11"] = stage4[1];

	std::vector<Space> stage5;
	stage5.push_back(Space(LOCKED, PLOW_SOW));
	stage5.push_back(Space(LOCKED, FGWR));
	std::random_shuffle(stage5.begin(), stage5.end());
	action_set["round12"] = stage5[0];
	action_set["round13"] = stage5[1];

	/* 2. generate round vector
	 * this is fixed and includes harvests 
	 * not really sure what to use this for yet */
	rounds.push_back("round0"); // for the day we add cards... someday... SOMEDAY
	rounds.push_back("round1");
	rounds.push_back("round2");
	rounds.push_back("round3");
	rounds.push_back("round4");
	rounds.push_back("harvest1");
	rounds.push_back("round5");
	rounds.push_back("round6");
	rounds.push_back("round7");
	rounds.push_back("harvest2");
	rounds.push_back("round8");
	rounds.push_back("round9");
	rounds.push_back("harvest3");
	rounds.push_back("round10");
	rounds.push_back("round11");
	rounds.push_back("harvest4");
	rounds.push_back("round12");
	rounds.push_back("round13");
	rounds.push_back("harvest5");
	rounds.push_back("round14");
	rounds.push_back("harvest6");

	/* 3. initialize Major Improvements */
	improvements.push_back(Major(FIREPLACE_2));
	improvements.push_back(Major(FIREPLACE_3));
	improvements.push_back(Major(COOKINGHEARTH_4));
	improvements.push_back(Major(COOKINGHEARTH_5));
	improvements.push_back(Major(WELL));
	improvements.push_back(Major(CLAY_OVEN));
	improvements.push_back(Major(STONE_OVEN));
	improvements.push_back(Major(JOINERY));
	improvements.push_back(Major(POTTERY));
	improvements.push_back(Major(BASKETMAKERS));

	/* 4. initialize Player list
	 * no point in randomizing */
	for (int i = 0; i < player_count; i++)
		players.push_back(Player(i, getName(i)));
}

bool Game::update(Action a)
{
	// outright invalid action checks
	if (a.round < 0 || a.round > 21) {
		std::cerr << "Game::update - invalid round provided by Action: "
		 << a.round << std::endl;
		return false;
	}
	if (a.count > a.max_count) {
		std::cerr << "Game::update - action count exceeds max_count: "
		 << a.count << " " << a.max_count << std::endl;
		return false;
	}
	// get current game state - self.current_actions
	// state-based action validity check
	/* --> we are searching for the existence of an action, which would be easier
	   --> if the actions were keys instead of values, then the values could be round IDs 
	   --> unavailable actions can be marked invalid instead of round_x
	   --> even then we need a bimap so we can recover the action space in the next round */

	// with the new Space paradigm we can pass the whole action_set around, identify actions by keys

	// execute action (update action[space] to unavailable)
	// instruct PLAYER how to update Resources/Farm (somehow...)
	// if !last_action return modified action map 
	// else if last_action move (immediately?) to next round
	// if round == 4/7/9/11/13/14 move to harvest
}

bool Game::start()
{
	if (current_round != 0)
	{
		std::cout << "Error: Game::start called while current_round != 0" << std::endl;
		return false;
	}
	if (!is_family_game)
	{
		// deal with cards
	}
	current_round = 1;
	return true;
}

void Game::unlock (Space &space) { space.status = OPEN; }