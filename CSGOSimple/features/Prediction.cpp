#include "Prediction.hpp"

float m_flOldCurtime;
float m_flOldFrametime;

float oldGetEyeAngles;
void PredictionSystem::StartPrediction_e()
{
	for (int i = 0; i < g_EngineClient->GetMaxClients(); i++)
	{
		C_BasePlayer* p_ent = (C_BasePlayer*)g_EntityList->GetClientEntity(i);

		C_BasePlayer* localplayer = (C_BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());
		if (!localplayer || !localplayer->IsAlive())
			continue;

		if (!p_ent
			|| p_ent->IsDormant()
			|| !p_ent->IsAlive()
			|| p_ent->m_bGunGameImmunity()
			|| localplayer == p_ent)
			continue;

		CCSGOPlayerAnimState* animState = p_ent->GetPlayerAnimState();
		if (!animState)
			continue;

		m_flOldCurtime = g_GlobalVars->curtime;
		m_flOldFrametime = g_GlobalVars->frametime;

		oldGetEyeAngles = p_ent->m_angEyeAngles().yaw;

		p_ent->UpdateClientSideAnimation();

		g_GlobalVars->curtime = p_ent->m_nTickBase() * g_GlobalVars->interval_per_tick;
		g_GlobalVars->frametime = g_GlobalVars->interval_per_tick;

		//float delta = std::abs(animState - animState->goalFeetYaw);
		//float m_flMaxBodyYaw = maxDelta;
		//float m_flMinBodyYaw = -maxDelta;
		//float ResolvedYaw = animState->yaw;
		//if (m_flMaxBodyYaw < delta)
		/*{
			ResolvedYaw = p_ent->GetEyeAngles()->y - m_flMaxBodyYaw;

		}
		else if (m_flMinBodyYaw > delta)
		{
			ResolvedYaw = p_ent->GetEyeAngles()->y + m_flMinBodyYaw;

		}

		p_ent->GetEyeAngles()->y = ResolvedYaw;*/

		g_GameMovement->StartTrackPredictionErrors(p_ent);
		//g_GameMovement->ProcessMovement(localplayer, CMoveData);

		EndPrediction_e(p_ent);
	}


}

void PredictionSystem::EndPrediction_e(C_BasePlayer* p_ent)
{

	//p_ent->UpdateClientSideAnimation();

	g_GameMovement->FinishTrackPredictionErrors(p_ent);

	p_ent->m_angEyeAngles().yaw = oldGetEyeAngles;

	g_GlobalVars->curtime = m_flOldCurtime;
	g_GlobalVars->frametime = m_flOldFrametime;

}
void PredictionSystem::StartPrediction(CUserCmd* cmd)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());

	//nPredictionRandomSeed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;

	m_flOldCurtime = g_GlobalVars->curtime;
	m_flOldFrametime = g_GlobalVars->frametime;

	g_GlobalVars->curtime = localplayer->m_nTickBase() * g_GlobalVars->interval_per_tick;
	g_GlobalVars->frametime = g_GlobalVars->interval_per_tick;

	g_GameMovement->StartTrackPredictionErrors(localplayer);

	g_MoveHelper->SetHost(localplayer);
	//g_Prediction->SetupMove(localplayer, cmd, g_MoveHelper, g_MoveData);
	//g_GameMovement->ProcessMovement(localplayer, g_MoveData);
	//g_Prediction->FinishMove(localplayer, cmd, g_MoveData);
}

void PredictionSystem::EndPrediction()
{
	C_BasePlayer* localplayer = (C_BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());

	g_GameMovement->FinishTrackPredictionErrors(localplayer);
	g_MoveHelper->SetHost(0);

	//nPredictionRandomSeed = -1;

	g_GlobalVars->curtime = m_flOldCurtime;
	g_GlobalVars->frametime = m_flOldFrametime;
}