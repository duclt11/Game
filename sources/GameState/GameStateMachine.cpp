#include "GameStateMachine.h"
#include "GameStateBase.h"

GameStateMachine::GameStateMachine()
{
}

GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::Cleanup()
{
	while (!m_StateStack.empty()) {
		m_StateStack.back()->Exit();
		m_StateStack.pop_back();
	}
}

void GameStateMachine::ChangeState(std::shared_ptr<GameStateBase> state)
{
	m_pNextState = state;
}

void GameStateMachine::ChangeState(Engine::EStateType stt)
{
	Engine::Shared<GameStateBase> nextState = GameStateBase::CreateState(stt);
	ChangeState(nextState);
}

void GameStateMachine::PushState(Engine::EStateType stt)
{
	Engine::Shared<GameStateBase> nextState = GameStateBase::CreateState(stt);
	// pause current state
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Pause();
	}

	m_pNextState = nextState;
}

void GameStateMachine::PopState()
{
	if (!m_StateStack.empty()) {

		m_StateStack.back()->Exit();
		m_StateStack.pop_back();
	}

	// resume previous state
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Resume();
		m_pActiveState = m_StateStack.back();
	}
}

void GameStateMachine::PerformStateChange()
{
	if (m_pNextState != 0)
	{
		if (m_StateStack.empty() == false) {
			if (m_pActiveState->GetGameStateType() == Engine::EStateType::STATE_INTRO)
			{
				// Cleanup Intro state
				m_pActiveState->Exit();
				m_StateStack.pop_back();
			}
			else
			{
				// Pause other states
				m_pActiveState->Pause();
			}
		}

		// store and init the new state
		m_StateStack.push_back(m_pNextState);
		m_StateStack.back()->Init();
		m_pActiveState = m_pNextState;
	}

	m_pNextState = 0;
}
