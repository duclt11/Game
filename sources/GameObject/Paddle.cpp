#include "Paddle.h"
#include "GameConfig/GameConfigMgr.h"
Paddle::Paddle()
{
	Init();
}

Paddle::~Paddle()
{
}

void Paddle::Init()
{
	std::shared_ptr<GameConfigMgr> gameConfig = GameConfigMgr::GetInstance();
	m_size.x = gameConfig->GetConfigAsInt("PlayerSizeX", 100);
	m_size.y = gameConfig->GetConfigAsInt("PlayerSizeY", 20);
	m_speed = gameConfig->GetConfigAsFloat("PlayerSpeed", 3.0f);
	m_position.x = SCREEN_WIDTH / 2 - m_size.x;
	m_position.y = SCREEN_HEIGHT - m_size.y - 50;
	m_hp = gameConfig->GetConfigAsInt("PlayerHP", 5);
}

void Paddle::Move(int key)
{
	if (key == KEY_LEFT)
	{
		if (m_position.x <= 0) return;
		m_position.x -= m_speed;
	}
	if (key == KEY_RIGHT)
	{
		if (m_position.x >= SCREEN_WIDTH - m_size.x) return;
		m_position.x += m_speed;
	}
}

void Paddle::Draw()
{
	DrawRectangle(m_position.x, m_position.y, m_size.x, m_size.y, BLACK);
}

void Paddle::Update()
{
	if (IsKeyDown(KEY_LEFT))
	{
		Move(KEY_LEFT);
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		Move(KEY_RIGHT);
	}
}

void Paddle::SetOnHPChangeFunction(std::function<void(int)> cb)
{
	m_onHPChangeFunction = cb;
	m_onHPChangeFunction(m_hp);
}

Vector2 Paddle::GetPosition()
{
	return m_position;
}

Vector2 Paddle::GetSize()
{
	return m_size;
}

void Paddle::DecreaseHP(int num)
{
	m_hp -= num;
	m_onHPChangeFunction(m_hp);
}
