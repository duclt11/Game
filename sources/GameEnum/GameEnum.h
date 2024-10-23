#pragma once
namespace Engine
{
	enum class EStateType : int16_t
	{
		STATE_INVALID = 0,
		STATE_INTRO,
		STATE_MENU,
		STATE_PLAY,
		STATE_OPTION,
		STATE_CREDIT
	};
}
