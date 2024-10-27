#include "GS_MainMenu.h"
#include "GameStateMachine.h"

#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PLAYER_MAX_LIFE         5
#define LINES_OF_BRICKS         5
#define BRICKS_PER_LINE        20

static const int screenWidth = 800;
static const int screenHeight = 450;

static bool gameOver = false;
static bool pause = false;


struct Player {
    Vector2 position;
    Vector2 size;
    int life;
};

struct Ball {
    Vector2 position;
    Vector2 speed;
    int radius;
    bool active;
};

struct Brick {
    Vector2 position;
    bool active;
};

static Player player{ 0 };
static Ball ball { 0 };
static Brick brick[LINES_OF_BRICKS][BRICKS_PER_LINE] { 0 };

static Vector2 brickSize = { 0 };


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
    brickSize = Vector2{ (float)GetScreenWidth() / BRICKS_PER_LINE, 40 };

    // Initialize player
    player.position = Vector2{ screenWidth / 2, screenHeight * 7 / 8 };
    player.size = Vector2{ screenWidth / 10, 20 };
    player.life = PLAYER_MAX_LIFE;

    // Initialize ball
    ball.position = Vector2{ screenWidth / 2, screenHeight * 7 / 8 - 30 };
    ball.speed = Vector2{ 0, 0 };
    ball.radius = 7;
    ball.active = false;

    // Initialize bricks
    int initialDownPosition = 50;

    for (int i = 0; i < LINES_OF_BRICKS; i++)
    {
        for (int j = 0; j < BRICKS_PER_LINE; j++)
        {
            brick[i][j].position = Vector2{ j * brickSize.x + brickSize.x / 2, i * brickSize.y + initialDownPosition };
            brick[i][j].active = true;
        }
    }

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
    if (key == KEY_ENTER)
    {
        GameStateMachine::GetInstance()->PushState(Engine::EStateType::STATE_PLAY);
    }
}

void GS_MainMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
    std::cout << bIsPressed << std::endl;
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
    DrawRectangle(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2-20, 120, 80, BLACK);
    DrawText("Play", SCREEN_WIDTH/2-40, SCREEN_HEIGHT/2, 40, WHITE);
    DrawText("BREAK OUT", SCREEN_WIDTH/2-200, SCREEN_HEIGHT/4, 80, BLACK);
}
