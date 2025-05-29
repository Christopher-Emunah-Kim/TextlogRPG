#pragma once
#include "Area.h"

class Title : public Area 
{
public:
    string GetAreaName() const override { return "Title"; }
    void Enter(Player* player) override;
};