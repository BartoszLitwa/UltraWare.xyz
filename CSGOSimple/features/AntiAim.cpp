#include "AntiAim.hpp"
#include "BackTrack.hpp"

AntiAim antiaim;

QAngle m_oldangle;
float m_oldforward;
float m_oldsidemove;

void AntiAim::AA(CUserCmd* cmd, bool& bSendPacket)
{
	if (!g_LocalPlayer || !g_LocalPlayer->IsAlive() || !g_Options.DeSync)
		return;

	//if (cmd->buttons & IN_ATTACK || g_LocalPlayer->m_nMoveType() == MOVETYPE_LADDER || g_LocalPlayer->m_nMoveType() == MOVETYPE_NOCLIP || g_LocalPlayer->m_nMoveType() == MOVETYPE_OBSERVER)
		//return;
	bSendPacket = true;

	if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK2)
		return;

	fixMoveStart(cmd);

	AntiAimYaw(cmd, bSendPacket);

	fixMoveEnd(cmd);
}

void AntiAim::AntiAimYaw(CUserCmd* cmd, bool& bSendPacket)
{
	C_BasePlayer* Local = (C_BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());
	if (!Local)
		return;

	float server_time = g_LocalPlayer->m_nTickBase() * g_GlobalVars->interval_per_tick;
	static bool Flip = false;
	static bool Flip2;
	
	Flip2 = !Flip2;
	QAngle ViewANG;
	static int side = -1;
	static QAngle LastYaw;
	float maxdelta = Local->get_max_desync_delta() * 100;
	switch (g_Options.AntiAimTypeYaw) 
	{
	case 0:

		break;
	case 1: //Legit 
		if (LBYBreaker(cmd)) {
			cmd->viewangles.yaw += maxdelta * -LegitAASide;
			cmd->viewangles.Clamp();
		}
		else {
			if (cmd->tick_count % 2) {
				cmd->viewangles.yaw += g_Options.DeSyncValue * LegitAASide;
				cmd->viewangles.Clamp();
			}
		}

		if (cmd->buttons & IN_DUCK) //cmd->sidemove != IN_MOVELEFT && cmd->sidemove != IN_MOVERIGHT &&
			cmd->sidemove = cmd->tick_count % 2 ? 3.25f : -3.25f;
		else
			cmd->sidemove = cmd->tick_count % 2 ? 1.10f : -1.10f;

		//bSendPacket = cmd->tick_count % 2;
		//if (LBYUpdate()) {
		//	bSendPacket = false;
		//	cmd->viewangles.yaw += 75.f;
		//	cmd->viewangles.Clamp();
		//}
		//cmd->viewangles.yaw += bSendPacket ? g_Options.DeSyncValue * LegitAASide: 0;
		//cmd->viewangles.Clamp();//side = 1 / -1 for changing direction of aaaw
		//
		//if(cmd->buttons & IN_DUCK) //cmd->sidemove != IN_MOVELEFT && cmd->sidemove != IN_MOVERIGHT &&
		//	cmd->sidemove = cmd->tick_count % 2 ? 3.25f : -3.25f;
		//else
		//	cmd->sidemove = cmd->tick_count % 2 ? 1.10f : -1.10f;
		break;
	case 2: //Spinbot
		if(bSendPacket)
			ViewANG.yaw = (float)(fmod(server_time / 1.5f * 360.0f * (g_Options.AntiAim_SpinBotSpeed / 2), 360.0f));

		break;
	case 3: // Jitter
		bSendPacket = false;
		if (bSendPacket) {
			bSendPacket = true;
			if (Flip)
				ViewANG.yaw -= 270.0f;
			else
				ViewANG.yaw -= 90.0f;
		}
		else
			bSendPacket = false;

		break;
	case 4: //SideWays
		if (bSendPacket) {
			bSendPacket = true;
			if (Flip)
				ViewANG.yaw += 90.0f;
			else
				ViewANG.yaw -= 90.0f;
		}
		else
			bSendPacket = true;
		break;
	case 5: //Fake SideWays
		if (bSendPacket) {
			bSendPacket = true;
			if (Flip)
				ViewANG.yaw += 90.0f;
			else
				ViewANG.yaw -= 90.0f;
		}
		else
			bSendPacket = false;
		break;
	case 6: //Static
		if (bSendPacket) {
			bSendPacket = true;
			if (Flip)
			{
				if (Flip2)
					ViewANG.yaw += 90.0f;
				else
					ViewANG.yaw -= 90.0f;
			}
			else
			{
				ViewANG.yaw += 180.0f;
			}
		}
		else
			bSendPacket = false;
		break;
	case 7: //Fake Static
		if (bSendPacket) {
			bSendPacket = true;
			if (Flip)
			{
				if (Flip2)
					ViewANG.yaw += 90.0f;
				else
					ViewANG.yaw -= 90.0f;
			}
			else
				ViewANG.yaw += 180.0f;
		}
		else
			bSendPacket = false;
		break;
	case 8: //Custom
		if (bSendPacket)
		{
			bSendPacket = true;
			ViewANG.yaw += g_Options.DeSyncValue;
		}
		else
			bSendPacket = false;
		break;
	default:
		break;
	}
	if (g_Options.AntiAimTypeYaw != 0) {
		ViewANG.Clamp();
		cmd->viewangles = ViewANG;
	}
}

bool AntiAim::LBYUpdate()
{
	static float Nextupdate = 0;
	float curtime = g_GlobalVars->curtime;
	auto AnimState = g_LocalPlayer->GetPlayerAnimState();

	if (!AnimState || !(g_LocalPlayer->m_fFlags() & FL_ONGROUND))
		return false;

	if (AnimState->speed_2d > 0.1f)
		Nextupdate = curtime + 0.22f;

	if (Nextupdate < curtime) {
		Nextupdate = curtime + 1.1f;
		return true;
	}
	return false;
}

bool AntiAim::LBYBreaker(CUserCmd* cmd)
{
	static float Nextupdate = 0;
	float curtime = g_GlobalVars->curtime;
	auto AnimState = g_LocalPlayer->GetPlayerAnimState();

	if (!AnimState || !(g_LocalPlayer->m_fFlags() & FL_ONGROUND))
		return false;

	if (AnimState->speed_2d > 0.1f)
		Nextupdate = curtime + 0.2f;

	if (Nextupdate < curtime) {
		Nextupdate = curtime + 1.f;
		return true;
	}
	return false;
	//g_GlobalVars->curtime + BackTrack::timeToTicks(0.22f) >= Nextupdate;
}

void AntiAim::fixMoveStart(CUserCmd* cmd)
{
	m_oldangle = cmd->viewangles;
	m_oldforward = cmd->forwardmove;
	m_oldsidemove = cmd->sidemove;
}

void AntiAim::fixMoveEnd(CUserCmd* cmd)
{
	float yaw_delta = cmd->viewangles.yaw - m_oldangle.yaw;
	float f1;
	float f2;

	if (m_oldangle.yaw < 0.f)
		f1 = 360.0f + m_oldangle.yaw;
	else
		f1 = m_oldangle.yaw;

	if (cmd->viewangles.yaw < 0.0f)
		f2 = 360.0f + cmd->viewangles.yaw;
	else
		f2 = cmd->viewangles.yaw;

	if (f2 < f1)
		yaw_delta = abs(f2 - f1);
	else
		yaw_delta = 360.0f - abs(f1 - f2);
	yaw_delta = 360.0f - yaw_delta;

	cmd->forwardmove = cos(DEG2RAD(yaw_delta)) * m_oldforward + cos(DEG2RAD(yaw_delta + 90.f)) * m_oldsidemove;
	cmd->sidemove = sin(DEG2RAD(yaw_delta)) * m_oldforward + sin(DEG2RAD(yaw_delta + 90.f)) * m_oldsidemove;
}
