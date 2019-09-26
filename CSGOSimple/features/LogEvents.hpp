#pragma once
#include "../Includes.h"
#include <deque>

class CLogEvents
{
public:
	struct LogInfo
	{
		std::string text;
		float time;
		Color color;
	};

	struct StepsInfo
	{
		Vector pos;
		float time;
		C_BasePlayer* player;
		Color color;
	};

	std::deque<LogInfo> Logs;
	std::deque<StepsInfo> Steps;
	void Draw(int w, int h);
	void DrawSteps(int w, int h);
	void Player_FootSteps(IGameEvent* event);
	void Player_hurt(IGameEvent* event);
	void Player_death(IGameEvent* event);
	void Item_Purchase(IGameEvent* event);
	void Bomb_planted(IGameEvent* event);
	void Bomb_begindefuse(IGameEvent* event);
	void Bomb_abortdefuse(IGameEvent* event);
	void Bomb_beginplant(IGameEvent* event);
	C_BasePlayer* get_player(int userid);
};

extern CLogEvents logevents;