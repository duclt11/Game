#include <GameEngine\Application.h>

int main()
{
	Engine::WindowConfig Config{SCREEN_WIDTH, SCREEN_HEIGHT, "BreakOut", "v0.1"};

	if (Engine::Application::GetInstance()->Init(Config))
	{
		Engine::Application::GetInstance()->Run();
	}
	Engine::Application::GetInstance()->Shutdown();
}