#pragma once  
#include "../Util/Common.h"

using namespace std;

constexpr __int8 ADDITIONAL_EXPERIENCE_PER_LEVEL = 50; 
constexpr __int8 ADDITIONAL_HEALTH_PER_LEVEL = 10;
constexpr __int8 ADDITIONAL_ATTACK_PER_LEVEL = 1;
constexpr __int8 ADDITIONAL_DEFENSE_PER_LEVEL = 1;
constexpr __int8 ADDITIONAL_AGILITY_PER_LEVEL = 1;

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
	
public:
	FLevelProperties GetLevelData(int16 level);

	
};
