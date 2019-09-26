#pragma once
#include <deque>
#include <algorithm>
#include "Includes.h"
#include "render.hpp"
#include "options.hpp"
#include "features/Autowall.hpp"

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

namespace BackTrack //https://github.com/danielkrupinski/Osiris/blob/master/Osiris/Hacks/Backtrack.cpp
{
	void update(ClientFrameStage_t stage);
	void Run(CUserCmd* cmd);
	QAngle calculateRelativeAngle(const Vector& source, const Vector& destination, const QAngle& viewAngles);

	float degreesToRadians(float degrees);

	float radiansToDegrees(float radians);

	struct Record {
		Vector origin;
		float simulationTime;
		matrix3x4_t matrix[128];
		bool isVisible;
		int BestHitboxAW;
		float BestDamageAW;
	};

	extern std::deque<Record> records[65];

	struct Cvars {
		ConVar* updateRate;
		ConVar* maxUpdateRate;
		ConVar* interp;
		ConVar* interpRatio;
		ConVar* minInterpRatio;
		ConVar* maxInterpRatio;
		ConVar* maxUnlag;
	};

	extern Cvars cvars;

	static float getLerp() //http://cpp0x.pl/dokumentacja/standard-C++11/constexpr/1096
	{
		auto ratio = std::clamp(cvars.interpRatio->GetFloat(), cvars.minInterpRatio->GetFloat(), cvars.maxInterpRatio->GetFloat());
		return max(cvars.interp->GetFloat(), (ratio / ((cvars.maxUpdateRate->GetBool()) ? cvars.maxUpdateRate->GetFloat() : cvars.updateRate->GetFloat())));
	}

	static auto valid(float simtime)
	{
		auto network = g_EngineClient->GetNetChannelInfo();
		if (!network)
			return false; 
		
		float server_time = g_LocalPlayer->m_nTickBase() * g_GlobalVars->interval_per_tick;//g_GlobalVars->interpolation_amount = servertime ??
		auto delta = std::clamp(network->GetLatency(FLOW_OUTGOING) + network->GetLatency(FLOW_INCOMING) + getLerp(), 0.f, cvars.maxUnlag->GetFloat()) - (server_time - simtime);
		return std::fabsf(delta) <= 0.2f;
	}

	static auto timeToTicks(float time)
	{
		return static_cast<int>(0.5f + time / g_GlobalVars->interval_per_tick); 
	}

	static void init()
	{
		records->clear();

		cvars.updateRate = g_CVar->FindVar("cl_updaterate");
		cvars.maxUpdateRate = g_CVar->FindVar("sv_maxupdaterate");
		cvars.interp = g_CVar->FindVar("cl_interp");
		cvars.interpRatio = g_CVar->FindVar("cl_interp_ratio");
		cvars.minInterpRatio = g_CVar->FindVar("sv_client_min_interp_ratio");
		cvars.maxInterpRatio = g_CVar->FindVar("sv_client_max_interp_ratio");
		cvars.maxUnlag = g_CVar->FindVar("sv_maxunlag");
	}
}