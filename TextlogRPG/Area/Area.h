#pragma once
#include "../Util/Common.h"
#include "../Util/EGameState.h"

class Player;
enum class EGameState;

class Area 
{
public:
    virtual		~Area() = default;

protected:
	bool				m_isRunning = false;
	EGameState			m_nextState = EGameState::TITLE;
	char				m_input = 0;
	float				m_accumulatedTime = 0.0f;

public:
	virtual				EGameState Run(Player* player, float deltaTime = 0.0f);

public:
    virtual string		GetAreaName() const = 0;
    virtual void		Enter(Player* player) = 0;
	
protected:
	//GAME LOOP
	virtual void		ProcessInput(Player* player) = 0;
	virtual void		Update(float deltaTime) = 0;
	virtual void		Render() = 0;

	//EXIT CONDTIONS
	virtual bool		ShouldExit() = 0;
	virtual EGameState	GetNextState() = 0;


};