#pragma once
#include "GameEngine\pch.h"
#include "GameManager/Singleton.h"
#include "rapidjson/document.h"

class GameConfigMgr : public CSingleton<GameConfigMgr>
{
public:
    GameConfigMgr();
    ~GameConfigMgr();
    void InitConfig();
    int GetConfigAsInt(std::string config, int defaultValue = 0);
    float GetConfigAsFloat(std::string config, float defaultValue = 0);
private:
    rapidjson::Document m_jsonDoc;

    int m_playerSize;
    int m_playerSpeed;
    int m_playerHP;
};