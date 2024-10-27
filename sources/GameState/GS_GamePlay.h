#pragma once
#include "GameEngine\pch.h"
#include "GameEnum\GameEnum.h"
#include "GameState\GameStateBase.h"

class GS_GamePlay : public GameStateBase
{
public:
	GS_GamePlay();
	~GS_GamePlay();

public:
	void Init() override;
	void Exit() override;

	void Pause() override;
	void Resume() override;

	void HandleEvents() override;
	void HandleKeyEvents(int key, bool bIsPressed) override;
	void HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void HandleMouseMoveEvents(int x, int y) override;
	void Update(float deltaTime) override;
	void Draw() override;

};