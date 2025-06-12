#pragma once
#include "Area.h"

enum class EGameState;

class Title : public Area 
{
public:
	Title();
	virtual ~Title();

public:
	virtual string GetAreaName() const override { return "Title"; }
	virtual void Enter(Player* player) override;

public:
	void Initialize(Player* player);
	EGameState Process(Player* player);

private:
	EGameState HandleChoice(char menuChoice, Player* player);

	void RenderPlayerGreeting(Player* player);

};