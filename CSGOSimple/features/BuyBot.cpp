#include "BuyBot.hpp"
#include "..//options.hpp"

CBuyBot buybot;

void CBuyBot::Buy()
{
	if (!g_Options.misc_BuyBot)
		return;

	if (!RoundStarted)
		return;

	if (!g_LocalPlayer || !g_LocalPlayer->IsAlive())
		return;

	switch (g_Options.misc_BuyBot_Primary)
	{
	case 0:
		g_EngineClient->ClientCmd("buy scar20; buy g3sg1;");
		break;
	case 1:
		g_EngineClient->ClientCmd("buy awp;");
		break;
	case 2:
		g_EngineClient->ClientCmd("buy ssg08;");
		break;
	case 3:
		g_EngineClient->ClientCmd("buy ak47; buy m4a1_silencer; buy m4a1;");
		break;
	default:
		break;
	}

	switch (g_Options.misc_BuyBot_Secondary)
	{
	case 0:
		g_EngineClient->ClientCmd("buy elite;");
		break;
	case 1:
		g_EngineClient->ClientCmd("buy deagle;");
		break;
	case 2:
		g_EngineClient->ClientCmd("buy p250;");
		break;
	case 3:
		g_EngineClient->ClientCmd("buy fn57;");
		break;
	default:
		break;
	}
	if (g_Options.misc_BuyBot_Kevlar)
		g_EngineClient->ClientCmd("buy vesthelm; buy vest;");
	if (g_Options.misc_BuyBot_Grenades)
		g_EngineClient->ClientCmd("buy molotov; buy incgrenade; buy smokegrenade; buy hegrenade; buy flashbang;");
	if (g_Options.misc_BuyBot_Defuser)
		g_EngineClient->ClientCmd("buy defuser;");
	if (g_Options.misc_BuyBot_Taser)
		g_EngineClient->ClientCmd("buy taser;");

	RoundStarted = false;
}
