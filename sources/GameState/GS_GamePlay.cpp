#include "GS_GamePlay.h"

GS_GamePlay::GS_GamePlay() :
    GameStateBase(Engine::EStateType::STATE_PLAY)
{
}

GS_GamePlay::~GS_GamePlay()
{
}

void GS_GamePlay::Init()
{
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

}

void GS_GamePlay::Draw()
{
    GameStateBase::Draw();
    ClearBackground(BLACK);
}

