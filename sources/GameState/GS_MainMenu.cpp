#include "GS_MainMenu.h"
#include "GameStateMachine.h"

#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define BUTTON_POSITION_X (SCREEN_WIDTH / 2 - 60)
#define BUTTON_POSITION_Y (SCREEN_HEIGHT / 2 - 20)
#define BUTTON_WIDTH 140
#define BUTTON_HEIGHT 80

GS_MainMenu::GS_MainMenu()
	: GameStateBase(Engine::EStateType::STATE_MENU) 
{
    Init();
}

GS_MainMenu::~GS_MainMenu()
{
}

void GS_MainMenu::Init()
{


}

void GS_MainMenu::Exit()
{
}

void GS_MainMenu::Pause()
{
}

void GS_MainMenu::Resume()
{
}

void GS_MainMenu::HandleEvents()
{
    
}

void GS_MainMenu::HandleKeyEvents(int key, bool bIsPressed)
{
    if (key == KEY_SPACE)
    {
        PlayGame();
    }
}

void GS_MainMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
    std::cout << bIsPressed << std::endl;
    //click on button
    if (x > BUTTON_POSITION_X
        && x < BUTTON_POSITION_X + BUTTON_WIDTH
        && y > BUTTON_POSITION_Y
        && y < BUTTON_POSITION_Y + BUTTON_HEIGHT)
    {
        PlayGame();
    }
}

void GS_MainMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GS_MainMenu::Update(float deltaTime)
{
    
}

void GS_MainMenu::Draw()
{
    GameStateBase::Draw();
    DrawRectangle(BUTTON_POSITION_X, BUTTON_POSITION_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK);
    DrawText("PLAY", SCREEN_WIDTH/2 - 40, SCREEN_HEIGHT/2, 40, WHITE);
    DrawText("<[SPACE] to PLAY>", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 + 80, 20, BLACK);
    DrawText("<[ESC] to QUIT>", SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 160, 20, BLACK);
    DrawText("BREAK OUT", SCREEN_WIDTH/2-200, SCREEN_HEIGHT/4, 80, BLACK);
}

void GS_MainMenu::PlayGame()
{
    GameStateMachine::GetInstance()->PushState(Engine::EStateType::STATE_PLAY);

}
