#pragma once
//#include "valve_sdk/interfaces/IGameEventmanager.hpp"
//#include "Includes.h"
//#include "hooks.hpp"
#include "valve_sdk/sdk.hpp"
#include "features/SpotMarkers.hpp"
#include "features/BuyBot.hpp"
#include "features/Hitmarker.hpp"
#include "features/LogEvents.hpp"
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")

class RoundStart : IGameEventListener2
{
public:
	RoundStart()
	{
		g_GameEvents->AddListener(this, "round_start", false);
	}

	~RoundStart()
	{
		g_GameEvents->RemoveListener(this);
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		spotmarkers->marker = 0; //Set walkbot to start again
		buybot.RoundStarted = true;
	}

	int GetEventDebugID(void)
	{
		return EVENT_DEBUG_ID_INIT;
	}
};

class RoundEnd : IGameEventListener2
{
public:
	RoundEnd()
	{
		g_GameEvents->AddListener(this, "round_end", false);
	}

	~RoundEnd()
	{
		g_GameEvents->RemoveListener(this);
	}

	virtual void FireGameEvent(IGameEvent* event)
	{

	}

	int GetEventDebugID(void)
	{
		return EVENT_DEBUG_ID_INIT;
	}
};

class StartVote : IGameEventListener2 //doesnt work
{
public:
	StartVote()
	{
		g_GameEvents->AddListener(this, "start_vote", false);
	}

	~StartVote()
	{
		g_GameEvents->RemoveListener(this);
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		short userid = g_EngineClient->GetPlayerForUserID(event->GetInt("user_id"));
		byte type = event->GetUint64("type");
		short vote_parameter = event->GetInt("vote_parameter");
		Utils::ConsolePrint(std::to_string(userid).c_str());
		Utils::ConsolePrint(std::to_string(type).c_str());
		Utils::ConsolePrint(std::to_string(vote_parameter).c_str());
	}

	int GetEventDebugID(void)
	{
		return EVENT_DEBUG_ID_INIT;
	}
};

class EnableRestartVote : IGameEventListener2 //doesnt work
{
public:
	EnableRestartVote()
	{
		g_GameEvents->AddListener(this, "enable_restart_voting", false);
	}

	~EnableRestartVote()
	{
		g_GameEvents->RemoveListener(this);
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		bool enable = event->GetBool("enable");
		Utils::ConsolePrint(std::to_string(enable).c_str());
	}

	int GetEventDebugID(void)
	{
		return EVENT_DEBUG_ID_INIT;
	}
};

class PlayerHurt : IGameEventListener2
{
public:
	PlayerHurt()
	{
		g_GameEvents->AddListener(this, "player_hurt", false);
	}

	~PlayerHurt()
	{
		g_GameEvents->RemoveListener(this);
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		auto userid = g_EngineClient->GetPlayerForUserID(event->GetInt("user_id"));
		hitmarker->player_hurt(event);
		logevents.Player_hurt(event);
		C_BasePlayer* attacker = get_player(event->GetInt("attacker"));
		if (attacker == g_LocalPlayer) {
			if (g_Options.misc_HitmarkerSound == 1)
				PlaySound("csgo/sound/skeethitmarker.wav", GetModuleHandle(NULL), SND_ASYNC);
			if (g_Options.misc_HitmarkerSound == 2)
				PlaySound("csgo/sound/hitsound.wav", GetModuleHandle(NULL), SND_ASYNC);
		}
	}

	int GetEventDebugID(void)
	{
		return EVENT_DEBUG_ID_INIT;
	}

	C_BasePlayer* get_player(int userid)
	{
		int index = g_EngineClient->GetPlayerForUserID(userid);
		return (C_BasePlayer*)g_EntityList->GetClientEntity(index);
	}
};

class PlayerFootStep : IGameEventListener2 //doesnt work
{
public:
	PlayerFootStep()
	{
		g_GameEvents->AddListener(this, "player_footstep", true);
	}

	~PlayerFootStep()
	{
		g_GameEvents->RemoveListener(this);
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		logevents.Player_FootSteps(event);
	}

	int GetEventDebugID(void)
	{
		return EVENT_DEBUG_ID_INIT;
	}

	C_BasePlayer* get_player(int userid)
	{
		int index = g_EngineClient->GetPlayerForUserID(userid);
		return (C_BasePlayer*)g_EntityList->GetClientEntity(index);
	}
};

class PlayerDeath : IGameEventListener2
{
public:
	PlayerDeath()
	{
		g_GameEvents->AddListener(this, "player_death", false);
	}

	~PlayerDeath()
	{
		g_GameEvents->RemoveListener(this);
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		auto userid = g_EngineClient->GetPlayerForUserID(event->GetInt("user_id"));
		logevents.Player_death(event);
	}

	int GetEventDebugID(void)
	{
		return EVENT_DEBUG_ID_INIT;
	}
};

class ItemPurchase : IGameEventListener2
{
public:
	ItemPurchase()
	{
		g_GameEvents->AddListener(this, "item_purchase", false);
	}

	~ItemPurchase()
	{
		g_GameEvents->RemoveListener(this);
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		auto userid = g_EngineClient->GetPlayerForUserID(event->GetInt("user_id"));
		logevents.Item_Purchase(event);
	}

	int GetEventDebugID(void)
	{
		return EVENT_DEBUG_ID_INIT;
	}
};

class BeginDefuse : IGameEventListener2
{
public:
	BeginDefuse()
	{
		g_GameEvents->AddListener(this, "bomb_begindefuse", false);
	}

	~BeginDefuse()
	{
		g_GameEvents->RemoveListener(this);
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		auto userid = g_EngineClient->GetPlayerForUserID(event->GetInt("user_id"));
		logevents.Bomb_begindefuse(event);
	}

	int GetEventDebugID(void)
	{
		return EVENT_DEBUG_ID_INIT;
	}
};


class BombBeginPlant : IGameEventListener2
{
public:
	BombBeginPlant()
	{
		g_GameEvents->AddListener(this, "bomb_beginplant", false);
	}

	~BombBeginPlant()
	{
		g_GameEvents->RemoveListener(this);
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		auto userid = g_EngineClient->GetPlayerForUserID(event->GetInt("user_id"));
		logevents.Bomb_beginplant(event);
	}

	int GetEventDebugID(void)
	{
		return EVENT_DEBUG_ID_INIT;
	}
};

class BombAbortDefuse : IGameEventListener2
{
public:
	BombAbortDefuse()
	{
		g_GameEvents->AddListener(this, "bomb_abortdefuse", false);
	}

	~BombAbortDefuse()
	{
		g_GameEvents->RemoveListener(this);
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		auto userid = g_EngineClient->GetPlayerForUserID(event->GetInt("user_id"));
		logevents.Bomb_abortdefuse(event);
	}

	int GetEventDebugID(void)
	{
		return EVENT_DEBUG_ID_INIT;
	}
};

class BombPlanted : IGameEventListener2
{
public:
	BombPlanted()
	{
		g_GameEvents->AddListener(this, "bomb_planted", false);
	}

	~BombPlanted()
	{
		g_GameEvents->RemoveListener(this);
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		auto userid = g_EngineClient->GetPlayerForUserID(event->GetInt("user_id"));
		logevents.Bomb_planted(event);
	}

	int GetEventDebugID(void)
	{
		return EVENT_DEBUG_ID_INIT;
	}
};
