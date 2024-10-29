#include "GameConfigMgr.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
GameConfigMgr::GameConfigMgr()
{
	InitConfig();
}

GameConfigMgr::~GameConfigMgr()
{
}

void GameConfigMgr::InitConfig()
{
	const char* configJson = LoadFileText("../resources/config.json");
	m_jsonDoc.Parse(configJson);
	
}

int GameConfigMgr::GetConfigAsInt(std::string config, int defaultValue)
{
	if (m_jsonDoc.HasMember(config.c_str()))
	{
		rapidjson::Value& PlayerHP = m_jsonDoc[config.c_str()];
		int configValue = PlayerHP.GetInt();
		if (configValue != 0)
		{
			return configValue;
		}
	}

	return defaultValue;
}

float GameConfigMgr::GetConfigAsFloat(std::string config, float defaultValue)
{
	if (m_jsonDoc.HasMember(config.c_str()))
	{
		rapidjson::Value& PlayerHP = m_jsonDoc[config.c_str()];
		float configValue = PlayerHP.GetFloat();
		if (configValue != 0.0f)
		{
			return configValue;
		}
	}
	return defaultValue;
}
