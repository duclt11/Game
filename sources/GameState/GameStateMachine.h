#pragma once
#include "GameEngine\pch.h"
#include "GameManager/Singleton.h"
#include "GameEnum\GameEnum.h"

class GameStateBase;

class GameStateMachine : public CSingleton<GameStateMachine>
{
public:
	GameStateMachine();
	~GameStateMachine();

	void	Cleanup();

	void	ChangeState(std::shared_ptr<GameStateBase> state);
	void	ChangeState(Engine::EStateType stt);
	void	PushState(Engine::EStateType stt);
	void	PopState();

	bool	isRunning() { return m_running; }
	void	Quit() { m_running = false; }
	void	PerformStateChange();

	inline std::shared_ptr<GameStateBase> CurrentState()const
	{
		return m_pActiveState;
	}

	inline bool NeedsToChangeState()const
	{
		return (m_pNextState != 0);
	}

	inline bool HasState()const
	{
		return m_StateStack.size() > 0;
	}

private:
	std::list<Engine::Shared<GameStateBase>>	m_StateStack;
	Engine::Shared<GameStateBase>				m_pActiveState;
	Engine::Shared<GameStateBase>				m_pNextState;
	bool	m_running;
};
