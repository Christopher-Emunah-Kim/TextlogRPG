#pragma once  
#include <cstdint>

using namespace std;

struct FLevelProperties
{
	int32_t maxExperiencePerLevel;
	int32_t maxHealthPerLevel;
	int16_t attackPerLevel;
	int16_t defensePerLevel;
	int16_t agilityPerLevel;
};

static FLevelProperties levelData[100]; // Array to hold level data for 100 levels

class LevelData  
{  
private:  

public:
	//Constructor
	LevelData();
	
	FLevelProperties GetLevelData(int16_t level);

	//Destructor
	~LevelData();
};
