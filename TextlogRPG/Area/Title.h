#pragma once
#include "Area.h"

class Title : public Area 
{
public:
	virtual string GetAreaName() const override { return "Title"; }
	virtual void Enter(Player* player) override;
};