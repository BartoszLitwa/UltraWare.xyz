#include "LogEvents.hpp"
#include "../render.hpp"
#include "..//options.hpp"

CLogEvents logevents;

void CLogEvents::Draw(int w, int h) //https://wiki.alliedmods.net/Counter-Strike:_Global_Offensive_Events
{
	if (!g_Options.misc_LogEvents)
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer)
		return;

	if (Logs.size() == 0)
		return;

	for (int i = 0; i < Logs.size(); i += 2) {
		float time = g_GlobalVars->curtime - Logs[i].time;
		if (time > 6.f)
			Logs[i].color = Color(Logs[i].color[0], Logs[i].color[1], Logs[i].color[2], Logs[i].color[3] * 0.9);
		Render::Get().RenderText(Logs[i].text, 25.f, 250.f - i * 10, 18.f, Logs[i].color);
	}
}

void CLogEvents::DrawSteps(int w, int h)
{
	if (!g_Options.esp_footstep)
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer)
		return;

	if (Steps.size() == 0)
		return;

	for (int i = 0; i < Steps.size(); i++) {
		float time = g_GlobalVars->curtime - Steps[i].time;
		if(time > 1.f)
			Steps[i].color = Color(Steps[i].color[0], Steps[i].color[1], Steps[i].color[2], Steps[i].color[3] * 0.9);
		Render::Get().RenderCircle3D(Steps.at(i).pos, 1, 25, Steps[i].color);

		Steps.pop_front();
	}
}

void CLogEvents::Player_FootSteps(IGameEvent* event)
{
	if (!g_Options.esp_footstep)
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer)
		return;

	C_BasePlayer* player = get_player(event->GetInt("userid"));
	if (!player || player == g_LocalPlayer)
		return;

	int playerindex = g_EngineClient->GetPlayerForUserID(event->GetInt("userid"));
	player_info_t playerinfo;
	if (!g_EngineClient->GetPlayerInfo(playerindex, &playerinfo))
		return;

	StepsInfo Sinfo;
	Sinfo.player = player;
	Sinfo.pos = player->GetAbsOrigin();
	Sinfo.time = g_GlobalVars->curtime;
	Sinfo.color = g_Options.esp_footstep_color;

	Steps.push_front(Sinfo);
}

void CLogEvents::Player_hurt(IGameEvent* event)
{
	if (!g_Options.misc_LogEvents || !g_Options.misc_LogEvents_Damage)
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer)
		return;

	C_BasePlayer* attacker = get_player(event->GetInt("attacker"));
	C_BasePlayer* victim = get_player(event->GetInt("userid"));

	if (!attacker || !victim || attacker != g_LocalPlayer)
		return;

	int attackerindex = g_EngineClient->GetPlayerForUserID(event->GetInt("attacker"));
	int victimindex = g_EngineClient->GetPlayerForUserID(event->GetInt("userid"));

	player_info_t info_attacker, info_victim;
	if (!g_EngineClient->GetPlayerInfo(attackerindex, &info_attacker))
		return;
	if (!g_EngineClient->GetPlayerInfo(victimindex, &info_victim))
		return;
	LogInfo Linfo;
	Linfo.time = g_GlobalVars->curtime;
	Linfo.color = g_Options.misc_LogEvents_color;
	std::string Health = std::to_string(event->GetInt("health"));
	std::string text = static_cast<std::string>(info_attacker.szName) + static_cast<std::string>(" dealt ") + std::to_string(event->GetInt("dmg_health"))
		+ " damage to " + info_victim.szName + " (" + Health + " health remaining)" + ".";
	Linfo.text = text;
	for (int i = 0; i < Logs.size(); i++) {
		if (Linfo.text == Logs[i].text)
			return;
	}

	Logs.push_front(Linfo);

	if (Logs.size() > 18)
		Logs.pop_back();
}

void CLogEvents::Player_death(IGameEvent* event)
{
	if (!g_Options.misc_LogEvents || !g_Options.misc_ChatSpam)
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer)
		return;

	C_BasePlayer* attacker = get_player(event->GetInt("attacker"));
	C_BasePlayer* victim = get_player(event->GetInt("userid"));

	if (!attacker || !victim)
		return;

	int attackerindex = g_EngineClient->GetPlayerForUserID(event->GetInt("attacker"));
	int victimindex = g_EngineClient->GetPlayerForUserID(event->GetInt("userid"));

	player_info_t info_attacker, info_victim;
	if (!g_EngineClient->GetPlayerInfo(attackerindex, &info_attacker))
		return;
	if (!g_EngineClient->GetPlayerInfo(victimindex, &info_victim))
		return;

	//std::string weapon = std::to_string((ItemDefinitionIndex)g_LocalPlayer->m_hActiveWeapon().Get()->m_Item().m_iItemDefinitionIndex());
	//std::string fixedweapon = weapon.erase(0, 7);

	std::stringstream msg; msg << "say ";
	std::string Lastplace = victim->m_szLastPlaceName();
	if (attacker == g_LocalPlayer) {
		switch (g_Options.misc_ChatSpamKill)
		{
		case 1:
			msg << info_victim.szName << " you got rekt by UltraWare.xyz";
			break;
		case 2:
			msg << info_victim.szName << " you got destroyed by shit 'paste'";
			break;
		case 3:
			msg << info_victim.szName << " buy better PASTE next time.";
			break;
		case 4:
			msg << info_victim.szName << " you died on " + Lastplace;
			break;
		default:
			break;
		}
		if(g_Options.misc_ChatSpamKill != 0)
			g_EngineClient->ClientCmd(msg.str().c_str());
	}
	else if(victim == g_LocalPlayer){
		switch (g_Options.misc_ChatSpamDeath)
		{
		case 1:
			msg << "Lucky, I got rekt using UltraWare.xyz";
			break;
		default:
			break;
		}
		if (g_Options.misc_ChatSpamDeath != 0)
			g_EngineClient->ClientCmd(msg.str().c_str());
	}
}

void CLogEvents::Item_Purchase(IGameEvent* event)
{
	if (!g_Options.misc_LogEvents || !g_Options.misc_LogEvents_ItemsPurchase)
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer)
		return;

	C_BasePlayer* player = get_player(event->GetInt("userid"));
	if (!player)
		return;

	int playerindex = g_EngineClient->GetPlayerForUserID(event->GetInt("userid"));

	player_info_t info_player;
	if (!g_EngineClient->GetPlayerInfo(playerindex, &info_player))
		return;

	LogInfo Linfo;
	Linfo.time = g_GlobalVars->curtime;
	Linfo.color = g_Options.misc_LogEvents_color;
	int t = event->GetInt("team");
	std::string team = t == 3 ? "CT" : "T";
	std::string weapon = event->GetString("weapon");
	std::string fixedweapon = weapon.erase(0, 7);
	std::string text = static_cast<std::string>(info_player.szName) + " [" + team + "]" + static_cast<std::string>(" purchased ") + fixedweapon + ".";
	Linfo.text = text;
	for (int i = 0; i < Logs.size(); i++) {
		if (Linfo.text == Logs[i].text)
			return;
	}

	Logs.push_front(Linfo);

	if (Logs.size() > 18)
		Logs.pop_back();
}

void CLogEvents::Bomb_planted(IGameEvent* event)
{
	if (!g_Options.misc_LogEvents || !g_Options.misc_LogEvents_Bomb)
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer)
		return;

	C_BasePlayer* player = get_player(event->GetInt("userid"));
	if (!player)
		return;

	int playerindex = g_EngineClient->GetPlayerForUserID(event->GetInt("userid"));

	player_info_t info_player;
	if (!g_EngineClient->GetPlayerInfo(playerindex, &info_player))
		return;

	LogInfo Linfo;
	Linfo.time = g_GlobalVars->curtime;
	Linfo.color = g_Options.misc_LogEvents_color;
	std::string Site = std::to_string(event->GetInt("site"));
	Site = Site == "425" ? "A" : "B";
	std::string text = static_cast<std::string>(info_player.szName) + static_cast<std::string>(" planted bomb on site ") + Site + ".";
	Linfo.text = text;
	for (int i = 0; i < Logs.size(); i++) {
		if (Linfo.text == Logs[i].text)
			return;
	}

	Logs.push_front(Linfo);

	if (Logs.size() > 18)
		Logs.pop_back();
}

void CLogEvents::Bomb_begindefuse(IGameEvent* event)
{
	if (!g_Options.misc_LogEvents || !g_Options.misc_LogEvents_Bomb)
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer)
		return;

	C_BasePlayer* player = get_player(event->GetInt("userid"));
	if (!player)
		return;

	int playerindex = g_EngineClient->GetPlayerForUserID(event->GetInt("userid"));

	player_info_t info_player;
	if (!g_EngineClient->GetPlayerInfo(playerindex, &info_player))
		return;

	LogInfo Linfo;
	Linfo.time = g_GlobalVars->curtime;
	Linfo.color = g_Options.misc_LogEvents_color;
	bool HasKit = event->GetBool("haskit");
	std::string kit = HasKit ? "with defuser" : "without defuser";
	std::string text = static_cast<std::string>(info_player.szName) + static_cast<std::string>(" has started defusing bomb ") + kit + ".";
	Linfo.text = text;
	for (int i = 0; i < Logs.size(); i++) {
		if (Linfo.text == Logs[i].text)
			return;
	}

	Logs.push_front(Linfo);

	if (Logs.size() > 18)
		Logs.pop_back();
}

void CLogEvents::Bomb_abortdefuse(IGameEvent* event)
{
	if (!g_Options.misc_LogEvents || !g_Options.misc_LogEvents_Bomb)
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer)
		return;

	C_BasePlayer* player = get_player(event->GetInt("userid"));
	if (!player)
		return;

	int playerindex = g_EngineClient->GetPlayerForUserID(event->GetInt("userid"));

	player_info_t info_player;
	if (!g_EngineClient->GetPlayerInfo(playerindex, &info_player))
		return;

	LogInfo Linfo;
	Linfo.time = g_GlobalVars->curtime;
	Linfo.color = g_Options.misc_LogEvents_color;
	std::string Site = std::to_string(event->GetInt("site"));
	Site = Site == "425" ? "A" : "B"; //A = 425 B = 426
	std::string text = static_cast<std::string>(info_player.szName) + static_cast<std::string>(" has stopped defusing bomb on site ") + Site + ".";
	Linfo.text = text;
	for (int i = 0; i < Logs.size(); i++) {
		if (Linfo.text == Logs[i].text)
			return;
	}

	Logs.push_front(Linfo);

	if (Logs.size() > 18)
		Logs.pop_back();
}

void CLogEvents::Bomb_beginplant(IGameEvent* event)
{
	if (!g_Options.misc_LogEvents || !g_Options.misc_LogEvents_Bomb)
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer)
		return;

	C_BasePlayer* player = get_player(event->GetInt("userid"));
	if (!player)
		return;

	int playerindex = g_EngineClient->GetPlayerForUserID(event->GetInt("userid"));

	player_info_t info_player;
	if (!g_EngineClient->GetPlayerInfo(playerindex, &info_player))
		return;

	LogInfo Linfo;
	Linfo.time = g_GlobalVars->curtime;
	Linfo.color = g_Options.misc_LogEvents_color;
	std::string Site = std::to_string(event->GetInt("site"));
	Site = Site == "425" ? "A" : "B"; //A = 425 B = 426
	std::string text = static_cast<std::string>(info_player.szName) + static_cast<std::string>(" has started planting bomb on site ") + Site + ".";
	Linfo.text = text;
	for (int i = 0; i < Logs.size(); i++) {
		if (Linfo.text == Logs[i].text)
			return;
	}

	Logs.push_front(Linfo);

	if (Logs.size() > 18)
		Logs.pop_back();
}

C_BasePlayer* CLogEvents::get_player(int userid)
{
	int index = g_EngineClient->GetPlayerForUserID(userid);
	return (C_BasePlayer*)g_EntityList->GetClientEntity(index);
}
