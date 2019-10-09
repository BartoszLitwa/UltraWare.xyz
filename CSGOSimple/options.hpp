#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include "valve_sdk/Misc/Color.hpp"

#include <filesystem>

#define A( s ) #s
#define OPTION(type, var, val) Var<type> var = {A(var), val}

template <typename T = bool>
class Var {
public:
	std::string name;
	std::shared_ptr<T> value;
	int32_t size;
	Var(std::string name, T v) : name(name) {
		value = std::make_shared<T>(v);
		size = sizeof(T);
	}
	operator T() { return *value; }
	operator T*() { return &*value; }
	operator T() const { return *value; }
	//operator T*() const { return value; }
};

class Options
{
public:
		// 
		// ESP
		// 
		bool esp_enabled = true;
		bool esp_localplayer = false;
		bool esp_enemies_only = false;
		bool esp_player_boxes = true;
		bool esp_player_skeleton = true;
		bool esp_player_names = true;
		bool esp_player_health = true;
		bool esp_player_armour = false;
		bool esp_player_weapons = true;
		bool esp_player_snaplines = false;
		bool esp_crosshair = false;
		bool esp_dropped_weapons = true;
		bool esp_defuse_kit = false;
		bool esp_planted_c4 = false;
		bool esp_items = false;
		bool esp_footstep = false;
		bool esp_footstep_enemies_only = true;
		Color esp_footstep_color = Color(255,255,255,255);

		// 
		// GLOW
		// 
		bool glow_enabled = true;
		bool glow_localplayer = false;
		bool glow_enemies_only = false;
		bool glow_players = false;
		bool glow_chickens = false;
		bool glow_c4_carrier = false;
		bool glow_planted_c4 = false;
		bool glow_defuse_kits = false;
		bool glow_weapons = false;

		//
		// CHAMS
		//
		bool chams_player_enabled = true;
		bool chams_localplayer = true;
		bool chams_Disable_Model_Occulusion = false;
		bool chams_player_enemies_only = false;
		bool chams_player_wireframe = false;
		bool chams_player_flat = false;
		bool chams_player_ignorez = true;
		bool chams_player_glass = false;

		bool chams_arms_enabled = true;
		bool chams_arms_wireframe = false;
		bool chams_arms_flat = false;
		bool chams_arms_ignorez = false;
		bool chams_arms_glass = false;

		bool chams_weapons_enabled = true;
		bool chams_weapons_wireframe = false;
		bool chams_weapons_flat = false;
		bool chams_weapons_ignorez = false;
		bool chams_weapons_glass = false;

		//
		//Aimbot Pistols
		//
		bool Aimbot_Aimbot_Pistols = true;
		bool Aimbot_Silent_Pistols = true;
		bool Aimbot_IgnoreWhenJumping_Pistols = false;
		bool Aimbot_IgnoreWhenFlashed_Pistols = false;
		bool Aimbot_VisibilityCheck_Pistols = true;
		bool Aimbot_RecoilPrediction_Pistols = true;
		bool Aimbot_Smoothing_Pistols = true;
		bool Aimbot_AutoScope_Pistols = true;
		bool Aimbot_AutoStop_Pistols = true;
		bool Aimbot_AutoCrouch_Pistols = true;
		int Aimbot_Hitbox_Pistols = 0;
		float Aimbot_FOV_Pistols = 10;
		float Aimbot_SilentFOV_Pistols = 10;
		bool Aimbot_ShowFOV_Pistols = true;
		float Aimbot_SmoothAmount_Pistols = 0;
		//
		// Triggerbot Pistols
		//
		bool TriggerBot_TriggerBot_Pistols = true;
		int TriggerBot_Delay_Pistols = 0;
		bool TriggerBot_Backtrack_Pistols = false;
		int TriggerBot_HitBox_Pistols = 0;
		float TriggerBot_HitChance_Pistols = 50.f;

		//
		//Aimbot Rifles
		//
		bool Aimbot_Aimbot_Rifles = true;
		bool Aimbot_Silent_Rifles = true;
		bool Aimbot_IgnoreWhenJumping_Rifles = false;
		bool Aimbot_IgnoreWhenFlashed_Rifles = false;
		bool Aimbot_VisibilityCheck_Rifles = true;
		bool Aimbot_RecoilPrediction_Rifles = true;
		bool Aimbot_Smoothing_Rifles = true;
		bool Aimbot_AutoScope_Rifles = true;
		bool Aimbot_AutoStop_Rifles = true;
		bool Aimbot_AutoCrouch_Rifles = true;
		int Aimbot_Hitbox_Rifles = 0;
		float Aimbot_FOV_Rifles = 10;
		float Aimbot_SilentFOV_Rifles = 10;
		bool Aimbot_ShowFOV_Rifles = true;
		float Aimbot_SmoothAmount_Rifles = 0;
		//
		// Triggerbot Rifles
		//
		bool TriggerBot_TriggerBot_Rifles = true;
		int TriggerBot_Delay_Rifles = 0;
		bool TriggerBot_Backtrack_Rifles = false;
		int TriggerBot_HitBox_Rifles = 0;
		float TriggerBot_HitChance_Rifles = 50.f;

		//
		//Aimbot SMG
		//
		bool Aimbot_Aimbot_SMG = true;
		bool Aimbot_Silent_SMG = true;
		bool Aimbot_IgnoreWhenJumping_SMG = false;
		bool Aimbot_IgnoreWhenFlashed_SMG = false;
		bool Aimbot_VisibilityCheck_SMG = true;
		bool Aimbot_RecoilPrediction_SMG = true;
		bool Aimbot_Smoothing_SMG = true;
		bool Aimbot_AutoScope_SMG = true;
		bool Aimbot_AutoStop_SMG = true;
		bool Aimbot_AutoCrouch_SMG = true;
		int Aimbot_Hitbox_SMG = 0;
		float Aimbot_FOV_SMG = 10;
		float Aimbot_SilentFOV_SMG = 10;
		bool Aimbot_ShowFOV_SMG = true;
		float Aimbot_SmoothAmount_SMG = 0;
		//
		// Triggerbot SMG
		//
		bool TriggerBot_TriggerBot_SMG = true;
		int TriggerBot_Delay_SMG = 0;
		bool TriggerBot_Backtrack_SMG = false;
		int TriggerBot_HitBox_SMG = 0;
		float TriggerBot_HitChance_SMG = 50.f;

		//
		//Aimbot Shotguns
		//
		bool Aimbot_Aimbot_Shotguns = true;
		bool Aimbot_Silent_Shotguns = true;
		bool Aimbot_IgnoreWhenJumping_Shotguns = false;
		bool Aimbot_IgnoreWhenFlashed_Shotguns = false;
		bool Aimbot_VisibilityCheck_Shotguns = true;
		bool Aimbot_RecoilPrediction_Shotguns = true;
		bool Aimbot_Smoothing_Shotguns = true;
		bool Aimbot_AutoScope_Shotguns = true;
		bool Aimbot_AutoStop_Shotguns = true;
		bool Aimbot_AutoCrouch_Shotguns = true;
		int Aimbot_Hitbox_Shotguns = 0;
		float Aimbot_FOV_Shotguns = 10;
		float Aimbot_SilentFOV_Shotguns = 10;
		bool Aimbot_ShowFOV_Shotguns = true;
		float Aimbot_SmoothAmount_Shotguns = 0;
		//
		// Triggerbot Shotguns
		//
		bool TriggerBot_TriggerBot_Shotguns = true;
		int TriggerBot_Delay_Shotguns = 0;
		bool TriggerBot_Backtrack_Shotguns = false;
		int TriggerBot_HitBox_Shotguns = 0;
		float TriggerBot_HitChance_Shotguns = 50.f;

		//
		//Aimbot AWP
		//
		bool Aimbot_Aimbot_AWP = true;
		bool Aimbot_Silent_AWP = true;
		bool Aimbot_IgnoreWhenJumping_AWP = false;
		bool Aimbot_IgnoreWhenFlashed_AWP = false;
		bool Aimbot_VisibilityCheck_AWP = true;
		bool Aimbot_RecoilPrediction_AWP = true;
		bool Aimbot_Smoothing_AWP = true;
		bool Aimbot_AutoScope_AWP = true;
		bool Aimbot_AutoStop_AWP = true;
		bool Aimbot_AutoCrouch_AWP = true;
		int Aimbot_Hitbox_AWP = 0;
		float Aimbot_FOV_AWP = 10;
		float Aimbot_SilentFOV_AWP = 10;
		bool Aimbot_ShowFOV_AWP = true;
		float Aimbot_SmoothAmount_AWP = 0;
		//
		// Triggerbot AWP
		//
		bool TriggerBot_TriggerBot_AWP = true;
		int TriggerBot_Delay_AWP = 0;
		bool TriggerBot_Backtrack_AWP = false;
		int TriggerBot_HitBox_AWP = 0;
		float TriggerBot_HitChance_AWP = 50.f;

		//
		//Aimbot SSG08
		//
		bool Aimbot_Aimbot_SSG08 = true;
		bool Aimbot_Silent_SSG08 = true;
		bool Aimbot_IgnoreWhenJumping_SSG08 = false;
		bool Aimbot_IgnoreWhenFlashed_SSG08 = false;
		bool Aimbot_VisibilityCheck_SSG08 = true;
		bool Aimbot_RecoilPrediction_SSG08 = true;
		bool Aimbot_Smoothing_SSG08 = true;
		bool Aimbot_AutoScope_SSG08 = true;
		bool Aimbot_AutoStop_SSG08 = true;
		bool Aimbot_AutoCrouch_SSG08 = true;
		int Aimbot_Hitbox_SSG08 = 0;
		float Aimbot_FOV_SSG08 = 10;
		float Aimbot_SilentFOV_SSG08 = 10;
		bool Aimbot_ShowFOV_SSG08 = true;
		float Aimbot_SmoothAmount_SSG08 = 0;
		//
		// Triggerbot SSG08
		//
		bool TriggerBot_TriggerBot_SSG08 = true;
		int TriggerBot_Delay_SSG08 = 0;
		bool TriggerBot_Backtrack_SSG08 = false;
		int TriggerBot_HitBox_SSG08 = 0;
		float TriggerBot_HitChance_SSG08 = 50.f;

		//
		//Aimbot Autos
		//
		bool Aimbot_Aimbot_Autos = true;
		bool Aimbot_Silent_Autos = true;
		bool Aimbot_IgnoreWhenJumping_Autos = false;
		bool Aimbot_IgnoreWhenFlashed_Autos = false;
		bool Aimbot_VisibilityCheck_Autos = true;
		bool Aimbot_RecoilPrediction_Autos = true;
		bool Aimbot_Smoothing_Autos = true;
		bool Aimbot_AutoScope_Autos = true;
		bool Aimbot_AutoStop_Autos = true;
		bool Aimbot_AutoCrouch_Autos = true;
		int Aimbot_Hitbox_Autos = 0;
		float Aimbot_FOV_Autos = 10;
		float Aimbot_SilentFOV_Autos = 10;
		bool Aimbot_ShowFOV_Autos = true;
		float Aimbot_SmoothAmount_Autos = 0;
		//
		// Triggerbot Autos
		//
		bool TriggerBot_TriggerBot_Autos = true;
		int TriggerBot_Delay_Autos = 0;
		bool TriggerBot_Backtrack_Autos = false;
		int TriggerBot_HitBox_Autos = 0;
		float TriggerBot_HitChance_Autos = 50.f;

		//
		//Backtrack
		//
		bool BackTrack_BackTrack = true;
		bool BackTrack_RecoilBasedFov = true;
		bool BackTrack_ignoreSmoke = false;
		int BackTrack_Ticks = 12;
		bool esp_player_BackTrackTicks = false;
		bool BackTrack_Chams = false;
		bool BackTrack_Chams_LastTick = false;
		Color BackTrack_Chams_color = Color(189, 195, 199, 1);

		//
		//SkinChanger
		//
		bool SkinChanger_SkinChanger = false;
		int SkinChanger_Skin = 100;
		float SkinChanger_Wear = 0.00001;
		int SkinChanger_Stattrak = -1;
		float SkinChanger_Seed = 1;
		int WEAPON_DEAGLE = 0;
		int WEAPON_ELITE = 0;
		int WEAPON_FIVESEVEN = 0;
		int WEAPON_GLOCK = 0;
		int WEAPON_AK47 = 0;
		int WEAPON_AUG = 0;
		int WEAPON_AWP = 0;
		int WEAPON_FAMAS = 0;
		int WEAPON_G3SG1 = 0;
		int WEAPON_GALILAR = 0;
		int WEAPON_M249 = 0;
		int WEAPON_M4A1 = 0;
		int WEAPON_MAC10 = 0;
		int WEAPON_P90 = 0;
		int WEAPON_MP5 = 0;
		int WEAPON_UMP45 = 0;
		int WEAPON_XM1014 = 0;
		int WEAPON_BIZON = 0;
		int WEAPON_MAG7 = 0;
		int WEAPON_NEGEV = 0;
		int WEAPON_SAWEDOFF = 0;
		int WEAPON_HKP2000 = 0;
		int WEAPON_MP7 = 0;
		int WEAPON_MP9 = 0;
		int WEAPON_NOVA = 0;
		int WEAPON_P250 = 0;
		int WEAPON_SCAR20 = 0;
		int WEAPON_SG556 = 0;
		int WEAPON_SSG08 = 0;
		int WEAPON_M4A1_SILENCER = 0;
		int WEAPON_USP_SILENCER = 0;
		int WEAPON_CZ75A = 0;
		int WEAPON_REVOLVER = 0;

		//CT
		bool SkinChanger_KnifeChangerCT = false;
		int KnifeCT = 507;
		int WEAPON_KNIFECT = 0;
		int KNIFE_SKINCT = 0;
		float KNIFE_WearCT = 0.00001;
		int KNIFE_StattrakCT = -1;
		float KNIFE_SeedCT = 1;

		//T
		bool SkinChanger_KnifeChangerT = false;
		int KnifeT = 507;
		int WEAPON_KNIFET = 0;
		int KNIFE_SKINT = 0;
		float KNIFE_WearT = 0.00001;
		int KNIFE_StattrakT = -1;
		float KNIFE_SeedT = 1;

		bool SkinChanger_GloveChanger = false;
		int GLOVE_MODEL = 5033;
		int GLOVE_SKIN = 1027;
		float GLOVE_WEAR = 0.00001f;

		//
		// MISC
		//
		int misc_Fov = 90;
		bool misc_bhop = true;
		bool misc_AutoStrafe = false;
		bool misc_FakePing= false;
		bool misc_FakePingIgnoreBacktrack = false;
		int misc_FakePingAmount = 100;
		bool misc_FakeLag = false;
		int misc_FakeLagStandingAmount = 0;
		int misc_FakeLagMovingAmount = 0;
		int misc_FakeLagInAirAmount = 0;
		bool misc_no_hands = false;
		bool misc_thirdperson = false;
		bool misc_showranks = true;
		bool misc_AutoAccept = true;
		bool misc_watermark = false;
		float misc_thirdperson_dist = 150.f;
		int viewmodel_fov = 68;
		float mat_ambient_light_r = 0.0f;
		float mat_ambient_light_g = 0.0f;
		float mat_ambient_light_b = 0.0f;
		bool misc_NightMode = true;
		bool misc_NoFlash = true;
		bool misc_NoSmoke = false;
		bool misc_Radar = true;
		bool misc_UnlimitedDuck = true;
		bool misc_RemoveScope = false;
		int misc_SkyBox = 0;
		bool misc_SpotMarkers = true;
		bool misc_SpotMarkersShow = true;
		bool misc_WalkBot = false;
		bool misc_BuyBot = false;
		int misc_BuyBot_Primary = 0;
		int misc_BuyBot_Secondary = 0;
		bool misc_BuyBot_Kevlar = true;
		bool misc_BuyBot_Grenades = false;
		bool misc_BuyBot_Defuser = true;
		bool misc_BuyBot_Taser = false;
		bool misc_Hitmarker = true;
		int misc_HitmarkerMode = 1;
		int misc_HitmarkerSound = 0;
		int misc_HitmarkerSize = 10;
		int misc_HitmarkerDuration = 1500;
		Color misc_Hitmarker_color = Color(255, 255, 255, 255);
		bool misc_LogEvents = true;
		bool misc_LogEvents_Damage = true;
		bool misc_LogEvents_ItemsPurchase = true;
		bool misc_LogEvents_Bomb = true;
		Color misc_LogEvents_color = Color(255, 255, 255, 255);
		bool misc_ChatSpam = true;
		int misc_ChatSpamKill = 0;
		int misc_ChatSpamDeath = 0;
		bool misc_AntiKick = true;
		bool misc_InverseRagdollGravity = false;
		bool misc_spectatorsList = false;
		bool misc_spectatorsListOnlyMe = false;
		Color misc_spectatorsList_color = Color(255, 255, 255, 120);
		bool misc_DisablePostProcess = true;
		bool misc_ClanTag = false;
		int misc_ClanTagClan = 0;
		std::string misc_ClanTagName = "UltraWare.xyz";
		bool misc_edgejump = true;
		bool misc_grenadeTrajectory = false;
		bool misc_AsusWalls = false;
		int misc_AsusWallsInt = 0;
		float misc_AsusWallsAlpha = 0.5f;

		//
		//Rage AutoWall
		//
		bool AutoWall_ShowDamage = false;
		//Pistols
		bool AutoWall_AutoWall_Pistols = false;
		bool AutoWall_BackTrack_Pistols = false;
		int AutoWall_Hitbox_Pistols = 0;
		float AutoWall_MinDamage_Pistols = 10;
		float AutoWall_Hitchance_Pistols = 50;
		//Rifles
		bool AutoWall_AutoWall_Rifles = false;
		bool AutoWall_BackTrack_Rifles = false;
		int AutoWall_Hitbox_Rifles = 0;
		float AutoWall_MinDamage_Rifles = 10;
		float AutoWall_Hitchance_Rifles = 50;
		//SMG
		bool AutoWall_AutoWall_SMG = false;
		bool AutoWall_BackTrack_SMG = false;
		int AutoWall_Hitbox_SMG = 0;
		float AutoWall_MinDamage_SMG = 10;
		float AutoWall_Hitchance_SMG = 50;
		//ShotGuns
		bool AutoWall_AutoWall_ShotGuns = false;
		bool AutoWall_BackTrack_ShotGuns = false;
		int AutoWall_Hitbox_ShotGuns = 0;
		float AutoWall_MinDamage_ShotGuns = 10;
		float AutoWall_Hitchance_ShotGuns = 50;
		//SSG08
		bool AutoWall_AutoWall_SSG08 = false;
		bool AutoWall_BackTrack_SSG08 = false;
		int AutoWall_Hitbox_SSG08 = 0;
		float AutoWall_MinDamage_SSG08 = 10;
		float AutoWall_Hitchance_SSG08 = 50;
		//AWP
		bool AutoWall_AutoWall_AWP = false;
		bool AutoWall_BackTrack_AWP = false;
		int AutoWall_Hitbox_AWP = 0;
		float AutoWall_MinDamage_AWP = 10;
		float AutoWall_Hitchance_AWP = 50;
		//Autos
		bool AutoWall_AutoWall_Autos = false;
		bool AutoWall_BackTrack_Autos = false;
		int AutoWall_Hitbox_Autos = 0;
		float AutoWall_MinDamage_Autos = 10;
		float AutoWall_Hitchance_Autos = 50;

		//
		//AntiAim
		//
		bool DeSync;
		float DeSyncValue;
		float DeSyncValue2;
		int AntiAimTypeYaw;
		int AntiAim_SpinBotSpeed;

		// 
		// COLORS
		// 
		Color color_esp_ally_visible = Color(0, 128, 255);
		Color color_esp_enemy_visible = Color(255, 0, 0);
		Color color_esp_ally_occluded = Color(0, 128, 255);
		Color color_esp_enemy_occluded = Color(255, 0, 0);
		Color color_esp_crosshair = Color(255, 255, 255);
		Color color_esp_weapons = Color(128, 0, 128);
		Color color_esp_defuse = Color(0, 128, 255);
		Color color_esp_c4 = Color(0, 255, 0);
		Color color_esp_item = Color(255, 255, 255);
			  
		Color color_glow_ally = Color(0, 128, 255);
		Color color_glow_enemy = Color(255, 0, 0);
		Color color_glow_chickens = Color(0, 128, 0);
		Color color_glow_c4_carrier = Color(255, 255, 0);
		Color color_glow_planted_c4 = Color(128, 0, 128);
		Color color_glow_defuse = Color(255, 255, 255);
		Color color_glow_weapons = Color(255, 128, 0);
			  
		Color color_chams_player_ally_visible = Color(0, 128, 255);
		Color color_chams_player_ally_occluded = Color(0, 255, 128);
		Color color_chams_player_enemy_visible = Color(255, 0, 0);
		Color color_chams_player_enemy_occluded = Color(255, 128, 0);
		Color color_chams_arms_visible = Color(0, 128, 255);
		Color color_chams_arms_occluded = Color(0, 128, 255);
		Color color_chams_weapons_visible = Color(0, 128, 255);
		Color color_chams_weapons_occluded = Color(0, 128, 255);
		Color color_watermark = Color(0, 255, 0); // no menu config cuz its useless
};

class SaveLoadConfigs {
public:
	static void Save(const char Name[], Options CV)
	{
		CreateDirectoryA("C:\\Cheat", 0);
		char FilePath[200];   // array to hold the result.
		char one[] = "C:\\Cheat\\";
		char three[] = ".ini";
		strcpy(FilePath, one); // copy string one into the result.
		strcat(FilePath, Name); // append string two to the result.
		strcat(FilePath, three); // append string two to the result.

		WriteBool("Visuals", "esp_enabled", CV.esp_enabled, FilePath);
		WriteBool("Visuals", "esp_localplayer", CV.esp_localplayer, FilePath);
		WriteBool("Visuals", "esp_enemies_only", CV.esp_enemies_only, FilePath);
		WriteBool("Visuals", "esp_player_boxes", CV.esp_player_boxes, FilePath);
		WriteBool("Visuals", "esp_player_skeleton", CV.esp_player_skeleton, FilePath);
		WriteBool("Visuals", "esp_player_names", CV.esp_player_names, FilePath);
		WriteBool("Visuals", "esp_player_health", CV.esp_player_health, FilePath);
		WriteBool("Visuals", "esp_player_armour", CV.esp_player_armour, FilePath);
		WriteBool("Visuals", "esp_player_weapons", CV.esp_player_weapons, FilePath);
		WriteBool("Visuals", "esp_player_snaplines", CV.esp_player_snaplines, FilePath);
		WriteBool("Visuals", "esp_crosshair", CV.esp_crosshair, FilePath);
		WriteBool("Visuals", "esp_dropped_weapons", CV.esp_dropped_weapons, FilePath);
		WriteBool("Visuals", "esp_defuse_kit", CV.esp_defuse_kit, FilePath);
		WriteBool("Visuals", "esp_planted_c4", CV.esp_planted_c4, FilePath);
		WriteBool("Visuals", "esp_items Only", CV.esp_items, FilePath);
		WriteBool("Visuals", "esp_footstep", CV.esp_footstep, FilePath);
		WriteBool("Visuals", "esp_footstep_enemies_only Only", CV.esp_footstep_enemies_only, FilePath);

		WriteBool("Glow", "glow_enabled", CV.glow_enabled, FilePath);
		WriteBool("Glow", "glow_localplayer", CV.glow_localplayer, FilePath);
		WriteBool("Glow", "glow_enemies_only", CV.glow_enemies_only, FilePath);
		WriteBool("Glow", "glow_players", CV.glow_players, FilePath);
		WriteBool("Glow", "glow_chickens", CV.glow_chickens, FilePath);
		WriteBool("Glow", "glow_c4_carrier", CV.glow_c4_carrier, FilePath);
		WriteBool("Glow", "glow_planted_c4", CV.glow_planted_c4, FilePath);
		WriteBool("Glow", "glow_defuse_kits", CV.glow_defuse_kits, FilePath);
		WriteBool("Glow", "glow_weapons", CV.glow_weapons, FilePath);

		WriteBool("Chams", "chams_player_enabled", CV.chams_player_enabled, FilePath);
		WriteBool("Chams", "chams_localplayer", CV.chams_localplayer, FilePath);
		WriteBool("Chams", "chams_Disable_Model_Occulusion", CV.chams_Disable_Model_Occulusion, FilePath);
		WriteBool("Chams", "chams_player_enemies_only", CV.chams_player_enemies_only, FilePath);
		WriteBool("Chams", "chams_player_wireframe", CV.chams_player_wireframe, FilePath);
		WriteBool("Chams", "chams_player_flat", CV.chams_player_flat, FilePath);
		WriteBool("Chams", "chams_player_ignorez", CV.chams_player_ignorez, FilePath);
		WriteBool("Chams", "chams_player_glass", CV.chams_player_glass, FilePath);
		WriteBool("Chams", "chams_arms_enabled", CV.chams_arms_enabled, FilePath);
		WriteBool("Chams", "chams_arms_wireframe", CV.chams_arms_wireframe, FilePath);
		WriteBool("Chams", "chams_arms_flat", CV.chams_arms_flat, FilePath);
		WriteBool("Chams", "chams_arms_ignorez", CV.chams_arms_ignorez, FilePath);
		WriteBool("Chams", "chams_arms_glass", CV.chams_arms_glass, FilePath);
		WriteBool("Chams", "chams_weapons_enabled", CV.chams_weapons_enabled, FilePath);
		WriteBool("Chams", "chams_weapons_wireframe", CV.chams_weapons_wireframe, FilePath);
		WriteBool("Chams", "chams_weapons_flat", CV.chams_weapons_flat, FilePath);
		WriteBool("Chams", "chams_weapons_ignorez", CV.chams_weapons_ignorez, FilePath);
		WriteBool("Chams", "chams_weapons_glass", CV.chams_weapons_glass, FilePath);

		//pistols
		WriteBool("Aimbot", "Aimbot_Aimbot_Pistols", CV.Aimbot_Aimbot_Pistols, FilePath);
		WriteBool("Aimbot", "Aimbot_Silent_Pistols", CV.Aimbot_Silent_Pistols, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenJumping_Pistols", CV.Aimbot_IgnoreWhenJumping_Pistols, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenFlashed_Pistols", CV.Aimbot_IgnoreWhenFlashed_Pistols, FilePath);
		WriteBool("Aimbot", "Aimbot_VisibilityCheck_Pistols", CV.Aimbot_VisibilityCheck_Pistols, FilePath);
		WriteBool("Aimbot", "Aimbot_RecoilPrediction_Pistols", CV.Aimbot_RecoilPrediction_Pistols, FilePath);
		WriteBool("Aimbot", "Aimbot_Smoothing_Pistols", CV.Aimbot_Smoothing_Pistols, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoScope_Pistols", CV.Aimbot_AutoScope_Pistols, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoStop_Pistols", CV.Aimbot_AutoStop_Pistols, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoCrouch_Pistols", CV.Aimbot_AutoCrouch_Pistols, FilePath);
		WriteInt("Aimbot", "Aimbot_Hitbox_Pistols", CV.Aimbot_Hitbox_Pistols, FilePath);
		WriteFloat("Aimbot", "Aimbot_FOV_Pistols", CV.Aimbot_FOV_Pistols, FilePath);
		WriteFloat("Aimbot", "Aimbot_SilentFOV_Pistols", CV.Aimbot_SilentFOV_Pistols, FilePath);
		WriteBool("Aimbot", "Aimbot_ShowFOV_Pistols", CV.Aimbot_ShowFOV_Pistols, FilePath);
		WriteFloat("Aimbot", "Aimbot_SmoothAmount_Pistols", CV.Aimbot_SmoothAmount_Pistols, FilePath);
		WriteBool("TriggerBot", "TriggerBot_TriggerBot_Pistols", CV.TriggerBot_TriggerBot_Pistols, FilePath);
		WriteInt("TriggerBot", "TriggerBot_Delay_Pistols", CV.TriggerBot_Delay_Pistols, FilePath);
		WriteBool("TriggerBot", "TriggerBot_Backtrack_Pistols", CV.TriggerBot_Backtrack_Pistols, FilePath);
		WriteInt("TriggerBot", "TriggerBot_HitBox_Pistols", CV.TriggerBot_HitBox_Pistols, FilePath);
		WriteFloat("TriggerBot", "TriggerBot_HitChance_Pistols", CV.TriggerBot_HitChance_Pistols, FilePath);

		//rifles
		WriteBool("Aimbot", "Aimbot_Aimbot_Rifles", CV.Aimbot_Aimbot_Rifles, FilePath);
		WriteBool("Aimbot", "Aimbot_Silent_Rifles", CV.Aimbot_Silent_Rifles, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenJumping_Rifles", CV.Aimbot_IgnoreWhenJumping_Rifles, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenFlashed_Rifles", CV.Aimbot_IgnoreWhenFlashed_Rifles, FilePath);
		WriteBool("Aimbot", "Aimbot_VisibilityCheck_Rifles", CV.Aimbot_VisibilityCheck_Rifles, FilePath);
		WriteBool("Aimbot", "Aimbot_RecoilPrediction_Rifles", CV.Aimbot_RecoilPrediction_Rifles, FilePath);
		WriteBool("Aimbot", "Aimbot_Smoothing_Rifles", CV.Aimbot_Smoothing_Rifles, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoScope_Rifles", CV.Aimbot_AutoScope_Rifles, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoStop_Rifles", CV.Aimbot_AutoStop_Rifles, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoCrouch_Rifles", CV.Aimbot_AutoCrouch_Rifles, FilePath);
		WriteInt("Aimbot", "Aimbot_Hitbox_Rifles", CV.Aimbot_Hitbox_Rifles, FilePath);
		WriteFloat("Aimbot", "Aimbot_FOV_Rifles", CV.Aimbot_FOV_Rifles, FilePath);
		WriteFloat("Aimbot", "Aimbot_SilentFOV_Rifles", CV.Aimbot_SilentFOV_Rifles, FilePath);
		WriteBool("Aimbot", "Aimbot_ShowFOV_Rifles", CV.Aimbot_ShowFOV_Rifles, FilePath);
		WriteFloat("Aimbot", "Aimbot_SmoothAmount_Rifles", CV.Aimbot_SmoothAmount_Rifles, FilePath);
		WriteBool("TriggerBot", "TriggerBot_TriggerBot_Rifles", CV.TriggerBot_TriggerBot_Rifles, FilePath);
		WriteInt("TriggerBot", "TriggerBot_Delay_Rifles", CV.TriggerBot_Delay_Rifles, FilePath);
		WriteBool("TriggerBot", "TriggerBot_Backtrack_Rifles", CV.TriggerBot_Backtrack_Rifles, FilePath);
		WriteInt("TriggerBot", "TriggerBot_HitBox_Rifles", CV.TriggerBot_HitBox_Rifles, FilePath);
		WriteFloat("TriggerBot", "TriggerBot_HitChance_Rifles", CV.TriggerBot_HitChance_Rifles, FilePath);

		//smg
		WriteBool("Aimbot", "Aimbot_Aimbot_SMG", CV.Aimbot_Aimbot_SMG, FilePath);
		WriteBool("Aimbot", "Aimbot_Silent_SMG", CV.Aimbot_Silent_SMG, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenJumping_SMG", CV.Aimbot_IgnoreWhenJumping_SMG, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenFlashed_SMG", CV.Aimbot_IgnoreWhenFlashed_SMG, FilePath);
		WriteBool("Aimbot", "Aimbot_VisibilityCheck_SMG", CV.Aimbot_VisibilityCheck_SMG, FilePath);
		WriteBool("Aimbot", "Aimbot_RecoilPrediction_SMG", CV.Aimbot_RecoilPrediction_SMG, FilePath);
		WriteBool("Aimbot", "Aimbot_Smoothing_SMG", CV.Aimbot_Smoothing_SMG, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoScope_SMG", CV.Aimbot_AutoScope_SMG, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoStop_SMG", CV.Aimbot_AutoStop_SMG, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoCrouch_SMG", CV.Aimbot_AutoCrouch_SMG, FilePath);
		WriteInt("Aimbot", "Aimbot_Hitbox_SMG", CV.Aimbot_Hitbox_SMG, FilePath);
		WriteFloat("Aimbot", "Aimbot_FOV_SMG", CV.Aimbot_FOV_SMG, FilePath);
		WriteFloat("Aimbot", "Aimbot_SilentFOV_SMG", CV.Aimbot_SilentFOV_SMG, FilePath);
		WriteBool("Aimbot", "Aimbot_ShowFOV_SMG", CV.Aimbot_ShowFOV_SMG, FilePath);
		WriteFloat("Aimbot", "Aimbot_SmoothAmount_SMG", CV.Aimbot_SmoothAmount_SMG, FilePath);
		WriteBool("TriggerBot", "TriggerBot_TriggerBot_SMG", CV.TriggerBot_TriggerBot_SMG, FilePath);
		WriteInt("TriggerBot", "TriggerBot_Delay_SMG", CV.TriggerBot_Delay_SMG, FilePath);
		WriteBool("TriggerBot", "TriggerBot_Backtrack_SMG", CV.TriggerBot_Backtrack_SMG, FilePath);
		WriteInt("TriggerBot", "TriggerBot_HitBox_SMG", CV.TriggerBot_HitBox_SMG, FilePath);
		WriteFloat("TriggerBot", "TriggerBot_HitChance_SMG", CV.TriggerBot_HitChance_SMG, FilePath);

		//shotguns
		WriteBool("Aimbot", "Aimbot_Aimbot_Shotguns", CV.Aimbot_Aimbot_Shotguns, FilePath);
		WriteBool("Aimbot", "Aimbot_Silent_Shotguns", CV.Aimbot_Silent_Shotguns, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenJumping_Shotguns", CV.Aimbot_IgnoreWhenJumping_Shotguns, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenFlashed_Shotguns", CV.Aimbot_IgnoreWhenFlashed_Shotguns, FilePath);
		WriteBool("Aimbot", "Aimbot_VisibilityCheck_Shotguns", CV.Aimbot_VisibilityCheck_Shotguns, FilePath);
		WriteBool("Aimbot", "Aimbot_RecoilPrediction_Shotguns", CV.Aimbot_RecoilPrediction_Shotguns, FilePath);
		WriteBool("Aimbot", "Aimbot_Smoothing_Shotguns", CV.Aimbot_Smoothing_Shotguns, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoScope_Shotguns", CV.Aimbot_AutoScope_Shotguns, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoStop_Shotguns", CV.Aimbot_AutoStop_Shotguns, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoCrouch_Shotguns", CV.Aimbot_AutoCrouch_Shotguns, FilePath);
		WriteInt("Aimbot", "Aimbot_Hitbox_Shotguns", CV.Aimbot_Hitbox_Shotguns, FilePath);
		WriteFloat("Aimbot", "Aimbot_FOV_Shotguns", CV.Aimbot_FOV_Shotguns, FilePath);
		WriteFloat("Aimbot", "Aimbot_SilentFOV_Shotguns", CV.Aimbot_SilentFOV_Shotguns, FilePath);
		WriteBool("Aimbot", "Aimbot_ShowFOV_Shotguns", CV.Aimbot_ShowFOV_Shotguns, FilePath);
		WriteFloat("Aimbot", "Aimbot_SmoothAmount_Shotguns", CV.Aimbot_SmoothAmount_Shotguns, FilePath);
		WriteBool("TriggerBot", "TriggerBot_TriggerBot_Shotguns", CV.TriggerBot_TriggerBot_Shotguns, FilePath);
		WriteInt("TriggerBot", "TriggerBot_Delay_Shotguns", CV.TriggerBot_Delay_Shotguns, FilePath);
		WriteBool("TriggerBot", "TriggerBot_Backtrack_Shotguns", CV.TriggerBot_Backtrack_Shotguns, FilePath);
		WriteInt("TriggerBot", "TriggerBot_HitBox_Shotguns", CV.TriggerBot_HitBox_Shotguns, FilePath);
		WriteFloat("TriggerBot", "TriggerBot_HitChance_Shotguns", CV.TriggerBot_HitChance_Shotguns, FilePath);

		//awp
		WriteBool("Aimbot", "Aimbot_Aimbot_AWP", CV.Aimbot_Aimbot_AWP, FilePath);
		WriteBool("Aimbot", "Aimbot_Silent_AWP", CV.Aimbot_Silent_AWP, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenJumping_AWP", CV.Aimbot_IgnoreWhenJumping_AWP, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenFlashed_AWP", CV.Aimbot_IgnoreWhenFlashed_AWP, FilePath);
		WriteBool("Aimbot", "Aimbot_VisibilityCheck_AWP", CV.Aimbot_VisibilityCheck_AWP, FilePath);
		WriteBool("Aimbot", "Aimbot_RecoilPrediction_AWP", CV.Aimbot_RecoilPrediction_AWP, FilePath);
		WriteBool("Aimbot", "Aimbot_Smoothing_AWP", CV.Aimbot_Smoothing_AWP, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoScope_AWP", CV.Aimbot_AutoScope_AWP, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoStop_AWP", CV.Aimbot_AutoStop_AWP, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoCrouch_AWP", CV.Aimbot_AutoCrouch_AWP, FilePath);
		WriteInt("Aimbot", "Aimbot_Hitbox_AWP", CV.Aimbot_Hitbox_AWP, FilePath);
		WriteFloat("Aimbot", "Aimbot_FOV_AWP", CV.Aimbot_FOV_AWP, FilePath);
		WriteFloat("Aimbot", "Aimbot_SilentFOV_AWP", CV.Aimbot_SilentFOV_AWP, FilePath);
		WriteBool("Aimbot", "Aimbot_ShowFOV_AWP", CV.Aimbot_ShowFOV_AWP, FilePath);
		WriteFloat("Aimbot", "Aimbot_SmoothAmount_AWP", CV.Aimbot_SmoothAmount_AWP, FilePath);
		WriteBool("TriggerBot", "TriggerBot_TriggerBot_AWP", CV.TriggerBot_TriggerBot_AWP, FilePath);
		WriteInt("TriggerBot", "TriggerBot_Delay_AWP", CV.TriggerBot_Delay_AWP, FilePath);
		WriteBool("TriggerBot", "TriggerBot_Backtrack_AWP", CV.TriggerBot_Backtrack_AWP, FilePath);
		WriteInt("TriggerBot", "TriggerBot_HitBox_AWP", CV.TriggerBot_HitBox_AWP, FilePath);
		WriteFloat("TriggerBot", "TriggerBot_HitChance_AWP", CV.TriggerBot_HitChance_AWP, FilePath);

		//ssg08
		WriteBool("Aimbot", "Aimbot_Aimbot_SSG08", CV.Aimbot_Aimbot_SSG08, FilePath);
		WriteBool("Aimbot", "Aimbot_Silent_SSG08", CV.Aimbot_Silent_SSG08, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenJumping_SSG08", CV.Aimbot_IgnoreWhenJumping_SSG08, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenFlashed_SSG08", CV.Aimbot_IgnoreWhenFlashed_SSG08, FilePath);
		WriteBool("Aimbot", "Aimbot_VisibilityCheck_SSG08", CV.Aimbot_VisibilityCheck_SSG08, FilePath);
		WriteBool("Aimbot", "Aimbot_RecoilPrediction_SSG08", CV.Aimbot_RecoilPrediction_SSG08, FilePath);
		WriteBool("Aimbot", "Aimbot_Smoothing_SSG08", CV.Aimbot_Smoothing_SSG08, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoScope_SSG08", CV.Aimbot_AutoScope_SSG08, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoStop_SSG08", CV.Aimbot_AutoStop_SSG08, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoCrouch_SSG08", CV.Aimbot_AutoCrouch_SSG08, FilePath);
		WriteInt("Aimbot", "Aimbot_Hitbox_SSG08", CV.Aimbot_Hitbox_SSG08, FilePath);
		WriteFloat("Aimbot", "Aimbot_FOV_SSG08", CV.Aimbot_FOV_SSG08, FilePath);
		WriteFloat("Aimbot", "Aimbot_SilentFOV_SSG08", CV.Aimbot_SilentFOV_SSG08, FilePath);
		WriteBool("Aimbot", "Aimbot_ShowFOV_SSG08", CV.Aimbot_ShowFOV_SSG08, FilePath);
		WriteFloat("Aimbot", "Aimbot_SmoothAmount_SSG08", CV.Aimbot_SmoothAmount_SSG08, FilePath);
		WriteBool("TriggerBot", "TriggerBot_TriggerBot_SSG08", CV.TriggerBot_TriggerBot_SSG08, FilePath);
		WriteInt("TriggerBot", "TriggerBot_Delay_SSG08", CV.TriggerBot_Delay_SSG08, FilePath);
		WriteBool("TriggerBot", "TriggerBot_Backtrack_SSG08", CV.TriggerBot_Backtrack_SSG08, FilePath);
		WriteInt("TriggerBot", "TriggerBot_HitBox_SSG08", CV.TriggerBot_HitBox_SSG08, FilePath);
		WriteFloat("TriggerBot", "TriggerBot_HitChance_SSG08", CV.TriggerBot_HitChance_SSG08, FilePath);

		//autos
		WriteBool("Aimbot", "Aimbot_Aimbot_Autos", CV.Aimbot_Aimbot_Autos, FilePath);
		WriteBool("Aimbot", "Aimbot_Silent_Autos", CV.Aimbot_Silent_Autos, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenJumping_Autos", CV.Aimbot_IgnoreWhenJumping_Autos, FilePath);
		WriteBool("Aimbot", "Aimbot_IgnoreWhenFlashed_Autos", CV.Aimbot_IgnoreWhenFlashed_Autos, FilePath);
		WriteBool("Aimbot", "Aimbot_VisibilityCheck_Autos", CV.Aimbot_VisibilityCheck_Autos, FilePath);
		WriteBool("Aimbot", "Aimbot_RecoilPrediction_Autos", CV.Aimbot_RecoilPrediction_Autos, FilePath);
		WriteBool("Aimbot", "Aimbot_Smoothing_Autos", CV.Aimbot_Smoothing_Autos, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoScope_Autos", CV.Aimbot_AutoScope_Autos, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoStop_Autos", CV.Aimbot_AutoStop_Autos, FilePath);
		WriteBool("Aimbot", "Aimbot_AutoCrouch_Autos", CV.Aimbot_AutoCrouch_Autos, FilePath);
		WriteInt("Aimbot", "Aimbot_Hitbox_Autos", CV.Aimbot_Hitbox_Autos, FilePath);
		WriteFloat("Aimbot", "Aimbot_FOV_Autos", CV.Aimbot_FOV_Autos, FilePath);
		WriteFloat("Aimbot", "Aimbot_SilentFOV_Autos", CV.Aimbot_SilentFOV_Autos, FilePath);
		WriteBool("Aimbot", "Aimbot_ShowFOV_Autos", CV.Aimbot_ShowFOV_Autos, FilePath);
		WriteFloat("Aimbot", "Aimbot_SmoothAmount_Autos", CV.Aimbot_SmoothAmount_Autos, FilePath);
		WriteBool("TriggerBot", "TriggerBot_TriggerBot_Autos", CV.TriggerBot_TriggerBot_Autos, FilePath);
		WriteInt("TriggerBot", "TriggerBot_Delay_Autos", CV.TriggerBot_Delay_Autos, FilePath);
		WriteBool("TriggerBot", "TriggerBot_Backtrack_Autos", CV.TriggerBot_Backtrack_Autos, FilePath);
		WriteInt("TriggerBot", "TriggerBot_HitBox_Autos", CV.TriggerBot_HitBox_Autos, FilePath);
		WriteFloat("TriggerBot", "TriggerBot_HitChance_Autos", CV.TriggerBot_HitChance_Autos, FilePath);

		WriteBool("BackTrack", "BackTrack_BackTrack", CV.BackTrack_BackTrack, FilePath);
		WriteInt("BackTrack", "BackTrack_Ticks", CV.BackTrack_Ticks, FilePath);
		WriteBool("BackTrack", "esp_player_BackTrackTicks", CV.esp_player_BackTrackTicks, FilePath);
		WriteBool("BackTrack", "BackTrack_Chams", CV.BackTrack_Chams, FilePath);
		WriteBool("BackTrack", "BackTrack_Chams_LastTick", CV.BackTrack_Chams_LastTick, FilePath);
		WriteColor("BackTrack", "BackTrack_Chams_color", CV.BackTrack_Chams_color, FilePath);

		WriteInt("MISC", "misc_Fov", CV.misc_Fov, FilePath);
		WriteBool("MISC", "misc_bhop", CV.misc_bhop, FilePath);
		WriteBool("MISC", "misc_AutoStrafe", CV.misc_AutoStrafe, FilePath);
		WriteBool("MISC", "misc_FakePing", CV.misc_FakePing, FilePath);
		WriteBool("MISC", "misc_FakePingIgnoreBacktrack", CV.misc_FakePingIgnoreBacktrack, FilePath);
		WriteInt("MISC", "misc_FakePingAmount", CV.misc_FakePingAmount, FilePath);
		WriteBool("MISC", "misc_FakeLag", CV.misc_FakeLag, FilePath);
		WriteInt("MISC", "misc_FakeLagStandingAmount", CV.misc_FakeLagStandingAmount, FilePath);
		WriteInt("MISC", "misc_FakeLagMovingAmount", CV.misc_FakeLagMovingAmount, FilePath);
		WriteInt("MISC", "misc_FakeLagInAirAmount", CV.misc_FakeLagInAirAmount, FilePath);
		WriteBool("MISC", "misc_no_hands", CV.misc_no_hands, FilePath);
		WriteBool("MISC", "misc_thirdperson", CV.misc_thirdperson, FilePath);
		WriteFloat("MISC", "misc_thirdperson_dist", CV.misc_thirdperson_dist, FilePath);
		WriteBool("MISC", "misc_showranks", CV.misc_showranks, FilePath);
		WriteBool("MISC", "misc_AutoAccept", CV.misc_AutoAccept, FilePath);
		WriteBool("MISC", "misc_watermark", CV.misc_watermark, FilePath);
		WriteInt("MISC", "viewmodel_fov", CV.viewmodel_fov, FilePath);
		WriteFloat("MISC", "mat_ambient_light_r", CV.mat_ambient_light_r, FilePath);
		WriteFloat("MISC", "mat_ambient_light_g", CV.mat_ambient_light_g, FilePath);
		WriteFloat("MISC", "mat_ambient_light_b", CV.mat_ambient_light_b, FilePath);
		WriteBool("MISC", "misc_NightMode", CV.misc_NightMode, FilePath);
		WriteBool("MISC", "misc_NoFlash", CV.misc_NoFlash, FilePath);
		WriteBool("MISC", "misc_NoSmoke", CV.misc_NoSmoke, FilePath);
		WriteBool("MISC", "misc_Radar", CV.misc_Radar, FilePath);
		WriteBool("MISC", "misc_UnlimitedDuck", CV.misc_UnlimitedDuck, FilePath);
		WriteBool("MISC", "misc_RemoveScope", CV.misc_RemoveScope, FilePath);
		WriteInt("MISC", "misc_SkyBox", CV.misc_SkyBox, FilePath);
		WriteBool("MISC", "misc_SpotMarkers", CV.misc_SpotMarkers, FilePath);
		WriteBool("MISC", "misc_SpotMarkersShow", CV.misc_SpotMarkersShow, FilePath);
		WriteBool("MISC", "misc_WalkBot", CV.misc_WalkBot, FilePath);
		WriteBool("MISC", "misc_BuyBot", CV.misc_BuyBot, FilePath);
		WriteInt("MISC", "misc_BuyBot_Primary", CV.misc_BuyBot_Primary, FilePath);
		WriteInt("MISC", "misc_BuyBot_Secondary", CV.misc_BuyBot_Secondary, FilePath);
		WriteBool("MISC", "misc_BuyBot_Kevlar", CV.misc_BuyBot_Kevlar, FilePath);
		WriteBool("MISC", "misc_BuyBot_Grenades", CV.misc_BuyBot_Grenades, FilePath);
		WriteBool("MISC", "misc_BuyBot_Defuser", CV.misc_BuyBot_Defuser, FilePath);
		WriteBool("MISC", "misc_BuyBot_Taser", CV.misc_BuyBot_Taser, FilePath);
		WriteBool("MISC", "misc_Hitmarker", CV.misc_Hitmarker, FilePath);
		WriteInt("MISC", "misc_HitmarkerMode", CV.misc_HitmarkerMode, FilePath);
		WriteInt("MISC", "misc_HitmarkerSound", CV.misc_HitmarkerSound, FilePath);
		WriteInt("MISC", "misc_HitmarkerSize", CV.misc_HitmarkerSize, FilePath);
		WriteInt("MISC", "misc_HitmarkerDuration", CV.misc_HitmarkerDuration, FilePath);
		WriteColor("MISC", "misc_Hitmarker_color", CV.misc_Hitmarker_color, FilePath);
		WriteBool("MISC", "misc_LogEvents", CV.misc_LogEvents, FilePath);
		WriteBool("MISC", "misc_LogEvents_Damage", CV.misc_LogEvents_Damage, FilePath);
		WriteBool("MISC", "misc_LogEvents_ItemsPurchase", CV.misc_LogEvents_ItemsPurchase, FilePath);
		WriteBool("MISC", "misc_LogEvents_Bomb", CV.misc_LogEvents_Bomb, FilePath);
		WriteColor("MISC", "misc_LogEvents_color", CV.misc_LogEvents_color, FilePath);
		WriteBool("MISC", "misc_ChatSpam", CV.misc_ChatSpam, FilePath);
		WriteInt("MISC", "misc_ChatSpamKill", CV.misc_ChatSpamKill, FilePath);
		WriteInt("MISC", "misc_ChatSpamDeath", CV.misc_ChatSpamDeath, FilePath);
		WriteBool("MISC", "misc_AntiKick", CV.misc_AntiKick, FilePath);
		WriteBool("MISC", "misc_InverseRagdollGravity", CV.misc_InverseRagdollGravity, FilePath);
		WriteBool("MISC", "misc_spectatorsList", CV.misc_spectatorsList, FilePath);
		WriteBool("MISC", "misc_spectatorsListOnlyMe", CV.misc_spectatorsListOnlyMe, FilePath);
		WriteColor("MISC", "misc_spectatorsList_color", CV.misc_spectatorsList_color, FilePath);
		WriteBool("MISC", "misc_DisablePostProcess", CV.misc_DisablePostProcess, FilePath);
		WriteBool("MISC", "misc_ClanTag", CV.misc_ClanTag, FilePath);
		WriteInt("MISC", "misc_ClanTagClan", CV.misc_ClanTagClan, FilePath);
		//WriteString("MISC", "misc_ClanTagName", CV.misc_ClanTagName.c_str(), FilePath);
		WriteBool("MISC", "misc_edgejump", CV.misc_edgejump, FilePath);
		WriteBool("MISC", "misc_grenadeTrajectory", CV.misc_grenadeTrajectory, FilePath);
		WriteBool("MISC", "misc_AsusWalls", CV.misc_AsusWalls, FilePath);
		WriteInt("MISC", "misc_AsusWallsInt", CV.misc_AsusWallsInt, FilePath);
		WriteFloat("MISC", "misc_AsusWallsAlpha", CV.misc_AsusWallsAlpha, FilePath);

		WriteBool("SkinChanger", "SkinChanger_SkinChanger", CV.SkinChanger_SkinChanger, FilePath);
		WriteFloat("SkinChanger", "SkinChanger_Wear", CV.SkinChanger_Wear, FilePath);
		WriteInt("SkinChanger", "SkinChanger_Stattrak", CV.SkinChanger_Stattrak, FilePath);
		WriteFloat("SkinChanger", "SkinChanger_Seed", CV.SkinChanger_Seed, FilePath);
		WriteInt("SkinChanger", "WEAPON_DEAGLE", CV.WEAPON_DEAGLE, FilePath);
		WriteInt("SkinChanger", "WEAPON_ELITE", CV.WEAPON_ELITE, FilePath);
		WriteInt("SkinChanger", "WEAPON_FIVESEVEN", CV.WEAPON_FIVESEVEN, FilePath);
		WriteInt("SkinChanger", "WEAPON_GLOCK", CV.WEAPON_GLOCK, FilePath);
		WriteInt("SkinChanger", "WEAPON_AK47", CV.WEAPON_AK47, FilePath);
		WriteInt("SkinChanger", "WEAPON_AUG", CV.WEAPON_AUG, FilePath);
		WriteInt("SkinChanger", "WEAPON_AWP", CV.WEAPON_AWP, FilePath);
		WriteInt("SkinChanger", "WEAPON_FAMAS", CV.WEAPON_FAMAS, FilePath);
		WriteInt("SkinChanger", "WEAPON_G3SG1", CV.WEAPON_G3SG1, FilePath);
		WriteInt("SkinChanger", "WEAPON_GALILAR", CV.WEAPON_GALILAR, FilePath);
		WriteInt("SkinChanger", "WEAPON_M249", CV.WEAPON_M249, FilePath);
		WriteInt("SkinChanger", "WEAPON_M4A1", CV.WEAPON_M4A1, FilePath);
		WriteInt("SkinChanger", "WEAPON_MAC10", CV.WEAPON_MAC10, FilePath);
		WriteInt("SkinChanger", "WEAPON_P90", CV.WEAPON_P90, FilePath);
		WriteInt("SkinChanger", "WEAPON_MP5", CV.WEAPON_MP5, FilePath);
		WriteInt("SkinChanger", "WEAPON_UMP45", CV.WEAPON_UMP45, FilePath);
		WriteInt("SkinChanger", "WEAPON_XM1014", CV.WEAPON_XM1014, FilePath);
		WriteInt("SkinChanger", "WEAPON_BIZON", CV.WEAPON_BIZON, FilePath);
		WriteInt("SkinChanger", "WEAPON_MAG7", CV.WEAPON_MAG7, FilePath);
		WriteInt("SkinChanger", "WEAPON_NEGEV", CV.WEAPON_NEGEV, FilePath);
		WriteInt("SkinChanger", "WEAPON_SAWEDOFF", CV.WEAPON_SAWEDOFF, FilePath);
		WriteInt("SkinChanger", "WEAPON_HKP2000", CV.WEAPON_HKP2000, FilePath);
		WriteInt("SkinChanger", "WEAPON_MP7", CV.WEAPON_MP7, FilePath);
		WriteInt("SkinChanger", "WEAPON_MP9", CV.WEAPON_MP9, FilePath);
		WriteInt("SkinChanger", "WEAPON_NOVA", CV.WEAPON_NOVA, FilePath);
		WriteInt("SkinChanger", "WEAPON_P250", CV.WEAPON_P250, FilePath);
		WriteInt("SkinChanger", "WEAPON_SCAR20", CV.WEAPON_SCAR20, FilePath);
		WriteInt("SkinChanger", "WEAPON_SG556", CV.WEAPON_SG556, FilePath);
		WriteInt("SkinChanger", "WEAPON_SSG08", CV.WEAPON_SSG08, FilePath);
		WriteInt("SkinChanger", "WEAPON_M4A1_SILENCER", CV.WEAPON_M4A1_SILENCER, FilePath);
		WriteInt("SkinChanger", "WEAPON_USP_SILENCER", CV.WEAPON_USP_SILENCER, FilePath);
		WriteInt("SkinChanger", "WEAPON_CZ75A", CV.WEAPON_CZ75A, FilePath);
		WriteInt("SkinChanger", "WEAPON_REVOLVER", CV.WEAPON_REVOLVER, FilePath);

		//CT
		WriteBool("SkinChanger", "SkinChanger_KnifeChangerCT", CV.SkinChanger_KnifeChangerCT, FilePath);
		WriteInt("SkinChanger", "KnifeCT", CV.KnifeCT, FilePath);
		WriteInt("SkinChanger", "WEAPON_KNIFECT", CV.WEAPON_KNIFECT, FilePath);
		WriteInt("SkinChanger", "KNIFE_SKINCT", CV.KNIFE_SKINCT, FilePath);
		WriteFloat("SkinChanger", "KNIFE_WearCT", CV.KNIFE_WearCT, FilePath);
		WriteInt("SkinChanger", "KNIFE_StattrakCT", CV.KNIFE_StattrakCT, FilePath);
		WriteFloat("SkinChanger", "KNIFE_SeedCT", CV.KNIFE_SeedCT, FilePath);

		//T
		WriteBool("SkinChanger", "SkinChanger_KnifeChangerT", CV.SkinChanger_KnifeChangerT, FilePath);
		WriteInt("SkinChanger", "KnifeT", CV.KnifeT, FilePath);
		WriteInt("SkinChanger", "WEAPON_KNIFET", CV.WEAPON_KNIFET, FilePath);
		WriteInt("SkinChanger", "KNIFE_SKINT", CV.KNIFE_SKINT, FilePath);
		WriteFloat("SkinChanger", "KNIFE_WearT", CV.KNIFE_WearT, FilePath);
		WriteInt("SkinChanger", "KNIFE_StattrakT", CV.KNIFE_StattrakT, FilePath);
		WriteFloat("SkinChanger", "KNIFE_SeedT", CV.KNIFE_SeedT, FilePath);

		WriteBool("SkinChanger", "SkinChanger_GloveChanger", CV.SkinChanger_GloveChanger, FilePath);
		WriteInt("SkinChanger", "GLOVE_MODEL", CV.GLOVE_MODEL, FilePath);
		WriteInt("SkinChanger", "GLOVE_SKIN", CV.GLOVE_SKIN, FilePath);
		WriteFloat("SkinChanger", "GLOVE_WEAR", CV.GLOVE_WEAR, FilePath);

		WriteBool("Rage", "AutoWall_ShowDamage", CV.AutoWall_ShowDamage, FilePath);

		WriteBool("Rage", "AutoWall_AutoWall_Pistols", CV.AutoWall_AutoWall_Pistols, FilePath);
		WriteBool("Rage", "AutoWall_BackTrack_Pistols", CV.AutoWall_BackTrack_Pistols, FilePath);
		WriteInt("Rage", "AutoWall_Hitbox_Pistols", CV.AutoWall_Hitbox_Pistols, FilePath);
		WriteFloat("Rage", "AutoWall_MinDamage_Pistols", CV.AutoWall_MinDamage_Pistols, FilePath);
		WriteFloat("Rage", "AutoWall_Hitchance_Pistols", CV.AutoWall_Hitchance_Pistols, FilePath);

		WriteBool("Rage", "AutoWall_AutoWall_Rifles", CV.AutoWall_AutoWall_Rifles, FilePath);
		WriteBool("Rage", "AutoWall_BackTrack_Rifles", CV.AutoWall_BackTrack_Rifles, FilePath);
		WriteInt("Rage", "AutoWall_Hitbox_Rifles", CV.AutoWall_Hitbox_Rifles, FilePath);
		WriteFloat("Rage", "AutoWall_MinDamage_Rifles", CV.AutoWall_MinDamage_Rifles, FilePath);
		WriteFloat("Rage", "AutoWall_Hitchance_Rifles", CV.AutoWall_Hitchance_Rifles, FilePath);

		WriteBool("Rage", "AutoWall_AutoWall_SMG", CV.AutoWall_AutoWall_SMG, FilePath);
		WriteBool("Rage", "AutoWall_BackTrack_SMG", CV.AutoWall_BackTrack_SMG, FilePath);
		WriteInt("Rage", "AutoWall_Hitbox_SMG", CV.AutoWall_Hitbox_SMG, FilePath);
		WriteFloat("Rage", "AutoWall_MinDamage_SMG", CV.AutoWall_MinDamage_SMG, FilePath);
		WriteFloat("Rage", "AutoWall_Hitchance_SMG", CV.AutoWall_Hitchance_SMG, FilePath);

		WriteBool("Rage", "AutoWall_AutoWall_ShotGuns", CV.AutoWall_AutoWall_ShotGuns, FilePath);
		WriteBool("Rage", "AutoWall_BackTrack_ShotGuns", CV.AutoWall_BackTrack_ShotGuns, FilePath);
		WriteInt("Rage", "AutoWall_Hitbox_ShotGuns", CV.AutoWall_Hitbox_ShotGuns, FilePath);
		WriteFloat("Rage", "AutoWall_MinDamage_ShotGuns", CV.AutoWall_MinDamage_ShotGuns, FilePath);
		WriteFloat("Rage", "AutoWall_Hitchance_ShotGuns", CV.AutoWall_Hitchance_ShotGuns, FilePath);

		WriteBool("Rage", "AutoWall_AutoWall_SSG08", CV.AutoWall_AutoWall_SSG08, FilePath);
		WriteBool("Rage", "AutoWall_BackTrack_SSG08", CV.AutoWall_BackTrack_SSG08, FilePath);
		WriteInt("Rage", "AutoWall_Hitbox_SSG08", CV.AutoWall_Hitbox_SSG08, FilePath);
		WriteFloat("Rage", "AutoWall_MinDamage_SSG08", CV.AutoWall_MinDamage_SSG08, FilePath);
		WriteFloat("Rage", "AutoWall_Hitchance_SSG08", CV.AutoWall_Hitchance_SSG08, FilePath);

		WriteBool("Rage", "AutoWall_AutoWall_AWP", CV.AutoWall_AutoWall_AWP, FilePath);
		WriteBool("Rage", "AutoWall_BackTrack_AWP", CV.AutoWall_BackTrack_AWP, FilePath);
		WriteInt("Rage", "AutoWall_Hitbox_AWP", CV.AutoWall_Hitbox_AWP, FilePath);
		WriteFloat("Rage", "AutoWall_MinDamage_AWP", CV.AutoWall_MinDamage_AWP, FilePath);
		WriteFloat("Rage", "AutoWall_Hitchance_AWP", CV.AutoWall_Hitchance_AWP, FilePath);

		WriteBool("Rage", "AutoWall_AutoWall_Autos", CV.AutoWall_AutoWall_Autos, FilePath);
		WriteBool("Rage", "AutoWall_BackTrack_Autos", CV.AutoWall_BackTrack_Autos, FilePath);
		WriteInt("Rage", "AutoWall_Hitbox_Autos", CV.AutoWall_Hitbox_Autos, FilePath);
		WriteFloat("Rage", "AutoWall_MinDamage_Autos", CV.AutoWall_MinDamage_Autos, FilePath);
		WriteFloat("Rage", "AutoWall_Hitchance_Autos", CV.AutoWall_Hitchance_Autos, FilePath);

		WriteBool("Rage", "DeSync", CV.DeSync, FilePath);
		WriteFloat("Rage", "DeSyncValue", CV.DeSyncValue, FilePath);
		WriteInt("Rage", "AntiAimTypeYaw", CV.AntiAimTypeYaw, FilePath);
		WriteInt("Rage", "AntiAim_SpinBotSpeed", CV.AntiAim_SpinBotSpeed, FilePath);

		WriteColor("Color", "color_esp_ally_visible", CV.color_esp_ally_visible, FilePath);
		WriteColor("Color", "color_esp_enemy_visible", CV.color_esp_enemy_visible, FilePath);
		WriteColor("Color", "color_esp_ally_occluded", CV.color_esp_ally_occluded, FilePath);
		WriteColor("Color", "color_esp_enemy_occluded", CV.color_esp_enemy_occluded, FilePath);
		WriteColor("Color", "color_esp_crosshair", CV.color_esp_crosshair, FilePath);
		WriteColor("Color", "color_esp_weapons", CV.color_esp_weapons, FilePath);
		WriteColor("Color", "color_esp_defuse", CV.color_esp_defuse, FilePath);
		WriteColor("Color", "color_esp_c4", CV.color_esp_c4, FilePath);
		WriteColor("Color", "color_esp_item", CV.color_esp_item, FilePath);
		WriteColor("Color", "esp_footstep_color", CV.esp_footstep_color, FilePath);

		WriteColor("Color", "color_glow_ally", CV.color_glow_ally, FilePath);
		WriteColor("Color", "color_glow_enemy", CV.color_glow_enemy, FilePath);
		WriteColor("Color", "color_glow_chickens", CV.color_glow_chickens, FilePath);
		WriteColor("Color", "color_glow_c4_carrier", CV.color_glow_c4_carrier, FilePath);
		WriteColor("Color", "color_glow_planted_c4", CV.color_glow_planted_c4, FilePath);
		WriteColor("Color", "color_glow_defuse", CV.color_glow_defuse, FilePath);
		WriteColor("Color", "color_glow_weapons", CV.color_glow_weapons, FilePath);

		WriteColor("Color", "color_chams_player_ally_visible", CV.color_chams_player_ally_visible, FilePath);
		WriteColor("Color", "color_chams_player_ally_occluded", CV.color_chams_player_ally_occluded, FilePath);
		WriteColor("Color", "color_chams_player_enemy_visible", CV.color_chams_player_enemy_visible, FilePath);
		WriteColor("Color", "color_chams_player_enemy_occluded", CV.color_chams_player_enemy_occluded, FilePath);
		WriteColor("Color", "color_chams_arms_visible", CV.color_chams_arms_visible, FilePath);
		WriteColor("Color", "color_chams_arms_occluded", CV.color_chams_arms_occluded, FilePath);
		WriteColor("Color", "color_chams_weapons_visible", CV.color_chams_weapons_visible, FilePath);
		WriteColor("Color", "color_chams_weapons_occluded", CV.color_chams_weapons_occluded, FilePath);

		WriteColor("Color", "color_watermark", CV.color_watermark, FilePath);
	}

	static void Load(const char Name[], Options& CV)
	{
		char FilePath[200];   // array to hold the result.
		char one[] = "C:\\Cheat\\";
		char three[] = ".ini";
		strcpy(FilePath, one); // copy string one into the result.
		strcat(FilePath, Name); // append string two to the result.
		strcat(FilePath, three); // append string two to the result.

		ReadBool("Visuals", "esp_enabled", CV.esp_enabled, FilePath);
		ReadBool("Visuals", "esp_localplayer", CV.esp_localplayer, FilePath);
		ReadBool("Visuals", "esp_enemies_only", CV.esp_enemies_only, FilePath);
		ReadBool("Visuals", "esp_player_boxes", CV.esp_player_boxes, FilePath);
		ReadBool("Visuals", "esp_player_skeleton", CV.esp_player_skeleton, FilePath);
		ReadBool("Visuals", "esp_player_names", CV.esp_player_names, FilePath);
		ReadBool("Visuals", "esp_player_health", CV.esp_player_health, FilePath);
		ReadBool("Visuals", "esp_player_armour", CV.esp_player_armour, FilePath);
		ReadBool("Visuals", "esp_player_weapons", CV.esp_player_weapons, FilePath);
		ReadBool("Visuals", "esp_player_snaplines", CV.esp_player_snaplines, FilePath);
		ReadBool("Visuals", "esp_crosshair", CV.esp_crosshair, FilePath);
		ReadBool("Visuals", "esp_dropped_weapons", CV.esp_dropped_weapons, FilePath);
		ReadBool("Visuals", "esp_defuse_kit", CV.esp_defuse_kit, FilePath);
		ReadBool("Visuals", "esp_planted_c4", CV.esp_planted_c4, FilePath);
		ReadBool("Visuals", "esp_items Only", CV.esp_items, FilePath);
		ReadBool("Visuals", "esp_footstep", CV.esp_footstep, FilePath);
		ReadBool("Visuals", "esp_footstep_enemies_only Only", CV.esp_footstep_enemies_only, FilePath);

		ReadBool("Glow", "glow_enabled", CV.glow_enabled, FilePath);
		ReadBool("Glow", "glow_localplayer", CV.glow_localplayer, FilePath);
		ReadBool("Glow", "glow_enemies_only", CV.glow_enemies_only, FilePath);
		ReadBool("Glow", "glow_players", CV.glow_players, FilePath);
		ReadBool("Glow", "glow_chickens", CV.glow_chickens, FilePath);
		ReadBool("Glow", "glow_c4_carrier", CV.glow_c4_carrier, FilePath);
		ReadBool("Glow", "glow_planted_c4", CV.glow_planted_c4, FilePath);
		ReadBool("Glow", "glow_defuse_kits", CV.glow_defuse_kits, FilePath);
		ReadBool("Glow", "glow_weapons", CV.glow_weapons, FilePath);

		ReadBool("Chams", "chams_player_enabled", CV.chams_player_enabled, FilePath);
		ReadBool("Chams", "chams_localplayer", CV.chams_localplayer, FilePath);
		ReadBool("Chams", "chams_Disable_Model_Occulusion", CV.chams_Disable_Model_Occulusion, FilePath);
		ReadBool("Chams", "chams_player_enemies_only", CV.chams_player_enemies_only, FilePath);
		ReadBool("Chams", "chams_player_wireframe", CV.chams_player_wireframe, FilePath);
		ReadBool("Chams", "chams_player_flat", CV.chams_player_flat, FilePath);
		ReadBool("Chams", "chams_player_ignorez", CV.chams_player_ignorez, FilePath);
		ReadBool("Chams", "chams_player_glass", CV.chams_player_glass, FilePath);
		ReadBool("Chams", "chams_arms_enabled", CV.chams_arms_enabled, FilePath);
		ReadBool("Chams", "chams_arms_wireframe", CV.chams_arms_wireframe, FilePath);
		ReadBool("Chams", "chams_arms_flat", CV.chams_arms_flat, FilePath);
		ReadBool("Chams", "chams_arms_ignorez", CV.chams_arms_ignorez, FilePath);
		ReadBool("Chams", "chams_arms_glass", CV.chams_arms_glass, FilePath);
		ReadBool("Chams", "chams_weapons_enabled", CV.chams_weapons_enabled, FilePath);
		ReadBool("Chams", "chams_weapons_wireframe", CV.chams_weapons_wireframe, FilePath);
		ReadBool("Chams", "chams_weapons_flat", CV.chams_weapons_flat, FilePath);
		ReadBool("Chams", "chams_weapons_ignorez", CV.chams_weapons_ignorez, FilePath);
		ReadBool("Chams", "chams_weapons_glass", CV.chams_weapons_glass, FilePath);

		//pistols
		ReadBool("Aimbot", "Aimbot_Aimbot_Pistols", CV.Aimbot_Aimbot_Pistols, FilePath);
		ReadBool("Aimbot", "Aimbot_Silent_Pistols", CV.Aimbot_Silent_Pistols, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenJumping_Pistols", CV.Aimbot_IgnoreWhenJumping_Pistols, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenFlashed_Pistols", CV.Aimbot_IgnoreWhenFlashed_Pistols, FilePath);
		ReadBool("Aimbot", "Aimbot_VisibilityCheck_Pistols", CV.Aimbot_VisibilityCheck_Pistols, FilePath);
		ReadBool("Aimbot", "Aimbot_RecoilPrediction_Pistols", CV.Aimbot_RecoilPrediction_Pistols, FilePath);
		ReadBool("Aimbot", "Aimbot_Smoothing_Pistols", CV.Aimbot_Smoothing_Pistols, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoScope_Pistols", CV.Aimbot_AutoScope_Pistols, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoStop_Pistols", CV.Aimbot_AutoStop_Pistols, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoCrouch_Pistols", CV.Aimbot_AutoCrouch_Pistols, FilePath);
		ReadInt("Aimbot", "Aimbot_Hitbox_Pistols", CV.Aimbot_Hitbox_Pistols, FilePath);
		ReadFloat("Aimbot", "Aimbot_FOV_Pistols", CV.Aimbot_FOV_Pistols, FilePath);
		ReadFloat("Aimbot", "Aimbot_SilentFOV_Pistols", CV.Aimbot_SilentFOV_Pistols, FilePath);
		ReadBool("Aimbot", "Aimbot_ShowFOV_Pistols", CV.Aimbot_ShowFOV_Pistols, FilePath);
		ReadFloat("Aimbot", "Aimbot_SmoothAmount_Pistols", CV.Aimbot_SmoothAmount_Pistols, FilePath);
		ReadBool("TriggerBot", "TriggerBot_TriggerBot_Pistols", CV.TriggerBot_TriggerBot_Pistols, FilePath);
		ReadInt("TriggerBot", "TriggerBot_Delay_Pistols", CV.TriggerBot_Delay_Pistols, FilePath);
		ReadBool("TriggerBot", "TriggerBot_Backtrack_Pistols", CV.TriggerBot_Backtrack_Pistols, FilePath);
		ReadInt("TriggerBot", "TriggerBot_HitBox_Pistols", CV.TriggerBot_HitBox_Pistols, FilePath);
		ReadFloat("TriggerBot", "TriggerBot_HitChance_Pistols", CV.TriggerBot_HitChance_Pistols, FilePath);

		//rifles
		ReadBool("Aimbot", "Aimbot_Aimbot_Rifles", CV.Aimbot_Aimbot_Rifles, FilePath);
		ReadBool("Aimbot", "Aimbot_Silent_Rifles", CV.Aimbot_Silent_Rifles, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenJumping_Rifles", CV.Aimbot_IgnoreWhenJumping_Rifles, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenFlashed_Rifles", CV.Aimbot_IgnoreWhenFlashed_Rifles, FilePath);
		ReadBool("Aimbot", "Aimbot_VisibilityCheck_Rifles", CV.Aimbot_VisibilityCheck_Rifles, FilePath);
		ReadBool("Aimbot", "Aimbot_RecoilPrediction_Rifles", CV.Aimbot_RecoilPrediction_Rifles, FilePath);
		ReadBool("Aimbot", "Aimbot_Smoothing_Rifles", CV.Aimbot_Smoothing_Rifles, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoScope_Rifles", CV.Aimbot_AutoScope_Rifles, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoStop_Rifles", CV.Aimbot_AutoStop_Rifles, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoCrouch_Rifles", CV.Aimbot_AutoCrouch_Rifles, FilePath);
		ReadInt("Aimbot", "Aimbot_Hitbox_Rifles", CV.Aimbot_Hitbox_Rifles, FilePath);
		ReadFloat("Aimbot", "Aimbot_FOV_Rifles", CV.Aimbot_FOV_Rifles, FilePath);
		ReadFloat("Aimbot", "Aimbot_SilentFOV_Rifles", CV.Aimbot_SilentFOV_Rifles, FilePath);
		ReadBool("Aimbot", "Aimbot_ShowFOV_Rifles", CV.Aimbot_ShowFOV_Rifles, FilePath);
		ReadFloat("Aimbot", "Aimbot_SmoothAmount_Rifles", CV.Aimbot_SmoothAmount_Rifles, FilePath);
		ReadBool("TriggerBot", "TriggerBot_TriggerBot_Rifles", CV.TriggerBot_TriggerBot_Rifles, FilePath);
		ReadInt("TriggerBot", "TriggerBot_Delay_Rifles", CV.TriggerBot_Delay_Rifles, FilePath);
		ReadBool("TriggerBot", "TriggerBot_Backtrack_Rifles", CV.TriggerBot_Backtrack_Rifles, FilePath);
		ReadInt("TriggerBot", "TriggerBot_HitBox_Rifles", CV.TriggerBot_HitBox_Rifles, FilePath);
		ReadFloat("TriggerBot", "TriggerBot_HitChance_Rifles", CV.TriggerBot_HitChance_Rifles, FilePath);

		//smg
		ReadBool("Aimbot", "Aimbot_Aimbot_SMG", CV.Aimbot_Aimbot_SMG, FilePath);
		ReadBool("Aimbot", "Aimbot_Silent_SMG", CV.Aimbot_Silent_SMG, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenJumping_SMG", CV.Aimbot_IgnoreWhenJumping_SMG, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenFlashed_SMG", CV.Aimbot_IgnoreWhenFlashed_SMG, FilePath);
		ReadBool("Aimbot", "Aimbot_VisibilityCheck_SMG", CV.Aimbot_VisibilityCheck_SMG, FilePath);
		ReadBool("Aimbot", "Aimbot_RecoilPrediction_SMG", CV.Aimbot_RecoilPrediction_SMG, FilePath);
		ReadBool("Aimbot", "Aimbot_Smoothing_SMG", CV.Aimbot_Smoothing_SMG, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoScope_SMG", CV.Aimbot_AutoScope_SMG, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoStop_SMG", CV.Aimbot_AutoStop_SMG, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoCrouch_SMG", CV.Aimbot_AutoCrouch_SMG, FilePath);
		ReadInt("Aimbot", "Aimbot_Hitbox_SMG", CV.Aimbot_Hitbox_SMG, FilePath);
		ReadFloat("Aimbot", "Aimbot_FOV_SMG", CV.Aimbot_FOV_SMG, FilePath);
		ReadFloat("Aimbot", "Aimbot_SilentFOV_SMG", CV.Aimbot_SilentFOV_SMG, FilePath);
		ReadBool("Aimbot", "Aimbot_ShowFOV_SMG", CV.Aimbot_ShowFOV_SMG, FilePath);
		ReadFloat("Aimbot", "Aimbot_SmoothAmount_SMG", CV.Aimbot_SmoothAmount_SMG, FilePath);
		ReadBool("TriggerBot", "TriggerBot_TriggerBot_SMG", CV.TriggerBot_TriggerBot_SMG, FilePath);
		ReadInt("TriggerBot", "TriggerBot_Delay_SMG", CV.TriggerBot_Delay_SMG, FilePath);
		ReadBool("TriggerBot", "TriggerBot_Backtrack_SMG", CV.TriggerBot_Backtrack_SMG, FilePath);
		ReadInt("TriggerBot", "TriggerBot_HitBox_SMG", CV.TriggerBot_HitBox_SMG, FilePath);
		ReadFloat("TriggerBot", "TriggerBot_HitChance_SMG", CV.TriggerBot_HitChance_SMG, FilePath);

		//shotguns
		ReadBool("Aimbot", "Aimbot_Aimbot_Shotguns", CV.Aimbot_Aimbot_Shotguns, FilePath);
		ReadBool("Aimbot", "Aimbot_Silent_Shotguns", CV.Aimbot_Silent_Shotguns, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenJumping_Shotguns", CV.Aimbot_IgnoreWhenJumping_Shotguns, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenFlashed_Shotguns", CV.Aimbot_IgnoreWhenFlashed_Shotguns, FilePath);
		ReadBool("Aimbot", "Aimbot_VisibilityCheck_Shotguns", CV.Aimbot_VisibilityCheck_Shotguns, FilePath);
		ReadBool("Aimbot", "Aimbot_RecoilPrediction_Shotguns", CV.Aimbot_RecoilPrediction_Shotguns, FilePath);
		ReadBool("Aimbot", "Aimbot_Smoothing_Shotguns", CV.Aimbot_Smoothing_Shotguns, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoScope_Shotguns", CV.Aimbot_AutoScope_Shotguns, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoStop_Shotguns", CV.Aimbot_AutoStop_Shotguns, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoCrouch_Shotguns", CV.Aimbot_AutoCrouch_Shotguns, FilePath);
		ReadInt("Aimbot", "Aimbot_Hitbox_Shotguns", CV.Aimbot_Hitbox_Shotguns, FilePath);
		ReadFloat("Aimbot", "Aimbot_FOV_Shotguns", CV.Aimbot_FOV_Shotguns, FilePath);
		ReadFloat("Aimbot", "Aimbot_SilentFOV_Shotguns", CV.Aimbot_SilentFOV_Shotguns, FilePath);
		ReadBool("Aimbot", "Aimbot_ShowFOV_Shotguns", CV.Aimbot_ShowFOV_Shotguns, FilePath);
		ReadFloat("Aimbot", "Aimbot_SmoothAmount_Shotguns", CV.Aimbot_SmoothAmount_Shotguns, FilePath);
		ReadBool("TriggerBot", "TriggerBot_TriggerBot_Shotguns", CV.TriggerBot_TriggerBot_Shotguns, FilePath);
		ReadInt("TriggerBot", "TriggerBot_Delay_Shotguns", CV.TriggerBot_Delay_Shotguns, FilePath);
		ReadBool("TriggerBot", "TriggerBot_Backtrack_Shotguns", CV.TriggerBot_Backtrack_Shotguns, FilePath);
		ReadInt("TriggerBot", "TriggerBot_HitBox_Shotguns", CV.TriggerBot_HitBox_Shotguns, FilePath);
		ReadFloat("TriggerBot", "TriggerBot_HitChance_Shotguns", CV.TriggerBot_HitChance_Shotguns, FilePath);

		//awp
		ReadBool("Aimbot", "Aimbot_Aimbot_AWP", CV.Aimbot_Aimbot_AWP, FilePath);
		ReadBool("Aimbot", "Aimbot_Silent_AWP", CV.Aimbot_Silent_AWP, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenJumping_AWP", CV.Aimbot_IgnoreWhenJumping_AWP, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenFlashed_AWP", CV.Aimbot_IgnoreWhenFlashed_AWP, FilePath);
		ReadBool("Aimbot", "Aimbot_VisibilityCheck_AWP", CV.Aimbot_VisibilityCheck_AWP, FilePath);
		ReadBool("Aimbot", "Aimbot_RecoilPrediction_AWP", CV.Aimbot_RecoilPrediction_AWP, FilePath);
		ReadBool("Aimbot", "Aimbot_Smoothing_AWP", CV.Aimbot_Smoothing_AWP, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoScope_AWP", CV.Aimbot_AutoScope_AWP, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoStop_AWP", CV.Aimbot_AutoStop_AWP, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoCrouch_AWP", CV.Aimbot_AutoCrouch_AWP, FilePath);
		ReadInt("Aimbot", "Aimbot_Hitbox_AWP", CV.Aimbot_Hitbox_AWP, FilePath);
		ReadFloat("Aimbot", "Aimbot_FOV_AWP", CV.Aimbot_FOV_AWP, FilePath);
		ReadFloat("Aimbot", "Aimbot_SilentFOV_AWP", CV.Aimbot_SilentFOV_AWP, FilePath);
		ReadBool("Aimbot", "Aimbot_ShowFOV_AWP", CV.Aimbot_ShowFOV_AWP, FilePath);
		ReadFloat("Aimbot", "Aimbot_SmoothAmount_AWP", CV.Aimbot_SmoothAmount_AWP, FilePath);
		ReadBool("TriggerBot", "TriggerBot_TriggerBot_AWP", CV.TriggerBot_TriggerBot_AWP, FilePath);
		ReadInt("TriggerBot", "TriggerBot_Delay_AWP", CV.TriggerBot_Delay_AWP, FilePath);
		ReadBool("TriggerBot", "TriggerBot_Backtrack_AWP", CV.TriggerBot_Backtrack_AWP, FilePath);
		ReadInt("TriggerBot", "TriggerBot_HitBox_AWP", CV.TriggerBot_HitBox_AWP, FilePath);
		ReadFloat("TriggerBot", "TriggerBot_HitChance_AWP", CV.TriggerBot_HitChance_AWP, FilePath);

		//ssg08
		ReadBool("Aimbot", "Aimbot_Aimbot_SSG08", CV.Aimbot_Aimbot_SSG08, FilePath);
		ReadBool("Aimbot", "Aimbot_Silent_SSG08", CV.Aimbot_Silent_SSG08, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenJumping_SSG08", CV.Aimbot_IgnoreWhenJumping_SSG08, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenFlashed_SSG08", CV.Aimbot_IgnoreWhenFlashed_SSG08, FilePath);
		ReadBool("Aimbot", "Aimbot_VisibilityCheck_SSG08", CV.Aimbot_VisibilityCheck_SSG08, FilePath);
		ReadBool("Aimbot", "Aimbot_RecoilPrediction_SSG08", CV.Aimbot_RecoilPrediction_SSG08, FilePath);
		ReadBool("Aimbot", "Aimbot_Smoothing_SSG08", CV.Aimbot_Smoothing_SSG08, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoScope_SSG08", CV.Aimbot_AutoScope_SSG08, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoStop_SSG08", CV.Aimbot_AutoStop_SSG08, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoCrouch_SSG08", CV.Aimbot_AutoCrouch_SSG08, FilePath);
		ReadInt("Aimbot", "Aimbot_Hitbox_SSG08", CV.Aimbot_Hitbox_SSG08, FilePath);
		ReadFloat("Aimbot", "Aimbot_FOV_SSG08", CV.Aimbot_FOV_SSG08, FilePath);
		ReadFloat("Aimbot", "Aimbot_SilentFOV_SSG08", CV.Aimbot_SilentFOV_SSG08, FilePath);
		ReadBool("Aimbot", "Aimbot_ShowFOV_SSG08", CV.Aimbot_ShowFOV_SSG08, FilePath);
		ReadFloat("Aimbot", "Aimbot_SmoothAmount_SSG08", CV.Aimbot_SmoothAmount_SSG08, FilePath);
		ReadBool("TriggerBot", "TriggerBot_TriggerBot_SSG08", CV.TriggerBot_TriggerBot_SSG08, FilePath);
		ReadInt("TriggerBot", "TriggerBot_Delay_SSG08", CV.TriggerBot_Delay_SSG08, FilePath);
		ReadBool("TriggerBot", "TriggerBot_Backtrack_SSG08", CV.TriggerBot_Backtrack_SSG08, FilePath);
		ReadInt("TriggerBot", "TriggerBot_HitBox_SSG08", CV.TriggerBot_HitBox_SSG08, FilePath);
		ReadFloat("TriggerBot", "TriggerBot_HitChance_SSG08", CV.TriggerBot_HitChance_SSG08, FilePath);

		//autos
		ReadBool("Aimbot", "Aimbot_Aimbot_Autos", CV.Aimbot_Aimbot_Autos, FilePath);
		ReadBool("Aimbot", "Aimbot_Silent_Autos", CV.Aimbot_Silent_Autos, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenJumping_Autos", CV.Aimbot_IgnoreWhenJumping_Autos, FilePath);
		ReadBool("Aimbot", "Aimbot_IgnoreWhenFlashed_Autos", CV.Aimbot_IgnoreWhenFlashed_Autos, FilePath);
		ReadBool("Aimbot", "Aimbot_VisibilityCheck_Autos", CV.Aimbot_VisibilityCheck_Autos, FilePath);
		ReadBool("Aimbot", "Aimbot_RecoilPrediction_Autos", CV.Aimbot_RecoilPrediction_Autos, FilePath);
		ReadBool("Aimbot", "Aimbot_Smoothing_Autos", CV.Aimbot_Smoothing_Autos, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoScope_Autos", CV.Aimbot_AutoScope_Autos, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoStop_Autos", CV.Aimbot_AutoStop_Autos, FilePath);
		ReadBool("Aimbot", "Aimbot_AutoCrouch_Autos", CV.Aimbot_AutoCrouch_Autos, FilePath);
		ReadInt("Aimbot", "Aimbot_Hitbox_Autos", CV.Aimbot_Hitbox_Autos, FilePath);
		ReadFloat("Aimbot", "Aimbot_FOV_Autos", CV.Aimbot_FOV_Autos, FilePath);
		ReadFloat("Aimbot", "Aimbot_SilentFOV_Autos", CV.Aimbot_SilentFOV_Autos, FilePath);
		ReadBool("Aimbot", "Aimbot_ShowFOV_Autos", CV.Aimbot_ShowFOV_Autos, FilePath);
		ReadFloat("Aimbot", "Aimbot_SmoothAmount_Autos", CV.Aimbot_SmoothAmount_Autos, FilePath);
		ReadBool("TriggerBot", "TriggerBot_TriggerBot_Autos", CV.TriggerBot_TriggerBot_Autos, FilePath);
		ReadInt("TriggerBot", "TriggerBot_Delay_Autos", CV.TriggerBot_Delay_Autos, FilePath);
		ReadBool("TriggerBot", "TriggerBot_Backtrack_Autos", CV.TriggerBot_Backtrack_Autos, FilePath);
		ReadInt("TriggerBot", "TriggerBot_HitBox_Autos", CV.TriggerBot_HitBox_Autos, FilePath);
		ReadFloat("TriggerBot", "TriggerBot_HitChance_Autos", CV.TriggerBot_HitChance_Autos, FilePath);

		ReadBool("BackTrack", "BackTrack_BackTrack", CV.BackTrack_BackTrack, FilePath);
		ReadInt("BackTrack", "BackTrack_Ticks", CV.BackTrack_Ticks, FilePath);
		ReadBool("BackTrack", "esp_player_BackTrackTicks", CV.esp_player_BackTrackTicks, FilePath);
		ReadBool("BackTrack", "BackTrack_Chams", CV.BackTrack_Chams, FilePath);
		ReadBool("BackTrack", "BackTrack_Chams_LastTick", CV.BackTrack_Chams_LastTick, FilePath);
		ReadColor("BackTrack", "BackTrack_Chams_color", CV.BackTrack_Chams_color, FilePath);

		ReadInt("MISC", "misc_Fov", CV.misc_Fov, FilePath);
		ReadBool("MISC", "misc_bhop", CV.misc_bhop, FilePath);
		ReadBool("MISC", "misc_AutoStrafe", CV.misc_AutoStrafe, FilePath);
		ReadBool("MISC", "misc_FakePing", CV.misc_FakePing, FilePath);
		ReadBool("MISC", "misc_FakePingIgnoreBacktrack", CV.misc_FakePingIgnoreBacktrack, FilePath);
		ReadInt("MISC", "misc_FakePingAmount", CV.misc_FakePingAmount, FilePath);
		ReadBool("MISC", "misc_FakeLag", CV.misc_FakeLag, FilePath);
		ReadInt("MISC", "misc_FakeLagStandingAmount", CV.misc_FakeLagStandingAmount, FilePath);
		ReadInt("MISC", "misc_FakeLagMovingAmount", CV.misc_FakeLagMovingAmount, FilePath);
		ReadInt("MISC", "misc_FakeLagInAirAmount", CV.misc_FakeLagInAirAmount, FilePath);
		ReadBool("MISC", "misc_no_hands", CV.misc_no_hands, FilePath);
		ReadBool("MISC", "misc_thirdperson", CV.misc_thirdperson, FilePath);
		ReadFloat("MISC", "misc_thirdperson_dist", CV.misc_thirdperson_dist, FilePath);
		ReadBool("MISC", "misc_showranks", CV.misc_showranks, FilePath);
		ReadBool("MISC", "misc_AutoAccept", CV.misc_AutoAccept, FilePath);
		ReadBool("MISC", "misc_watermark", CV.misc_watermark, FilePath);
		ReadInt("MISC", "viewmodel_fov", CV.viewmodel_fov, FilePath);
		ReadFloat("MISC", "mat_ambient_light_r", CV.mat_ambient_light_r, FilePath);
		ReadFloat("MISC", "mat_ambient_light_g", CV.mat_ambient_light_g, FilePath);
		ReadFloat("MISC", "mat_ambient_light_b", CV.mat_ambient_light_b, FilePath);
		ReadBool("MISC", "misc_NightMode", CV.misc_NightMode, FilePath);
		ReadBool("MISC", "misc_NoFlash", CV.misc_NoFlash, FilePath);
		ReadBool("MISC", "misc_NoSmoke", CV.misc_NoSmoke, FilePath);
		ReadBool("MISC", "misc_Radar", CV.misc_Radar, FilePath);
		ReadBool("MISC", "misc_UnlimitedDuck", CV.misc_UnlimitedDuck, FilePath);
		ReadBool("MISC", "misc_RemoveScope", CV.misc_RemoveScope, FilePath);
		ReadInt("MISC", "misc_SkyBox", CV.misc_SkyBox, FilePath);
		ReadBool("MISC", "misc_SpotMarkers", CV.misc_SpotMarkers, FilePath);
		ReadBool("MISC", "misc_SpotMarkersShow", CV.misc_SpotMarkersShow, FilePath);
		ReadBool("MISC", "misc_WalkBot", CV.misc_WalkBot, FilePath);
		ReadBool("MISC", "misc_BuyBot", CV.misc_BuyBot, FilePath);
		ReadInt("MISC", "misc_BuyBot_Primary", CV.misc_BuyBot_Primary, FilePath);
		ReadInt("MISC", "misc_BuyBot_Secondary", CV.misc_BuyBot_Secondary, FilePath);
		ReadBool("MISC", "misc_BuyBot_Kevlar", CV.misc_BuyBot_Kevlar, FilePath);
		ReadBool("MISC", "misc_BuyBot_Grenades", CV.misc_BuyBot_Grenades, FilePath);
		ReadBool("MISC", "misc_BuyBot_Defuser", CV.misc_BuyBot_Defuser, FilePath);
		ReadBool("MISC", "misc_BuyBot_Taser", CV.misc_BuyBot_Taser, FilePath);
		ReadBool("MISC", "misc_Hitmarker", CV.misc_Hitmarker, FilePath);
		ReadInt("MISC", "misc_HitmarkerMode", CV.misc_HitmarkerMode, FilePath);
		ReadInt("MISC", "misc_HitmarkerSound", CV.misc_HitmarkerSound, FilePath);
		ReadInt("MISC", "misc_HitmarkerSize", CV.misc_HitmarkerSize, FilePath);
		ReadInt("MISC", "misc_HitmarkerDuration", CV.misc_HitmarkerDuration, FilePath);
		ReadColor("MISC", "misc_Hitmarker_color", CV.misc_Hitmarker_color, FilePath);
		ReadBool("MISC", "misc_LogEvents", CV.misc_LogEvents, FilePath);
		ReadBool("MISC", "misc_LogEvents_Damage", CV.misc_LogEvents_Damage, FilePath);
		ReadBool("MISC", "misc_LogEvents_ItemsPurchase", CV.misc_LogEvents_ItemsPurchase, FilePath);
		ReadBool("MISC", "misc_LogEvents_Bomb", CV.misc_LogEvents_Bomb, FilePath);
		ReadColor("MISC", "misc_LogEvents_color", CV.misc_LogEvents_color, FilePath);
		ReadBool("MISC", "misc_ChatSpam", CV.misc_ChatSpam, FilePath);
		ReadInt("MISC", "misc_ChatSpamKill", CV.misc_ChatSpamKill, FilePath);
		ReadInt("MISC", "misc_ChatSpamDeath", CV.misc_ChatSpamDeath, FilePath);
		ReadBool("MISC", "misc_AntiKick", CV.misc_AntiKick, FilePath);
		ReadBool("MISC", "misc_InverseRagdollGravity", CV.misc_InverseRagdollGravity, FilePath);
		ReadBool("MISC", "misc_spectatorsList", CV.misc_spectatorsList, FilePath);
		ReadBool("MISC", "misc_spectatorsListOnlyMe", CV.misc_spectatorsListOnlyMe, FilePath);
		ReadColor("MISC", "misc_spectatorsList_color", CV.misc_spectatorsList_color, FilePath);
		ReadBool("MISC", "misc_DisablePostProcess", CV.misc_DisablePostProcess, FilePath);
		ReadBool("MISC", "misc_ClanTag", CV.misc_ClanTag, FilePath);
		ReadInt("MISC", "misc_ClanTagClan", CV.misc_ClanTagClan, FilePath);
		//ReadString("MISC", "misc_ClanTagName", CV.misc_ClanTagName.c_str, FilePath);
		ReadBool("MISC", "misc_edgejump", CV.misc_edgejump, FilePath);
		ReadBool("MISC", "misc_grenadeTrajectory", CV.misc_grenadeTrajectory, FilePath);
		ReadBool("MISC", "misc_AsusWalls", CV.misc_AsusWalls, FilePath);
		ReadInt("MISC", "misc_AsusWallsInt", CV.misc_AsusWallsInt, FilePath);
		ReadFloat("MISC", "misc_AsusWallsAlpha", CV.misc_AsusWallsAlpha, FilePath);

		ReadBool("SkinChanger", "SkinChanger_SkinChanger", CV.SkinChanger_SkinChanger, FilePath);
		ReadFloat("SkinChanger", "SkinChanger_Wear", CV.SkinChanger_Wear, FilePath);
		ReadInt("SkinChanger", "SkinChanger_Stattrak", CV.SkinChanger_Stattrak, FilePath);
		ReadFloat("SkinChanger", "SkinChanger_Seed", CV.SkinChanger_Seed, FilePath);
		ReadInt("SkinChanger", "WEAPON_DEAGLE", CV.WEAPON_DEAGLE, FilePath);
		ReadInt("SkinChanger", "WEAPON_ELITE", CV.WEAPON_ELITE, FilePath);
		ReadInt("SkinChanger", "WEAPON_FIVESEVEN", CV.WEAPON_FIVESEVEN, FilePath);
		ReadInt("SkinChanger", "WEAPON_GLOCK", CV.WEAPON_GLOCK, FilePath);
		ReadInt("SkinChanger", "WEAPON_AK47", CV.WEAPON_AK47, FilePath);
		ReadInt("SkinChanger", "WEAPON_AUG", CV.WEAPON_AUG, FilePath);
		ReadInt("SkinChanger", "WEAPON_AWP", CV.WEAPON_AWP, FilePath);
		ReadInt("SkinChanger", "WEAPON_FAMAS", CV.WEAPON_FAMAS, FilePath);
		ReadInt("SkinChanger", "WEAPON_G3SG1", CV.WEAPON_G3SG1, FilePath);
		ReadInt("SkinChanger", "WEAPON_GALILAR", CV.WEAPON_GALILAR, FilePath);
		ReadInt("SkinChanger", "WEAPON_M249", CV.WEAPON_M249, FilePath);
		ReadInt("SkinChanger", "WEAPON_M4A1", CV.WEAPON_M4A1, FilePath);
		ReadInt("SkinChanger", "WEAPON_MAC10", CV.WEAPON_MAC10, FilePath);
		ReadInt("SkinChanger", "WEAPON_P90", CV.WEAPON_P90, FilePath);
		ReadInt("SkinChanger", "WEAPON_MP5", CV.WEAPON_MP5, FilePath);
		ReadInt("SkinChanger", "WEAPON_UMP45", CV.WEAPON_UMP45, FilePath);
		ReadInt("SkinChanger", "WEAPON_XM1014", CV.WEAPON_XM1014, FilePath);
		ReadInt("SkinChanger", "WEAPON_BIZON", CV.WEAPON_BIZON, FilePath);
		ReadInt("SkinChanger", "WEAPON_MAG7", CV.WEAPON_MAG7, FilePath);
		ReadInt("SkinChanger", "WEAPON_NEGEV", CV.WEAPON_NEGEV, FilePath);
		ReadInt("SkinChanger", "WEAPON_SAWEDOFF", CV.WEAPON_SAWEDOFF, FilePath);
		ReadInt("SkinChanger", "WEAPON_HKP2000", CV.WEAPON_HKP2000, FilePath);
		ReadInt("SkinChanger", "WEAPON_MP7", CV.WEAPON_MP7, FilePath);
		ReadInt("SkinChanger", "WEAPON_MP9", CV.WEAPON_MP9, FilePath);
		ReadInt("SkinChanger", "WEAPON_NOVA", CV.WEAPON_NOVA, FilePath);
		ReadInt("SkinChanger", "WEAPON_P250", CV.WEAPON_P250, FilePath);
		ReadInt("SkinChanger", "WEAPON_SCAR20", CV.WEAPON_SCAR20, FilePath);
		ReadInt("SkinChanger", "WEAPON_SG556", CV.WEAPON_SG556, FilePath);
		ReadInt("SkinChanger", "WEAPON_SSG08", CV.WEAPON_SSG08, FilePath);
		ReadInt("SkinChanger", "WEAPON_M4A1_SILENCER", CV.WEAPON_M4A1_SILENCER, FilePath);
		ReadInt("SkinChanger", "WEAPON_USP_SILENCER", CV.WEAPON_USP_SILENCER, FilePath);
		ReadInt("SkinChanger", "WEAPON_CZ75A", CV.WEAPON_CZ75A, FilePath);
		ReadInt("SkinChanger", "WEAPON_REVOLVER", CV.WEAPON_REVOLVER, FilePath);

		//CT
		ReadBool("SkinChanger", "SkinChanger_KnifeChangerCT", CV.SkinChanger_KnifeChangerCT, FilePath);
		ReadInt("SkinChanger", "KnifeCT", CV.KnifeCT, FilePath);
		ReadInt("SkinChanger", "WEAPON_KNIFECT", CV.WEAPON_KNIFECT, FilePath);
		ReadInt("SkinChanger", "KNIFE_SKINCT", CV.KNIFE_SKINCT, FilePath);
		ReadFloat("SkinChanger", "KNIFE_WearCT", CV.KNIFE_WearCT, FilePath);
		ReadInt("SkinChanger", "KNIFE_StattrakCT", CV.KNIFE_StattrakCT, FilePath);
		ReadFloat("SkinChanger", "KNIFE_SeedCT", CV.KNIFE_SeedCT, FilePath);

		//T
		ReadBool("SkinChanger", "SkinChanger_KnifeChangerT", CV.SkinChanger_KnifeChangerT, FilePath);
		ReadInt("SkinChanger", "KnifeT", CV.KnifeT, FilePath);
		ReadInt("SkinChanger", "WEAPON_KNIFET", CV.WEAPON_KNIFET, FilePath);
		ReadInt("SkinChanger", "KNIFE_SKINT", CV.KNIFE_SKINT, FilePath);
		ReadFloat("SkinChanger", "KNIFE_WearT", CV.KNIFE_WearT, FilePath);
		ReadInt("SkinChanger", "KNIFE_StattrakT", CV.KNIFE_StattrakT, FilePath);
		ReadFloat("SkinChanger", "KNIFE_SeedT", CV.KNIFE_SeedT, FilePath);

		ReadBool("SkinChanger", "SkinChanger_GloveChanger", CV.SkinChanger_GloveChanger, FilePath);
		ReadInt("SkinChanger", "GLOVE_MODEL", CV.GLOVE_MODEL, FilePath);
		ReadInt("SkinChanger", "GLOVE_SKIN", CV.GLOVE_SKIN, FilePath);
		ReadFloat("SkinChanger", "GLOVE_WEAR", CV.GLOVE_WEAR, FilePath);

		ReadBool("Rage", "AutoWall_ShowDamage", CV.AutoWall_ShowDamage, FilePath);

		ReadBool("Rage", "AutoWall_AutoWall_Pistols", CV.AutoWall_AutoWall_Pistols, FilePath);
		ReadBool("Rage", "AutoWall_BackTrack_Pistols", CV.AutoWall_BackTrack_Pistols, FilePath);
		ReadInt("Rage", "AutoWall_Hitbox_Pistols", CV.AutoWall_Hitbox_Pistols, FilePath);
		ReadFloat("Rage", "AutoWall_MinDamage_Pistols", CV.AutoWall_MinDamage_Pistols, FilePath);
		ReadFloat("Rage", "AutoWall_Hitchance_Pistols", CV.AutoWall_Hitchance_Pistols, FilePath);

		ReadBool("Rage", "AutoWall_AutoWall_Rifles", CV.AutoWall_AutoWall_Rifles, FilePath);
		ReadBool("Rage", "AutoWall_BackTrack_Rifles", CV.AutoWall_BackTrack_Rifles, FilePath);
		ReadInt("Rage", "AutoWall_Hitbox_Rifles", CV.AutoWall_Hitbox_Rifles, FilePath);
		ReadFloat("Rage", "AutoWall_MinDamage_Rifles", CV.AutoWall_MinDamage_Rifles, FilePath);
		ReadFloat("Rage", "AutoWall_Hitchance_Rifles", CV.AutoWall_Hitchance_Rifles, FilePath);

		ReadBool("Rage", "AutoWall_AutoWall_SMG", CV.AutoWall_AutoWall_SMG, FilePath);
		ReadBool("Rage", "AutoWall_BackTrack_SMG", CV.AutoWall_BackTrack_SMG, FilePath);
		ReadInt("Rage", "AutoWall_Hitbox_SMG", CV.AutoWall_Hitbox_SMG, FilePath);
		ReadFloat("Rage", "AutoWall_MinDamage_SMG", CV.AutoWall_MinDamage_SMG, FilePath);
		ReadFloat("Rage", "AutoWall_Hitchance_SMG", CV.AutoWall_Hitchance_SMG, FilePath);

		ReadBool("Rage", "AutoWall_AutoWall_ShotGuns", CV.AutoWall_AutoWall_ShotGuns, FilePath);
		ReadBool("Rage", "AutoWall_BackTrack_ShotGuns", CV.AutoWall_BackTrack_ShotGuns, FilePath);
		ReadInt("Rage", "AutoWall_Hitbox_ShotGuns", CV.AutoWall_Hitbox_ShotGuns, FilePath);
		ReadFloat("Rage", "AutoWall_MinDamage_ShotGuns", CV.AutoWall_MinDamage_ShotGuns, FilePath);
		ReadFloat("Rage", "AutoWall_Hitchance_ShotGuns", CV.AutoWall_Hitchance_ShotGuns, FilePath);

		ReadBool("Rage", "AutoWall_AutoWall_SSG08", CV.AutoWall_AutoWall_SSG08, FilePath);
		ReadBool("Rage", "AutoWall_BackTrack_SSG08", CV.AutoWall_BackTrack_SSG08, FilePath);
		ReadInt("Rage", "AutoWall_Hitbox_SSG08", CV.AutoWall_Hitbox_SSG08, FilePath);
		ReadFloat("Rage", "AutoWall_MinDamage_SSG08", CV.AutoWall_MinDamage_SSG08, FilePath);
		ReadFloat("Rage", "AutoWall_Hitchance_SSG08", CV.AutoWall_Hitchance_SSG08, FilePath);

		ReadBool("Rage", "AutoWall_AutoWall_AWP", CV.AutoWall_AutoWall_AWP, FilePath);
		ReadBool("Rage", "AutoWall_BackTrack_AWP", CV.AutoWall_BackTrack_AWP, FilePath);
		ReadInt("Rage", "AutoWall_Hitbox_AWP", CV.AutoWall_Hitbox_AWP, FilePath);
		ReadFloat("Rage", "AutoWall_MinDamage_AWP", CV.AutoWall_MinDamage_AWP, FilePath);
		ReadFloat("Rage", "AutoWall_Hitchance_AWP", CV.AutoWall_Hitchance_AWP, FilePath);

		ReadBool("Rage", "AutoWall_AutoWall_Autos", CV.AutoWall_AutoWall_Autos, FilePath);
		ReadBool("Rage", "AutoWall_BackTrack_Autos", CV.AutoWall_BackTrack_Autos, FilePath);
		ReadInt("Rage", "AutoWall_Hitbox_Autos", CV.AutoWall_Hitbox_Autos, FilePath);
		ReadFloat("Rage", "AutoWall_MinDamage_Autos", CV.AutoWall_MinDamage_Autos, FilePath);
		ReadFloat("Rage", "AutoWall_Hitchance_Autos", CV.AutoWall_Hitchance_Autos, FilePath);

		ReadBool("Rage", "DeSync", CV.DeSync, FilePath);
		ReadFloat("Rage", "DeSyncValue", CV.DeSyncValue, FilePath);
		ReadInt("Rage", "AntiAimTypeYaw", CV.AntiAimTypeYaw, FilePath);
		ReadInt("Rage", "AntiAim_SpinBotSpeed", CV.AntiAim_SpinBotSpeed, FilePath);

		ReadColor("Color", "color_esp_ally_visible", CV.color_esp_ally_visible, FilePath);
		ReadColor("Color", "color_esp_enemy_visible", CV.color_esp_enemy_visible, FilePath);
		ReadColor("Color", "color_esp_ally_occluded", CV.color_esp_ally_occluded, FilePath);
		ReadColor("Color", "color_esp_enemy_occluded", CV.color_esp_enemy_occluded, FilePath);
		ReadColor("Color", "color_esp_crosshair", CV.color_esp_crosshair, FilePath);
		ReadColor("Color", "color_esp_weapons", CV.color_esp_weapons, FilePath);
		ReadColor("Color", "color_esp_defuse", CV.color_esp_defuse, FilePath);
		ReadColor("Color", "color_esp_c4", CV.color_esp_c4, FilePath);
		ReadColor("Color", "color_esp_item", CV.color_esp_item, FilePath);
		ReadColor("Color", "esp_footstep_color", CV.esp_footstep_color, FilePath);

		ReadColor("Color", "color_glow_ally", CV.color_glow_ally, FilePath);
		ReadColor("Color", "color_glow_enemy", CV.color_glow_enemy, FilePath);
		ReadColor("Color", "color_glow_chickens", CV.color_glow_chickens, FilePath);
		ReadColor("Color", "color_glow_c4_carrier", CV.color_glow_c4_carrier, FilePath);
		ReadColor("Color", "color_glow_planted_c4", CV.color_glow_planted_c4, FilePath);
		ReadColor("Color", "color_glow_defuse", CV.color_glow_defuse, FilePath);
		ReadColor("Color", "color_glow_weapons", CV.color_glow_weapons, FilePath);

		ReadColor("Color", "color_chams_player_ally_visible", CV.color_chams_player_ally_visible, FilePath);
		ReadColor("Color", "color_chams_player_ally_occluded", CV.color_chams_player_ally_occluded, FilePath);
		ReadColor("Color", "color_chams_player_enemy_visible", CV.color_chams_player_enemy_visible, FilePath);
		ReadColor("Color", "color_chams_player_enemy_occluded", CV.color_chams_player_enemy_occluded, FilePath);
		ReadColor("Color", "color_chams_arms_visible", CV.color_chams_arms_visible, FilePath);
		ReadColor("Color", "color_chams_arms_occluded", CV.color_chams_arms_occluded, FilePath);
		ReadColor("Color", "color_chams_weapons_visible", CV.color_chams_weapons_visible, FilePath);
		ReadColor("Color", "color_chams_weapons_occluded", CV.color_chams_weapons_occluded, FilePath);

		ReadColor("Color", "color_watermark", CV.color_watermark, FilePath);
	}

	static LPCSTR BoolToLPCSTR(bool b)
	{
		return b ? "true" : "false";
	}

	static void WriteColor(const char* Category, const char* Name, Color f, const char* File) 
	{
		std::string buf(Name);
		WritePrivateProfileStringA(Category, buf.c_str(), std::to_string(f[0]).c_str(), File);
		buf.append("1");
		WritePrivateProfileStringA(Category, buf.c_str(), std::to_string(f[1]).c_str(), File);
		buf.append("2");
		WritePrivateProfileStringA(Category, buf.c_str(), std::to_string(f[2]).c_str(), File);
		buf.append("3");
		WritePrivateProfileStringA(Category, buf.c_str(), std::to_string(f[3]).c_str(), File);
	}

	static void ReadColor(const char* Category, const char* Name, Color& f, const char* File)
	{
		std::string buf(Name);
		ReadInt(Category, buf.c_str(), (int&)f[0], File);
		buf.append("1");
		ReadInt(Category, buf.c_str(), (int&)f[1], File);
		buf.append("2");
		ReadInt(Category, buf.c_str(), (int&)f[2], File);
		buf.append("3");
		ReadInt(Category, buf.c_str(), (int&)f[3], File);
	}

	static void WriteString(const char* Category, const char* Name, std::string string, const char* File)
	{
		WritePrivateProfileStringA(Category, Name, string.c_str(), File);
	}

	static void ReadString(const char* Category, const char* Name, char*& string, const char* File)
	{
		GetPrivateProfileStringA(Category, Name, "", string, 32, File);
	}

	static void WriteFloat(const char* Category, const char* Name, float floate, const char* File)
	{
		WritePrivateProfileStringA(Category, Name, std::to_string(floate).c_str(), File);
	}

	static void ReadFloat(const char* Category, const char* Name, float& Floate, const char* File)
	{
		char Temp[32];
		GetPrivateProfileStringA(Category, Name, "", Temp, 32, File);
		Floate = atof(Temp);
	}

	static void WriteInt(const char* Category, const char* Name, int Integer, const char* File)
	{
		WritePrivateProfileStringA(Category, Name, std::to_string(Integer).c_str(), File);
	}

	static void ReadInt(const char* Category, const char* Name, int& Integer, const char* File)
	{
		char Temp[32];
		GetPrivateProfileStringA(Category, Name, "", Temp, 32, File);
		Integer = atoi(Temp);
	}

	static void WriteBool(const char* Category, const char* Name, bool Boolean, const char* File)
	{
		WritePrivateProfileStringA(Category, Name, BoolToLPCSTR(Boolean), File);
	}

	static void ReadBool(const char* Category, const char* Name, bool& Boolean, const char* File)
	{
		char Temp[32];
		GetPrivateProfileStringA(Category, Name, "", Temp, 32, File);
		Boolean = charoBool(Temp);
	}

	static bool charoBool(char* b)
	{
		if (!strcmp(b, "false"))
			return false;
		else
			return true;
	}

	static wchar_t* CharArrayToLPCWSTR(const char* charArray)
	{
		wchar_t* wString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
		return wString;
	}

	void RefreshConfigs(std::vector<std::string> & Files)
	{
		std::string path = "C:\\Cheat";
		std::string extension = ".ini";
		Files.clear();
		for (auto& f : std::experimental::filesystem::recursive_directory_iterator(path))
			if (f.path().extension() == extension)
				if (!f.path().filename().string()._Starts_with("maps")) {
					std::string temp = f.path().filename().string();
					temp.erase(temp.find(".ini")); 
					Files.push_back(temp);
				}			
	}
};

inline SaveLoadConfigs g_SaveLoadConfig;
inline Options g_Options;
inline bool   g_Unload;
