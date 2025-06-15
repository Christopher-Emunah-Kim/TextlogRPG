#include "LevelAreaManager.h"
#include "BaseLevel.h"

LevelAreaManager::LevelAreaManager()
	: m_playerPtr(nullptr),
	m_currentState(EGameState::TITLE) 
{ }

LevelAreaManager::~LevelAreaManager()
{
	m_levelAreaMap.clear();
	m_gameObjects.clear();
}

void LevelAreaManager::Init(Player* player)
{
	m_playerPtr = player;

	BaseLevel* currentArea = GetCurrentLevelArea();
	if (currentArea)
	{
		currentArea->Enter(player);
	}
	else
	{
		Common::PrintErrorMsg("현재 LevelArea가 없습니다. 초기화를 중단합니다.");
		return;
	}

	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		IGameObject* gameObject = m_gameObjects[i];
		if (gameObject)
		{
			gameObject->Init();
		}
		else
		{
			Common::PrintErrorMsg("GameObject가 nullptr 입니다. 초기화를 중단합니다.");
		}
	}

}

void LevelAreaManager::Update(float deltaTime)
{
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		IGameObject* gameObject = m_gameObjects[i];
		if (gameObject)
		{
			gameObject->Update(deltaTime);
		}
	}

	//TODO : 각 Area의 게임루프를 여기로 끄집어올리기.

}

void LevelAreaManager::Render()
{
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		IGameObject* gameObject = m_gameObjects[i];
		if (gameObject)
		{
			gameObject->Render();
		}
	}
}

EGameState LevelAreaManager::ProcessCurrentArea(Player* player, float deltaTime /*= 0.0f*/)
{
	BaseLevel* currentArea = GetCurrentLevelArea();

	if (currentArea != nullptr)
	{
		EGameState nextState = currentArea->Run(player, deltaTime);
		return nextState;
	}
	else
	{
		Common::PrintErrorMsg("현재 LevelArea가 nullptr 입니다. 게임 루프를 중단합니다.");
		return EGameState::GAME_OVER;
	}

	return m_currentState;
}

EGameState LevelAreaManager::GetCurrnetState() const
{
	return m_currentState;
}

void LevelAreaManager::SetCurrentState(const EGameState& newState)
{
	m_currentState = newState;
}

void LevelAreaManager::RegisterGameObejcts(IGameObject* gameObject)
{
	if (gameObject != nullptr)
	{
		m_gameObjects.push_back(gameObject);
	}
	else
	{
		Common::PrintErrorMsg("GameObject가 nullptr 입니다. 등록을 중단합니다.");
	}
}

void LevelAreaManager::UnregisterGameObjects(IGameObject* gameObject)
{
	vector<IGameObject*>::iterator it = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
	if (it != m_gameObjects.end())
	{
		m_gameObjects.erase(it);
	}
	else
	{
		Common::PrintErrorMsg("GameObject가 등록되어 있지 않습니다. 제거를 중단합니다.");
	}
}

void LevelAreaManager::ClearGameObjects()
{
	m_gameObjects.clear();
}

BaseLevel* LevelAreaManager::GetLevelArea(const EGameState& state) const
{
	unordered_map<EGameState, BaseLevel*>::const_iterator it = m_levelAreaMap.find(state);
	if (it != m_levelAreaMap.end())
	{
		return it->second;
	}
	else
	{
		Common::PrintErrorMsg("해당 EGameState에 대한 LevelArea가 등록되어 있지 않습니다.");
		return nullptr;
	}
}

BaseLevel* LevelAreaManager::GetCurrentLevelArea() const
{
	return GetLevelArea(m_currentState);
}

void LevelAreaManager::RegisterLevelArea(const EGameState& state, BaseLevel* levelArea)
{
	if (levelArea != nullptr)
	{
		m_levelAreaMap[state] = levelArea;
	}
	else
	{
		Common::PrintErrorMsg("LevelArea가 nullptr 입니다. 등록을 중단합니다.");
	}
}
