#include "BackTrack.hpp"
#include "Ragebot.hpp"
#include "..//g_Variables.hpp"

std::deque<BackTrack::Record> BackTrack::records[65];
BackTrack::Cvars BackTrack::cvars;

void BackTrack::update(ClientFrameStage_t stage)
{
	C_BasePlayer* local = (C_BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());
	if (!local || !g_Options.BackTrack_BackTrack || !local->IsAlive() || !g_EngineClient->IsInGame() || !g_EngineClient->IsConnected()) {
		for (auto& record : records)
			record.clear();
		return;
	}

	if (stage == FRAME_RENDER_START) {
		if (g_Options.DeSync) {
			QAngle SetAngles = ragebot.AngleToDrawonScreen;
			SetAngles.pitch = 0;
			SetAngles.roll = 0;
			local->SetAbsAngles(SetAngles);
			local->InvalidateBoneCache();
			local->SetupBones(ragebot.LocalPlayerMatrix, 128, 0x7FF00, g_GlobalVars->curtime);
		}

		for (int i = 1; i <= g_EngineClient->GetMaxClients(); i++) {
			C_BasePlayer* entity = (C_BasePlayer*)g_EntityList->GetClientEntity(i);
			if (!entity || entity == local || entity->IsDormant() || !entity->IsAlive() || entity->m_iTeamNum() == local->m_iTeamNum() || entity->m_bGunGameImmunity()) {
				records[i].clear(); //Thats the problem with dme backtrack chams
				continue;
			}

			if (!records[i].empty() && (records[i].front().simulationTime == entity->m_flSimulationTime()))
				continue;

			Record record{};
			record.player = entity;
			record.origin = entity->GetAbsOrigin();
			record.simulationTime = entity->m_flSimulationTime();
			entity->InvalidateBoneCache();
			entity->SetupBones(record.matrix, 128, 0x7FF00, g_GlobalVars->curtime);
			record.isVisible = local->CanSeePlayer(entity, entity->GetHitboxPos(HITBOX_CHEST));
			if ((g_Options.AutoWall_AutoWall_Pistols || g_Options.AutoWall_AutoWall_Rifles || g_Options.AutoWall_AutoWall_SMG || g_Options.AutoWall_AutoWall_ShotGuns || g_Options.AutoWall_AutoWall_AWP || g_Options.AutoWall_AutoWall_SSG08 || g_Options.AutoWall_AutoWall_Autos)
				&& (g_Options.AutoWall_BackTrack_Pistols || g_Options.AutoWall_BackTrack_Rifles || g_Options.AutoWall_BackTrack_SMG || g_Options.AutoWall_BackTrack_ShotGuns || g_Options.AutoWall_BackTrack_AWP || g_Options.AutoWall_BackTrack_SSG08 || g_Options.AutoWall_BackTrack_Autos)) {
				float bestDamage = 0;
				int bestHitbox = 0;
				for (int i = 0; i < 19; i++) {
					float TempDamage = Autowall::GetDamage(entity->GetHitboxPos(i));
					if (TempDamage > bestDamage) {
						bestDamage = TempDamage;
						bestHitbox = i;
					}
				}
				record.BestDamageAW = bestDamage;
				record.BestHitboxAW = bestHitbox;
			}

			records[i].push_front(record);

			while (records[i].size() > 3 && records[i].size() > static_cast<int>(timeToTicks((float)(g_Options.BackTrack_Ticks / 1000.f))))
				records[i].pop_back(); //Removes Last record

			//https://stackoverflow.com/questions/12001410/what-is-the-reason-behind-cbegin-cend
			if (auto invalid = std::find_if(std::cbegin(records[i]), std::cend(records[i]), [](const Record& rec) {return !valid(rec.simulationTime); }); invalid != std::cend(records[i]))
				records[i].erase(invalid, std::cend(records[i])); //Removes invalid record at invalid record
		}
	}
}

void BackTrack::Run(CUserCmd* cmd)
{
	if (!g_Options.BackTrack_BackTrack)
		return;

	if (!(cmd->buttons & IN_ATTACK))
		return;

	C_BasePlayer* local = (C_BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());
	if (!local && !local->IsAlive())
		return;

	QAngle Viewangle; g_EngineClient->GetViewAngles(&Viewangle);

	auto localPlayerEyePos = local->GetEyePos();

	auto bestFov{ 255.f };
	C_BasePlayer* BestEntity = nullptr;
	int BestEntityindex;
	Vector BestTargetOrigin;
	int BestRecord{};

	static auto weaponRecoilScale = g_CVar->FindVar("weapon_recoil_scale");
	const auto aimPunch = local->m_aimPunchAngle() * weaponRecoilScale->GetFloat();

	for (int i = 1; i <= g_EngineClient->GetMaxClients(); i++) {
		C_BasePlayer* entity = (C_BasePlayer*)g_EntityList->GetClientEntity(i);
		if (!entity || entity == local || entity->IsDormant() || !entity->IsAlive() || entity->m_iTeamNum() == local->m_iTeamNum())
			continue;

		auto origin = entity->GetAbsOrigin();
		auto angle = calculateRelativeAngle(localPlayerEyePos, origin, cmd->viewangles + (g_Options.BackTrack_BackTrack ? aimPunch : QAngle{}));
		auto fov = std::hypotf(angle.yaw, angle.pitch); //http://www.cplusplus.com/reference/cmath/hypot/ calculate 3rd side of triangle
		if (fov < bestFov) {
			bestFov = fov;
			BestEntity = entity;
			BestEntityindex = i;
			BestTargetOrigin = origin;
		}
	}

	if (BestEntity) {
		if (records[BestEntityindex].size() <= 3 /*|| (!g_Options.BackTrack_ignoreSmoke && Utils::lineGoesThroughSmoke(local->GetEyePos(), BestTargetOrigin, 1))*/)
			return;

		bestFov = 255.f;
		for (size_t i = 0; i < records[BestEntityindex].size(); i++) {
			auto& record = records[BestEntityindex][i];
			if (!valid(record.simulationTime))
				continue;

			auto angle = calculateRelativeAngle(localPlayerEyePos, record.origin, cmd->viewangles + (g_Options.BackTrack_BackTrack ? aimPunch : QAngle{}));
			auto fov = std::hypotf(angle.yaw, angle.pitch);
			if (fov < bestFov) {
				bestFov = fov;
				BestRecord = i;
			}
		}
	}

	if (BestRecord) {
		auto record = records[BestEntityindex][BestRecord];
		BestEntity->SetAbsOrigin(record.origin);
		cmd->tick_count = timeToTicks(record.simulationTime + getLerp());
	}
}

QAngle BackTrack::calculateRelativeAngle(const Vector& source, const Vector& destination, const QAngle& viewAngles)
{
	Vector delta = destination - source;
	QAngle angles{ radiansToDegrees(atan2f(-delta.z, std::hypotf(delta.x, delta.y))) - viewAngles.pitch,
				   radiansToDegrees(atan2f(delta.y, delta.x)) - viewAngles.yaw, 0.f };
	angles.Clamp();
	return angles;
}

float BackTrack::degreesToRadians(float degrees)
{
	return degrees * static_cast<float>(M_PI) / 180.0f;
}
float BackTrack::radiansToDegrees(float radians)
{
	return radians * 180.0f / static_cast<float>(M_PI);
}

