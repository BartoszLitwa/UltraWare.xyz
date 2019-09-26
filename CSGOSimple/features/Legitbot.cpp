#include "Legitbot.h"
#include "../BackTrack.hpp"

LegitBot legitbot;

//void LegitBot::BacktrackStart(CUserCmd* cmd)
//{
//	if (!g_LocalPlayer || !g_Options.BackTrack_BackTrack)
//		return;
//
//	for (size_t i = 1; i <= g_EngineClient->GetMaxClients(); i++) {
//		C_BasePlayer* entity = (C_BasePlayer*)g_EntityList->GetClientEntity(i);
//		if (entity && entity->IsAlive() && entity->m_iTeamNum() != g_LocalPlayer->m_iTeamNum() && !entity->IsDormant()) {
//			tick[i].insert(tick[i].begin(), RecordTicks(cmd->tick_count, entity->GetHitboxPos(g_Options.Aimbot_Hitbox)));
//
//			if (tick[i].size() > g_Options.BackTrack_Ticks)
//				tick[i].pop_back(); //Removes Last Tick
//		}
//	}
//}
//
//void LegitBot::BacktrackCalc(CUserCmd* cmd)
//{
//	if (!g_LocalPlayer || !g_Options.BackTrack_BackTrack)
//		return;
//
//	QAngle Viewangles;
//	g_EngineClient->GetViewAngles(&Viewangles);
//	Viewangles += g_LocalPlayer->m_aimPunchAngle() * 2;
//	float BestDelta = FLT_MAX;
//	int ClosestPlayerIndex = -1;
//	for (size_t i = 1; i <= g_EngineClient->GetMaxClients(); i++){
//		C_BasePlayer* entity = (C_BasePlayer*)g_EntityList->GetClientEntity(i);
//		if (entity && entity->IsAlive() && entity->m_iTeamNum() != g_LocalPlayer->m_iTeamNum() && !entity->IsDormant()) {
//			QAngle Enemyangle = Math::CalcAngle(g_LocalPlayer->GetEyePos(), entity->GetHitboxPos(g_Options.Aimbot_Hitbox));
//			float delta = Math::GetFOV(Viewangles, Enemyangle);
//			if (delta < BestDelta) {
//				BestDelta = delta;
//				ClosestPlayerIndex = i;
//			}
//		}
//	}
//
//	int Index = -1;
//	if (ClosestPlayerIndex != -1) {
//		for (size_t i = 0; i < tick[ClosestPlayerIndex].size(); i++){
//			QAngle EnemyAngle = Math::CalcAngle(g_LocalPlayer->GetEyePos(), tick[ClosestPlayerIndex].at(i).Head);
//			float deltaTick = Math::GetFOV(Viewangles, EnemyAngle);
//			if (deltaTick < BestDelta) {
//				Index = i;
//				BestDelta = deltaTick;
//			}
//		}
//
//		if (Index != -1 && cmd->buttons & IN_ATTACK) {
//			cmd->tick_count = tick[ClosestPlayerIndex].at(Index).tick;
//		}
//	}
//}

void LegitBot::StartLegitbot(CUserCmd* cmd)
{
	if (!g_LocalPlayer || !g_LocalPlayer->IsAlive() || !g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
		return;

	auto weapon = g_LocalPlayer->m_hActiveWeapon();
	if (!weapon)
		return;

	C_BaseCombatWeapon* gun = (C_BaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(weapon);
	if (!gun)
		return;

	short index = gun->m_Item().m_iItemDefinitionIndex();
	//Pistols
	if (index == WEAPON_HKP2000 || index == WEAPON_DEAGLE || index == WEAPON_ELITE || index == WEAPON_FIVESEVEN || index == WEAPON_GLOCK || index == WEAPON_P250 || index == WEAPON_TEC9 || index == WEAPON_USP_SILENCER || index == WEAPON_CZ75A || index == WEAPON_REVOLVER) {
		AimAtEnemy(cmd, g_Options.Aimbot_Aimbot_Pistols, g_Options.Aimbot_AutoScope_Pistols, g_Options.Aimbot_AutoStop_Pistols, g_Options.Aimbot_AutoCrouch_Pistols, g_Options.Aimbot_Hitbox_Pistols, g_Options.Aimbot_RecoilPrediction_Pistols,
			g_Options.Aimbot_SmoothAmount_Pistols, g_Options.Aimbot_Silent_Pistols, g_Options.Aimbot_VisibilityCheck_Pistols, g_Options.Aimbot_FOV_Pistols);
		Triggerbot(cmd, g_Options.TriggerBot_TriggerBot_Pistols, g_Options.TriggerBot_Delay_Pistols, g_Options.TriggerBot_HitBox_Pistols, g_Options.TriggerBot_HitChance_Pistols);
	}
	//Rifles
	else if (index == WEAPON_AK47 || index == WEAPON_AUG || index == WEAPON_FAMAS || index == WEAPON_GALILAR || index == WEAPON_M4A1 || index == WEAPON_SG556 || index == WEAPON_M4A1_SILENCER) {
		AimAtEnemy(cmd, g_Options.Aimbot_Aimbot_Rifles, g_Options.Aimbot_AutoScope_Rifles, g_Options.Aimbot_AutoStop_Rifles, g_Options.Aimbot_AutoCrouch_Rifles, g_Options.Aimbot_Hitbox_Rifles, g_Options.Aimbot_RecoilPrediction_Rifles,
			g_Options.Aimbot_SmoothAmount_Rifles, g_Options.Aimbot_Silent_Rifles, g_Options.Aimbot_VisibilityCheck_Rifles, g_Options.Aimbot_FOV_Rifles);
		Triggerbot(cmd, g_Options.TriggerBot_TriggerBot_Rifles, g_Options.TriggerBot_Delay_Rifles, g_Options.TriggerBot_HitBox_Rifles, g_Options.TriggerBot_HitChance_Rifles);
	}
	//SMG
	else if (index == WEAPON_M249 || index == WEAPON_MAC10 || index == WEAPON_P90 || index == WEAPON_MP5 || index == WEAPON_UMP45 || index == WEAPON_BIZON || index == WEAPON_NEGEV || index == WEAPON_MP7 || index == WEAPON_MP9) {
		AimAtEnemy(cmd, g_Options.Aimbot_Aimbot_SMG, g_Options.Aimbot_AutoScope_SMG, g_Options.Aimbot_AutoStop_SMG, g_Options.Aimbot_AutoCrouch_SMG, g_Options.Aimbot_Hitbox_SMG, g_Options.Aimbot_RecoilPrediction_SMG,
			g_Options.Aimbot_SmoothAmount_SMG, g_Options.Aimbot_Silent_SMG, g_Options.Aimbot_VisibilityCheck_SMG, g_Options.Aimbot_FOV_SMG);
		Triggerbot(cmd, g_Options.TriggerBot_TriggerBot_SMG, g_Options.TriggerBot_Delay_SMG, g_Options.TriggerBot_HitBox_SMG, g_Options.TriggerBot_HitChance_SMG);
	}
	//Shotguns
	else if (index == WEAPON_XM1014 || index == WEAPON_MAG7 || index == WEAPON_SAWEDOFF || index == WEAPON_NOVA) {
		AimAtEnemy(cmd, g_Options.Aimbot_Aimbot_Shotguns, g_Options.Aimbot_AutoScope_Shotguns, g_Options.Aimbot_AutoStop_Shotguns, g_Options.Aimbot_AutoCrouch_Shotguns, g_Options.Aimbot_Hitbox_Shotguns, g_Options.Aimbot_RecoilPrediction_Shotguns,
			g_Options.Aimbot_SmoothAmount_Shotguns, g_Options.Aimbot_Silent_Shotguns, g_Options.Aimbot_VisibilityCheck_Shotguns, g_Options.Aimbot_FOV_Shotguns);
		Triggerbot(cmd, g_Options.TriggerBot_TriggerBot_Shotguns, g_Options.TriggerBot_Delay_Shotguns, g_Options.TriggerBot_HitBox_Shotguns, g_Options.TriggerBot_HitChance_Shotguns);
	}
	//AWP
	else if (index == WEAPON_AWP) {
		AimAtEnemy(cmd, g_Options.Aimbot_Aimbot_AWP, g_Options.Aimbot_AutoScope_AWP, g_Options.Aimbot_AutoStop_AWP, g_Options.Aimbot_AutoCrouch_AWP, g_Options.Aimbot_Hitbox_AWP, g_Options.Aimbot_RecoilPrediction_AWP,
			g_Options.Aimbot_SmoothAmount_AWP, g_Options.Aimbot_Silent_AWP, g_Options.Aimbot_VisibilityCheck_AWP, g_Options.Aimbot_FOV_AWP);
		Triggerbot(cmd, g_Options.TriggerBot_TriggerBot_AWP, g_Options.TriggerBot_Delay_AWP, g_Options.TriggerBot_HitBox_AWP, g_Options.TriggerBot_HitChance_AWP);
	}
	//SSG08
	else if (index == WEAPON_SSG08) {
		AimAtEnemy(cmd, g_Options.Aimbot_Aimbot_SSG08, g_Options.Aimbot_AutoScope_SSG08, g_Options.Aimbot_AutoStop_SSG08, g_Options.Aimbot_AutoCrouch_SSG08, g_Options.Aimbot_Hitbox_SSG08, g_Options.Aimbot_RecoilPrediction_SSG08,
			g_Options.Aimbot_SmoothAmount_SSG08, g_Options.Aimbot_Silent_SSG08, g_Options.Aimbot_VisibilityCheck_SSG08, g_Options.Aimbot_FOV_SSG08);
		Triggerbot(cmd, g_Options.TriggerBot_TriggerBot_SSG08, g_Options.TriggerBot_Delay_SSG08, g_Options.TriggerBot_HitBox_SSG08, g_Options.TriggerBot_HitChance_SSG08);
	}
	//Autos
	else if (index == WEAPON_G3SG1 || index == WEAPON_SCAR20) {
		AimAtEnemy(cmd, g_Options.Aimbot_Aimbot_Autos, g_Options.Aimbot_AutoScope_Autos, g_Options.Aimbot_AutoStop_Autos, g_Options.Aimbot_AutoCrouch_Autos, g_Options.Aimbot_Hitbox_Autos, g_Options.Aimbot_RecoilPrediction_Autos,
			g_Options.Aimbot_SmoothAmount_Autos, g_Options.Aimbot_Silent_Autos, g_Options.Aimbot_VisibilityCheck_Autos, g_Options.Aimbot_FOV_Autos);
		Triggerbot(cmd, g_Options.TriggerBot_TriggerBot_Autos, g_Options.TriggerBot_Delay_Autos, g_Options.TriggerBot_HitBox_Autos, g_Options.TriggerBot_HitChance_Autos);
	}
}

C_BasePlayer* LegitBot::ClosestEnemyToCrosshair(QAngle Angle, bool Aimbot_VisibilityCheck, int Aimbot_Hitbox, float Aimbot_FOV)
{
	C_BasePlayer* Entity = nullptr;
	float BestDelta = FLT_MAX;
	for (size_t i = 1; i <= g_EngineClient->GetMaxClients(); i++){
		C_BasePlayer* Ent = (C_BasePlayer*)g_EntityList->GetClientEntity(i);
		if (Ent && !Ent->IsDormant() && Ent->IsAlive() && Ent->m_iTeamNum() != g_LocalPlayer->m_iTeamNum() && !Ent->m_bGunGameImmunity()){
			if (Aimbot_VisibilityCheck)
				if (!g_LocalPlayer->CanSeePlayer(Ent, HITBOX_CHEST))
					continue;

			QAngle EnemyAngle = calculateRelativeAngle(g_LocalPlayer->GetEyePos(), Ent->GetHitboxPos(Aimbot_Hitbox), Angle - g_LocalPlayer->m_aimPunchAngle() * 2) ;
			float delta = std::hypotf(EnemyAngle.yaw, EnemyAngle.pitch); //(EnemyAng - (g_LocalPlayer->m_aimPunchAngle() * 2) - ViewAngles).Clamped().Length();

			if (delta < BestDelta && delta <= Aimbot_FOV){
				BestDelta = delta;
				Entity = Ent;
			}
		}
	}

	return Entity;
}

void LegitBot::Smoothing(QAngle& viewangle, QAngle& angle, float smoothValue)
{
	angle = (viewangle + (angle - viewangle).Clamp() / smoothValue).Clamp();
}

static int oldforwardmove;
static int oldsidemove;
void LegitBot::AimAtEnemy(CUserCmd* cmd, bool Aimbot_Aimbot, bool Aimbot_AutoScope, bool Aimbot_AutoStop, bool Aimbot_AutoCrouch, int Aimbot_Hitbox, bool Aimbot_RecoilPrediction, float Aimbot_SmoothAmount, bool Aimbot_Silent, bool Aimbot_VisibilityCheck, float Aimbot_FOV)
{
	if(Aimbot_Aimbot && g_LocalPlayer->IsAlive())
		if (cmd->buttons & IN_ATTACK){
			QAngle ViewAngles;
			g_EngineClient->GetViewAngles(&ViewAngles);
			C_BasePlayer* Entity = ClosestEnemyToCrosshair(ViewAngles, Aimbot_VisibilityCheck, Aimbot_Hitbox, Aimbot_FOV);

			if (Entity) {
				if (g_LocalPlayer->m_hActiveWeapon()->CanFire()) {
					if (Aimbot_AutoScope && !g_LocalPlayer->m_bIsScoped() && g_LocalPlayer->m_hActiveWeapon()->IsSniper())
						cmd->buttons |= IN_ATTACK2;

					if (Aimbot_AutoStop) {
						if (cmd->sidemove == IN_MOVELEFT || cmd->sidemove == IN_MOVERIGHT || cmd->forwardmove == IN_FORWARD || cmd->forwardmove == IN_BACK) {
							cmd->forwardmove = -oldforwardmove;
							cmd->sidemove = -oldsidemove;
						}
						//cmd->upmove = 0;
					}

					if (Aimbot_AutoCrouch)
						cmd->buttons |= IN_DUCK;
				}

				QAngle EnemyAngle = Math::CalcAngle(g_LocalPlayer->GetEyePos(), Entity->GetHitboxPos(Aimbot_Hitbox));

				if (Aimbot_RecoilPrediction) {
					static auto weaponRecoilScale = g_CVar->FindVar("weapon_recoil_scale");
					auto aimPunch = g_LocalPlayer->m_aimPunchAngle() * weaponRecoilScale->GetFloat();
					EnemyAngle -= aimPunch;
				}

				if (Aimbot_SmoothAmount > 0) 
					Smoothing(ViewAngles, EnemyAngle, Aimbot_SmoothAmount); 

				EnemyAngle.Clamp(); //Important

				if (Aimbot_Silent)
					cmd->viewangles = EnemyAngle;
				else
					g_EngineClient->SetViewAngles(&EnemyAngle);
			}

			oldforwardmove = cmd->forwardmove;
			oldsidemove = cmd->sidemove;
		}
}

void LegitBot::Triggerbot(CUserCmd* cmd, bool TriggerBot_TriggerBot, int TriggerBot_Delay, int TriggerBot_HitBox, float TriggerBot_HitChance)
{
	static bool TimeSet = false;
	static bool CanShoot = true;
	static float Time;

	if (TriggerBot_TriggerBot && g_LocalPlayer->IsAlive() && g_LocalPlayer) {

		if (TriggerBot_Delay > 0) {
			if (g_LocalPlayer->m_iShotsFired() < 1 && !TimeSet) {
				Time = g_GlobalVars->curtime + (TriggerBot_Delay / 100);
				TimeSet = true;
			}

			long long currentTime = g_GlobalVars->curtime;
			if (Time < currentTime || !TimeSet)
				return;
		}

		auto weapon = (C_BaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(g_LocalPlayer->m_hActiveWeapon());
		if (!weapon)
			return;

		auto weaponData = weapon->GetCSWeaponData();
		if (!weaponData)
			return;

		Vector src = g_LocalPlayer->GetEyePos();
		Vector Angles = Vector();
		QAngle ang; g_EngineClient->GetViewAngles(&ang); 
		ang += g_LocalPlayer->m_aimPunchAngle() * 2;
		//thats AngleVectors and i dont do normalize
		float c = cos(ang.pitch * 3.14159265f / 180.f);
		Vector forwardVec = Vector(c * cos(ang.yaw * 3.14159265f / 180.f), c * sin(ang.yaw * 3.14159265f / 180.f), -sin(ang.pitch * 3.14159265f / 180.f));

		Vector dst = Vector();

		forwardVec *= weaponData->flRange; //weaponData->flRange - crashing
		dst = src + forwardVec;

		CGameTrace trace;
		CTraceFilter filter; 
		Ray_t ray;
		ray.Init(src, dst); //Init ray
		filter.pSkip = g_LocalPlayer;

		g_EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace); //0x46004003 trace everything that can be shooten through

		auto Entity = trace.hit_entity;
		if (!Entity)
			return;

		auto Entity_class = Entity->GetClientClass();
		if (!Entity_class)
			return;

		if (Entity_class->m_ClassID != ClassId_CCSPlayer)
			return;

		C_BasePlayer* PlayerToShoot = (C_BasePlayer*)Entity;
		if (!PlayerToShoot || PlayerToShoot->m_iTeamNum() == g_LocalPlayer->m_iTeamNum() || PlayerToShoot->IsDormant() || !PlayerToShoot->IsAlive())
			return;

		if(TriggerBot_HitBox != 0)
			if (trace.hitgroup != TriggerBot_HitBox)
				return; 

		if (TriggerBot_HitChance > 0) {
			auto ChanceToHit = (100.f - TriggerBot_HitChance) * 0.65f * 0.01125f;
			if (ChanceToHit <= weapon->GetInaccuracy())
				return;
		}

			cmd->buttons |= IN_ATTACK;
			TimeSet = false;
	}
}

QAngle LegitBot::calculateRelativeAngle(const Vector& source, const Vector& destination, const QAngle& viewAngles)
{
	Vector delta = destination - source;
	QAngle angles{ radiansToDegrees(atan2f(-delta.z, std::hypotf(delta.x, delta.y))) - viewAngles.pitch,
				   radiansToDegrees(atan2f(delta.y, delta.x)) - viewAngles.yaw, 0.f };
	angles.Clamp();
	return angles;
}

float LegitBot::degreesToRadians(float degrees)
{
	return degrees * static_cast<float>(M_PI) / 180.0f;
}
float LegitBot::radiansToDegrees(float radians)
{
	return radians * 180.0f / static_cast<float>(M_PI);
}
