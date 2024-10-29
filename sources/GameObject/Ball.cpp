#include "Ball.h"
#include "Paddle.h"

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
	m_moveVector = Vector2{ 0,0 };
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
		using namespace std;
		cout << "x = " << m_paddle->GetPosition().x << endl;
		cout << "y = " << m_paddle->GetPosition().y << endl << endl;;
		
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
		m_position.y = paddlePos.y - m_size - 100;
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
		
}

void Ball::SetActive(bool active)
{
	if (active != m_active)
	{
		m_active = active;
		m_moveVector = Vector2{ 0, -m_speed };// start moving vertical
	}
	
}


void Ball::Dead()
{
}

void Ball::OnCollision()
{
}

void Ball::AttachPaddle(std::shared_ptr<Paddle> paddle)
{
	m_paddle = paddle;
}
