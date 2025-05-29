#pragma once
#include "Area.h"

class Monster;

class Dungeon : public Area {
private:
    vector<Monster*> monsters;
public:
    string GetAreaName() const override { return "Dungeon"; }
    void Enter(Player* player) override;
    void AddMonster(Monster* monster);
    void RemoveMonster(Monster* monster);
	vector<Monster*>& GetMonsterList();
    void EncounterMonster(Player* player, Monster* monster);
};