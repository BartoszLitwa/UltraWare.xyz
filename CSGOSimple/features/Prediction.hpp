#pragma once
#include "..//options.hpp"
#include "../valve_sdk/csgostructs.hpp"
#include "..//valve_sdk/sdk.hpp"
#include "..//Includes.h"

namespace PredictionSystem
{
	void StartPrediction_e();
	void EndPrediction_e(C_BasePlayer* p_ent);

	void StartPrediction(CUserCmd* cmd);
	void EndPrediction();
};