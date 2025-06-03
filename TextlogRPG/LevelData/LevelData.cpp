#include "../../TextlogRPG/LevelData/LevelData.h"
#include <iostream>

using namespace std;

LevelData::LevelData()
{
	// Initialize level data for 100 levels
	for (int i = 0; i < 100; ++i)
	{
		levelData[i].maxExperiencePerLevel = 100 + (i * 50); // Example formula
		levelData[i].maxHealthPerLevel = 100 + (i * 10); // Example formula
		levelData[i].attackPerLevel = 5 + (i * 2); // Example formula
		levelData[i].defensePerLevel = 3 + (i * 1); // Example formula
		levelData[i].agilityPerLevel = 2 + (i * 1); // Example formula
	}
	//TODO : 레벨데이터 csv파일에서 값 가져와 세팅하기
}

FLevelProperties LevelData::GetLevelData(uint16 level)
{
	
	if (level < 1 || level > 100)
	{
		cout << "Level must be between 1 and 100." << endl;
        return FLevelProperties{ 0, 0, 0, 0, 0 };
	}
	return levelData[level - 1];
}

LevelData::~LevelData() { }
