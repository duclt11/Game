#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "GameConfig/GameConfigMgr.h"

Ball::Ball()
	: m_position(Vector2{ 300,300 })
	, m_active(false)
{
	Init();
}

Ball::~Ball()
{
}

void Ball::Init()
{
	m_size = GameConfigMgr::GetInstance()->GetConfigAsInt("BallSize", 20);
	m_speed = GameConfigMgr::GetInstance()->GetConfigAsFloat("BallSpeed", 10.0f);
	m_ballDamage = GameConfigMgr::GetInstance()->GetConfigAsInt("BallDamage", 1);
	m_scorePerBrick = GameConfigMgr::GetInstance()->GetConfigAsInt("ScorePerBrick", 1);
	m_moveVector = Vector2{ 0,0 };
	m_score = 0;
}


void Ball::Draw()
{
	DrawCircle(m_position.x, m_position.y, m_size, BLACK);
}

void Ball::Update()
{
	// ball vs paddle
	Rectangle paddleRec = Rectangle{ m_paddle->GetPosition().x, m_paddle->GetPosition().y, m_paddle->GetSize().x, m_paddle->GetSize().y };
	if (CheckCollisionCircleRec(m_position, m_size, paddleRec))
	{
		if (m_moveVector.y > 0)
		{
			m_moveVector.y *= -1;
			m_moveVector.x = (m_position.x - m_paddle->GetPosition().x) / (m_paddle->GetSize().x / 2) * m_speed;
		}
	}
	//ball movement
	if (m_active)
	{		
		m_position.x += m_moveVector.x;
		m_position.y += m_moveVector.y;
	}
	else
	{
		Vector2 paddlePos = m_paddle->GetPosition();
		Vector2 paddleSize = m_paddle->GetSize();
		m_position.x = paddlePos.x + paddleSize.x / 2;
		m_position.y = paddlePos.y - m_size;
	}
	//ball vs wall
	if (((m_position.x + m_size) >= SCREEN_WIDTH) || ((m_position.x - m_size) <= 0)) m_moveVector.x *= -1;
	if ((m_position.y - m_size) <= 0) m_moveVector.y *= -1;
	if ((m_position.y + m_size) >= SCREEN_HEIGHT)
	{
		m_moveVector = Vector2{ 0, 0 };
		m_active = false;

		m_paddle->DecreaseHP();
	}
	//ball vs brick
	for (auto brick : m_bricks)
	{
		if (brick->IsActive())
		{
			Vector2 brickPos = brick->GetPosition();
			Vector2 brickSize = brick->GetSize();
			Rectangle paddleRec = Rectangle{ brickPos.x, brickPos.y, brickSize.x, brickSize.y };
			if (CheckCollisionCircleRec(m_position, m_size, paddleRec))
			{
				brick->DecreaseHP(m_ballDamage);
				ChangeScore(m_scorePerBrick);
				//below
				if (m_position.x > brickPos.x
					&& m_position.x < brickPos.x + brickSize.x
					&& m_position.y > brickPos.y + brickSize.y )
				{
					m_moveVector.y *= -1;
				}
				//above
				else if (m_position.x > brickPos.x
					&& m_position.x < brickPos.x + brickSize.x
					&& m_position.y < brickPos.y)
				{
					m_moveVector.y *= -1;
				}
				//left
				else if (m_position.x < brickPos.x 
					&& m_position.y > brickPos.y
					&& m_position.y < brickPos.y + brickSize.y)
				{
					m_moveVector.x *= -1;
				}
				//right
				else if (m_position.x > brickPos.x + brickSize.x
					&& m_position.y > brickPos.y
					&& m_position.y < brickPos.y + brickSize.y)
				{
					m_moveVector.x *= -1;
				}
				else // angle
				{
					m_moveVector.x *= -1;
					m_moveVector.y *= -1;
				}

			}
		}
	}
}

void Ball::SetActive(bool active)
{
	if (active != m_active)
	{
		m_active = active;
		m_moveVector = Vector2{ 0, -m_speed };// start moving vertical
	}
	
}

void Ball::OnCollision()
{
}

void Ball::AttachPaddle(std::shared_ptr<Paddle> paddle)
{
	m_paddle = paddle;
}

void Ball::AttachBricks(std::vector<std::shared_ptr<Brick>> bricks)
{
	m_bricks = bricks;
}

void Ball::SetOnScoreChangeFunction(std::function<void(int)> cb)
{
	m_onScoreChangeFunction = cb;
	m_onScoreChangeFunction(m_score);
}

int Ball::GetScore()
{
	return m_score;
}

void Ball::ChangeScore(int num)
{
	m_score += num;
	m_onScoreChangeFunction(m_score);
}
