#pragma once
#include "GameEngine\pch.h"
#include "GameEnum\GameEnum.h"

class GameStateBase
{
public:
	GameStateBase();
	GameStateBase(Engine::EStateType StateType);
	virtual ~GameStateBase() = default;

public:
	virtual void Init() = 0;
	virtual void Exit() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents() = 0;
	virtual void HandleKeyEvents(int key, bool bIsPressed) = 0;
	virtual void HandleTouchEvents(int x, int y, bool bIsPressed) = 0;
	virtual void HandleMouseMoveEvents(int x, int y) = 0;
	virtual void Update(float deltaTime);
	virtual void Draw();

	static Engine::Shared<GameStateBase> CreateState(Engine::EStateType StateType);

	inline Engine::EStateType GetGameStateType() { return m_StateType; }

protected:
	Engine::EStateType m_StateType;
};