#pragma once
#include "../Includes.h"

struct impact_info 
{
	float x, y, z;
	long long time; //timestamps in ms thats why long long coz it will be big
};

struct hitmarker_info
{
	impact_info impact;
	int alpha;
};

class CHitmarker : IGameEventListener2
{
public:
	void initialize();
	void paint(int w2, int h2);
	void player_hurt(IGameEvent* event);
private:
	void FireGameEvent(IGameEvent* event) override;
	int GetEventDebugID(void) override;
	void bullet_impact(IGameEvent* event);
	C_BasePlayer* get_player(int userid);
	std::vector<impact_info> impacts;
	std::vector<hitmarker_info> hitmarkers;
};

extern CHitmarker* hitmarker;
