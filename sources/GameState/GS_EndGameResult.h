#pragma once
#include "GameEngine\pch.h"
#include "GameEnum\GameEnum.h"
#include "GameStateBase.h"

class GS_EndGameResult : public GameStateBase
{
public:
	GS_EndGameResult(bool isWin, int score, float time);
	 ~GS_EndGameResult();

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
private:
	bool m_isWin;
	int m_score;
	float m_time;

};