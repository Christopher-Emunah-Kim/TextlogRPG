#pragma once  
#include <cstdint>

using namespace std;

class LevelData  
{  
private:  
	// Experience required for each level  
	static int32_t experiencePerLevel[100];

	// Status per level (HP, ATK, DEF, AGI)  
	static int16_t statsPerLevel[100][4]; 
	
	//Initialized Data
	const int16_t InitializationData[5] { 100, 100, 10, 10, 10 }; //EXP, HP, ATK, DEF, AGI
public:
	//Constructor
	LevelData();
	
	// Returns the experience required for the given level
	const int32_t& getExperienceForLevel(int16_t level);

	// Returns a array pointer to the stats array for the given level
	const int16_t* getStatsForLevel(int16_t level);

	//Destructor
	~LevelData();
};
