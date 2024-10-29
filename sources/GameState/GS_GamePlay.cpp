#include "GS_GamePlay.h"
#include "GameObject/Paddle.h"
#include "GameObject/Brick.h"
#include "GameObject/Ball.h"

GS_GamePlay::GS_GamePlay() :
    GameStateBase(Engine::EStateType::STATE_PLAY)
{
}

GS_GamePlay::~GS_GamePlay()
{
}

void GS_GamePlay::Init()
{
    m_paddle = Engine::MakeShared<Paddle>();
    m_ball = Engine::MakeShared<Ball>();
    m_ball->AttachPaddle(m_paddle);

}

void GS_GamePlay::Exit()
{

}

void GS_GamePlay::Pause()
{
}

void GS_GamePlay::Resume()
{
}

void GS_GamePlay::HandleEvents()
{
}

void GS_GamePlay::HandleKeyEvents(int key, bool bIsPressed)
{
    if (key == KEY_SPACE)
    {
        m_ball->SetActive(true);
    }
}

void GS_GamePlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GS_GamePlay::HandleMouseMoveEvents(int x, int y)
{
}

void GS_GamePlay::Update(float deltaTime)
{
    GameStateBase::Update(deltaTime);
    m_paddle->Update();
    m_ball->Update();
}

void GS_GamePlay::Draw()
{
    GameStateBase::Draw();
    m_paddle->Draw();
    m_ball->Draw();
    ClearBackground(RAYWHITE);
}

