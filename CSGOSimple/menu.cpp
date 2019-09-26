#include "menu.hpp"
#include <d3dx9.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui_internal.h"
#include "imgui/impl/imgui_impl_dx9.h"
#include "imgui/impl/imgui_impl_win32.h"
#include "SkinChanger.hpp"
#include "resource.h"
#include "features/AntiAim.hpp"
#include "features/bhop.hpp"

int CurrentTab = 0;

namespace ImGuiEx
{
	bool ColorEdit4(const char* label, Color* v, bool show_alpha = true)
	{
		auto clr = ImVec4{
			v->r() / 255.0f,
			v->g() / 255.0f,
			v->b() / 255.0f,
			v->a() / 255.0f
		};

		if (ImGui::ColorEdit4(label, &clr.x, show_alpha)) {
			v->SetColor(clr.x, clr.y, clr.z, clr.w);
			return true;
		}
		return false;
	}
	bool ColorEdit3(const char* label, Color* v)
	{
		return ColorEdit4(label, v, false);
	}
}

IDirect3DTexture9* AK47;
IDirect3DTexture9* AK471;
IDirect3DTexture9* AK472;
IDirect3DTexture9* AK473;
IDirect3DTexture9* AK474;

void Menu::Initialize()
{
	//MAKEINTRESOURCE(IDB_PNG50)
	_visible = true;
	D3DXCreateTextureFromFileA(g_D3DDevice9, "..\iconlib\32_.png", &AK47) == D3D_OK;
	D3DXCreateTextureFromFileA(g_D3DDevice9, "iconlib\32_.png", &AK471) == D3D_OK;
	D3DXCreateTextureFromFileA(g_D3DDevice9, "..\..\iconlib\32_.png", &AK472) == D3D_OK;
	D3DXCreateTextureFromFileA(g_D3DDevice9, "\32_.png", &AK473) == D3D_OK;
	D3DXCreateTextureFromFileA(g_D3DDevice9, "iconlib\32.png", &AK474) == D3D_OK;
	//D3DXCreateTextureFromFileA(g_D3DDevice9, "..\iconlib\32_.png", &AK47); //"..\iconlib\32_.png"
}

void Menu::Shutdown()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Menu::OnDeviceLost()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
}

void Menu::OnDeviceReset()
{
	ImGui_ImplDX9_CreateDeviceObjects();
}

int iTab;
int AimbotTab;
int RageTab;
int Knifeteam;
void color()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	style.Colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15, 255);
	style.Colors[ImGuiCol_ChildWindowBg] = ImColor(10, 10, 10, 255);
	style.Colors[ImGuiCol_Border] = ImColor(15, 15, 15, 255);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.02f, 0.60f, 0.22f);
	//style.Colors[ImGuiCol_CloseButton] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	//style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
}

void styled()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.f;
	style.FramePadding = ImVec2(4, 0);
	style.WindowPadding = ImVec2(0, 0);
	style.ItemSpacing = ImVec2(0, 0);
	style.ScrollbarSize = 10.f;
	style.ScrollbarRounding = 0.f;
	style.GrabMinSize = 5.f;
}

void ButtonColor(int r, int g, int b)
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Button] = ImColor(r, g, b);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(r, g, b);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(r, g, b);
}

void Menu::Render()
{
	ImGui::GetIO().MouseDrawCursor = _visible;

	if (!_visible)
		return;

#pragma region Combos
	static const char* Hitboxes[]{ "Head", "Neck", "Pelvis", "Stomach", "Lower Chest", "Chest", "Upper Chest", "Right Thigh", "Left Thigh", "Right Calf", "Left Calf", "Right Foot", "Left Foot",
		"Right Hand", "Left Hand", "Right Upper Arm", "Left Upper Arm", "Right ForeArm", "Left ForeArm" };

	static const char* HitGroups[]{ "Generic", "Head", "Chest", "Stomach", "Left Arm", "Right Arm", "Left Leg", "Right Leg", "Gear" };

	static const char* ConfigsNames[]{ "Legit", "Rage", "Custom", "Default" };

	static const char* AATypeYaw[]{ "Auto", "Legit", "Spinbot", "Jitter", "SideWays", "Fake SideWays", "Static", "Fake Static", "Custom" };

	static const char* Knives[]{ "Bayonet", "Flip Knife", "Gut Knife", "Karambit", "M9 Bayonet", "Huntsman", "Falchion", "Bowie", "Butterfly", "Shaddow Daggers", "Ursus", "Navaja", "Stiletto", "Talon" };

	static const char* Weapons[]{ "WEAPON_DEAGLE", "WEAPON_ELITE", "WEAPON_FIVESEVEN", "WEAPON_GLOCK", "WEAPON_AK47", "WEAPON_AUG", "WEAPON_AWP", "WEAPON_FAMAS", "WEAPON_G3SG1", "WEAPON_GALILAR",
		"WEAPON_M249", "WEAPON_M4A1", "WEAPON_MAC10", "WEAPON_P90", "WEAPON_MP5", "WEAPON_UMP45", "WEAPON_XM1014", "WEAPON_BIZON", "WEAPON_MAG7", "WEAPON_NEGEV", "WEAPON_SAWEDOFF", "WEAPON_HKP2000",
		"WEAPON_MP7", "WEAPON_MP9", "WEAPON_NOVA", "WEAPON_P250", "WEAPON_SCAR20", "WEAPON_SG556", "WEAPON_SSG08", "WEAPON_M4A1_SILENCER", "WEAPON_USP_SILENCER", "WEAPON_CZ75A", "WEAPON_REVOLVER" };

	static const char* SkyNames[]{ "cs_baggage_skybox_", "cs_tibet", "embassy", "italy", "jungle", "office", "sky_cs15_daylight01_hdr", "sky_cs15_daylight02_hdr", "sky_day02_05", "nukeblank",
		"dustblank", "sky_venice", "sky_cs15_daylight03_hdr", "sky_cs15_daylight04_hdr", "sky_csgo_cloudy01", "sky_csgo_night02", "sky_csgo_night02b", "vertigo", "vertigoblue_hdr",
		"sky_dust", "vietnam" };

	static const char* ButBot_Primary[]{ "Scar20 / G3SG1", "AWP", "SSG08", "AK47 / M4" };

	static const char* ButBot_Secondary[]{ "Berettas", "deagle", "P250", "Five-Seven" };

	static const char* HitmarkerModes[]{ "Standard", "Aimware" };

	static const char* HitmarkerSounds[]{ "None","Skeet", "HitSound" };

	static const char* Killmsg[]{ "None", "UltraWare.xyz", "Paste", "Better Paste", "Last Place" };

	static const char* Deathmsg[]{ "None", "Meme" };

	static const char* Teams[]{ "CT", "T" };

	static const char* ClanTags[]{ "UltraWare.xyz", "Custom" };

	static const char* AsusWallsType[]{ "World", "Static Props", "Both" };

	static int SelectedConfig = 2;
	static int SelectedWeapon = 0;
	static int OldKnifeCT = 0;
	static int OldKnifeT = 0;

	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();

	ImVec2 pos;

	style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	style.Colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15, 255);
	style.Colors[ImGuiCol_ChildWindowBg] = ImColor(10, 10, 10, 255);
	style.Colors[ImGuiCol_Border] = ImColor(15, 15, 15, 255);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.02f, 0.60f, 0.22f);
	//style.Colors[ImGuiCol_CloseButton] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	//style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
#pragma endregion

	ImGui::Begin("skeetttt", NULL, ImVec2(840, 560), 1.f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
	{

		pos = ImGui::GetWindowPos();

		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 135);

		ImGui::TextColored(ImVec4(255, 255, 255, 255) ,"UltraWare.xyz");
		//Tabs design
		#pragma region Tabsshit
					ButtonColor(15, 15, 15);
					ImGui::Button("##upprtabs", ImVec2(114, 20));

					ImGui::SameLine();
					styled();
					color();
					ButtonColor(50, 50, 50);
					ImGui::Button("##rageupline", ImVec2(1, 20));

					//MainTabs
					#pragma region MainTabsshit
					/*Visuals*/
					{
						if (iTab == 0) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##rageupline", ImVec2(118, 1));

						ImGui::SameLine();

						ButtonColor(50, 50, 50);
						ImGui::Button("##fgfgfg", ImVec2(1, 1));

						ButtonColor(15, 15, 15);
						if (iTab == 0) style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200); else style.Colors[ImGuiCol_Text] = ImColor(80, 80, 80);
						if (ImGui::Button("Visuals", ImVec2(118, 100))) iTab = 0;

						ImGui::SameLine();

						if (iTab != 0)ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##gfgfgfgfgfgf", ImVec2(1, 100));

						if (iTab == 0) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##ragedownline", ImVec2(118, 1));

						ImGui::SameLine();

						ButtonColor(50, 50, 50);
						ImGui::Button("##fgfgfg", ImVec2(1, 1));

					}

					/*legit*/
					{
						if (iTab == 1) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##lupline", ImVec2(118, 1));

						ImGui::SameLine();

						ButtonColor(50, 50, 50);
						ImGui::Button("##fgfgfg", ImVec2(1, 1));

						ButtonColor(15, 15, 15);
						if (iTab == 1) style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200); else style.Colors[ImGuiCol_Text] = ImColor(80, 80, 80);
						if (ImGui::Button("LegitBot", ImVec2(118, 100))) iTab = 1;

						ImGui::SameLine();

						if (iTab != 1)ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##gfgfgfgfgfgf", ImVec2(1, 100));

						if (iTab == 1) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##ldownline", ImVec2(118, 1));

						ImGui::SameLine();

						ButtonColor(50, 50, 50);
						ImGui::Button("##fgfgfg", ImVec2(1, 1));
					}

					/*Misc*/
					{
						if (iTab == 2) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##vupline", ImVec2(118, 1));

						ImGui::SameLine();

						ButtonColor(50, 50, 50);
						ImGui::Button("##fgfgfg", ImVec2(1, 1));

						ButtonColor(15, 15, 15);
						if (iTab == 2) style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200); else style.Colors[ImGuiCol_Text] = ImColor(80, 80, 80);
						if (ImGui::Button("Misc", ImVec2(118, 100))) iTab = 2;
						ImGui::SameLine();

						if (iTab != 2)ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##gfgfgfgfgfgf", ImVec2(1, 100));

						if (iTab == 2) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##vdownline", ImVec2(118, 1));

						ImGui::SameLine();

						ButtonColor(50, 50, 50);
						ImGui::Button("##fgfgfg", ImVec2(1, 1));
					}

					/*Skins*/
					{
						if (iTab == 3) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##mupline", ImVec2(118, 1));

						ImGui::SameLine();

						ButtonColor(50, 50, 50);
						ImGui::Button("##fgfgfg", ImVec2(1, 1));

						ButtonColor(15, 15, 15);
						if (iTab == 3) style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200); else style.Colors[ImGuiCol_Text] = ImColor(80, 80, 80);
						if (ImGui::Button("Skins", ImVec2(118, 100))) iTab = 3;
						ImGui::SameLine();

						if (iTab != 3)ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##gfgfgfgfgfgf", ImVec2(1, 100));

						if (iTab == 3) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##mdownline", ImVec2(118, 1));

						ImGui::SameLine();

						ButtonColor(50, 50, 50);
						ImGui::Button("##fgfgfg", ImVec2(1, 1));
					}

					/*Rage*/
					{
						if (iTab == 4) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##supline", ImVec2(118, 1));

						ImGui::SameLine();

						ButtonColor(50, 50, 50);
						ImGui::Button("##fgfgfg", ImVec2(1, 1));

						ButtonColor(15, 15, 15);
						if (iTab == 4) style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200); else style.Colors[ImGuiCol_Text] = ImColor(80, 80, 80);
						if (ImGui::Button("Rage", ImVec2(118, 100))) iTab = 4;
						ImGui::SameLine();

						if (iTab != 4)ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##gfgfgfgfgfgf", ImVec2(1, 100));

						if (iTab == 4) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						ImGui::Button("##sdownline", ImVec2(118, 1));

						ImGui::SameLine();

						ButtonColor(50, 50, 50);
						ImGui::Button("##fgfgfg", ImVec2(1, 1));
					}

					ButtonColor(15, 15, 15);
					ImGui::Button("##upprtabs", ImVec2(118, 20));

					ImGui::SameLine();

					ButtonColor(50, 50, 50);
					ImGui::Button("##rageupline", ImVec2(1, 20));
#pragma endregion 

					//AimbotTabs

					ImGui::NextColumn();
					style.WindowPadding = ImVec2(8, 8);
					style.ItemSpacing = ImVec2(4, 4);
					style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
					style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
					style.Colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15, 255);
					style.Colors[ImGuiCol_ChildWindowBg] = ImColor(15, 15, 15, 255);
					style.Colors[ImGuiCol_Border] = ImColor(15, 15, 15, 255);
					style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
					style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
					style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
					style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
					style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
					style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
					style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
					style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
					style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
					style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.78f);
					style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
					style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
					style.Colors[ImGuiCol_Button] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
					style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
					style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
					style.Colors[ImGuiCol_Header] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
					style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
					style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
					style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.02f, 0.60f, 0.22f);
					//style.Colors[ImGuiCol_CloseButton] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
					//style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
			#pragma endregion 

		ImGui::BeginChild("main", ImVec2(700, 540));
		{
			//do tabs here
			if (iTab == 0) { // Visuals
				ImGui::BeginGroup();
				{
					ImGui::Columns(3, "", false);
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "ESP");
					ImGui::Checkbox("ESP Enabled", &g_Options.esp_enabled);
					ImGui::Checkbox("ESP localplayer", &g_Options.esp_localplayer);
					ImGui::Checkbox("Team check ESP", &g_Options.esp_enemies_only);
					ImGui::Checkbox("Boxes", &g_Options.esp_player_boxes);
					ImGui::Checkbox("Skeleton", &g_Options.esp_player_skeleton);
					ImGui::Checkbox("Names", &g_Options.esp_player_names);
					ImGui::Checkbox("Health", &g_Options.esp_player_health);
					ImGui::Checkbox("Armour", &g_Options.esp_player_armour);
					ImGui::Checkbox("Weapon", &g_Options.esp_player_weapons);
					ImGui::Checkbox("Snaplines", &g_Options.esp_player_snaplines);

					ImGui::Checkbox("Crosshair", &g_Options.esp_crosshair);
					ImGui::Checkbox("Dropped Weapons", &g_Options.esp_dropped_weapons);
					ImGui::Checkbox("Defuse Kit", &g_Options.esp_defuse_kit);
					ImGui::Checkbox("Planted C4", &g_Options.esp_planted_c4);
					ImGui::Checkbox("Item Esp", &g_Options.esp_items);

					ImGui::Checkbox("FootStep ESP", &g_Options.esp_footstep);
					ImGui::Checkbox("Enemies Only FootSteps", &g_Options.esp_footstep_enemies_only);
					ImGuiEx::ColorEdit3("FootSteps color", &g_Options.esp_footstep_color);

					ImGuiEx::ColorEdit3("Allies Visible", &g_Options.color_esp_ally_visible);
					ImGuiEx::ColorEdit3("Enemies Visible", &g_Options.color_esp_enemy_visible);
					ImGuiEx::ColorEdit3("Allies Occluded", &g_Options.color_esp_ally_occluded);
					ImGuiEx::ColorEdit3("Enemies Occluded", &g_Options.color_esp_enemy_occluded);
					ImGuiEx::ColorEdit3("Crosshair", &g_Options.color_esp_crosshair);
					ImGuiEx::ColorEdit3("Dropped Weapons", &g_Options.color_esp_weapons);
					ImGuiEx::ColorEdit3("Defuse Kit", &g_Options.color_esp_defuse);
					ImGuiEx::ColorEdit3("Planted C4", &g_Options.color_esp_c4);
					ImGuiEx::ColorEdit3("Item Esp", &g_Options.color_esp_item);

					ImGui::NextColumn();
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "Glow");
					ImGui::Checkbox("Enabled Glow", &g_Options.glow_enabled);
					ImGui::Checkbox("Glow localplayer", &g_Options.glow_localplayer);
					ImGui::Checkbox("Team check Glow", &g_Options.glow_enemies_only);
					ImGui::Checkbox("Players", &g_Options.glow_players);
					ImGui::Checkbox("Chickens", &g_Options.glow_chickens);
					ImGui::Checkbox("C4 Carrier", &g_Options.glow_c4_carrier);
					ImGui::Checkbox("Planted C4 Glow", &g_Options.glow_planted_c4);
					ImGui::Checkbox("Defuse Kits", &g_Options.glow_defuse_kits);
					ImGui::Checkbox("Weapons", &g_Options.glow_weapons);
					ImGuiEx::ColorEdit3("Ally", &g_Options.color_glow_ally);
					ImGuiEx::ColorEdit3("Enemy", &g_Options.color_glow_enemy);
					ImGuiEx::ColorEdit3("Chickens", &g_Options.color_glow_chickens);
					ImGuiEx::ColorEdit3("C4 Carrier", &g_Options.color_glow_c4_carrier);
					ImGuiEx::ColorEdit3("Planted C4 Glow", &g_Options.color_glow_planted_c4);
					ImGuiEx::ColorEdit3("Defuse Kits", &g_Options.color_glow_defuse);
					ImGuiEx::ColorEdit3("Weapons", &g_Options.color_glow_weapons);

					ImGui::NextColumn();
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "Chams Players");
					ImGui::Checkbox("Enabled Chams", &g_Options.chams_player_enabled); ImGui::SameLine();
					ImGui::Checkbox("Chams localplayer", &g_Options.chams_localplayer);
					ImGui::Checkbox("Team Check Chams", &g_Options.chams_player_enemies_only);
					ImGui::Checkbox("Wireframe", &g_Options.chams_player_wireframe);
					ImGui::Checkbox("Flat", &g_Options.chams_player_flat);
					ImGui::Checkbox("Ignore-Z", &g_Options.chams_player_ignorez);
					ImGui::Checkbox("Glass", &g_Options.chams_player_glass);
					ImGuiEx::ColorEdit4("Ally (Visible)", &g_Options.color_chams_player_ally_visible, false);
					ImGuiEx::ColorEdit4("Ally (Occluded)", &g_Options.color_chams_player_ally_occluded, false);
					ImGuiEx::ColorEdit4("Enemy (Visible)", &g_Options.color_chams_player_enemy_visible, false);
					ImGuiEx::ColorEdit4("Enemy (Occluded)", &g_Options.color_chams_player_enemy_occluded, false);

					ImGui::NewLine();
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "Chams Arms");
					ImGui::Checkbox("Enabled Arms", &g_Options.chams_arms_enabled);
					ImGui::Checkbox("Wireframe Arms", &g_Options.chams_arms_wireframe);
					ImGui::Checkbox("Flat Arms", &g_Options.chams_arms_flat);
					ImGui::Checkbox("Ignore-Z Arms", &g_Options.chams_arms_ignorez);
					ImGui::Checkbox("Glass Arms", &g_Options.chams_arms_glass);
					ImGuiEx::ColorEdit4("Color (Visible) Arms", &g_Options.color_chams_arms_visible, false);
					ImGuiEx::ColorEdit4("Color (Occluded) Arms", &g_Options.color_chams_arms_occluded, false);

					ImGui::NewLine();
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "Chams Weapons");
					ImGui::Checkbox("Enabled Weapons", &g_Options.chams_weapons_enabled);
					ImGui::Checkbox("Wireframe Weapons", &g_Options.chams_weapons_wireframe);
					ImGui::Checkbox("Flat Weapons", &g_Options.chams_weapons_flat);
					ImGui::Checkbox("Ignore-Z Weapons", &g_Options.chams_weapons_ignorez);
					ImGui::Checkbox("Glass Weapons", &g_Options.chams_weapons_glass);
					ImGuiEx::ColorEdit4("Color (Visible) Weapons", &g_Options.color_chams_weapons_visible, false);
					ImGuiEx::ColorEdit4("Color (Occluded) Weapons", &g_Options.color_chams_weapons_occluded, false);
				}
				ImGui::EndGroup();
			}

			if (iTab == 1) { //LegitBot
				ImGui::Columns(7, "", false);
				{
					if (AimbotTab == 0) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						if (ImGui::Button("Pistols", ImVec2(700 / 7, 40))) AimbotTab = 0;
					ImGui::NextColumn();

					if (AimbotTab == 1) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						if (ImGui::Button("Rifles", ImVec2(700 / 7, 40))) AimbotTab = 1;
					ImGui::NextColumn();

					if (AimbotTab == 2) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						if (ImGui::Button("Smg", ImVec2(700 / 7, 40))) AimbotTab = 2;
					ImGui::NextColumn();

					if (AimbotTab == 3) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						if (ImGui::Button("Shotguns", ImVec2(700 / 7, 40))) AimbotTab = 3;
					ImGui::NextColumn();

					if (AimbotTab == 4) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						if (ImGui::Button("AWP", ImVec2(700 / 7, 40))) AimbotTab = 4;
					ImGui::NextColumn();

					if (AimbotTab == 5) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						if (ImGui::Button("SSG08", ImVec2(700 / 7, 40))) AimbotTab = 5;
					ImGui::NextColumn();

					if (AimbotTab == 6) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
						if (ImGui::Button("Autos", ImVec2(700 / 7, 40))) AimbotTab = 6;
				}
				ImGui::EndColumns();
				ImGui::BeginChild("settings");
				{
					if (AimbotTab == 0) { //pistols
						ImGui::Columns(2, "", false);
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Aimbot", &g_Options.Aimbot_Aimbot_Pistols);
						ImGui::Combo("Hitbox", &g_Options.Aimbot_Hitbox_Pistols, Hitboxes, IM_ARRAYSIZE(Hitboxes));
						ImGui::SliderInt("Fov", &g_Options.Aimbot_FOV_Pistols, 0.0f, 360.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Show FOV", &g_Options.Aimbot_ShowFOV_Pistols);
						ImGui::SliderFloat("Smooth", &g_Options.Aimbot_SmoothAmount_Pistols, 0.0f, 20.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Smooth", &g_Options.Aimbot_Smoothing_Pistols);
						ImGui::Checkbox("Silent", &g_Options.Aimbot_Silent_Pistols);

						ImGui::NewLine();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "TriggerBot");
						ImGui::Checkbox("TriggerBot", &g_Options.TriggerBot_TriggerBot_Pistols);
						ImGui::SliderInt("Delay", &g_Options.TriggerBot_Delay_Pistols, 0, 400);
						ImGui::Combo("HitGroup", &g_Options.TriggerBot_HitBox_Pistols, HitGroups, IM_ARRAYSIZE(HitGroups));
						ImGui::SliderFloat("Hitchance", &g_Options.TriggerBot_HitChance_Pistols, 0, 100.f);

						ImGui::NextColumn();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Recoil Prediction", &g_Options.Aimbot_RecoilPrediction_Pistols);
						ImGui::Checkbox("Visibility Check", &g_Options.Aimbot_VisibilityCheck_Pistols);
						ImGui::Checkbox("AutoCrouch", &g_Options.Aimbot_AutoCrouch_Pistols);
						ImGui::Checkbox("AutoStop", &g_Options.Aimbot_AutoStop_Pistols);
						ImGui::Checkbox("AutoScope", &g_Options.Aimbot_AutoScope_Pistols);
					}

					if (AimbotTab == 1) { //rifles
						ImGui::Columns(2, "", false);
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Aimbot", &g_Options.Aimbot_Aimbot_Rifles);
						ImGui::Combo("Hitbox", &g_Options.Aimbot_Hitbox_Rifles, Hitboxes, IM_ARRAYSIZE(Hitboxes));
						ImGui::SliderInt("Fov", &g_Options.Aimbot_FOV_Rifles, 0.0f, 360.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Show FOV", &g_Options.Aimbot_ShowFOV_Rifles);
						ImGui::SliderFloat("Smooth", &g_Options.Aimbot_SmoothAmount_Rifles, 0.0f, 20.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Smooth", &g_Options.Aimbot_Smoothing_Rifles);
						ImGui::Checkbox("Silent", &g_Options.Aimbot_Silent_Rifles);

						ImGui::NewLine();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "TriggerBot");
						ImGui::Checkbox("TriggerBot", &g_Options.TriggerBot_TriggerBot_Rifles);
						ImGui::SliderInt("Delay", &g_Options.TriggerBot_Delay_Rifles, 0, 400);
						ImGui::Combo("HitGroup", &g_Options.TriggerBot_HitBox_Rifles, HitGroups, IM_ARRAYSIZE(HitGroups));
						ImGui::SliderFloat("Hitchance", &g_Options.TriggerBot_HitChance_Rifles, 0, 100.f);

						ImGui::NextColumn();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Recoil Prediction", &g_Options.Aimbot_RecoilPrediction_Rifles);
						ImGui::Checkbox("Visibility Check", &g_Options.Aimbot_VisibilityCheck_Rifles);
						ImGui::Checkbox("AutoCrouch", &g_Options.Aimbot_AutoCrouch_Rifles);
						ImGui::Checkbox("AutoStop", &g_Options.Aimbot_AutoStop_Rifles);
						ImGui::Checkbox("AutoScope", &g_Options.Aimbot_AutoScope_Rifles);
					}

					if (AimbotTab == 2) { //smg
						ImGui::Columns(2, "", false);
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Aimbot", &g_Options.Aimbot_Aimbot_SMG);
						ImGui::Combo("Hitbox", &g_Options.Aimbot_Hitbox_SMG, Hitboxes, IM_ARRAYSIZE(Hitboxes));
						ImGui::SliderInt("Fov", &g_Options.Aimbot_FOV_SMG, 0.0f, 360.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Show FOV", &g_Options.Aimbot_ShowFOV_SMG);
						ImGui::SliderFloat("Smooth", &g_Options.Aimbot_SmoothAmount_SMG, 0.0f, 20.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Smooth", &g_Options.Aimbot_Smoothing_SMG);
						ImGui::Checkbox("Silent", &g_Options.Aimbot_Silent_SMG);

						ImGui::NewLine();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "TriggerBot");
						ImGui::Checkbox("TriggerBot", &g_Options.TriggerBot_TriggerBot_SMG);
						ImGui::SliderInt("Delay", &g_Options.TriggerBot_Delay_SMG, 0, 400);
						ImGui::Combo("HitGroup", &g_Options.TriggerBot_HitBox_SMG, HitGroups, IM_ARRAYSIZE(HitGroups));
						ImGui::SliderFloat("Hitchance", &g_Options.TriggerBot_HitChance_SMG, 0, 100.f);

						ImGui::NextColumn();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Recoil Prediction", &g_Options.Aimbot_RecoilPrediction_SMG);
						ImGui::Checkbox("Visibility Check", &g_Options.Aimbot_VisibilityCheck_SMG);
						ImGui::Checkbox("AutoCrouch", &g_Options.Aimbot_AutoCrouch_SMG);
						ImGui::Checkbox("AutoStop", &g_Options.Aimbot_AutoStop_SMG);
						ImGui::Checkbox("AutoScope", &g_Options.Aimbot_AutoScope_SMG);
					}

					if (AimbotTab == 3) { //shotguns
						ImGui::Columns(2, "", false);
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Aimbot", &g_Options.Aimbot_Aimbot_Shotguns);
						ImGui::Combo("Hitbox", &g_Options.Aimbot_Hitbox_Shotguns, Hitboxes, IM_ARRAYSIZE(Hitboxes));
						ImGui::SliderInt("Fov", &g_Options.Aimbot_FOV_Shotguns, 0.0f, 360.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Show FOV", &g_Options.Aimbot_ShowFOV_Shotguns);
						ImGui::SliderFloat("Smooth", &g_Options.Aimbot_SmoothAmount_Shotguns, 0.0f, 20.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Smooth", &g_Options.Aimbot_Smoothing_Shotguns);
						ImGui::Checkbox("Silent", &g_Options.Aimbot_Silent_Shotguns);

						ImGui::NewLine();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "TriggerBot");
						ImGui::Checkbox("TriggerBot", &g_Options.TriggerBot_TriggerBot_Shotguns);
						ImGui::SliderInt("Delay", &g_Options.TriggerBot_Delay_Shotguns, 0, 400);
						ImGui::Combo("HitGroup", &g_Options.TriggerBot_HitBox_Shotguns, HitGroups, IM_ARRAYSIZE(HitGroups));
						ImGui::SliderFloat("Hitchance", &g_Options.TriggerBot_HitChance_Shotguns, 0, 100.f);

						ImGui::NextColumn();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Recoil Prediction", &g_Options.Aimbot_RecoilPrediction_Shotguns);
						ImGui::Checkbox("Visibility Check", &g_Options.Aimbot_VisibilityCheck_Shotguns);
						ImGui::Checkbox("AutoCrouch", &g_Options.Aimbot_AutoCrouch_Shotguns);
						ImGui::Checkbox("AutoStop", &g_Options.Aimbot_AutoStop_Shotguns);
						ImGui::Checkbox("AutoScope", &g_Options.Aimbot_AutoScope_Shotguns);
					}

					if (AimbotTab == 4) { //awp
						ImGui::Columns(2, "", false);
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Aimbot", &g_Options.Aimbot_Aimbot_AWP);
						ImGui::Combo("Hitbox", &g_Options.Aimbot_Hitbox_AWP, Hitboxes, IM_ARRAYSIZE(Hitboxes));
						ImGui::SliderInt("Fov", &g_Options.Aimbot_FOV_AWP, 0.0f, 360.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Show FOV", &g_Options.Aimbot_ShowFOV_AWP);
						ImGui::SliderFloat("Smooth", &g_Options.Aimbot_SmoothAmount_AWP, 0.0f, 20.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Smooth", &g_Options.Aimbot_Smoothing_AWP);
						ImGui::Checkbox("Silent", &g_Options.Aimbot_Silent_AWP);

						ImGui::NewLine();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "TriggerBot");
						ImGui::Checkbox("TriggerBot", &g_Options.TriggerBot_TriggerBot_AWP);
						ImGui::SliderInt("Delay", &g_Options.TriggerBot_Delay_AWP, 0, 400);
						ImGui::Combo("HitGroup", &g_Options.TriggerBot_HitBox_AWP, HitGroups, IM_ARRAYSIZE(HitGroups));
						ImGui::SliderFloat("Hitchance", &g_Options.TriggerBot_HitChance_AWP, 0, 100.f);

						ImGui::NextColumn();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Recoil Prediction", &g_Options.Aimbot_RecoilPrediction_AWP);
						ImGui::Checkbox("Visibility Check", &g_Options.Aimbot_VisibilityCheck_AWP);
						ImGui::Checkbox("AutoCrouch", &g_Options.Aimbot_AutoCrouch_AWP);
						ImGui::Checkbox("AutoStop", &g_Options.Aimbot_AutoStop_AWP);
						ImGui::Checkbox("AutoScope", &g_Options.Aimbot_AutoScope_AWP);
					}

					if (AimbotTab == 5) { //ssg08
						ImGui::Columns(2, "", false);
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Aimbot", &g_Options.Aimbot_Aimbot_SSG08);
						ImGui::Combo("Hitbox", &g_Options.Aimbot_Hitbox_SSG08, Hitboxes, IM_ARRAYSIZE(Hitboxes));
						ImGui::SliderInt("Fov", &g_Options.Aimbot_FOV_SSG08, 0.0f, 360.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Show FOV", &g_Options.Aimbot_ShowFOV_SSG08);
						ImGui::SliderFloat("Smooth", &g_Options.Aimbot_SmoothAmount_SSG08, 0.0f, 20.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Smooth", &g_Options.Aimbot_Smoothing_SSG08);
						ImGui::Checkbox("Silent", &g_Options.Aimbot_Silent_SSG08);

						ImGui::NewLine();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "TriggerBot");
						ImGui::Checkbox("TriggerBot", &g_Options.TriggerBot_TriggerBot_SSG08);
						ImGui::SliderInt("Delay", &g_Options.TriggerBot_Delay_SSG08, 0, 400);
						ImGui::Combo("HitGroup", &g_Options.TriggerBot_HitBox_SSG08, HitGroups, IM_ARRAYSIZE(HitGroups));
						ImGui::SliderFloat("Hitchance", &g_Options.TriggerBot_HitChance_SSG08, 0, 100.f);

						ImGui::NextColumn();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Recoil Prediction", &g_Options.Aimbot_RecoilPrediction_SSG08);
						ImGui::Checkbox("Visibility Check", &g_Options.Aimbot_VisibilityCheck_SSG08);
						ImGui::Checkbox("AutoCrouch", &g_Options.Aimbot_AutoCrouch_SSG08);
						ImGui::Checkbox("AutoStop", &g_Options.Aimbot_AutoStop_SSG08);
						ImGui::Checkbox("AutoScope", &g_Options.Aimbot_AutoScope_SSG08);
					}

					if (AimbotTab == 6) { //autos
						ImGui::Columns(2, "", false);
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Aimbot", &g_Options.Aimbot_Aimbot_Autos);
						ImGui::Combo("Hitbox", &g_Options.Aimbot_Hitbox_Autos, Hitboxes, IM_ARRAYSIZE(Hitboxes));
						ImGui::SliderInt("Fov", &g_Options.Aimbot_FOV_Autos, 0.0f, 360.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Show FOV", &g_Options.Aimbot_ShowFOV_Autos);
						ImGui::SliderFloat("Smooth", &g_Options.Aimbot_SmoothAmount_Autos, 0.0f, 20.0f);
						ImGui::SameLine();
						ImGui::Checkbox("Smooth", &g_Options.Aimbot_Smoothing_Autos);
						ImGui::Checkbox("Silent", &g_Options.Aimbot_Silent_Autos);

						ImGui::NewLine();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "TriggerBot");
						ImGui::Checkbox("TriggerBot", &g_Options.TriggerBot_TriggerBot_Autos);
						ImGui::SliderInt("Delay", &g_Options.TriggerBot_Delay_Autos, 0, 400);
						ImGui::Combo("HitGroup", &g_Options.TriggerBot_HitBox_Autos, HitGroups, IM_ARRAYSIZE(HitGroups));
						ImGui::SliderFloat("Hitchance", &g_Options.TriggerBot_HitChance_Autos, 0, 100.f);

						ImGui::NextColumn();
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Aimbot");
						ImGui::Checkbox("Recoil Prediction", &g_Options.Aimbot_RecoilPrediction_Autos);
						ImGui::Checkbox("Visibility Check", &g_Options.Aimbot_VisibilityCheck_Autos);
						ImGui::Checkbox("AutoCrouch", &g_Options.Aimbot_AutoCrouch_Autos);
						ImGui::Checkbox("AutoStop", &g_Options.Aimbot_AutoStop_Autos);
						ImGui::Checkbox("AutoScope", &g_Options.Aimbot_AutoScope_Autos);
					}

					ImGui::NewLine();
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "BackTrack");
					ImGui::Checkbox("BackTrack", &g_Options.BackTrack_BackTrack);
					ImGui::Checkbox("Compensate Recoil", &g_Options.BackTrack_RecoilBasedFov);
					//ImGui::Checkbox("Ignore Smoke", &g_Options.BackTrack_ignoreSmoke);
					ImGui::SliderInt("Time Limit", &g_Options.BackTrack_Ticks, 0, 1000);
					ImGui::Checkbox("Show Ticks", &g_Options.esp_player_BackTrackTicks);
					ImGui::Checkbox("BackTrack chams", &g_Options.BackTrack_Chams);
					ImGui::SameLine();
					ImGui::Checkbox("Last Tick", &g_Options.BackTrack_Chams_LastTick);
					ImGuiEx::ColorEdit4("Chams Color", &g_Options.BackTrack_Chams_color, false);
				}
				ImGui::EndChild();
			}

			if (iTab == 2) { //Misc
				ImGui::Columns(2, "", false);
				ImGui::Checkbox("Watermark", &g_Options.misc_watermark);
				ImGui::Checkbox("ClanTag Changer", &g_Options.misc_ClanTag);
				if (g_Options.misc_ClanTag) {
					ImGui::Combo("Clan Type", &g_Options.misc_ClanTagClan, ClanTags, IM_ARRAYSIZE(ClanTags));
					//if (g_Options.misc_ClanTagClan == 1)
						//ImGui::InputText("ClanTag", &g_Options.misc_ClanTagName.c_str, 32);
				}
				ImGui::Checkbox("Bunny hop", &g_Options.misc_bhop);
				ImGui::Checkbox("AutoStrafe", &g_Options.misc_AutoStrafe);
				ImGui::Checkbox("Radar hack", &g_Options.misc_Radar);
				ImGui::Checkbox("Third Person", &g_Options.misc_thirdperson); ImGui::SameLine(); ImGui::Text("Bind F1");
				if (g_Options.misc_thirdperson)
					ImGui::SliderFloat("Distance", &g_Options.misc_thirdperson_dist, 0.f, 250.f);
				ImGui::Checkbox("No hands", &g_Options.misc_no_hands);
				ImGui::Checkbox("Remove Scope", &g_Options.misc_RemoveScope);
				ImGui::Checkbox("Rank reveal", &g_Options.misc_showranks);
				ImGui::Checkbox("AutoAccept", &g_Options.misc_AutoAccept);
				ImGui::Checkbox("UnlimitedDuck", &g_Options.misc_UnlimitedDuck);
				ImGui::Checkbox("Hitmarker", &g_Options.misc_Hitmarker);
				if (g_Options.misc_Hitmarker) {
					ImGui::Combo("Mode", &g_Options.misc_HitmarkerMode, HitmarkerModes, IM_ARRAYSIZE(HitmarkerModes));
					ImGui::Combo("Sound", &g_Options.misc_HitmarkerSound, HitmarkerSounds, IM_ARRAYSIZE(HitmarkerSounds));
					ImGui::SliderInt("Size", &g_Options.misc_HitmarkerSize, 1, 20);
					ImGui::SliderInt("Duration(ms)", &g_Options.misc_HitmarkerDuration, 1, 2000);
					ImGuiEx::ColorEdit4("Hitmarker color", &g_Options.misc_Hitmarker_color, false);
				}
				ImGui::Checkbox("Log Events", &g_Options.misc_LogEvents);
				if (g_Options.misc_LogEvents) {
					ImGui::Checkbox("Damage dealt", &g_Options.misc_LogEvents_Damage);
					ImGui::Checkbox("Purchases", &g_Options.misc_LogEvents_ItemsPurchase);
					ImGui::Checkbox("Bomb", &g_Options.misc_LogEvents_Bomb);
					ImGuiEx::ColorEdit4("Logs color", &g_Options.misc_LogEvents_color, false);
				}
				ImGui::NewLine();
				ImGui::TextColored(ImVec4(0, 255, 0, 255), "Bots");
				ImGui::Checkbox("SpotMarkers", &g_Options.misc_SpotMarkers);
				ImGui::SameLine();
				ImGui::Checkbox("Show Spots", &g_Options.misc_SpotMarkersShow);
				ImGui::SameLine(); ImGui::Text("Bind F3");
				ImGui::Checkbox("Walk Bot", &g_Options.misc_WalkBot);
				ImGui::Checkbox("BuyBot", &g_Options.misc_BuyBot);
				if (g_Options.misc_BuyBot) {
					ImGui::Combo("Primary", &g_Options.misc_BuyBot_Primary, ButBot_Primary, IM_ARRAYSIZE(ButBot_Primary));
					ImGui::Combo("Secondary", &g_Options.misc_BuyBot_Secondary, ButBot_Secondary, IM_ARRAYSIZE(ButBot_Secondary));
					ImGui::Checkbox("Kevlar", &g_Options.misc_BuyBot_Kevlar); ImGui::SameLine();
					ImGui::Checkbox("Grenades", &g_Options.misc_BuyBot_Grenades); ImGui::SameLine();
					ImGui::Checkbox("Defuser", &g_Options.misc_BuyBot_Defuser);
					ImGui::Checkbox("Taser", &g_Options.misc_BuyBot_Taser);
				}
				ImGui::Checkbox("Chat Spam", &g_Options.misc_ChatSpam);
				if (g_Options.misc_ChatSpam) {
					ImGui::Combo("Kill msg", &g_Options.misc_ChatSpamKill, Killmsg, IM_ARRAYSIZE(Killmsg));
					ImGui::Combo("Death msg", &g_Options.misc_ChatSpamDeath, Deathmsg, IM_ARRAYSIZE(Deathmsg));
				}
				ImGui::Checkbox("AntiKick", &g_Options.misc_AntiKick);


				ImGui::NextColumn();
				ImGui::Checkbox("FakePing", &g_Options.misc_FakePing);
				if (g_Options.misc_FakePing) {
					ImGui::SliderInt("Ping", &g_Options.misc_FakePingAmount, 0, 1000);
					ImGui::Checkbox("Ignore Backtrack", &g_Options.misc_FakePingIgnoreBacktrack);
				}
				ImGui::Checkbox("FakeLag", &g_Options.misc_FakeLag);
				if (g_Options.misc_FakeLag) {
					ImGui::SliderInt("Ticks Standinng", &g_Options.misc_FakeLagStandingAmount, 0, 15);
					ImGui::SliderInt("Ticks Moving", &g_Options.misc_FakeLagMovingAmount, 0, 15);
					ImGui::SliderInt("Ticks In Air", &g_Options.misc_FakeLagInAirAmount, 0, 15);
				}
				ImGui::Checkbox("No Flash", &g_Options.misc_NoFlash);
				ImGui::Checkbox("No Smoke", &g_Options.misc_NoSmoke);
				ImGui::SliderInt("viewmodel_fov:", &g_Options.viewmodel_fov, 0, 180);
				ImGui::SliderInt("Fov:", &g_Options.misc_Fov, 60, 150);
				ImGui::Text("Postprocessing:");
				ImGui::SliderFloat("Red", &g_Options.mat_ambient_light_r, 0, 1);
				ImGui::SliderFloat("Green", &g_Options.mat_ambient_light_g, 0, 1);
				ImGui::SliderFloat("Blue", &g_Options.mat_ambient_light_b, 0, 1);
				ImGui::Combo("SkyBox", &g_Options.misc_SkyBox, SkyNames, IM_ARRAYSIZE(SkyNames));
				ImGui::Checkbox("Inverse Gravity", &g_Options.misc_InverseRagdollGravity);
				ImGui::Checkbox("Specator List", &g_Options.misc_spectatorsList);
				if (g_Options.misc_spectatorsList) {
					ImGui::Checkbox("Only me", &g_Options.misc_spectatorsListOnlyMe);
					ImGuiEx::ColorEdit4("Box color", &g_Options.misc_spectatorsList_color);
				}
				ImGui::Checkbox("Disable Postprocess", &g_Options.misc_DisablePostProcess);
				ImGui::Checkbox("NightMode", &g_Options.misc_NightMode);
				ImGui::Checkbox("Edge Jump", &g_Options.misc_edgejump);
				ImGui::Checkbox("Grenade Trajectory", &g_Options.misc_grenadeTrajectory);
				ImGui::Checkbox("Asus Walls", &g_Options.misc_AsusWalls);
				if (g_Options.misc_AsusWalls) {
					ImGui::Combo("Asus Type", &g_Options.misc_AsusWallsInt, AsusWallsType, IM_ARRAYSIZE(AsusWallsType));
					ImGui::SliderFloat("Alpha", &g_Options.misc_AsusWallsAlpha, 0.01f, 1.f);
				}
				//if (ImGui::Button("Fake VAC"))
					//MISC::FakeCommends();
			}

			if (iTab == 3) { //Skins
				ImGui::Columns(2, "", true);
				ImGui::TextColored(ImVec4(0, 255, 0, 255), "SkinChanger");
				ImGui::Checkbox("SkinChanger", &g_Options.SkinChanger_SkinChanger);
				ImGui::Combo("Weapon", &SelectedWeapon, Weapons, IM_ARRAYSIZE(Weapons));
				ImGui::InputInt("Skin", &g_Options.SkinChanger_Skin);
				ImGui::InputInt("Stattrak", &g_Options.SkinChanger_Stattrak);
				ImGui::InputFloat("Seed", &g_Options.SkinChanger_Seed);
				ImGui::SliderFloat("Wear", &g_Options.SkinChanger_Wear, 0.00001, 1.f);
				if (ImGui::Button("Apply")) {
					switch (SelectedWeapon)
					{
					case 0:
						g_Options.WEAPON_DEAGLE = g_Options.SkinChanger_Skin;
						break;
					case 1:
						g_Options.WEAPON_ELITE = g_Options.SkinChanger_Skin;
						break;
					case 2:
						g_Options.WEAPON_FIVESEVEN = g_Options.SkinChanger_Skin;
						break;
					case 3:
						g_Options.WEAPON_GLOCK = g_Options.SkinChanger_Skin;
						break;
					case 4:
						g_Options.WEAPON_AK47 = g_Options.SkinChanger_Skin;
						break;
					case 5:
						g_Options.WEAPON_AUG = g_Options.SkinChanger_Skin;
						break;
					case 6:
						g_Options.WEAPON_AWP = g_Options.SkinChanger_Skin;
						break;
					case 7:
						g_Options.WEAPON_FAMAS = g_Options.SkinChanger_Skin;
						break;
					case 8:
						g_Options.WEAPON_G3SG1 = g_Options.SkinChanger_Skin;
						break;
					case 9:
						g_Options.WEAPON_GALILAR = g_Options.SkinChanger_Skin;
						break;
					case 10:
						g_Options.WEAPON_M249 = g_Options.SkinChanger_Skin;
						break;
					case 11:
						g_Options.WEAPON_M4A1 = g_Options.SkinChanger_Skin;
						break;
					case 12:
						g_Options.WEAPON_MAC10 = g_Options.SkinChanger_Skin;
						break;
					case 13:
						g_Options.WEAPON_P90 = g_Options.SkinChanger_Skin;
						break;
					case 14:
						g_Options.WEAPON_MP5 = g_Options.SkinChanger_Skin;
						break;
					case 15:
						g_Options.WEAPON_UMP45 = g_Options.SkinChanger_Skin;
						break;
					case 16:
						g_Options.WEAPON_XM1014 = g_Options.SkinChanger_Skin;
						break;
					case 17:
						g_Options.WEAPON_BIZON = g_Options.SkinChanger_Skin;
						break;
					case 18:
						g_Options.WEAPON_MAG7 = g_Options.SkinChanger_Skin;
						break;
					case 19:
						g_Options.WEAPON_NEGEV = g_Options.SkinChanger_Skin;
						break;
					case 20:
						g_Options.WEAPON_SAWEDOFF = g_Options.SkinChanger_Skin;
						break;
					case 21:
						g_Options.WEAPON_HKP2000 = g_Options.SkinChanger_Skin;
						break;
					case 22:
						g_Options.WEAPON_MP7 = g_Options.SkinChanger_Skin;
						break;
					case 23:
						g_Options.WEAPON_MP9 = g_Options.SkinChanger_Skin;
						break;
					case 24:
						g_Options.WEAPON_NOVA = g_Options.SkinChanger_Skin;
						break;
					case 25:
						g_Options.WEAPON_P250 = g_Options.SkinChanger_Skin;
						break;
					case 26:
						g_Options.WEAPON_SCAR20 = g_Options.SkinChanger_Skin;
						break;
					case 27:
						g_Options.WEAPON_SG556 = g_Options.SkinChanger_Skin;
						break;
					case 28:
						g_Options.WEAPON_SSG08 = g_Options.SkinChanger_Skin;
						break;
					case 29:
						g_Options.WEAPON_M4A1_SILENCER = g_Options.SkinChanger_Skin;
						break;
					case 30:
						g_Options.WEAPON_USP_SILENCER = g_Options.SkinChanger_Skin;
						break;
					case 31:
						g_Options.WEAPON_CZ75A = g_Options.SkinChanger_Skin;
						break;
					case 32:
						g_Options.WEAPON_REVOLVER = g_Options.SkinChanger_Skin;
						break;
					default:
						break;
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("ForceUpdate")) {
					skinchanger.SetForceFullUpdate = true;
				}
				ImGui::NewLine();
				ImGui::TextColored(ImVec4(0, 255, 0, 255), "KnifeChanger");
				ImGui::SameLine(); ImGui::Combo("Team", &Knifeteam, Teams, IM_ARRAYSIZE(Teams));
				if (Knifeteam == 0) { //CT
					ImGui::Checkbox("KnifeChanger", &g_Options.SkinChanger_KnifeChangerCT);
					ImGui::Combo("Knife", &g_Options.KnifeCT, Knives, IM_ARRAYSIZE(Knives));
					ImGui::InputInt("Knife Skin", &g_Options.KNIFE_SKINCT);
					ImGui::InputInt("Knife Stattrak", &g_Options.KNIFE_StattrakCT);
					ImGui::InputFloat("Knife Seed", &g_Options.KNIFE_SeedCT);
					ImGui::SliderFloat("Knife Wear", &g_Options.KNIFE_WearCT, 0.00001, 1.f);
				}else if(Knifeteam == 1){ //T
					ImGui::Checkbox("KnifeChanger", &g_Options.SkinChanger_KnifeChangerT);
					ImGui::Combo("Knife", &g_Options.KnifeT, Knives, IM_ARRAYSIZE(Knives));
					ImGui::InputInt("Knife Skin", &g_Options.KNIFE_SKINT);
					ImGui::InputInt("Knife Stattrak", &g_Options.KNIFE_StattrakT);
					ImGui::InputFloat("Knife Seed", &g_Options.KNIFE_SeedT);
					ImGui::SliderFloat("Knife Wear", &g_Options.KNIFE_WearT, 0.00001, 1.f);
				}
				if (ImGui::Button("ForceUpdate Knife")) {
					skinchanger.SetForceFullUpdate = true;
				}

				if(OldKnifeCT != g_Options.KnifeCT || OldKnifeT != g_Options.KnifeT)
					skinchanger.SetForceFullUpdate = true;

				OldKnifeCT = g_Options.KnifeCT;
				OldKnifeT = g_Options.KnifeT;
				if (Knifeteam == 0) {
					switch (g_Options.KnifeCT)
					{
					case 0:
						g_Options.WEAPON_KNIFECT = WEAPON_BAYONET;
						break;
					case 1:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_FLIP;
						break;
					case 2:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_GUT;
						break;
					case 3:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_KARAMBIT;
						break;
					case 4:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_M9_BAYONET;
						break;
					case 5:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_TACTICAL;
						break;
					case 6:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_FALCHION;
						break;
					case 7:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_SURVIVAL_BOWIE;
						break;
					case 8:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_BUTTERFLY;
						break;
					case 9:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_PUSH;
						break;
					case 10:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_URSUS;
						break;
					case 11:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_GYPSY_JACKKNIFE;
						break;
					case 12:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_STILETTO;
						break;
					case 13:
						g_Options.WEAPON_KNIFECT = WEAPON_KNIFE_WIDOWMAKER;
						break;
					default:
						break;
					}
				}else if (Knifeteam == 1) {
					switch (g_Options.KnifeT)
					{
					case 0:
						g_Options.WEAPON_KNIFET = WEAPON_BAYONET;
						break;
					case 1:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_FLIP;
						break;
					case 2:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_GUT;
						break;
					case 3:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_KARAMBIT;
						break;
					case 4:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_M9_BAYONET;
						break;
					case 5:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_TACTICAL;
						break;
					case 6:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_FALCHION;
						break;
					case 7:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_SURVIVAL_BOWIE;
						break;
					case 8:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_BUTTERFLY;
						break;
					case 9:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_PUSH;
						break;
					case 10:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_URSUS;
						break;
					case 11:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_GYPSY_JACKKNIFE;
						break;
					case 12:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_STILETTO;
						break;
					case 13:
						g_Options.WEAPON_KNIFET = WEAPON_KNIFE_WIDOWMAKER;
						break;
					default:
						break;
					}
				}

				ImGui::NewLine();
				ImGui::TextColored(ImVec4(0, 255, 0, 255), "GloveChanger");
				ImGui::Checkbox("GloveChanger", &g_Options.SkinChanger_GloveChanger);
				ImGui::InputInt("Glove Model", &g_Options.GLOVE_MODEL);
				ImGui::InputInt("Glove Skin", &g_Options.GLOVE_SKIN);
				ImGui::SliderFloat("Glove Wear", &g_Options.GLOVE_WEAR, 0.00001f, 1.f);

				ImGui::NextColumn();
				ImGui::ListBox("Config", &SelectedConfig, ConfigsNames, IM_ARRAYSIZE(ConfigsNames));
				if (ImGui::Button("Save")) {
					switch (SelectedConfig) {
					case 0:
						g_SaveLoadConfig.Save("Legit", g_Options);
						break;
					case 1:
						g_SaveLoadConfig.Save("Rage", g_Options);
						break;
					case 2:
						g_SaveLoadConfig.Save("Custom", g_Options);
						break;
					case 3:
						g_SaveLoadConfig.Save("Default", g_Options);
						break;

					default:
						g_SaveLoadConfig.Save("Default", g_Options);
						break;
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Load")) {
					switch (SelectedConfig) {
					case 0:
						g_SaveLoadConfig.Load("Legit", g_Options);
						break;
					case 1:
						g_SaveLoadConfig.Load("Rage", g_Options);
						break;
					case 2:
						g_SaveLoadConfig.Load("Custom", g_Options);
						break;
					case 3:
						g_SaveLoadConfig.Load("Default", g_Options);
						break;

					default:
						g_SaveLoadConfig.Load("Default", g_Options);
						break;
					}
				}
				if (ImGui::Button("Unload"))
					g_Unload = true;
			}

			if (iTab == 4) { //Rage
				ImGui::Columns(7, "", false);
				{
					if (RageTab == 0) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
					if (ImGui::Button("Pistols", ImVec2(700 / 7, 40))) RageTab = 0;
					ImGui::NextColumn();

					if (RageTab == 1) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
					if (ImGui::Button("Rifles", ImVec2(700 / 7, 40))) RageTab = 1;
					ImGui::NextColumn();

					if (RageTab == 2) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
					if (ImGui::Button("SMG", ImVec2(700 / 7, 40))) RageTab = 2;
					ImGui::NextColumn();

					if (RageTab == 3) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
					if (ImGui::Button("Shotguns", ImVec2(700 / 7, 40))) RageTab = 3;
					ImGui::NextColumn();

					if (RageTab == 4) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
					if (ImGui::Button("AWP", ImVec2(700 / 7, 40))) RageTab = 4;
					ImGui::NextColumn();

					if (RageTab == 5) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
					if (ImGui::Button("SSG08", ImVec2(700 / 7, 40))) RageTab = 5;
					ImGui::NextColumn();

					if (RageTab == 6) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
					if (ImGui::Button("Autos", ImVec2(700 / 7, 40))) RageTab = 6;
				}
				ImGui::EndColumns();
				ImGui::BeginChild("AutoWall");
				{
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "AutoWall");
					ImGui::Checkbox("Show Damage", &g_Options.AutoWall_ShowDamage);
					if (RageTab == 0) { //Pistols
						ImGui::Checkbox("AutoWall", &g_Options.AutoWall_AutoWall_Pistols);
						ImGui::Checkbox("AW BackTrack", &g_Options.AutoWall_BackTrack_Pistols);
						ImGui::SliderFloat("Min Damage", &g_Options.AutoWall_MinDamage_Pistols, 0, 100);
						ImGui::SliderFloat("Hitchance", &g_Options.AutoWall_Hitchance_Pistols, 0, 100);
					}
					if (RageTab == 1) { //Rifles
						ImGui::Checkbox("AutoWall", &g_Options.AutoWall_AutoWall_Rifles);
						ImGui::Checkbox("AW BackTrack", &g_Options.AutoWall_BackTrack_Rifles);
						ImGui::SliderFloat("Min Damage", &g_Options.AutoWall_MinDamage_Rifles, 0, 100);
						ImGui::SliderFloat("Hitchance", &g_Options.AutoWall_Hitchance_Rifles, 0, 100);
					}
					if (RageTab == 2) { //SMG
						ImGui::Checkbox("AutoWall", &g_Options.AutoWall_AutoWall_SMG);
						ImGui::Checkbox("AW BackTrack", &g_Options.AutoWall_BackTrack_SMG);
						ImGui::SliderFloat("Min Damage", &g_Options.AutoWall_MinDamage_SMG, 0, 100);
						ImGui::SliderFloat("Hitchance", &g_Options.AutoWall_Hitchance_SMG, 0, 100);
					}
					if (RageTab == 3) { //ShotGuns
						ImGui::Checkbox("AutoWall", &g_Options.AutoWall_AutoWall_ShotGuns);
						ImGui::Checkbox("AW BackTrack", &g_Options.AutoWall_BackTrack_ShotGuns);
						ImGui::SliderFloat("Min Damage", &g_Options.AutoWall_MinDamage_ShotGuns, 0, 100);
						ImGui::SliderFloat("Hitchance", &g_Options.AutoWall_Hitchance_ShotGuns, 0, 100);
					}
					if (RageTab == 4) { //AWP
						ImGui::Checkbox("AutoWall", &g_Options.AutoWall_AutoWall_AWP);
						ImGui::Checkbox("AW BackTrack", &g_Options.AutoWall_BackTrack_AWP);
						ImGui::SliderFloat("Min Damage", &g_Options.AutoWall_MinDamage_AWP, 0, 100);
						ImGui::SliderFloat("Hitchance", &g_Options.AutoWall_Hitchance_AWP, 0, 100);
					}
					if (RageTab == 5) { //SSG08
						ImGui::Checkbox("AutoWall", &g_Options.AutoWall_AutoWall_SSG08);
						ImGui::Checkbox("AW BackTrack", &g_Options.AutoWall_BackTrack_SSG08);
						ImGui::SliderFloat("Min Damage", &g_Options.AutoWall_MinDamage_SSG08, 0, 100);
						ImGui::SliderFloat("Hitchance", &g_Options.AutoWall_Hitchance_SSG08, 0, 100);
					}
					if (RageTab == 6) { //Autos
						ImGui::Checkbox("AutoWall", &g_Options.AutoWall_AutoWall_Autos);
						ImGui::Checkbox("AW BackTrack", &g_Options.AutoWall_BackTrack_Autos);
						ImGui::SliderFloat("Min Damage", &g_Options.AutoWall_MinDamage_Autos, 0, 100);
						ImGui::SliderFloat("Hitchance", &g_Options.AutoWall_Hitchance_Autos, 0, 100);
					}

					ImGui::NewLine();
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "AntiAim");
					ImGui::Checkbox("Anti Aim", &g_Options.DeSync);
					ImGui::Combo("AA Yaw:", &g_Options.AntiAimTypeYaw, AATypeYaw, IM_ARRAYSIZE(AATypeYaw));
					if (g_Options.AntiAimTypeYaw == 0) {
						ImGui::SliderFloat("Yaw", &g_Options.DeSyncValue, -180, 180);
						ImGui::SliderFloat("Pitch", &g_Options.DeSyncValue2, -89, 89);
					}
					else if (g_Options.AntiAimTypeYaw == 1) {
						ImGui::SliderFloat("Legit AA side", &g_Options.DeSyncValue2, -1, 1);
						ImGui::SliderFloat("yaw", &g_Options.DeSyncValue, -180.0f, 180.0f);
					}
					
					/*ImGui::Combo("AA Yaw:", &g_Options.AntiAimTypeYaw, AATypeYaw, IM_ARRAYSIZE(AATypeYaw));
					if (g_Options.AntiAimTypeYaw == 0) {
						ImGui::SliderInt("Legit AA side", &antiaim.LegitAASide, -1, 1);
						ImGui::SliderFloat("AA yaw", &g_Options.DeSyncValue, -180.0f, 180.0f);
						ImGui::SliderFloat("LBY yaw", &g_Options.DeSyncValue2, -180.0f, 180.0f);
					}
					if (g_Options.AntiAimTypeYaw == 1) {
						ImGui::SliderInt("Spinbot Speed:", &g_Options.AntiAim_SpinBotSpeed, 1, 50);
					}
					if (g_Options.AntiAimTypeYaw == 7) {
						ImGui::SliderFloat("AA yaw", &g_Options.DeSyncValue, -180.0f, 180.0f);
					}*/
				}
				ImGui::EndChild();
			}
		}ImGui::EndChild();

	}
	ImGui::End();

	style.Colors[ImGuiCol_WindowBg] = ImColor(30, 30, 30, 255);
	ImGui::SetNextWindowPos(ImVec2(pos.x - 4, pos.y - 4));
	ImGui::Begin("borderr", NULL, ImVec2(848, 568), 1.f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoInputs |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
	{

	}ImGui::End();
}

void Menu::Toggle()
{
	_visible = !_visible;
}