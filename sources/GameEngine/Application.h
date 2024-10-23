#pragma once
#include "pch.h"
#include "GameManager\Singleton.h"

namespace Engine
{
    struct WindowConfig {
        WindowConfig() = default;
        WindowConfig(int InWidth, int InHeight, std::string InTitle, std::string InVersion) :
            Width(InWidth),
            Height(InHeight),
            Title(InTitle),
            Version(InVersion)
        {}
        int Width = 0;
        int Height = 0;
        std::string Title;
        std::string Version;
    };

    class Application : public CSingleton<Application>
    {
    public:
        bool Init(int width, int height, const std::string& title, const std::string& version);
        bool Init(const WindowConfig& InConfig);
        void Run();
        void Shutdown();

        void SetTimeScale(float InScale);

    private:
        bool LoadScene();
        void ProcessInput();
        void Update(float deltaTime);
        void Render(float deltaTime);

    private:
        float mTimeScale;
    };
}