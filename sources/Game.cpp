#include <GameEngine\Application.h>

int main()
{
	Engine::WindowConfig Config{800, 600, "BreakOut", "v0.1"};

	if (Engine::Application::GetInstance()->Init(Config))
	{
		Engine::Application::GetInstance()->Run();
	}
	Engine::Application::GetInstance()->Shutdown();
}