#include "Ragebot.hpp"
#include "..//options.hpp"
#include "BackTrack.hpp"
#include "..//g_Variables.hpp"

RageBot ragebot;

void RageBot::CreateMove(CUserCmd* cmd, bool& SendPacket) {

	fixMoveStart(cmd);

	C_BasePlayer* local = (C_BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());
	if (!local || !local->IsAlive() || !g_EngineClient->IsInGame() || !g_EngineClient->IsConnected()) {
		DamageForESP = 0;
		return;
	}

	C_BaseCombatWeapon* weapon = local->m_hActiveWeapon();
	if (!weapon || weapon->IsKnife()) {
		DamageForESP = 0;
		return;
	}

	C_BaseCombatWeapon* gun = (C_BaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(local->m_hActiveWeapon());
	if (!gun)
		return;

	short index = gun->m_Item().m_iItemDefinitionIndex();
	//Pistols
	if (index == WEAPON_HKP2000 || index == WEAPON_DEAGLE || index == WEAPON_ELITE || index == WEAPON_FIVESEVEN || index == WEAPON_GLOCK || index == WEAPON_P250 || index == WEAPON_TEC9 || index == WEAPON_USP_SILENCER || index == WEAPON_CZ75A || index == WEAPON_REVOLVER) {
		RageAimbot(index, local, weapon, cmd, g_Options.AutoWall_AutoWall_Pistols, g_Options.AutoWall_MinDamage_Pistols, g_Options.AutoWall_Hitchance_Pistols, g_Options.AutoWall_BackTrack_Pistols);
	}
	//Rifles
	else if (index == WEAPON_AK47 || index == WEAPON_AUG || index == WEAPON_FAMAS || index == WEAPON_GALILAR || index == WEAPON_M4A1 || index == WEAPON_SG556 || index == WEAPON_M4A1_SILENCER) {
		RageAimbot(index, local, weapon, cmd, g_Options.AutoWall_AutoWall_Rifles, g_Options.AutoWall_MinDamage_Rifles, g_Options.AutoWall_Hitchance_Rifles, g_Options.AutoWall_BackTrack_Rifles);
	}
	//SMG
	else if (index == WEAPON_M249 || index == WEAPON_MAC10 || index == WEAPON_P90 || index == WEAPON_MP5 || index == WEAPON_UMP45 || index == WEAPON_BIZON || index == WEAPON_NEGEV || index == WEAPON_MP7 || index == WEAPON_MP9) {
		RageAimbot(index, local, weapon, cmd, g_Options.AutoWall_AutoWall_SMG, g_Options.AutoWall_MinDamage_SMG, g_Options.AutoWall_Hitchance_SMG, g_Options.AutoWall_BackTrack_SMG);
	}
	//Shotguns
	else if (index == WEAPON_XM1014 || index == WEAPON_MAG7 || index == WEAPON_SAWEDOFF || index == WEAPON_NOVA) {
		RageAimbot(index, local, weapon, cmd, g_Options.AutoWall_AutoWall_ShotGuns, g_Options.AutoWall_MinDamage_ShotGuns, g_Options.AutoWall_Hitchance_ShotGuns, g_Options.AutoWall_BackTrack_ShotGuns);
	}
	//SSG08
	else if (index == WEAPON_SSG08) {
		RageAimbot(index, local, weapon, cmd, g_Options.AutoWall_AutoWall_SSG08, g_Options.AutoWall_MinDamage_SSG08, g_Options.AutoWall_Hitchance_SSG08, g_Options.AutoWall_BackTrack_SSG08);
	}
	//AWP
	else if (index == WEAPON_AWP) {
		RageAimbot(index, local, weapon, cmd, g_Options.AutoWall_AutoWall_AWP, g_Options.AutoWall_MinDamage_AWP, g_Options.AutoWall_Hitchance_AWP, g_Options.AutoWall_BackTrack_AWP);
	}
	//Autos
	else if (index == WEAPON_G3SG1 || index == WEAPON_SCAR20) {
		RageAimbot(index, local, weapon, cmd, g_Options.AutoWall_AutoWall_Autos, g_Options.AutoWall_MinDamage_Autos, g_Options.AutoWall_Hitchance_Autos, g_Options.AutoWall_BackTrack_Autos);
	}

	fixMoveEnd(cmd);
}

bool RageBot::LBYUpdate()
{
	static float Nextupdate = 0;
	float curtime = g_GlobalVars->curtime;
	auto AnimState = g_LocalPlayer->GetPlayerAnimState();

	if (!AnimState || !(g_LocalPlayer->m_fFlags() & FL_ONGROUND))
		return false;

	if (AnimState->speed_2d > 0.1f)
		Nextupdate = curtime + 0.21f; //0.22

	if (Nextupdate < curtime) {
		Nextupdate = curtime + 1.09f; //1.1
		return true;
	}
	return false;
}

void RageBot::DrawAngles(QAngle Angle)
{
	if (!g_Options.DeSync || Angle.IsZero())
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer || !g_LocalPlayer->IsAlive())
		return;

	Vector src3D, dst3D, forward, forward2, src, dst;
	trace_t trace;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = g_LocalPlayer;

	QAngle EngineAngles;
	g_EngineClient->GetViewAngles(&EngineAngles);
	src3D = g_LocalPlayer->GetAbsOrigin();

	Math::AngleVectors(QAngle(0, g_LocalPlayer->m_flLowerBodyYawTarget(), 0), forward2);
	dst3D = src3D + (forward2 * 50.f);

	ray.Init(src3D, dst3D);
	g_EngineTrace->TraceRay(ray, 0, &filter, &trace);

	if (!Math::WorldToScreen(src3D, src) || !Math::WorldToScreen(trace.endpos, dst))
		return;

	Render::Get().RenderLine(src.x, src.y, dst.x, dst.y, Color(0, 0, 255, 255));
	Render::Get().RenderText("LBY", ImVec2(dst.x, dst.y), 14.f, Color(0, 0, 255, 255), true);

	Math::AngleVectors(QAngle(0, EngineAngles.yaw, 0), forward);
	dst3D = src3D + (forward * 50.f);

	ray.Init(src3D, dst3D);
	g_EngineTrace->TraceRay(ray, 0, &filter, &trace);

	if (!Math::WorldToScreen(src3D, src) || !Math::WorldToScreen(trace.endpos, dst))
		return;

	Render::Get().RenderLine(src.x, src.y, dst.x, dst.y, Color(255, 0, 0, 255));
	Render::Get().RenderText("Engine", ImVec2(dst.x, dst.y), 14.f, Color(255, 0, 0, 255), true);

	Math::AngleVectors(QAngle(0, Angle.yaw, 0), forward);
	dst3D = src3D + (forward * 50.f);

	ray.Init(src3D, dst3D);
	g_EngineTrace->TraceRay(ray, 0, &filter, &trace);

	if (!Math::WorldToScreen(src3D, src) || !Math::WorldToScreen(trace.endpos, dst))
		return;

	Render::Get().RenderLine(src.x, src.y, dst.x, dst.y, Color(0, 255, 0, 255));
	Render::Get().RenderText("Real", ImVec2(dst.x, dst.y), 14.f, Color(0, 255, 0, 255), true);
}

void RageBot::AA(CUserCmd* cmd, bool& bSendPacket, C_BasePlayer* local)
{
	if (!g_Options.DeSync)
		return;

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !g_LocalPlayer || !g_LocalPlayer->IsAlive())
		return;

	if (local->m_nMoveType() == MOVETYPE_NOCLIP || local->m_nMoveType() == MOVETYPE_FLY || local->m_nMoveType() == MOVETYPE_LADDER)
		return;

	if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK2 || local->m_hActiveWeapon()->GetCSWeaponData()->iWeaponType == WEAPONTYPE_GRENADE)
		return;

	fixMoveStart(cmd);

	float server_time = g_LocalPlayer->m_nTickBase() * g_GlobalVars->interval_per_tick;
	float maxdelta = local->get_max_desync_delta();
	QAngle ToDraw;
	ToDraw = cmd->viewangles;
	if (g_Options.AntiAimTypeYaw == 0) {//Auto
		float Damage;
		int BestHitbox;
		int BestRecord;
		QAngle ViewAngle = cmd->viewangles;
		C_BasePlayer* entity = GetBestEntity(cmd, ViewAngle, local, Damage, BestHitbox, BestRecord, true);
		if (!entity)
			return;

		QAngle EnemyAngle = Math::CalcAngle(local->GetEyePos(), entity->GetHitboxPos(HITBOX_CHEST));
		QAngle AAAngle = EnemyAngle;
		AAAngle.yaw += g_Options.DeSyncValue;
		AAAngle.pitch = g_Options.DeSyncValue2;
		AAAngle.Clamp();
		ToDraw = AAAngle;
		cmd->viewangles = AAAngle;
	}
	else if (g_Options.AntiAimTypeYaw == 1) {//legit
		if (cmd->sidemove != IN_MOVELEFT && cmd->sidemove != IN_MOVERIGHT)
			return;

		if (cmd->buttons & IN_DUCK) //cmd->sidemove != IN_MOVELEFT && cmd->sidemove != IN_MOVERIGHT &&
			cmd->sidemove = cmd->tick_count % 2 ? 3.25f : -3.25f;
		else
			cmd->sidemove = cmd->tick_count % 2 ? 1.10f : -1.10f;

		static int ChokedPackets = -1;
		ChokedPackets++;
		static bool yFlip;
		if (ChokedPackets < 1)
		{
			bSendPacket = true;
		}
		else
		{
			bSendPacket = false;
			yFlip ? AngleToDrawonScreen.yaw += 90.f : AngleToDrawonScreen.yaw -= 90.f;
			yFlip ? cmd->viewangles.yaw += 90.f : cmd->viewangles.yaw -= 90.f;
			ChokedPackets = -1;
		}
		yFlip != yFlip;
		/*if (LBYUpdate()) {
			cmd->viewangles.yaw -= maxdelta;
			ToDraw.yaw -= maxdelta;
			cmd->viewangles.Clamp();
		}
		else {
			if (cmd->tick_count % 2) {
				cmd->viewangles.yaw += g_Options.DeSyncValue * g_Options.DeSyncValue2;
				ToDraw.yaw += g_Options.DeSyncValue * g_Options.DeSyncValue2;
				cmd->viewangles.Clamp();
			}
		}*/
	}
	else if (g_Options.AntiAimTypeYaw == 2) {
		if (bSendPacket) {
			cmd->viewangles.yaw = (float)(fmod(server_time / 1.5f * 360.0f * (g_Options.AntiAim_SpinBotSpeed / 2), 360.0f));
			cmd->viewangles.Clamp();
			ToDraw.yaw = (float)(fmod(server_time / 1.5f * 360.0f * (g_Options.AntiAim_SpinBotSpeed / 2), 360.0f));
		}
	}
	AngleToDrawonScreen = ToDraw;

	fixMoveEnd(cmd);
}

C_BasePlayer* RageBot::GetBestEntity(CUserCmd* cmd,QAngle Angle, C_BasePlayer* local, float& Damage, int& BestHitbox, int& BestRecord, bool AWBackTrack)
{
	C_BasePlayer* BestEntity = nullptr;
	float BestDamage = -1;
	int Hitbox = 0;
	int Record{};
	if (AWBackTrack) {
		for (int i = 1; i <= g_EngineClient->GetMaxClients(); i++) {
			C_BasePlayer* entity = (C_BasePlayer*)g_EntityList->GetClientEntity(i);
			if (!entity || entity == local || entity->IsDormant() || !entity->IsAlive() || entity->m_iTeamNum() == local->m_iTeamNum())
				continue;

			int TempHitbox = 0;
			float TempDamage = 0;
			int TempRecord = 0;
			for (int t = 0; t < BackTrack::records[i].size(); t++) {
				if (BackTrack::records[i][t].BestDamageAW > TempDamage) {
					TempDamage = BackTrack::records[i][t].BestDamageAW;
					TempHitbox = BackTrack::records[i][t].BestHitboxAW;
					TempRecord = t;
				}
			}

			if (TempDamage > BestDamage) {
				BestDamage = TempDamage;
				BestEntity = entity;
				Hitbox = TempHitbox;
				Record = TempRecord;
			}
		}
	}
	else {
		for (int i = 1; i < g_EngineClient->GetMaxClients(); i++) {
			C_BasePlayer* Entity = (C_BasePlayer*)g_EntityList->GetClientEntity(i);
			if (Entity && Entity->m_iTeamNum() != local->m_iTeamNum() && !Entity->IsDormant() && !Entity->m_bGunGameImmunity()) {
				float TempDamageEntity = 0;
				int TempBestHitbox = 0;

				for (int i = 0; i < 19; i++) {
					float TempDamage = Autowall::GetDamage(Entity->GetHitboxPos(i));
					if (TempDamage > TempDamageEntity) {
						TempDamageEntity = TempDamage;
						TempBestHitbox = i;
					}
				}
				if (TempDamageEntity > BestDamage) {
					BestDamage = TempDamageEntity;
					BestEntity = Entity;
					Hitbox = TempBestHitbox;
				}
			}
		}
	}
	Damage = BestDamage;
	BestHitbox = Hitbox;
	BestRecord = Record;
	return BestEntity;
}

void RageBot::RageAimbot(int index, C_BasePlayer* local, C_BaseCombatWeapon* weapon, CUserCmd* cmd, bool AutoWall, float MinDamage, float HitChance, bool AWBackTrack)
{
	if (!AutoWall)
		return;

	static bool CanShoot = true;
	float Damage;
	int BestHitbox;
	int BestRecord;
	QAngle ViewAngle = cmd->viewangles;
	C_BasePlayer* Entity = GetBestEntity(cmd, ViewAngle, local, Damage, BestHitbox, BestRecord, AWBackTrack);
	DamageForESP = Damage; //For showing damage on screen
	if (!Entity) {
		DamageForESP = 0;
		return;
	}

	if (DamageForESP < MinDamage)
		return;
	
	if (HitChance > 0.f && HitChance != 0) { //TODO: Better Hitchance
		auto ChanceToHit = (100.f - HitChance + 0.1f) * 0.65f * 0.01125f;
		if (ChanceToHit <= weapon->GetInaccuracy()) {
			DamageForESP = 0;
		return;
		}
	}

	Vector vel = local->m_vecVelocity();
	QAngle dir; Math::VectorAngles(vel, dir);
	float speed = vel.Length();
	dir.yaw = cmd->viewangles.yaw - dir.yaw;
	Vector negated; Math::AngleVectors(dir, negated);
	negated = negated * -speed;
	cmd->forwardmove = -negated.x;
	cmd->sidemove = -negated.y;

	if (abs(cmd->sidemove) > 1.f && abs(cmd->forwardmove) > 1.f) {
		CanShoot = false;
		return;
	}

	QAngle EnemyAngle = Math::CalcAngle(local->GetEyePos(), Entity->GetHitboxPos(BestHitbox));
	EnemyAngle -= local->m_aimPunchAngle() * 2;
	EnemyAngle.Clamp();

	if (!weapon->CanFire())
		return;

	if (AWBackTrack && BestRecord != 0) {
		auto record = BackTrack::records[Entity->EntIndex()][BestRecord];
		Entity->SetAbsOrigin(record.origin);
		cmd->tick_count = BackTrack::timeToTicks(record.simulationTime + BackTrack::getLerp());
	}

	cmd->buttons |= IN_ATTACK;
	cmd->viewangles = EnemyAngle;
	
}

void RageBot::fixMoveStart(CUserCmd* cmd)
{
	m_oldangle = cmd->viewangles;
	m_oldforward = cmd->forwardmove;
	m_oldsidemove = cmd->sidemove;
}

void RageBot::fixMoveEnd(CUserCmd* cmd)
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

void RageBot::FakeLag(CUserCmd* cmd ,bool& SendPackets)
{
	if (!g_Options.misc_FakeLag)
		return;

	if (!g_LocalPlayer || !g_LocalPlayer->IsAlive() || !g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
		return;

	INetChannel* NetChannel = g_EngineClient->GetNetChannel();
	if (!NetChannel)
		return;

	float velocity = abs(g_LocalPlayer->m_vecVelocity().Length2D());
	if (velocity < 1.f && g_LocalPlayer->m_fFlags() & FL_ONGROUND) {
		g_Var::ChockedPacket = (NetChannel->m_nChokedPackets >= g_Options.misc_FakeLagStandingAmount);
		SendPackets = (NetChannel->m_nChokedPackets >= g_Options.misc_FakeLagStandingAmount);
	}
	else if (velocity >= 1.f && g_LocalPlayer->m_fFlags() & FL_ONGROUND) {
		g_Var::ChockedPacket = (NetChannel->m_nChokedPackets >= g_Options.misc_FakeLagStandingAmount);
		SendPackets = (NetChannel->m_nChokedPackets >= g_Options.misc_FakeLagMovingAmount);
	}
	else if (!(g_LocalPlayer->m_fFlags() & FL_ONGROUND)) {
		g_Var::ChockedPacket = (NetChannel->m_nChokedPackets >= g_Options.misc_FakeLagStandingAmount);
		SendPackets = (NetChannel->m_nChokedPackets >= g_Options.misc_FakeLagInAirAmount);
	}

}
