#pragma once
#include "../Includes.h"
#include "../render.hpp"
#include "Autowall.hpp"

class LegitBot
{
public:
	////Backtrack
	//struct RecordTicks
	//{
	//	RecordTicks(int Tickcount, Vector Headposition)
	//	{
	//		tick = Tickcount;
	//		Head = Headposition;
	//	}
	//	int tick = -1;
	//	Vector Head;
	//};
	//std::vector<RecordTicks> tick[64];
	//void BacktrackStart(CUserCmd* cmd);
	//void BacktrackCalc(CUserCmd* cmd);

	void StartLegitbot(CUserCmd* cmd);

	C_BasePlayer* ClosestEnemyToCrosshair(QAngle Angle, bool Aimbot_VisibilityCheck, int Aimbot_Hitbox, float Aimbot_FOV);

	void Smoothing(QAngle& viewangle, QAngle& angle, float smoothValue);

	void AimAtEnemy(CUserCmd* cmd, bool Aimbot_Aimbot, bool Aimbot_AutoScope, bool Aimbot_AutoStop, bool Aimbot_AutoCrouch, int Aimbot_Hitbox, bool Aimbot_RecoilPrediction, float Aimbot_SmoothAmount, bool Aimbot_Silent, bool Aimbot_VisibilityCheck, float Aimbot_FOV);

	void Triggerbot(CUserCmd* cmd, bool TriggerBot_TriggerBot, int TriggerBot_Delay, int TriggerBot_HitBox, float TriggerBot_HitChance);
	QAngle calculateRelativeAngle(const Vector& source, const Vector& destination, const QAngle& viewAngles);
	float degreesToRadians(float degrees);
	float radiansToDegrees(float radians);
};

extern LegitBot legitbot;