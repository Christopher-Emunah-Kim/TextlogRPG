#include "../../TextlogRPG/LevelData/LevelData.h"
#include "../Character/CharacterInfo.h"
#include "../Character/CharacterStatus.h"
#include <iostream>

using namespace std;

LevelData::LevelData()
{
	// Initialize level data for 100 levels
	for (int i = 0; i < 100; ++i)
	{
		levelDataArray[i].maxExperiencePerLevel = DEFAULT_PLAYER_MAX_EXPERIENCE + (i * ADDITIONAL_EXPERIENCE_PER_LEVEL); // Example formula
		levelDataArray[i].maxHealthPerLevel = DEFAULT_CHARACTER_MAX_HEALTH + (i * ADDITIONAL_HEALTH_PER_LEVEL); // Example formula
		levelDataArray[i].attackPerLevel = DEFAULT_ATTACK + (i * ADDITIONAL_ATTACK_PER_LEVEL); // Example formula
		levelDataArray[i].defensePerLevel = DEFAULT_DEFENSE + (i * ADDITIONAL_DEFENSE_PER_LEVEL); // Example formula
		levelDataArray[i].agilityPerLevel = DEFAULT_AGILITY + (i * ADDITIONAL_AGILITY_PER_LEVEL); // Example formula
	}
	//TODO : 레벨데이터 csv파일에서 값 가져와 세팅하기
}

FLevelProperties LevelData::GetLevelData(int16 level)
{
	
	if (level < 1 || level > 100)
	{
		cout << "Level must be between 1 and 100." << endl;
        return FLevelProperties{ 
			DEFAULT_PLAYER_MAX_EXPERIENCE, 
			DEFAULT_CHARACTER_MAX_HEALTH, 
			DEFAULT_ATTACK, 
			DEFAULT_DEFENSE, 
			DEFAULT_AGILITY };
	}
	return levelDataArray[level - 1];
}

LevelData::~LevelData() { }
