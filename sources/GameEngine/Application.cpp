#include "Application.h"
#include "GameState\GameStateMachine.h"
#include "GameState\GameStateBase.h"
#include "GameConfig/GameConfigMgr.h"

bool Engine::Application::Init(int width, int height, const std::string& title, const std::string& version)
{
	InitWindow(width, height, title.c_str());
	SetTargetFPS(MAX_FPS);
	return true;
}

bool Engine::Application::Init(const WindowConfig& InConfig)
{
	return Init(InConfig.Width, InConfig.Height, InConfig.Title, InConfig.Version);
}

void Engine::Application::Run()
{
	float LastTime = 0.0f;
	SetTimeScale(1.0f);
	GameStateMachine::GetInstance()->PushState(Engine::EStateType::STATE_MENU);

	while (!WindowShouldClose())
	{
		float CurrentTime = GetDeltaTime();
		float DeltaTime = CurrentTime - LastTime;
		LastTime = CurrentTime;

		ProcessInput();
		Update(DeltaTime * mTimeScale);
		Render(DeltaTime * mTimeScale);
	}
}

void Engine::Application::Shutdown()
{
	CloseWindow();
}

void Engine::Application::SetTimeScale(float InScale)
{
	mTimeScale = InScale;
}

bool Engine::Application::LoadScene()
{
	return false;
}

void Engine::Application::ProcessInput()
{
	if (!GameStateMachine::GetInstance()->HasState()) return;

	int key = GetKeyPressed();

	if (key != 0)
	{
		GameStateMachine::GetInstance()->CurrentState()->HandleKeyEvents(key, IsKeyPressed(key));
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		GameStateMachine::GetInstance()->CurrentState()->HandleTouchEvents(GetMouseX(), GetMouseY(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
	}
	GameStateMachine::GetInstance()->CurrentState()->HandleMouseMoveEvents(GetMouseX(), GetMouseY());

}

void Engine::Application::Update(float deltaTime)
{
	GameStateMachine::GetInstance()->PerformStateChange();
	if (GameStateMachine::GetInstance()->HasState())
	{
		GameStateMachine::GetInstance()->CurrentState()->Update(deltaTime);
	}
}

void Engine::Application::Render(float deltaTime)
{
	if (GameStateMachine::GetInstance()->HasState())
	{
		BeginDrawing();
		GameStateMachine::GetInstance()->CurrentState()->Draw();
		EndDrawing();
	}
}

