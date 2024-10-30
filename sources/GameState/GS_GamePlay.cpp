#include "GS_GamePlay.h"
#include "GameObject/Paddle.h"
#include "GameObject/Brick.h"
#include "GameObject/Ball.h"
#include "GameObject/BricksManager.h"
#include "GameConfig/GameConfigMgr.h"
#include "GameStateMachine.h"
#include "GameState/GS_EndGameResult.h"
#include "string"

GS_GamePlay::GS_GamePlay() :
    GameStateBase(Engine::EStateType::STATE_PLAY)
{
    m_time = GameConfigMgr::GetInstance()->GetConfigAsInt("Time", 300);
}

GS_GamePlay::~GS_GamePlay()
{
}

void GS_GamePlay::Init()
{
    m_paddle = Engine::MakeShared<Paddle>();
    m_paddle->SetOnHPChangeFunction([&](int value) {
        m_playerHP = value;
        if (m_playerHP <= 0)
        {
            EndGame(false);
        }
        });

    m_bricksManager = Engine::MakeShared<BricksManager>();
    m_bricksManager->CreateBricks();
    m_bricksManager->SetOnBrickBreak([&]() {
        EndGame(true);
        });

    m_ball = Engine::MakeShared<Ball>();
    m_ball->AttachPaddle(m_paddle);
    m_ball->SetOnScoreChangeFunction([&](int value) {
        m_score = value;
        });

    m_ball->AttachBricks(m_bricksManager->GetBricks());

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
    m_bricksManager->Update();
    UpdateTime(deltaTime);
}

void GS_GamePlay::Draw()
{
    GameStateBase::Draw();
    m_paddle->Draw();
    m_ball->Draw();
    m_bricksManager->Draw();
    ClearBackground(RAYWHITE);
}

void GS_GamePlay::EndGame(bool isWin)
{

    GameStateMachine::GetInstance()->ChangeState(std::make_shared<GS_EndGameResult>(isWin, m_ball->GetScore(), m_time));
}

void GS_GamePlay::UpdateTime(float deltaTime)
{
    m_time -= deltaTime;
    if (m_time > 0)
    {
        std::string timeText = "Time remaining: " + std::to_string((int)m_time);
        DrawText(timeText.c_str(), SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50, 20, BLACK);
    }
    else
    {
        EndGame(false);
    }
    std::string HPText = "HP: " + std::to_string(m_playerHP);
    DrawText(HPText.c_str(), SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT - 50, 20, BLACK);

    std::string scoreText = "Score: " + std::to_string(m_score);
    DrawText(scoreText.c_str(), SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT - 50, 20, BLACK);
}


