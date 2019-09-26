#pragma once
#include "../Includes.h"

class AntiAim
{
public:
	void AA(CUserCmd* cmd, bool& SendPacket);

	void AntiAimYaw(CUserCmd* cmd, bool& bSendPacket);

	bool LBYUpdate();

	bool LBYBreaker(CUserCmd* cmd);

	void fixMoveStart(CUserCmd* cmd);

	void fixMoveEnd(CUserCmd* cmd);

	int LegitAASide = 1;
};

extern AntiAim antiaim;