#pragma once
#include <unordered_map>
#include <string>

constexpr __int8   DEFAULT_NAMING_LENGTH = 20;

using namespace std;

class Player;
class Monster;
class Healer;
class Merchant;
class Area;
class Village;
class Dungeon;
class DungeonStage;
enum class EGameState;


class GameManager 
{
public:
	GameManager(EGameState initialState, Player* player, Dungeon* dungeon);

	~GameManager();

private:
	EGameState gameState;
    Player* playerPtr;
	Dungeon* dungeonptr;
	unordered_map<EGameState, Area*> gameAreaMap;

public:
    void Run();
	
public:
	inline void SetGameState(const EGameState& gs_in)	 { gameState = gs_in; }
	inline EGameState GetGameState() const 	{ return gameState;	}

private:
	//START GAME
	void InitializeGame();
	void RenderWelcomMsg();
	void RequestPlayerName();

	//TITLE
	void RunProcessTitle();

	//VILLAGE
	void RunProcessVillage();

	//DUNGEON
	void RunProcessDungeon();

};