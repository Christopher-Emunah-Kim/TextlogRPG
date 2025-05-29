#pragma once
#include "Area.h"

class NonPlayerCharacter;

class Village : public Area 
{
private:
    vector<NonPlayerCharacter*> npcCharacters;
public:
    string GetAreaName() const override { return "Village"; }

    void Enter(Player* player) override;

    void AddNPC(NonPlayerCharacter* npc);

    void RemoveNPC(NonPlayerCharacter* npc);

	vector<NonPlayerCharacter*>& GetNPCList();

    void InteractWithNPC(Player* player, NonPlayerCharacter* npc);
    
};