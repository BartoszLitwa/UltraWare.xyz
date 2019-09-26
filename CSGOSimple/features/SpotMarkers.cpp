#include "SpotMarkers.hpp"
#include "../hooks.hpp"
#include "../render.hpp"
#include "..//options.hpp"

CSpotMarkers* spotmarkers = new CSpotMarkers();

auto key = VK_F2;
Color colorDefault = Color(0, 0, 255, 255);
Color colorClose = Color(0, 255, 0, 255);
Color ColorSelected = Color(255, 0, 0, 255);

float DistanceMeters(Vector source, Vector destination)
{
	float dist = sqrt(source.DistToSqr(destination));
	return dist * 0.01905f;
}

void CSpotMarkers::WalkBot(CUserCmd* cmd)
{
	if (!g_Options.misc_WalkBot) {
		marker = 0;
		return;
	}
	if (spots.size() < 2)
		return;

	if (!g_LocalPlayer || !g_LocalPlayer->IsAlive())
		return;

	if (marker > spots.size() - 1)
		marker = 0; //TODO hook fire_eventlistener and player_hurt
	Vector target = spots.at(marker);
	QAngle AimaAt = Math::CalcAngle(g_LocalPlayer->GetEyePos(), target);
	AimaAt.Clamp();
	AimaAt.pitch = 0;
	cmd->viewangles = AimaAt;
	cmd->forwardmove = 450;
	float dist3D = DistanceMeters(g_LocalPlayer->GetAbsOrigin(), target);
	if (dist3D <= 0.5f)
		marker++;
}

void CSpotMarkers::Update()
{
	if (!g_LocalPlayer)
		return;

	std::string oldLevelName = levelName;
	int oldTeam = Team;
	levelName = g_EngineClient->GetLevelName();
	Team = g_LocalPlayer->m_iTeamNum();
	if (oldLevelName != levelName || oldTeam != Team) {
		Refresh(levelName, spots, false);
		return;
	}

	int screen_w, screen_h, center_w, center_h;
	g_EngineClient->GetScreenSize(screen_w, screen_h);
	center_w = screen_w / 2;
	center_h = screen_h / 2;
	bool spotErased = false, spotFound = false;

	for (int i = 0; i < spots.size(); i++) {
		Vector spot = spots.at(i);
		Color c = colorDefault;
		float dist3D = DistanceMeters(g_LocalPlayer->GetAbsOrigin(), spot);
		if (dist3D <= 1) c = colorClose;
		Vector pos2D;
		if (Math::WorldToScreen(spot, pos2D)) {
			float dist2D = pos2D.DistTo(Vector(center_w, center_h, 0));
			if (dist2D <= 15 && !spotFound) {
				c = ColorSelected;
				spotFound = true;
				if (button_clicked && !spotErased) { //button_clicked
					spots.erase(spots.begin() + i);
					spotErased = true;
					Refresh(levelName, spots, true);
					continue;
				}
			}
		}

		Ray_t ray; trace_t trace; CTraceFilter filter;
		ray.Init(g_LocalPlayer->GetEyePos(), spot);
		filter.pSkip = g_LocalPlayer;
		g_EngineTrace->TraceRay(ray, 0x46004003, &filter, &trace);
		bool isVisible = trace.IsVisible();

			
		if (g_Options.misc_SpotMarkersShow) {
			char dist_to[32];
			sprintf_s(dist_to, "%.0fm", dist3D);
			Render::Get().RenderBoxFilled(pos2D.x - 8, pos2D.y - 8, pos2D.x + 8, pos2D.y + 8, c);
			Render::Get().RenderText(std::to_string(i).c_str(), pos2D.x, pos2D.y - 8, 18, Color(255, 255, 255, 255), true, true, g_pSecondFont);
			Render::Get().RenderText(dist_to, pos2D.x, pos2D.y + 8, 18, Color(255, 255, 255, 255), true, true, g_pSecondFont);
		}
	}

	if (button_clicked && !spotErased) { //button_clicked
		Vector traceStart, traceEnd;
		QAngle viewAngles; g_EngineClient->GetViewAngles(&viewAngles);
		Math::AngleVectors(viewAngles, traceEnd);
		traceStart = g_LocalPlayer->GetEyePos();
		traceEnd = traceStart + (traceEnd * 8192.f);
		Ray_t ray; trace_t trace; CTraceFilter filter;
		ray.Init(traceStart, traceEnd);
		filter.pSkip = g_LocalPlayer;
		g_EngineTrace->TraceRay(ray, 0x46004003, &filter, &trace);
		Vector spot = trace.endpos;
		spots.push_back(spot);
		Refresh(levelName, spots, true);
	}
	spotmarkers->button_clicked = false;
}

void CSpotMarkers::Refresh(std::string levelName, std::vector<Vector> &spots, bool save)
{
	if (!g_LocalPlayer)
		return;

	std::string levelNameFixed;
	for (size_t i = 0; i < levelName.size(); ++i)
		if (levelName[i] != '\\') levelNameFixed += levelName[i];

	static char path[MAX_PATH] = "C:\\Cheat\\SpotMarkers\\";
	std::string folder, file;
	//char szCmd[256];
	//sprintf(szCmd, "SpotMarkers\\%s.ini", levelNameFixed);
	std::string Team = g_LocalPlayer->m_iTeamNum() == 3 ? "CT" : "T";
	folder = std::string(path) + std::string("SpotMarkers");
	levelNameFixed.erase(levelNameFixed.find(".bsp")); //Removes .bsp from levelname
	file = std::string(path) + levelNameFixed + Team + ".ini";

	CreateDirectoryA(path, NULL);
	if (save) {
		DeleteFileA(file.c_str());
		for (int i = 0; i < spots.size(); i++) {
			Vector spot = spots.at(i);
			WritePrivateProfileStringA(std::to_string(i).c_str(), "x", std::to_string(spot.x).c_str(), file.c_str());
			WritePrivateProfileStringA(std::to_string(i).c_str(), "y", std::to_string(spot.y).c_str(), file.c_str());
			WritePrivateProfileStringA(std::to_string(i).c_str(), "z", std::to_string(spot.z).c_str(), file.c_str());
		}
	}
	else {
		char value[32] = { '\0' };
		spots.clear();
		int i = 0;
		bool limitReached = false;
		while (!limitReached){
			GetPrivateProfileStringA(std::to_string(i).c_str(), "x", "", value, 32, file.c_str());
			float x = atof(value);
			GetPrivateProfileStringA(std::to_string(i).c_str(), "y", "", value, 32, file.c_str());
			float y = atof(value);
			GetPrivateProfileStringA(std::to_string(i).c_str(), "z", "", value, 32, file.c_str());
			float z = atof(value);
			if (x == 0 && y == 0 && z == 0) {
				limitReached = true;
				continue;
			}
			Vector spot = Vector(x, y, z);
			spots.push_back(spot);
			i++;
		}
	}
}
