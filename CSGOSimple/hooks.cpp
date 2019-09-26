#include "hooks.hpp"
#include <intrin.h>  

#include "render.hpp"
#include "menu.hpp"
#include "options.hpp"
#include "helpers/input.hpp"
#include "helpers/utils.hpp"
#include "features/bhop.hpp"
#include "features/chams.hpp"
#include "features/visuals.hpp"
#include "features/glow.hpp"
#include "features/Legitbot.h"
#include "features/AntiAim.hpp"
#include "SkinChanger.hpp"
#include "features/Ragebot.hpp"
#include "BackTrack.hpp"
#include "features/SpotMarkers.hpp"
#include "EventListeners.hpp"
#include "features/Hitmarker.hpp"
#include "features/LogEvents.hpp"

#pragma intrinsic(_ReturnAddress)  

namespace Hooks {

	void Initialize()
	{
		hlclient_hook.setup(g_CHLClient);
		direct3d_hook.setup(g_D3DDevice9);
		vguipanel_hook.setup(g_VGuiPanel);
		vguisurf_hook.setup(g_VGuiSurface);
		sound_hook.setup(g_EngineSound);
		mdlrender_hook.setup(g_MdlRender);
		clientmode_hook.setup(g_ClientMode);
		ConVar* sv_cheats_con = g_CVar->FindVar("sv_cheats");
		sv_cheats.setup(sv_cheats_con);
		gameEvent_hook.setup(g_GameEvents);

		direct3d_hook.hook_index(index::EndScene, hkEndScene);
		direct3d_hook.hook_index(index::Reset, hkReset);
		hlclient_hook.hook_index(index::FrameStageNotify, hkFrameStageNotify);
		hlclient_hook.hook_index(index::CreateMove, hkCreateMove_Proxy);
		vguipanel_hook.hook_index(index::PaintTraverse, hkPaintTraverse);
		sound_hook.hook_index(index::EmitSound1, hkEmitSound1);
		vguisurf_hook.hook_index(index::LockCursor, hkLockCursor);
		mdlrender_hook.hook_index(index::DrawModelExecute, hkDrawModelExecute);
		clientmode_hook.hook_index(index::DoPostScreenSpaceEffects, hkDoPostScreenEffects);
		clientmode_hook.hook_index(index::OverrideView, hkOverrideView);
		sv_cheats.hook_index(index::SvCheatsGetBool, hkSvCheatsGetBool);
		//gameEvent_hook.hook_index(index::FireEventClientSide, hkFireEventClientSide);
		RoundStart* g_RoundStart = new RoundStart;
		PlayerHurt* g_PlayerHurt = new PlayerHurt;
		//PlayerFootStep* g_PlayerFootStep = new PlayerFootStep;
		PlayerDeath* g_PlayerDeath = new PlayerDeath;
		BombPlanted* g_BombPlanted = new BombPlanted;
		BeginDefuse* g_BeginDefuse = new BeginDefuse;
		ItemPurchase* g_ItemPurchase = new ItemPurchase;
		BombBeginPlant* g_BombBeginPlant = new BombBeginPlant;
		BombAbortDefuse* g_BombAbortDefuse = new BombAbortDefuse;
		RoundEnd* g_RoundEnd = new RoundEnd;
		//StartVote* g_StartVote = new StartVote();
		//EnableRestartVote* g_EnableRestartVote = new EnableRestartVote();

		if (g_EngineClient->IsInGame() && g_EngineClient->IsConnected() && g_LocalPlayer && g_LocalPlayer->IsAlive())
			g_ClientState->ForceFullUpdate();

		hitmarker->initialize();
	}
	//--------------------------------------------------------------------------------
	void Shutdown()
	{
		hlclient_hook.unhook_all();
		direct3d_hook.unhook_all();
		vguipanel_hook.unhook_all();
		vguisurf_hook.unhook_all();
		mdlrender_hook.unhook_all();
		clientmode_hook.unhook_all();
		sound_hook.unhook_all();
		sv_cheats.unhook_all();
		gameEvent_hook.unhook_all();

		Glow::Get().Shutdown();
	}
	//--------------------------------------------------------------------------------
	long __stdcall hkEndScene(IDirect3DDevice9* pDevice)
	{
		static auto oEndScene = direct3d_hook.get_original<decltype(&hkEndScene)>(index::EndScene);

		static auto mat_ambient_light_r = g_CVar->FindVar("mat_ambient_light_r");
		static auto mat_ambient_light_g = g_CVar->FindVar("mat_ambient_light_g");
		static auto mat_ambient_light_b = g_CVar->FindVar("mat_ambient_light_b");
		static auto crosshair_cvar = g_CVar->FindVar("crosshair");

		mat_ambient_light_r->SetValue(g_Options.mat_ambient_light_r);
		mat_ambient_light_g->SetValue(g_Options.mat_ambient_light_g);
		mat_ambient_light_b->SetValue(g_Options.mat_ambient_light_b);
		
		crosshair_cvar->SetValue(!(g_Options.esp_enabled && g_Options.esp_crosshair));

		DWORD colorwrite, srgbwrite;
		IDirect3DVertexDeclaration9* vert_dec = nullptr;
		IDirect3DVertexShader9* vert_shader = nullptr;
		DWORD dwOld_D3DRS_COLORWRITEENABLE = NULL;
		pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwrite);
		pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &srgbwrite);

		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
		//removes the source engine color correction
		pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

		pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
		pDevice->GetVertexDeclaration(&vert_dec);
		pDevice->GetVertexShader(&vert_shader);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
		pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
		pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
		pDevice->SetSamplerState(NULL, D3DSAMP_SRGBTEXTURE, NULL);

		
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();


		auto esp_drawlist = Render::Get().RenderScene();

		Menu::Get().Render();
	

		ImGui::Render(esp_drawlist);

		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, colorwrite);
		pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, srgbwrite);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);
		pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, true);
		pDevice->SetVertexDeclaration(vert_dec);
		pDevice->SetVertexShader(vert_shader);

		return oEndScene(pDevice);
	}
	//--------------------------------------------------------------------------------
	long __stdcall hkReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
	{
		static auto oReset = direct3d_hook.get_original<decltype(&hkReset)>(index::Reset);

		Menu::Get().OnDeviceLost();

		auto hr = oReset(device, pPresentationParameters);

		if (hr >= 0)
			Menu::Get().OnDeviceReset();

		return hr;
	}
	//--------------------------------------------------------------------------------
	void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active, bool& bSendPacket)
	{
		static auto oCreateMove = hlclient_hook.get_original<decltype(&hkCreateMove_Proxy)>(index::CreateMove);

		oCreateMove(g_CHLClient, 0, sequence_number, input_sample_frametime, active);

		auto cmd = g_Input->GetUserCmd(sequence_number);
		auto verified = g_Input->GetVerifiedCmd(sequence_number);

		if (!g_EngineClient->IsInGame() && !g_EngineClient->IsConnected())
			return;

		if (!cmd || !cmd->command_number)
			return;

		MISC::EdgeJump(cmd);

		if (Menu::Get().IsVisible())
			cmd->buttons &= ~IN_ATTACK;

		ragebot.CreateMove(cmd, bSendPacket);

		ragebot.AA(cmd, bSendPacket, g_LocalPlayer);

		MISC::OnCreateMove(cmd);

		legitbot.StartLegitbot(cmd);

		MISC::NoFlash();

		MISC::Radar();

		MISC::FakePing();

		MISC::ClanTagChanger();

		MISC::UnlimitedDuck(cmd);

		BackTrack::Run(cmd);

		ragebot.FakeLag(cmd, bSendPacket);

		//antiaim.AA(cmd, bSendPacket);

		spotmarkers->WalkBot(cmd);

		buybot.Buy();

		verified->m_cmd = *cmd;
		verified->m_crc = cmd->GetChecksum();
	}
	//--------------------------------------------------------------------------------
	__declspec(naked) void __fastcall hkCreateMove_Proxy(void* _this, int, int sequence_number, float input_sample_frametime, bool active)
	{
		__asm
		{
			push ebp
			mov  ebp, esp
			push ebx; not sure if we need this
			push esp
			push dword ptr[active]
			push dword ptr[input_sample_frametime]
			push dword ptr[sequence_number]
			call Hooks::hkCreateMove
			pop  ebx
			pop  ebp
			retn 0Ch
		}
	}
	//--------------------------------------------------------------------------------
	void __fastcall hkPaintTraverse(void* _this, int edx, vgui::VPANEL panel, bool forceRepaint, bool allowForce)
	{
		static auto panelId = vgui::VPANEL{ 0 };
		static auto oPaintTraverse = vguipanel_hook.get_original<decltype(&hkPaintTraverse)>(index::PaintTraverse);
		if (g_Options.misc_RemoveScope)
			if (!strcmp("HudZoom", g_VGuiPanel->GetName(panel)))
				return;

		oPaintTraverse(g_VGuiPanel, edx, panel, forceRepaint, allowForce);

		if (!panelId) {
			const auto panelName = g_VGuiPanel->GetName(panel);
			if (!strcmp(panelName, "FocusOverlayPanel")) {
				panelId = panel;
			}
		}
		else if (panelId == panel) {
			//Ignore 50% cuz it called very often
			static bool bSkip = false;
			bSkip = !bSkip;

			if (bSkip)
				return;

			if (g_LocalPlayer && InputSys::Get().IsKeyDown(VK_TAB) && g_Options.misc_showranks)
				Utils::RankRevealAll();

			Render::Get().BeginScene();
		}
	}
	//--------------------------------------------------------------------------------
	void __fastcall hkEmitSound1(void* _this, int edx, IRecipientFilter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume,
		int nSeed, float flAttenuation, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, void* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, int unk) {
		static auto ofunc = sound_hook.get_original<decltype(&hkEmitSound1)>(index::EmitSound1);

		if (!strcmp(pSoundEntry, "UIPanorama.popup_accept_match_beep") && g_Options.misc_AutoAccept) {
			static auto fnAccept = reinterpret_cast<bool(__stdcall*)(const char*)>(Utils::PatternScan(GetModuleHandleA("client_panorama.dll"), "55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12"));

			if (fnAccept) {

				fnAccept("");

				//This will flash the CSGO window on the taskbar
				//so we know a game was found (you cant hear the beep sometimes cause it auto-accepts too fast)
				FLASHWINFO fi;
				fi.cbSize = sizeof(FLASHWINFO);
				fi.hwnd = InputSys::Get().GetMainWindow();
				fi.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
				fi.uCount = 0;
				fi.dwTimeout = 0;
				FlashWindowEx(&fi);
			}
		}

		ofunc(g_EngineSound, edx, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, nSeed, flAttenuation, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity, unk);

	}
	//--------------------------------------------------------------------------------
	int __fastcall hkDoPostScreenEffects(void* _this, int edx, int a1)
	{
		static auto oDoPostScreenEffects = clientmode_hook.get_original<decltype(&hkDoPostScreenEffects)>(index::DoPostScreenSpaceEffects);

		if (g_LocalPlayer && g_Options.glow_enabled)
			Glow::Get().Run();

		return oDoPostScreenEffects(g_ClientMode, edx, a1);
	}
	//--------------------------------------------------------------------------------
	void __fastcall hkFrameStageNotify(void* _this, int edx, ClientFrameStage_t stage)
	{
		static auto ofunc = hlclient_hook.get_original<decltype(&hkFrameStageNotify)>(index::FrameStageNotify);

		BackTrack::init();
		MISC::NightMode(stage);

		if (g_EngineClient->IsInGame())
			BackTrack::update(stage);

		skinchanger.SetSkin(stage);

		if (skinchanger.SetForceFullUpdate)
			skinchanger.ForceFullUpdate(stage);

		MISC::AsusWalls(stage);

		MISC::InverseRagdollGravity();

		MISC::DisablePostProccess();

		MISC::GrendaeTrajectory();

		ofunc(g_CHLClient, edx, stage);
	}
	//--------------------------------------------------------------------------------
	void __fastcall hkOverrideView(void* _this, int edx, CViewSetup* vsView)
	{
		static auto ofunc = clientmode_hook.get_original<decltype(&hkOverrideView)>(index::OverrideView);

		if (g_EngineClient->IsInGame() && vsView)
			Visuals::Get().ThirdPerson();

		MISC::Fov(vsView);

		MISC::SetSkyBox();

		ofunc(g_ClientMode, edx, vsView);
	}
	//--------------------------------------------------------------------------------
	void __fastcall hkLockCursor(void* _this)
	{
		static auto ofunc = vguisurf_hook.get_original<decltype(&hkLockCursor)>(index::LockCursor);

		if (Menu::Get().IsVisible()) {
			g_VGuiSurface->UnlockCursor(); 
			g_InputSystem->ResetInputState();
			return;
		}
		ofunc(g_VGuiSurface);

	}
	//--------------------------------------------------------------------------------
	void __fastcall hkDrawModelExecute(void* _this, int edx, IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
	{
		try {
			static auto ofunc = mdlrender_hook.get_original<decltype(&hkDrawModelExecute)>(index::DrawModelExecute);

			if (g_MdlRender->IsForcedMaterialOverride() &&
				!strstr(pInfo.pModel->szName, "arms") &&
				!strstr(pInfo.pModel->szName, "weapons/v_")) {
				return ofunc(_this, edx, ctx, state, pInfo, pCustomBoneToWorld);
			}

			Chams::Get().OnDrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

			MISC::NoFlash();
			MISC::NoSmoke();

			ofunc(_this, edx, ctx, state, pInfo, pCustomBoneToWorld);

			g_MdlRender->ForcedMaterialOverride(nullptr);
		}
		catch(std::exception&){}
	}

	bool __fastcall hkSvCheatsGetBool(PVOID pConVar, void* edx)
	{
		static auto dwCAM_Think = Utils::PatternScan(GetModuleHandleW(L"client_panorama.dll"), "85 C0 75 30 38 86");
		static auto ofunc = sv_cheats.get_original<bool(__thiscall *)(PVOID)>(index::SvCheatsGetBool);
		if (!ofunc)
			return false;

		if (reinterpret_cast<DWORD>(_ReturnAddress()) == reinterpret_cast<DWORD>(dwCAM_Think))
			return true;
		return ofunc(pConVar);
	}

	//bool __fastcall hkFireEventClientSide(void* thisptr, void* edx, IGameEvent* gameevent)
	//{
	//	static auto ofunc = gameEvent_hook.get_original<bool(__thiscall*)(void*, IGameEvent*)>(index::FireEventClientSide);

	//	if (gameevent) {
	//		if (!strcmp(gameevent->GetName(), "round_start")) {
	//			spotmarkers->marker = 0; //Set walkbot to start again
	//			g_EngineClient->ClientCmd_Unrestricted("buy deagle;"); //For testing
	//		}
	//	}

	//	return ofunc(thisptr, gameevent);
	//}
}
