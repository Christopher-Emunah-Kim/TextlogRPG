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
	EGameState							m_gameState;
    Player*								m_playerPtr;
	Dungeon*							m_dungeonptr;
	unordered_map<EGameState, Area*>	m_sceneAreaMap;

public:
    void				Run();
	
public:
	inline void			SetGameState(const EGameState& gs_in)	 { m_gameState = gs_in; }
	inline EGameState	GetGameState() const 	{ return m_gameState;	}

private:
	//START GAME
	void				InitializeGame();
	void				RenderWelcomMsg();
	void				RequestPlayerName();

	//TITLE
	void				RunProcessTitle(float deltaTime = 0.0f);

	//VILLAGE
	void				RunProcessVillage(float deltaTime = 0.0f);

	//DUNGEON
	void				RunProcessDungeon(float deltaTime = 0.0f);

};