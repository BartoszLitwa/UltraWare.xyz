#include "bhop.hpp"
#include "..//options.hpp"
#include "../valve_sdk/csgostructs.hpp"
#include "..//render.hpp"
#include <string>

int static flags_backup = 257;

void MISC::OnCreateMove(CUserCmd* cmd)
{
	if (!g_Options.misc_bhop)
		return;

  static bool jumped_last_tick = false;
  static bool should_fake_jump = false;

  if(!jumped_last_tick && should_fake_jump) {
    should_fake_jump = false;
    cmd->buttons |= IN_JUMP;
  } else if(cmd->buttons & IN_JUMP) {
    if(g_LocalPlayer->m_fFlags() & FL_ONGROUND) {
      jumped_last_tick = true;
      should_fake_jump = true;
    } else {
      cmd->buttons &= ~IN_JUMP;
      jumped_last_tick = false;
    }
  } else {
    jumped_last_tick = false;
    should_fake_jump = false;
  }

  if (g_Options.misc_AutoStrafe) {
	  if (g_LocalPlayer->m_fFlags() & FL_ONGROUND)
		  return;

	  if (cmd->mousedx > 1 || cmd->mousedx < -1)
		  cmd->sidemove = cmd->mousedx > 0.f ? 400.f : -400.f;
  }
}

std::unordered_map<MaterialHandle_t, Color> worldMaterials;
std::unordered_map<MaterialHandle_t, Color> worldMaterials2;
Color WallsColor = Color(1.f, 1.f, 1.f, 0.5f);
float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;

void MISC::AsusWalls(ClientFrameStage_t stage)
{
	static bool AsusSet = false;
	static float oldalpha;
	static int oldtype;

	if (!g_EngineClient->IsInGame() || !g_EngineClient->IsConnected() || !g_LocalPlayer)
		return;

	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END)
		return;

	if (oldalpha != g_Options.misc_AsusWallsAlpha || oldtype != g_Options.misc_AsusWallsInt)
		AsusSet = false;

	static auto DrawStaticProps = g_CVar->FindVar("r_DrawSpecificStaticProp");
	DrawStaticProps->SetValue(1);

	if (g_Options.misc_AsusWalls && !AsusSet) {
		for (MaterialHandle_t i = g_MatSystem->FirstMaterial(); i != g_MatSystem->InvalidMaterial(); i = g_MatSystem->NextMaterial(i)) {
			IMaterial* mat = g_MatSystem->GetMaterial(i);
			if (!mat || mat == nullptr)
				continue;

			if(g_Options.misc_AsusWallsInt == 0)
				if (strstr(mat->GetTextureGroupName(), "World"))
					mat->AlphaModulate(g_Options.misc_AsusWallsAlpha);

			if (g_Options.misc_AsusWallsInt == 1) {
				if (strstr(mat->GetTextureGroupName(), "StaticProp textures")) {
					mat->AlphaModulate(g_Options.misc_AsusWallsAlpha);
				}
				if (strstr(mat->GetName(), "crate")) {
					mat->AlphaModulate(g_Options.misc_AsusWallsAlpha);
				}
				if (strstr(mat->GetName(), "box")) {
					mat->AlphaModulate(g_Options.misc_AsusWallsAlpha);
				}
				if (strstr(mat->GetName(), "door")) {
					mat->AlphaModulate(g_Options.misc_AsusWallsAlpha);
				}
			}

			if (g_Options.misc_AsusWallsInt == 2) {
				if (strstr(mat->GetTextureGroupName(), "World")) {
					mat->AlphaModulate(g_Options.misc_AsusWallsAlpha);
				}
				if (strstr(mat->GetTextureGroupName(), "StaticProp textures")) {
					mat->AlphaModulate(g_Options.misc_AsusWallsAlpha);
				}
				if (strstr(mat->GetName(), "crate")) {
					mat->AlphaModulate(g_Options.misc_AsusWallsAlpha);
				}
				if (strstr(mat->GetName(), "box")) {
					mat->AlphaModulate(g_Options.misc_AsusWallsAlpha);
				}
				if (strstr(mat->GetName(), "door")) {
					mat->AlphaModulate(g_Options.misc_AsusWallsAlpha);
				}
			}
		}
		AsusSet = true;
	}
	else if (!g_Options.misc_AsusWalls && AsusSet) {
		for (MaterialHandle_t i = g_MatSystem->FirstMaterial(); i != g_MatSystem->InvalidMaterial(); i = g_MatSystem->NextMaterial(i)) {
			IMaterial* mat = g_MatSystem->GetMaterial(i);
			if (!mat || mat == nullptr)
				continue;

			if (strstr(mat->GetTextureGroupName(), "World")) {
				mat->AlphaModulate(1.f);
			}
			if (strstr(mat->GetTextureGroupName(), "StaticProp textures")) {
				mat->AlphaModulate(1.f);
			}
			if (strstr(mat->GetName(), "crate")) {
				mat->AlphaModulate(1.f);
			}
			if (strstr(mat->GetName(), "box")) {
				mat->AlphaModulate(1.f);
			}
			if (strstr(mat->GetName(), "door")) {
				mat->AlphaModulate(1.f);
			}
		}
		AsusSet = false;
	} 

	oldalpha = g_Options.misc_AsusWallsAlpha;
	oldtype = g_Options.misc_AsusWallsInt;
}

void MISC::EdgeJump(CUserCmd* cmd)
{
	if (!g_Options.misc_edgejump)
		return;

	C_BasePlayer* local = (C_BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());
	if (!local || local->m_nMoveType() == MOVETYPE_LADDER || local->m_nMoveType() == MOVETYPE_NOCLIP)
		return;

	Vector Start, End;
	Start = local->GetAbsOrigin();
	End = Start;

	End.z -= 64;
	Ray_t ray;
	ray.Init(Start, End);
	trace_t trace;
	CTraceFilter filter;
	filter.pSkip = local;

	g_EngineTrace->TraceRay(ray, MASK_PLAYERSOLID_BRUSHONLY, &filter, &trace);
	if(trace.fraction == 1.f)
		cmd->buttons |= IN_JUMP;
}

void MISC::GrendaeTrajectory() {
	static auto grenade = g_CVar->FindVar("cl_grenadepreview");
	if(g_Options.misc_grenadeTrajectory && grenade->GetInt() == 0)
		grenade->SetValue(1);
	if (!g_Options.misc_grenadeTrajectory && grenade->GetInt() == 1)
		grenade->SetValue(0);
}

void MISC::FakeCommends() {
	if (!g_LocalPlayer || !g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
		return;

	player_info_s localinfo;
	if (!g_EngineClient->GetPlayerInfo(g_EngineClient->GetLocalPlayer(), &localinfo))
		return;

	static auto name = g_CVar->FindVar("name");
	char* oldname = (char*)name->GetString();
	std::string Invisible = " \n\xAD\xAD\xAD ";
	Utils::SetName(Invisible.c_str());
	char* Fake = localinfo.szName;
	//Utils::SetName(Fake.c_str()); //Set the name to invisible
	Utils::SetName(u8" \x01""\x0B""\x07"" CRNYY \"0x01"" has been permanently banned from official CS:GO servers. ""\x01");
}

void MISC::ClanTagChanger() {
	if (!g_Options.misc_ClanTag || !g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
		return;

	std::string Clan;
	static float nextchange;
	static int faze = 0;
	switch (g_Options.misc_ClanTagClan)
	{
	case 0:
		if (nextchange == 0 || nextchange < g_GlobalVars->curtime) {
			switch (faze)
			{
			case 0:
				Clan = "UltraWare.xyz";
				break;
			case 1:
				Clan = "ltraWare.xyz ";
				break;
			case 2:
				Clan = "traWare.xyz  ";
				break;
			case 3:
				Clan = "raWare.xyz   ";
				break;
			case 4:
				Clan = "aWare.xyz    ";
				break;
			case 5:
				Clan = "Ware.xyz    U";
				break;
			case 6:
				Clan = "are.xyz    Ul";
				break;
			case 7:
				Clan = "re.xyz    Ult";
				break;
			case 8:
				Clan = "e.xyz    Ultr";
				break;
			case 9:
				Clan = ".xyz    Ultra";
				break;
			case 10:
				Clan = "xyz    UltraW";
				break;
			case 11:
				Clan = "yz    UltraWa";
				break;
			case 12:
				Clan = "z    UltraWar";
				break;
			case 13:
				Clan = "    UltraWare";
				break;
			case 14:
				Clan = "   UltraWare.";
				break;
			case 15:
				Clan = "  UltraWare.x";
				break;
			case 16:
				Clan = " UltraWare.xy";
				break;
			case 17:
				Clan = "UltraWare.xyz";
				break;
			default:
				break;
			}
			if (faze == 17)
				faze = 0;
			else
				faze++;

			nextchange = g_GlobalVars->curtime + 0.5;

			Utils::SetClantag(Clan.c_str());
		}
		break;
	case 1:
		Utils::SetClantag(g_Options.misc_ClanTagName.c_str());
		break;
	}
	
}

std::vector<const char*> flashbang_materials = {
	"effects\\flashbang",
	"effects\\flashbang_white",
};
void MISC::NoFlash()
{
	static bool noflash = false;
	if (g_Options.misc_NoFlash && !noflash) {
		for (auto mat : flashbang_materials) {
			g_MatSystem->FindMaterial(mat, TEXTURE_GROUP_CLIENT_EFFECTS)->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
		}
		noflash = true;
	}
	else if (!g_Options.misc_NoFlash && noflash) {
		for (auto mat : flashbang_materials) {
			g_MatSystem->FindMaterial(mat, TEXTURE_GROUP_CLIENT_EFFECTS)->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
		}
		noflash = false;
	}
}

std::vector<const char*> smoke_materials = {
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
	"particle/vistasmokev1/vistasmokev1_fire",
};
void MISC::NoSmoke()
{
	static bool nosmoke = false;
	if (g_Options.misc_NoSmoke && !nosmoke) {
		for (auto mat : smoke_materials) {
			g_MatSystem->FindMaterial(mat, TEXTURE_GROUP_CLIENT_EFFECTS)->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
		}
		nosmoke = true;
	}
	else if (!g_Options.misc_NoSmoke && nosmoke) {
		for (auto mat : smoke_materials) {
			g_MatSystem->FindMaterial(mat, TEXTURE_GROUP_CLIENT_EFFECTS)->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
		}
		nosmoke = false;
	}
}

void MISC::DisablePostProccess() 
{
	
	auto postprocess = g_CVar->FindVar("mat_postprocess_enable");
	if (g_Options.misc_DisablePostProcess && postprocess->GetInt() != 0)
		postprocess->SetValue(0);
	else if(!g_Options.misc_DisablePostProcess && postprocess->GetInt() != 1)
		postprocess->SetValue(1);
}

void MISC::UnlimitedDuck(CUserCmd* cmd)
{
	if (g_Options.misc_UnlimitedDuck)
		cmd->buttons |= IN_BULLRUSH;
}

void MISC::InverseRagdollGravity()
{
	static auto ragdoll = g_CVar->FindVar("cl_ragdoll_gravity");
	ragdoll->SetValue(g_Options.misc_InverseRagdollGravity ? -600 : 600);
}

void MISC::SpectatorList(int width, int height)
{
	if (!g_Options.misc_spectatorsList || !g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
		return;

	C_BasePlayer* local = (C_BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());
	if (!local)
		return;

	player_info_t localinfo;
	if (!g_EngineClient->GetPlayerInfo(g_EngineClient->GetLocalPlayer(), &localinfo))
		return;

	static int Namepos = 0;
	static int oldNamepos;
	Render::Get().RenderBoxFilled(width - 250, 220, width - 5, 250 + oldNamepos * 20 + 5, g_Options.misc_spectatorsList_color);
	Render::Get().RenderText("Spectator List", ImVec2(width - 130, 225), 25, Color::White, true, true, g_pDefaultFont);
	for (int i = 1; i < g_EngineClient->GetMaxClients(); i++) {
		C_BasePlayer* entity = (C_BasePlayer*)g_EntityList->GetClientEntity(i);
		if (!entity || entity->IsAlive() || entity->IsDormant()) { 
			continue;
		}

		player_info_t entinfo;
		if (g_EngineClient->GetPlayerInfo(i, &entinfo)) {
			if (strstr(entinfo.szName,"GOTV"))
				continue;

			C_BasePlayer* obs = (C_BasePlayer*)g_EntityList->GetClientEntityFromHandle(entity->m_hObserverTarget());
			if (!obs)
				continue;

			if (g_Options.misc_spectatorsListOnlyMe) {
				std::string text;
				if (obs != local || !local->IsAlive())
					continue;

				text = static_cast<std::string>("You") + " <- " + entinfo.szName;
				Render::Get().RenderText( text, ImVec2(width - 125, 250 + Namepos * 20), 18.f, Color::Green, true, true, g_pDefaultFont);
				Namepos++;
			}
			else {
				std::string text;
				player_info_t obsinfo;
				if (!g_EngineClient->GetPlayerInfo(obs->EntIndex(), &obsinfo))
					return;
				std::string Name = obs == local ? "You" : obsinfo.szName;
				text = Name + " <- " + static_cast<std::string>(entinfo.szName);
				if(obs == local)
					Render::Get().RenderText(text, ImVec2(width - 125, 250 + Namepos * 20), 18.f, Color::Green, true, true, g_pDefaultFont);
				else
					Render::Get().RenderText(text, ImVec2(width - 125, 250 + Namepos * 20), 18.f, Color::White, true, true, g_pDefaultFont);
				Namepos++;
			}
		}
	}
	oldNamepos = Namepos;
	Namepos = 0;
}

void MISC::Radar()
{
	for (size_t i = 1; i <= g_EngineClient->GetMaxClients(); i++) {
		C_BasePlayer* Ent = (C_BasePlayer*)g_EntityList->GetClientEntity(i);
		if (Ent && !Ent->IsDormant() && Ent->IsAlive() && Ent->m_iTeamNum() != g_LocalPlayer->m_iTeamNum()) {
			if (g_Options.misc_Radar)
				Ent->m_bSpotted() = true;
			else 
				Ent->m_bSpotted() = false;
		}
	}
}

static bool FovSet;
static int OldValue;
static bool FovSetView;
static int OldValueView;
void MISC::Fov(CViewSetup* vsView)
{
	static auto viemodelfov = g_CVar->FindVar("viewmodel_fov");
	viemodelfov->m_fnChangeCallbacks.m_Size = 0;
	if (g_EngineClient->IsInGame() && g_EngineClient->IsConnected() && g_LocalPlayer && g_LocalPlayer->IsAlive()) {
		if (!FovSetView) {
			if (g_Options.viewmodel_fov != 68)
				viemodelfov->SetValue(g_Options.viewmodel_fov);
			else
				viemodelfov->SetValue(68);
		}

		if (OldValueView != g_Options.viewmodel_fov) {
			FovSetView = false;
		}
		OldValueView = g_Options.viewmodel_fov;

		if (g_LocalPlayer->m_bIsScoped())
			return;

		else if (!FovSet && !g_LocalPlayer->m_bIsScoped()) {
			if (g_Options.misc_Fov != 90) {
				vsView->fov = g_Options.misc_Fov;
			}
			else {
				vsView->fov = 90;
			}
		}

		if (OldValue != g_Options.misc_Fov) {
			FovSet = false;
		}
		OldValue = g_Options.misc_Fov;
	}
}

void MISC::FakePing()
{
	static auto FakeLag = g_CVar->FindVar("net_fakelag");
	if (g_Options.misc_FakePing && g_Options.misc_FakePingAmount > 0 || g_Options.BackTrack_Ticks > 12) {
		INetChannelInfo* info = g_EngineClient->GetNetChannelInfo();
		int FinalFakePing;

		int Latency = info->GetLatency(FLOW_OUTGOING);
		if (g_Options.BackTrack_Ticks > 12 && !g_Options.misc_FakePingIgnoreBacktrack) {
			FinalFakePing = ((g_Options.BackTrack_Ticks - 12) * 16.66) - Latency;
			g_Options.misc_FakePingAmount = FinalFakePing;
			FinalFakePing = FinalFakePing / 2 + 40;
			g_Options.misc_FakePing = true;
		}
		else 
			FinalFakePing = (g_Options.misc_FakePingAmount - info->GetLatency(FLOW_OUTGOING)) / 2;

			FakeLag->SetValue(FinalFakePing);
	}
	else
		FakeLag->SetValue(0);
}

static int OldSky;
void MISC::SetSkyBox()
{
	static auto sv_skyname = g_CVar->FindVar("sv_skyname");
	if (OldSky != g_Options.misc_SkyBox) {
		switch (g_Options.misc_SkyBox)
		{
		case 0:
			sv_skyname->SetValue("cs_baggage_skybox_");
			break;
		case 1:
			sv_skyname->SetValue("cs_tibet");
			break;
		case 2:
			sv_skyname->SetValue("embassy");
			break;
		case 3:
			sv_skyname->SetValue("italy");
			break;
		case 4:
			sv_skyname->SetValue("jungle");
			break;
		case 5:
			sv_skyname->SetValue("office");
			break;
		case 6:
			sv_skyname->SetValue("sky_cs15_daylight01_hdr");
			break;
		case 7:
			sv_skyname->SetValue("sky_cs15_daylight02_hdr");
			break;
		case 8:
			sv_skyname->SetValue("sky_day02_05");
			break;
		case 9:
			sv_skyname->SetValue("nukeblank");
			break;
		case 10:
			sv_skyname->SetValue("dustblank");
			break;
		case 11:
			sv_skyname->SetValue("sky_venice");
			break;
		case 12:
			sv_skyname->SetValue("sky_cs15_daylight03_hdr");
			break;
		case 13:
			sv_skyname->SetValue("sky_cs15_daylight04_hdr");
			break;
		case 14:
			sv_skyname->SetValue("sky_csgo_cloudy01");
			break;
		case 15:
			sv_skyname->SetValue("sky_csgo_night02");
			break;
		case 16:
			sv_skyname->SetValue("sky_csgo_night02b");
			break;
		case 17:
			sv_skyname->SetValue("vertigo");
			break;
		case 18:
			sv_skyname->SetValue("vertigoblue_hdr");
			break;
		case 19:
			sv_skyname->SetValue("sky_dust");
			break;
		case 20:
			sv_skyname->SetValue("vietnam");
			break;
		default:
			break;
		}
		OldSky = g_Options.misc_SkyBox;
	}
}

void MISC::NightMode(ClientFrameStage_t stage)
{
	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END || !g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
		return;

	static auto sv_skyname = g_CVar->FindVar("sv_skyname");
	static bool SetSkybox = false;
	static std::string OldSkyBox;
	static auto mat_force_tonemap_scale = g_CVar->FindVar("mat_force_tonemap_scale");
	if (g_Options.misc_NightMode) {
		if (mat_force_tonemap_scale->GetFloat() != 0.2f)
			mat_force_tonemap_scale->SetValue("0.2");

		if (!SetSkybox) {
			OldSkyBox = sv_skyname->GetString();
			sv_skyname->SetValue("sky_csgo_night02b");
			SetSkybox = true;
		}
	}
	else {
		mat_force_tonemap_scale->SetValue("1");
		sv_skyname->SetValue(OldSkyBox.c_str());
		SetSkybox = false;
	}
}