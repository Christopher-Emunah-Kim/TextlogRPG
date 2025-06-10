# WMTextRPG

// Text-based RPG Game Design Document

[BaseCharacter]

0.0 class BaseCharacter <abstract>
0.0.0 int16 level
0.0.1 int32 health
0.0.2 int32 maxHealth
0.0.3 string characterName
0.0.4 int16 stats[3] #Attack, Defense, Agility
0.0.5 void Heal(int32 amount) = 0
0.0.6 void TakeDamage(int32 damage) = 0
0.0.7 int16 GetAttack(BaseCharacter* character) = 0
0.0.8 int16 GetDefense(BaseCharacter* character) = 0
0.0.9 int16 GetAgility(BaseCharacter* character) = 0

0.1 class Player - Derived
0.0.0 int32 playerExperience
0.0.1 int32 playerGold
0.0.2 Weapon* weaponEquipped
0.0.3 Armor* armorEquipped
0.0.4 void LevelUp()
0.0.5 void GainLoot(int32 experience, int32 gold, Item* item)
0.0.6 void EquipItem(Item* item)

0.2 class Monster - Derived
0.2.0 int32 dropExperience
0.2.1 vector<Item*> dropitems //weapon, armor, misc items
0.2.2 void DropLoot(Player* player)

[NonPlayerCharacter]

1.0 class NonPlayerCharacter <abstract>
1.0.0 string npcName
1.0.1 enum class NPCType {HEALER, MERCHANT}
1.0.2 NPCType type
1.1 class Healer
1.1.0 int32 healCost
1.1.1 void HealPlayer(Player* player, int32 cost)
1.2 class Merchant
1.2.0 vector<Item*> itemsForSale
1.2.1 map<Item*, int32> itemPrices
1.2.2 void SellItem(Player* player, Item* item)
1.2.3 void BuyItem(Player* player, Item* item)

[Area]

2.0 class Area <abstract>

2.3 class Title - Derived

2.1 class Village - Derived
2.1.0 vector<NonPlayerCharacter*> npcCharacters
2.1.1 void AddNPC(NonPlayerCharacter* npc)
2.1.2 void RemoveNPC(NonPlayerCharacter* npc)
2.1.3 void GetNPCList(vector<NonPlayerCharacter*>& npcList)
2.1.4 void InteractWithNPC(Player* player, NonPlayerCharacter* npc)

2.2 class Dungeon
2.2.0 vector<Monster*> monsters
2.2.1 void AddMonster(Monster* monster)
2.2.2 void RemoveMonster(Monster* monster)
2.2.3 void GetMonsterList(vector<Monster*>& monsterList)
2.2.4 void EnterDungeon(Player* player)
2.2.5 void ExitDungeon(Player* player)
2.2.6 void EncounterMonster(Player* player, Monster* monster)

[Item]
3.0 class Item <abstract>
3.0.0 string itemName
3.0.1 int16 itemStats[3] itemStats //Attack, Defense, Agility
3.0.2 enum class ItemType {WEAPON, ARMOR, MISC}
3.0.3 ItemType itemType
3.0.4 int32 itemCost
3.0.5 void Use(Player* player) = 0

3.1 class Wepon - Derived
3.2 class Armor - Derived
3.3 class MiscItem - Derived

[BattleSystem]
4.0 class BattleSystem
4.0.1 void StartBattle(Player* player, Monster* monster)
//Turn-based battle system
//Fight until one character's health reaches 0
//Turn order is determined by agility
//If agility is the same, player goes first
//Player and monster take turns attacking each other
//Fomula for damage: Damage = p1's Attack - p2's Defense
//Battle results are displayed


[LevelData]
5.0 class LevelData
5.0.1 static const int32 experiencePerLevel[100] //Experience required for each level
5.0.2 static const int16 statsPerLevel[100][4] //Status per level (HP, ATK, DEF, AGI)

[GameMode]
6.0 class GameMode 
6.0.1 Enum class EGameState
6.0.2 EGameState currentState
6.0.3 EGameState& GetCurrentState() const
6.0.4 void ChangeGameState(EGameState newState)
6.0.5 void InitializeGame()
//Game states: TITLE, VILLAGE, DUNGEON



//기획

1. Character
1-1. 플레이어 -> 상속 구조
 - 스탯 : 레벨, 보유 경험치, HP, 공격력, 방어력, 민첩성, 보유 금화
 - 장비 슬롯 : 무기, 방어구
1-2. 몬스터 -> 상속구조
 - 스탯 : 레벨, HP, 공격력, 방어력, 민첩성
 - 드랍 : 주는경험치, 아이템(무기, 방어구, 잡템 각 3종 중 1개를 드랍)
1-3. NPC -> 상속구조
 - 치유사 : 금화로,  HP 회복
 - 상점 : 장비구매, 판매

2. 지역
2-1. 마을
 - NPC
2-2. 사냥터
 - 몬스터

3. 전투
 - 턴 : 민첩성이 동일 할 경우 턴은 나와 몬스터 1회씩
 - 선타 : 민첩성이 높은 쪽이 선타
 - 전투 공식 = 공 - 방
 - 전투 결과

4. 데이터(배열)
 - 레벨별 필요 경험치 량
 - 레벨별 각 스탯

5. 게임모드, 게임스테이트 (옵션)
 - 타이틀
 - 마을
 - 사냥터

//필수 구현 요소
const 를 사용할것
explicit
stl 2종류 이상
상속, 다형성
동적할당, 포인터
casting
design pattern 
abstract class, pure virtual function
