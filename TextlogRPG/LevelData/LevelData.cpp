#include "../../TextlogRPG/LevelData/LevelData.h"

int32_t LevelData::experiencePerLevel[100];
int16_t LevelData::statsPerLevel[100][4];

LevelData::LevelData()
{
	for (int8_t i = 0; i < 100; ++i)
	{
		if (i == 0)
		{
			experiencePerLevel[i] = InitializationData[0];
			statsPerLevel[i][0] = InitializationData[1];
			statsPerLevel[i][1] = InitializationData[2];
			statsPerLevel[i][2] = InitializationData[3];
			statsPerLevel[i][3] = InitializationData[4];
		}
		else
		{
			experiencePerLevel[i] = experiencePerLevel[i - 1] + 2000; //EXP
			statsPerLevel[i][0] = statsPerLevel[i - 1][0] + 500; //HP
			statsPerLevel[i][1] = statsPerLevel[i - 1][1] + 3; //ATK
			statsPerLevel[i][2] = statsPerLevel[i - 1][2] + 2; //DEF
			statsPerLevel[i][3] = statsPerLevel[i - 1][3] + 2; //AGI
		}
	}
}

const int32_t& LevelData::getExperienceForLevel(int16_t level)
{
	if (level < 1 || level > 100) return experiencePerLevel[0]; 
	return experiencePerLevel[level - 1];
}

const int16_t* LevelData::getStatsForLevel(int16_t level)
{
	if (level < 1 || level > 100) return nullptr;
	return statsPerLevel[level - 1];
}


LevelData::~LevelData()
{

}
