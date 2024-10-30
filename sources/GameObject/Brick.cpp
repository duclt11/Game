#include "Brick.h"
#include "GameConfig/GameConfigMgr.h"

Brick::Brick(Vector2 position, Vector2 size)
	: m_position(position)
	, m_size(size)
	, m_active(true)
{
	Init();
}

Brick::~Brick()
{
}

void Brick::Init()
{
	std::shared_ptr<GameConfigMgr> gameConfig = GameConfigMgr::GetInstance();
	m_hp = gameConfig->GetConfigAsInt("BrickHP", 1);
}

void Brick::Move(int key)
{
}

void Brick::Draw()
{
	if (m_active)
	{
		DrawRectangle(m_position.x, m_position.y, m_size.x, m_size.y, BLACK);
	}
}

void Brick::Update()
{
}

Vector2 Brick::GetPosition()
{
	return m_position;
}

Vector2 Brick::GetSize()
{
	return m_size;
}

bool Brick::IsActive()
{
	return m_active;
}

void Brick::DecreaseHP(int num)
{
	if (m_active)
	{
		m_hp -= num;
		if (m_hp <= 0)
		{
			m_active = false;
		}
	}
	
}
