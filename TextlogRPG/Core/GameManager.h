#pragma once
#include <unordered_map>
#include <string>

constexpr __int32 DEFAULT_HEAL_COST = 15;
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
	//Main Process of Game
	void InitializeGame();
	void RenderWelcomMsg();
	void RequestPlayerName();

	//TITLE
	void RunProcessTitle();
	void RenderTitlePrompt();
	void UpdateTitleMenuChoice(char menuChoice);

	//VILLAGE
	void RunProcessVillage();
	/*void InitializeVillage(Village* pVilalgeArea, Healer* healer, Merchant* merchant);
	void RenderVillagePrompt(Village* pVilalgeArea);
	void UpdateVillageChoice(const char& villageChoice, Village* pVilalgeArea, Healer* healer, Merchant* merchant);
	void ClearVillage(Healer*& healer, Merchant*& merchant);*/

	//DUNGEON
	void RunProcessDungeon();
	void InitializeDungeon();
	void CreateDungeonStages();
	void RenderDungeonMenu();
	void UpdateDungeonBattleChoice();
	void RenderDungeonRunChoice();
	void UpdateDungeonChoice(char dungeonChoice);
	void RenderDungwonWrongChoice();
	void BattleInDungeonStage(const vector<Monster*>& monsters, DungeonStage* stage);
	void RenderGameOverMsg();

};