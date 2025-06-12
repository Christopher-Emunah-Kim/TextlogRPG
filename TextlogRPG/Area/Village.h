#pragma once
#include "Area.h"

class NonPlayerCharacter;
class Player;
class Healer;
class Merchant;
class Item;
enum class EGameState;

class Village : public Area 
{
public:
	Village();
	virtual ~Village();

private:
    vector<NonPlayerCharacter*> vecNpcCharacters;
	Healer* healerNPC;
	Merchant* merchantNPC;


	void RenderVillagePrompt();

public:
	virtual string GetAreaName() const override { return "Village"; }

	virtual void Enter(Player* player) override;

public:
	void Initialize(Player* player);
	EGameState Process(Player* player);
	void Clear();

public:
	void AddNPC(NonPlayerCharacter* npc);
    void RemoveNPC(NonPlayerCharacter* npc);
	vector<NonPlayerCharacter*>& GetNPCList();
    void InteractWithNPC(Player* player, NonPlayerCharacter* npc);

	EGameState HandleChoice(char villageChoice, Player* player);
};