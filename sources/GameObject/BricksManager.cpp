#include "BricksManager.h"
#include "GameConfig/GameConfigMgr.h"
#include "GameObject/Brick.h"
BricksManager::BricksManager()
{
	Init();
}

BricksManager::~BricksManager()
{
}

void BricksManager::Init()
{
	std::shared_ptr<GameConfigMgr> gameConfig = GameConfigMgr::GetInstance();
	m_levelSize.x = gameConfig->GetConfigAsInt("LevelSizeX", 8);
	m_levelSize.y = gameConfig->GetConfigAsInt("LevelSizeY", 4);
	m_brickSize.x = gameConfig->GetConfigAsInt("BrickSizeX", 80);
	m_brickSize.y = gameConfig->GetConfigAsInt("BrickSizeY", 40);
	m_margin.x = gameConfig->GetConfigAsInt("BrickMarginX", 5);
	m_margin.y = gameConfig->GetConfigAsInt("BrickMarginY", 5);
}

void BricksManager::Draw()
{
	bool allInactive = true;
	for (std::vector<std::shared_ptr<Brick>>::iterator brick = m_bricks.begin(); brick != m_bricks.end(); brick++)
	{
		if (brick->get()->IsActive())
		{
			brick->get()->Draw();
			allInactive = false;
		}		
	}
	//all brick are inactive
	if (allInactive && m_onBrickBreakFunction)
	{
		m_onBrickBreakFunction();
	}
}

void BricksManager::Update()
{
}

void BricksManager::CreateBricks()
{
	Vector2 brickPos;
	using namespace std;
	for (int col = 0; col < m_levelSize.x; col++)
	{
		brickPos.x = col * m_brickSize.x + (col+1) * m_margin.x;
		for (int row = 0; row < m_levelSize.y; row++)
		{
			brickPos.y = row * m_brickSize.y + (row + 1) * m_margin.y;
			std::shared_ptr<Brick> brick = std::make_shared<Brick>(brickPos, m_brickSize);
			m_bricks.push_back(brick);
		}
	}
}

std::vector<std::shared_ptr<Brick>> BricksManager::GetBricks()
{
	return m_bricks;
}

void BricksManager::SetOnBrickBreak(std::function<void()> cb)
{
		m_onBrickBreakFunction = cb;
}
