#pragma once
#include "BaseLevel.h"

enum class EGameState;

class Title : public BaseLevel 
{
public:
	Title();
	virtual ~Title();

private:
	Player*		m_player = nullptr;
	bool		m_shouldShowMenu = true;
	bool		m_shouldShowStatus = false;

public:
	virtual string			GetAreaName() const override { return "Title"; }
	virtual void			Enter(Player* player) override;

public:
	void					Initialize(Player* player);
	EGameState				Process(Player* player);

protected:
	virtual void			ProcessInput(Player* player) override;
	virtual void			Update(float deltaTime) override;
	virtual void			Render() override;
	virtual bool			ShouldExit() override;
	virtual EGameState		GetNextState() override;

private:

	void					RenderPlayerGreeting(Player* player);

};