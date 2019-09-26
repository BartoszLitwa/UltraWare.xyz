#pragma once
#include <deque>

class C_BasePlayer;
class CUserCmd;
class CViewSetup;
enum ClientFrameStage_t;

namespace MISC
{
    void OnCreateMove(CUserCmd* cmd);
	void AsusWalls(ClientFrameStage_t stage);
	void PrePredictionCreateMove(CUserCmd* cmd);
	void PostPredictionCreateMove(CUserCmd* cmd);
	void EdgeJump(CUserCmd* cmd);
	void GrendaeTrajectory();
	void FakeCommends();
	void ClanTagChanger();
	void NoFlash();
	void NoSmoke();
	void DisablePostProccess();
	void UnlimitedDuck(CUserCmd* cmd);
	void InverseRagdollGravity();
	void SpectatorList(int width, int height);
	void Radar();
	void Fov(CViewSetup* vsView);
	void FakePing();
	void SetSkyBox();
	void NightMode(ClientFrameStage_t stage);
}