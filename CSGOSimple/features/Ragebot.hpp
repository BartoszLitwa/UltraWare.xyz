#pragma once
#include "../Includes.h"
#include "../render.hpp"
#include "Autowall.hpp"

class RageBot
{
private:
	QAngle m_oldangle;
	float m_oldforward;
	float m_oldsidemove;
public:
	float DamageForESP;
	QAngle AngleToDrawonScreen;
	void CreateMove(CUserCmd* cmd, bool& SendPacket);
	bool LBYUpdate();
	void DrawAngles(QAngle Angle);
	void AA(CUserCmd* cmd, bool& bSendPacket, C_BasePlayer* local);
	C_BasePlayer* GetBestEntity(CUserCmd* cmd, QAngle Angle, C_BasePlayer* local, float& Damage, int& BestHitbox, int& BestRecord, bool AWBackTrack);
	void RageAimbot(int index, C_BasePlayer* local, C_BaseCombatWeapon* weapon, CUserCmd* cmd, bool AutoWall, float MinDamage, float HitChance, bool AWBackTrack);
	void fixMoveStart(CUserCmd* cmd);
	void fixMoveEnd(CUserCmd* cmd);
	void FakeLag(CUserCmd* cmd, bool& SendPackets);
};

extern RageBot ragebot;
