#include "Hitmarker.hpp"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include "../render.hpp"
#include "..//options.hpp"


CHitmarker* hitmarker = new CHitmarker();

void CHitmarker::initialize()
{
	//g_GameEvents->AddListener(this, "player_hurt", false);
	g_GameEvents->AddListener(this, "bullet_impact", false);
}

void CHitmarker::paint(int w2, int h2)
{
	if (!g_Options.misc_Hitmarker)
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer) {
		if (!impacts.empty())
			impacts.clear();
		if (!hitmarkers.empty())
			hitmarkers.clear();
		return;
	}

	long long time = Utils::EpochMs();
	std::vector<hitmarker_info>::iterator iter;
	for (iter = hitmarkers.begin(); iter != hitmarkers.end();) {

		bool expired = time > iter->impact.time + g_Options.misc_HitmarkerDuration; //2s
		static int alpha_interval = 255 / 25; //How fast it fades out
		if (expired)
			iter->alpha -= alpha_interval;
		if (expired && iter->alpha <= 0) {
			iter = hitmarkers.erase(iter);
			continue;
		}
		Vector pos3D = Vector(iter->impact.x, iter->impact.y, iter->impact.z);
		Vector pos2D;
		if (!Math::WorldToScreen(pos3D, pos2D)) {
			++iter;
			continue;
		}
		Color c = Color(g_Options.misc_Hitmarker_color[0], g_Options.misc_Hitmarker_color[1], g_Options.misc_Hitmarker_color[2], iter->alpha);
		int lineSize = g_Options.misc_HitmarkerSize;
		g_VGuiSurface->DrawSetColor(c);
		if (g_Options.misc_HitmarkerMode == 0) {
			g_VGuiSurface->DrawLine(w2 - lineSize, h2 - lineSize, w2 - (lineSize / 4), h2 - (lineSize / 4));
			g_VGuiSurface->DrawLine(w2 - lineSize, h2 + lineSize, w2 - (lineSize / 4), h2 + (lineSize / 4));
			g_VGuiSurface->DrawLine(w2 + lineSize, h2 - lineSize, w2 + (lineSize / 4), h2 - (lineSize / 4));
			g_VGuiSurface->DrawLine(w2 + lineSize, h2 + lineSize, w2 + (lineSize / 4), h2 + (lineSize / 4));
		}
		if (g_Options.misc_HitmarkerMode == 1) {
			g_VGuiSurface->DrawLine(pos2D.x - lineSize, pos2D.y - lineSize, pos2D.x - (lineSize / 4), pos2D.y - (lineSize / 4));
			g_VGuiSurface->DrawLine(pos2D.x - lineSize, pos2D.y + lineSize, pos2D.x - (lineSize / 4), pos2D.y + (lineSize / 4));
			g_VGuiSurface->DrawLine(pos2D.x + lineSize, pos2D.y - lineSize, pos2D.x + (lineSize / 4), pos2D.y - (lineSize / 4));
			g_VGuiSurface->DrawLine(pos2D.x + lineSize, pos2D.y + lineSize, pos2D.x + (lineSize / 4), pos2D.y + (lineSize / 4));
		}
		++iter;
	}
}

void CHitmarker::FireGameEvent(IGameEvent* event)
{
	if (!g_Options.misc_Hitmarker)
		return;

	if (!event || !g_LocalPlayer)
		return;

	/*if (!strcmp(event->GetName(), "player_hurt"))
		player_hurt(event);*/

	if (!strcmp(event->GetName(), "bullet_impact"))
		bullet_impact(event);
}

int CHitmarker::GetEventDebugID(void)
{
	return EVENT_DEBUG_ID_INIT;
}

void CHitmarker::player_hurt(IGameEvent* event)
{
	C_BasePlayer* attacker = get_player(event->GetInt("attacker"));
	C_BasePlayer* victim = get_player(event->GetInt("userid"));

	if (!attacker || !victim || attacker != g_LocalPlayer)
		return;

	Vector enemyposition = victim->GetAbsOrigin();
	impact_info best_impact;
	float best_impact_distance = -1;
	long long time = Utils::EpochMs();
	std::vector<impact_info>::iterator iter;
	for (iter = impacts.begin(); iter != impacts.end();) {
		if (time > iter->time + 25) {
			iter = impacts.erase(iter);
			continue;
		}
		Vector postion = Vector(iter->x, iter->y, iter->z);
		float distance = postion.DistTo(enemyposition);
		if (distance, best_impact_distance || best_impact_distance == -1) {
			best_impact_distance = distance;
			best_impact = *iter;
		}
		++iter;
	}
	if (best_impact_distance == -1)
		return;

	hitmarker_info info;
	info.impact = best_impact;
	info.alpha = 255;
	hitmarkers.push_back(info);
}

void CHitmarker::bullet_impact(IGameEvent* event)
{
	C_BasePlayer* shooter = get_player(event->GetInt("userid"));

	if (!shooter || shooter != g_LocalPlayer)
		return;

	impact_info info;
	info.x = event->GetFloat("x");
	info.y = event->GetFloat("y");
	info.z = event->GetFloat("z");
	info.time = Utils::EpochMs();
	impacts.push_back(info);
}

C_BasePlayer* CHitmarker::get_player(int userid)
{
	int index = g_EngineClient->GetPlayerForUserID(userid);
	return (C_BasePlayer*)g_EntityList->GetClientEntity(index);
}
