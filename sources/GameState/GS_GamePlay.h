#pragma once
#include "GameEngine\pch.h"
#include "GameEnum\GameEnum.h"
#include "GameState\GameStateBase.h"

class Paddle;
class Ball;
class BricksManager;
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

	void EndGame(bool isWin);
	void UpdateTime(float deltaTime);
private:
	std::shared_ptr<Paddle> m_paddle;
	std::shared_ptr<Ball> m_ball;
	std::shared_ptr<BricksManager> m_bricksManager;

	int m_score;
	float m_time;
	int m_playerHP;
};