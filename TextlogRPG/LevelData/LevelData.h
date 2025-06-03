#pragma once  
#include "../Util/Common.h"

using namespace std;

struct FLevelProperties
{
	uint32 maxExperiencePerLevel;
	uint32 maxHealthPerLevel;
	uint16 attackPerLevel;
	uint16 defensePerLevel;
	uint16 agilityPerLevel;
};

static FLevelProperties levelData[100]; // Array to hold level data for 100 levels

class LevelData  
{  
private:  

public:
	//Constructor
	LevelData();
	
	FLevelProperties GetLevelData(uint16 level);

	//Destructor
	~LevelData();
};
