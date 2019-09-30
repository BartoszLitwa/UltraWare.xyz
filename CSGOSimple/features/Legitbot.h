#pragma once
#include "../Includes.h"
#include "../render.hpp"
#include "Autowall.hpp"

class LegitBot
{
public:
	void StartLegitbot(CUserCmd* cmd);

	C_BasePlayer* ClosestEnemyToCrosshair(QAngle Angle, float& BDelta, bool Aimbot_VisibilityCheck, int Aimbot_Hitbox);

	void Smoothing(QAngle& viewangle, QAngle& angle, float smoothValue);

	void AimAtEnemy(CUserCmd* cmd, bool Aimbot_Aimbot, bool Aimbot_AutoScope, bool Aimbot_AutoStop, bool Aimbot_AutoCrouch, int Aimbot_Hitbox, bool Aimbot_RecoilPrediction, float Aimbot_SmoothAmount, bool Aimbot_Silent, bool Aimbot_VisibilityCheck, float Aimbot_FOV, float Aimbot_SilentFOV);

	void Triggerbot(CUserCmd* cmd, bool TriggerBot_TriggerBot, int TriggerBot_Delay, int TriggerBot_HitBox, float TriggerBot_HitChance);
	void RenderFOV(float width, float height, bool Aimbot, bool ShowFov, float Aimbot_FOV, float Silent_FOV);
	void Render(float width, float height);
	QAngle calculateRelativeAngle(const Vector& source, const Vector& destination, const QAngle& viewAngles);
	float degreesToRadians(float degrees);
	float radiansToDegrees(float radians);
};

extern LegitBot legitbot;