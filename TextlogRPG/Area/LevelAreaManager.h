#pragma once
#include "../Util/Common.h"
#include "../Util/EGameState.h"
#include "../Core/IGameObject.h"

class BaseLevel;
class Player;

class LevelAreaManager
{
public:
	LevelAreaManager();
	~LevelAreaManager();

private:
	Player*													m_playerPtr;
	EGameState												m_currentState;
	vector<IGameObject*>								m_gameObjects;
	unordered_map<EGameState, BaseLevel*>		m_levelAreaMap;

public: //GAME LOOP
	void Init(Player* player);
	void Update(float deltaTime);
	void Render();

	EGameState		ProcessCurrentArea(Player* player, float deltaTime = 0.0f);

public: //Managing Game State
	EGameState		GetCurrnetState() const;
	void				SetCurrentState(const EGameState& newState);

public: //Managing GameObjects
	void				RegisterGameObejcts(IGameObject* gameObject);
	void				UnregisterGameObjects(IGameObject* gameObject);
	void				ClearGameObjects();

public: //Managing LevelAreas
	BaseLevel*		GetLevelArea(const EGameState& state) const;
	BaseLevel*		GetCurrentLevelArea() const;
	void				RegisterLevelArea(const EGameState& state, BaseLevel* levelArea);


};

