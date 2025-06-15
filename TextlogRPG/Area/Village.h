#pragma once
#include "BaseLevel.h"

class NonPlayerCharacter;
class Player;
class Healer;
class Merchant;
class Item;
enum class EGameState;

constexpr __int32 DEFAULT_HEAL_COST = 15;

enum class EVillageState
{
	MAIN_MENU,
	INTERACTING,
	LEAVING
};



class Village : public BaseLevel 
{
public:
	Village();
	virtual ~Village();

private:
    vector<NonPlayerCharacter*>		vecNpcCharacters;
	Healer*							m_healerNPC;
	Merchant*						m_merchantNPC;
	Player*							m_player = nullptr;
	bool							m_isInteractingWithNPC = false;
	NonPlayerCharacter*				m_currentNPC = nullptr;
	EVillageState					m_villageState = EVillageState::MAIN_MENU;


public:
	virtual string					GetAreaName() const override { return "Village"; }
	virtual void					Enter(Player* player) override;

protected:
	virtual void					ProcessInput(Player* player) override;
	virtual void					Update(float deltaTime) override;
	virtual void					Render() override;

	virtual bool					ShouldExit() override;
	virtual EGameState				GetNextState() override;

public:
	void							Initialize(Player* player);
	EGameState						Process(Player* player);
	void							Clear();

public:
	void							AddNPC(NonPlayerCharacter* npc);
    void							RemoveNPC(NonPlayerCharacter* npc);
    void							InteractWithNPC(Player* player, NonPlayerCharacter* npc);
	void							RenderVillagePrompt();
	vector<NonPlayerCharacter*>&	GetNPCList();

};