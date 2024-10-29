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
    int GetConfigAsInt(std::string config, int defaultValue);
    float GetConfigAsFloat(std::string config, float defaultValue);
private:
    rapidjson::Document m_jsonDoc;

    int m_playerSize;
    int m_playerSpeed;
    int m_playerHP;
};