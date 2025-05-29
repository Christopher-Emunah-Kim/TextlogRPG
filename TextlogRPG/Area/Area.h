#pragma once
#include "../Util/Common.h"

class Player;

class Area {
public:
    virtual ~Area() = default;
    virtual string GetAreaName() const = 0;
    virtual void Enter(Player* player) = 0;
};