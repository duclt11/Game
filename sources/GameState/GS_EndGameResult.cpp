#include "GS_EndGameResult.h"


GS_EndGameResult::GS_EndGameResult(bool isWin, int score, float time)
    : GameStateBase(Engine::EStateType::STATE_INVALID)
    , m_isWin(isWin)
    , m_score(score)
    , m_time(time)    
{
}

GS_EndGameResult::~GS_EndGameResult()
{
}

void GS_EndGameResult::Init()
{
}

void GS_EndGameResult::Exit()
{
}

void GS_EndGameResult::Pause()
{
}

void GS_EndGameResult::Resume()
{
}

void GS_EndGameResult::HandleEvents()
{
}

void GS_EndGameResult::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GS_EndGameResult::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GS_EndGameResult::HandleMouseMoveEvents(int x, int y)
{
}

void GS_EndGameResult::Update(float deltaTime)
{
}

void GS_EndGameResult::Draw()
{
    ClearBackground(WHITE);
    std::string result = m_isWin ? "You win" : "You Lose";
    DrawText(result.c_str(), SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 200, 100, BLACK);
    std::string score = "Score: " + std::to_string(m_score);
    DrawText(score.c_str(), SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 30, BLACK);

    std::string timeScore = "Bonus from time: " + std::to_string((int)m_time);
    DrawText(timeScore.c_str(), SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 50, 30, BLACK);

    std::string finalScore = "Final score: " + std::to_string(m_score + (int)m_time);
    DrawText(finalScore.c_str(), SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 100, 40, BLACK);

    
}


