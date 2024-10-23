#include "GameStateBase.h"

GameStateBase::GameStateBase() :
    m_StateType(Engine::EStateType::STATE_INVALID)
{
}

GameStateBase::GameStateBase(Engine::EStateType StateType) :
    m_StateType(StateType)
{
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
        break;
    case Engine::EStateType::STATE_PLAY:
        break;
    default:
        break;
    }
    return GS;
}


