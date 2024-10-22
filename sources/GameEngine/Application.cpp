#include "Application.h"

Engine::Shared<Engine::Application> Engine::Application::GetInstance()
{
	static Shared<Application> application;
	if (application == nullptr) {
		application.reset(new Application());
	}
	return application;
}

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

Engine::Application::Application()
{
}

bool Engine::Application::LoadScene()
{
	return false;
}

void Engine::Application::ProcessInput()
{
}

void Engine::Application::Update(float deltaTime)
{
}

void Engine::Application::Render(float deltaTime)
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	EndDrawing();
}

