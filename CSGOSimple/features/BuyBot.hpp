#pragma once
#include "../Includes.h"

class CBuyBot
{
public:
	bool RoundStarted = false;
	void Buy();
};

extern CBuyBot buybot;