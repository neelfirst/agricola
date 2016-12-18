agricola ai work
by 1000s, first history found was 1551000
run at work 1 by 1
sudo pip install beautifulsoup4 

A C++ implementation of Agricola

Purpose: Provide a framework and CLI for human/machine agents to play as players in a game of Agricola.

Details:
- implement both variants of Agricola (family style, [normal style])
- implement 1-5 player versions
- provide clear CLI for an agent to build a state table and take an action

Framework:
Class Game: the master class
- Enum Action: All possible base actions are enumerated here.
- Struct Space: Spaces describe possible base actions, whether they are free or not, resources that can be collected.
- Struct Major: Majors describe major improvements, their cost and their availability
- Class Player: the player class
	- Struct Farm: The farm board
	- Struct Resources: Player resources
	- Fences, Stables, # People

Game flow:
- Initialize Game based on # Players, Family Style
- Game initializes round & space order
- Game initializes list of players
- Game initializes major improvements
- Game initializes Space resources
- Start Game: move current round from 0 to 1
- Request Player Move
- Update Game based on Player Move

State Map

START --> WAIT(GET_MOVE) <--> UPDATE(SET_MOVE) --> END