#include "SkinChanger.hpp"

SkinChanger skinchanger;
static int OldKnife = 0;
int iModel;
static int iKnife;
static int iBay;
static int iFlip;
static int iGut;
static int iKarambit;
static int iM9Bay;
static int iHuntsman;
static int iFalchion;
static int iBowie;
static int iButterfly;
static int iShadow;
static int iUrsus;
static int iNavaja;
static int iStilleto;
static int iWidow;

void SkinChanger::SetSkin(ClientFrameStage_t stage)
{
	if(g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())

	if (stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
		C_BasePlayer* Local = (C_BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());
		if (!Local || !Local->IsAlive())
			return;

		int Localteam = Local->m_iTeamNum();

		player_info_t LocalPlayerInfo;
		if (!g_EngineClient->GetPlayerInfo(g_EngineClient->GetLocalPlayer(), &LocalPlayerInfo))
			return;

		if ((Localteam == 3 && g_Options.SkinChanger_KnifeChangerCT) || (Localteam == 2 && g_Options.SkinChanger_KnifeChangerT)) {
			C_BaseCombatWeapon* gun = Local->m_hActiveWeapon();
			if (!gun)
				return;

			iBay = g_MdlInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
			iFlip = g_MdlInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
			iGut = g_MdlInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
			iKarambit = g_MdlInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
			iM9Bay = g_MdlInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
			iHuntsman = g_MdlInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
			iFalchion = g_MdlInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
			iBowie = g_MdlInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");
			iButterfly = g_MdlInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
			iShadow = g_MdlInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
			iUrsus = g_MdlInfo->GetModelIndex("models/weapons/v_knife_ursus.mdl");
			iNavaja = g_MdlInfo->GetModelIndex("models/weapons/v_knife_gypsy_jackknife.mdl");
			iStilleto = g_MdlInfo->GetModelIndex("models/weapons/v_knife_stiletto.mdl");
			iWidow = g_MdlInfo->GetModelIndex("models/weapons/v_knife_widowmaker.mdl");

			short weaponindex = gun->m_Item().m_iItemDefinitionIndex();

			//auto viemodel = Local->m_hViewModel().Get();
			//int Sequence = Local->m_nSequence();
			//int originalactivity = Local->GetSequenceActivity(Sequence);

			int knife = Localteam == 3 ? g_Options.WEAPON_KNIFECT : g_Options.WEAPON_KNIFET;
			if (knife == 0)
				return;

			switch (knife)
			{
			case WEAPON_BAYONET: //Bayonet
				iModel = iBay;
				iKnife = WEAPON_BAYONET;
				break;
			case WEAPON_KNIFE_FLIP: //Flip Knife
				iModel = iFlip;
				iKnife = WEAPON_KNIFE_FLIP;
				break;
			case WEAPON_KNIFE_GUT: //Gut Knife
				iModel = iGut;
				iKnife = WEAPON_KNIFE_GUT;
				break;
			case WEAPON_KNIFE_KARAMBIT: //Karambit
				iModel = iKarambit;
				iKnife = WEAPON_KNIFE_KARAMBIT;
				break;
			case WEAPON_KNIFE_M9_BAYONET: //M9 Bayonet
				iModel = iM9Bay;
				iKnife = WEAPON_KNIFE_M9_BAYONET;
				break;
			case WEAPON_KNIFE_TACTICAL: //Huntsman
				iModel = iHuntsman;
				iKnife = WEAPON_KNIFE_TACTICAL;
				break;
			case WEAPON_KNIFE_FALCHION: //Falchion
				iModel = iFalchion;
				iKnife = WEAPON_KNIFE_FALCHION;
				break;
			case WEAPON_KNIFE_SURVIVAL_BOWIE: //Bowie
				iModel = iBowie;
				iKnife = WEAPON_KNIFE_SURVIVAL_BOWIE;
				break;
			case WEAPON_KNIFE_BUTTERFLY: //Butterfly
				iModel = iButterfly;
				iKnife = WEAPON_KNIFE_BUTTERFLY;
				break;
			case WEAPON_KNIFE_PUSH: //Shaddow daggers
				iModel = iShadow;
				iKnife = WEAPON_KNIFE_PUSH;
				break;
			case WEAPON_KNIFE_URSUS: //Ursus
				iModel = iUrsus;
				iKnife = WEAPON_KNIFE_URSUS;
				break;
			case WEAPON_KNIFE_GYPSY_JACKKNIFE: //Navaja
				iModel = iNavaja;
				iKnife = WEAPON_KNIFE_GYPSY_JACKKNIFE;
				break;
			case WEAPON_KNIFE_STILETTO: //Stiletto
				iModel = iStilleto;
				iKnife = WEAPON_KNIFE_STILETTO;
				break;
			case WEAPON_KNIFE_WIDOWMAKER: //Talon
				iModel = iWidow;
				iKnife = WEAPON_KNIFE_WIDOWMAKER;
				break;
			default:
				break;
			}

			if (gun->IsKnife()) {
				gun->m_Item().m_iItemIDHigh() = -1;
				gun->m_nModelIndex() = iModel;
				Local->m_hViewModel()->m_nViewModelIndex() = iModel;  //Important
				Local->m_hViewModel()->m_nModelIndex() = iModel; //Important
				gun->m_Item().m_iItemDefinitionIndex() = iKnife;
			}

			//int newActivity = 1;
			//int num = 0;
			//for (size_t i = 0; i < 20; i++) // compare activity with original activity and save new activity // havent seen a sequence above 14 but using 20 if theres is
			//{
			//	int tempactivity = Local->GetSequenceActivity(i);
			//	if (originalactivity != -1 && originalactivity == tempactivity || originalactivity == -1 && tempactivity == 213) {
			//		newActivity = i;
			//		for (size_t t = 0; t < 4; t++)
			//		{
			//			if (Local->GetSequenceActivity(i + t) == tempactivity)
			//				num++;
			//		}
			//		break;
			//	}
			//}

			//if (originalactivity == -1 && newActivity == 1)
			//	newActivity = Sequence;
			//if (!num)
			//	Sequence = newActivity;
			//else
			//	Sequence = Math::RandomInt(newActivity, newActivity + num - 1);

			//viemodel->SendViewModelMatchingSequence(Sequence);
		}

		if (g_Options.SkinChanger_SkinChanger) {
			auto weapons = Local->m_hMyWeapons();
			if (!weapons)
				return;

			for (int i = 0; weapons[i]; i++) {
				C_BaseCombatWeapon* gun = (C_BaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(weapons[i]);
				if (!gun)
					continue;

				short weaponindex = gun->m_Item().m_iItemDefinitionIndex();
				int WeaponSkin = 0;
				switch (weaponindex)
				{
				case WEAPON_DEAGLE:
					WeaponSkin = g_Options.WEAPON_DEAGLE;
					break;
				case WEAPON_ELITE:
					WeaponSkin = g_Options.WEAPON_ELITE;
					break;
				case WEAPON_FIVESEVEN:
					WeaponSkin = g_Options.WEAPON_FIVESEVEN;
					break;
				case WEAPON_GLOCK:
					WeaponSkin = g_Options.WEAPON_GLOCK;
					break;
				case WEAPON_AK47:
					WeaponSkin = g_Options.WEAPON_AK47;
					break;
				case WEAPON_AUG:
					WeaponSkin = g_Options.WEAPON_AUG;
					break;
				case WEAPON_AWP:
					WeaponSkin = g_Options.WEAPON_AWP;
					break;
				case WEAPON_FAMAS:
					WeaponSkin = g_Options.WEAPON_FAMAS;
					break;
				case WEAPON_G3SG1:
					WeaponSkin = g_Options.WEAPON_G3SG1;
					break;
				case WEAPON_GALILAR:
					WeaponSkin = g_Options.WEAPON_GALILAR;
					break;
				case WEAPON_M249:
					WeaponSkin = g_Options.WEAPON_M249;
					break;
				case WEAPON_M4A1:
					WeaponSkin = g_Options.WEAPON_M4A1;
					break;
				case WEAPON_MAC10:
					WeaponSkin = g_Options.WEAPON_MAC10;
					break;
				case WEAPON_P90:
					WeaponSkin = g_Options.WEAPON_P90;
					break;
				case WEAPON_MP5:
					WeaponSkin = g_Options.WEAPON_MP5;
					break;
				case WEAPON_UMP45:
					WeaponSkin = g_Options.WEAPON_UMP45;
					break;
				case WEAPON_XM1014:
					WeaponSkin = g_Options.WEAPON_XM1014;
					break;
				case WEAPON_BIZON:
					WeaponSkin = g_Options.WEAPON_BIZON;
					break;
				case WEAPON_MAG7:
					WeaponSkin = g_Options.WEAPON_MAG7;
					break;
				case WEAPON_NEGEV:
					WeaponSkin = g_Options.WEAPON_NEGEV;
					break;
				case WEAPON_SAWEDOFF:
					WeaponSkin = g_Options.WEAPON_SAWEDOFF;
					break;
				case WEAPON_HKP2000:
					WeaponSkin = g_Options.WEAPON_HKP2000;
					break;
				case WEAPON_MP7:
					WeaponSkin = g_Options.WEAPON_MP7;
					break;
				case WEAPON_MP9:
					WeaponSkin = g_Options.WEAPON_MP9;
					break;
				case WEAPON_NOVA:
					WeaponSkin = g_Options.WEAPON_NOVA;
					break;
				case WEAPON_P250:
					WeaponSkin = g_Options.WEAPON_P250;
					break;
				case WEAPON_SCAR20:
					WeaponSkin = g_Options.WEAPON_SCAR20;
					break;
				case WEAPON_SG556:
					WeaponSkin = g_Options.WEAPON_SG556;
					break;
				case WEAPON_SSG08:
					WeaponSkin = g_Options.WEAPON_SSG08;
					break;
				case WEAPON_M4A1_SILENCER:
					WeaponSkin = g_Options.WEAPON_M4A1_SILENCER;
					break;
				case WEAPON_USP_SILENCER:
					WeaponSkin = g_Options.WEAPON_USP_SILENCER;
					break;
				case WEAPON_CZ75A:
					WeaponSkin = g_Options.WEAPON_NEGEV;
					break;
				case WEAPON_REVOLVER:
					WeaponSkin = g_Options.WEAPON_REVOLVER;
					break;
				}
				
				if (gun->IsKnife()) {
					gun->m_Item().m_iItemIDHigh() = -1; //Forces to use ours fallbackpaintkit
					weapons->Get()->m_nModelIndex() = iModel;
					weapons->Get()->m_iViewModelIndex() = iModel;
					weapons->Get()->m_Item().m_iItemDefinitionIndex() = iKnife; //important 3 lines without them skins on knives doesnt work
					gun->m_Item().m_iAccountID() = LocalPlayerInfo.xuid_low; //Set gun owner to ours also fixes stattrak
					gun->m_nFallbackPaintKit() = Localteam == 3 ? g_Options.KNIFE_SKINCT : g_Options.KNIFE_SKINT;
					gun->m_flFallbackWear() = Localteam == 3 ? g_Options.KNIFE_WearCT : g_Options.KNIFE_WearT; //Lower = better
					gun->m_nFallbackStatTrak() = Localteam == 3 ? g_Options.KNIFE_StattrakCT : g_Options.KNIFE_StattrakT;
					gun->m_nFallbackSeed() = Localteam == 3 ? g_Options.KNIFE_SeedCT : g_Options.KNIFE_SeedT;
					gun->m_Item().m_iEntityQuality() = 3;
				}
				else {
					gun->m_Item().m_iItemIDHigh() = -1; //Forces to use ours fallbackpaintkit
					gun->m_Item().m_iAccountID() = LocalPlayerInfo.xuid_low; //Set gun owner to ours also fixes stattrak
					gun->m_Item().m_iEntityQuality() = 0;
					gun->m_nFallbackPaintKit() = WeaponSkin;
					gun->m_flFallbackWear() = g_Options.SkinChanger_Wear; //Lower = better
					gun->m_nFallbackSeed() = g_Options.SkinChanger_Seed;
					gun->m_nFallbackStatTrak() = g_Options.SkinChanger_Stattrak;
				}
			}
		}

		if (g_Options.SkinChanger_GloveChanger) {
			static bool SetGloves = false;
			
			auto Wearables = Local->m_hMyWearables();

			if (!Local->IsAlive()) {
				auto glove = g_EntityList->GetClientEntityFromHandle(Wearables[0]);
				if (!glove)
					return;

				glove->GetClientNetworkable()->SetDestroyedOnRecreateEntities();
				glove->GetClientNetworkable()->Release();
				SetGloves = false;
				return;
			}

			if (SetGloves)
				return;

			auto glov = reinterpret_cast<IClientEntity*>(g_EntityList->GetClientEntityFromHandle(Wearables[0]));
			if (!glov) {
				static ClientClass* Class;
				if (!Class)
					Class = g_CHLClient->GetAllClasses();

				while (Class){
					if (Class->m_ClassID == ClassId_CEconWearable)
						break;
					Class = Class->m_pNext;
				}

				int iEntry, iSerial;
				Class->m_pCreateFn(iEntry = (g_EntityList->GetHighestEntityIndex() + 1), iSerial = rand() % 4095);  //iSerial = (RandomInt(0x0, 0xFFF) 0xFFF = 4095
				//Wearables[0] = iEntry | (iSerial << 16);

				C_BaseAttributableItem* Ent = reinterpret_cast<C_BaseAttributableItem *>( g_EntityList->GetClientEntityFromHandle(Wearables[0]));
				if (!Ent)
					return;

				Ent->m_Item2().m_iItemDefinitionIndex() = 5033;
				Ent->m_Item2().m_iItemIDHigh() = -1;
				Ent->m_Item2().m_iEntityQuality() = 4;
				Ent->m_Item2().m_iAccountID() = LocalPlayerInfo.xuid_low;
				Ent->m_flFallbackWear() = g_Options.GLOVE_WEAR;
				Ent->m_nFallbackSeed() = 0;
				Ent->m_nFallbackPaintKit() = 10026;
				Ent->SetGloveModelIndex(g_MdlInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
				Ent->GetClientNetworkable()->PreDataUpdate(0); //0 == DATA_UPDATE_CREATED
			}

			SetGloves = true;
		}
	}
}

void SkinChanger::ForceFullUpdate(ClientFrameStage_t stage)
{
	if (g_EngineClient->IsInGame() && g_EngineClient->IsConnected()) {
		if (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
			g_ClientState->ForceFullUpdate();
			SetForceFullUpdate = false;
		}
	}
}
