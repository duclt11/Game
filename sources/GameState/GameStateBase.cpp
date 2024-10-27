#include "GameStateBase.h"
#include "GS_MainMenu.h"
#include "GS_GamePlay.h"
#include "GameStateMachine.h"
GameStateBase::GameStateBase()
    : m_StateType(Engine::EStateType::STATE_INVALID)
{
}

GameStateBase::GameStateBase(Engine::EStateType StateType) :
    m_StateType(StateType)
{
}

void GameStateBase::Update(float deltaTime)
{   

}

void GameStateBase::Draw()
{
    ClearBackground(RAYWHITE);
}

Engine::Shared<GameStateBase> GameStateBase::CreateState(Engine::EStateType StateType)
{
    Engine::Shared<GameStateBase> GS = nullptr;
    switch (StateType)
    {
    case Engine::EStateType::STATE_INVALID:
        break;
    case Engine::EStateType::STATE_INTRO:
        break;
    case Engine::EStateType::STATE_MENU:
    {
        GS = std::make_shared<GS_MainMenu>();
        break;
    }       
    case Engine::EStateType::STATE_PLAY:
        GS = std::make_shared<GS_GamePlay>();
        break;
    default:
        break;
    }
    return GS;
}


