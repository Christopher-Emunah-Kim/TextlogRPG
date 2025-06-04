#pragma once  
#include "../Util/Common.h"

using namespace std;

struct FLevelProperties
{
	int32 maxExperiencePerLevel;
	int32 maxHealthPerLevel;
	int16 attackPerLevel;
	int16 defensePerLevel;
	int16 agilityPerLevel;
};

static FLevelProperties levelData[100]; // Array to hold level data for 100 levels

class LevelData  
{  

public:
	LevelData();
	~LevelData();

	FLevelProperties GetLevelData(int16 level);

	
};
