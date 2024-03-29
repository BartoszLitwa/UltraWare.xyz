#pragma once

enum ECstrike15UserMessages
{
    CS_UM_VGUIMenu = 1,
    CS_UM_Geiger = 2,
    CS_UM_Train = 3,
    CS_UM_HudText = 4,
    CS_UM_SayText = 5,
    CS_UM_SayText2 = 6,
    CS_UM_TextMsg = 7,
    CS_UM_HudMsg = 8,
    CS_UM_ResetHud = 9,
    CS_UM_GameTitle = 10,
    CS_UM_Shake = 12,
    CS_UM_Fade = 13,
    CS_UM_Rumble = 14,
    CS_UM_CloseCaption = 15,
    CS_UM_CloseCaptionDirect = 16,
    CS_UM_SendAudio = 17,
    CS_UM_RawAudio = 18,
    CS_UM_VoiceMask = 19,
    CS_UM_RequestState = 20,
    CS_UM_Damage = 21,
    CS_UM_RadioText = 22,
    CS_UM_HintText = 23,
    CS_UM_KeyHintText = 24,
    CS_UM_ProcessSpottedEntityUpdate = 25,
    CS_UM_ReloadEffect = 26,
    CS_UM_AdjustMoney = 27,
    CS_UM_UpdateTeamMoney = 28,
    CS_UM_StopSpectatorMode = 29,
    CS_UM_KillCam = 30,
    CS_UM_DesiredTimescale = 31,
    CS_UM_CurrentTimescale = 32,
    CS_UM_AchievementEvent = 33,
    CS_UM_MatchEndConditions = 34,
    CS_UM_DisconnectToLobby = 35,
    CS_UM_PlayerStatsUpdate = 36,
    CS_UM_DisplayInventory = 37,
    CS_UM_WarmupHasEnded = 38,
    CS_UM_ClientInfo = 39,
    CS_UM_XRankGet = 40,
    CS_UM_XRankUpd = 41,
    CS_UM_CallVoteFailed = 45,
    CS_UM_VoteStart = 46,
    CS_UM_VotePass = 47,
    CS_UM_VoteFailed = 48,
    CS_UM_VoteSetup = 49,
    CS_UM_ServerRankRevealAll = 50,
    CS_UM_SendLastKillerDamageToClient = 51,
    CS_UM_ServerRankUpdate = 52,
    CS_UM_ItemPickup = 53,
    CS_UM_ShowMenu = 54,
    CS_UM_BarTime = 55,
    CS_UM_AmmoDenied = 56,
    CS_UM_MarkAchievement = 57,
    CS_UM_MatchStatsUpdate = 58,
    CS_UM_ItemDrop = 59,
    CS_UM_GlowPropTurnOff = 60,
    CS_UM_SendPlayerItemDrops = 61,
    CS_UM_RoundBackupFilenames = 62,
    CS_UM_SendPlayerItemFound = 63,
    CS_UM_ReportHit = 64,
    CS_UM_XpUpdate = 65,
    CS_UM_QuestProgress = 66,
    CS_UM_ScoreLeaderboardData = 67,
    CS_UM_PlayerDecalDigitalSignature = 68,
    MAX_ECSTRIKE15USERMESSAGES
};

//enum GloveSKinsID
//{
//	 Charred = 10006,
//	 Snakebite = 10007,
//	 Bronzed = 10008,
//	 Leather = 10009,
//	 Spruce_DDPAT = 10010,
//	 Lunar_Weave = 10013,
//	 Convoy = 10015,
//	 Crimson_Weave = 10016,
//	 Superconductor = 10018,
//	 Arid = 10019,
//	 Slaughter = 10021,
//	 Eclipse = 10024,
//	 Spearmint = 10026,
//	 Boom = 10027,
//	 Cool_Mint = 10028,
//	 Forest_DDPAT = 10030,
//	 Crimson_Kimono = 10033,
//	 Emerald_Web = 10034,
//	 Foundation = 10035,
//	 Badlands = 10036,
//	 Pandoras_Box = 10037,
//	 Hedge_Maze = 10038,
//	 Guerrilla = 10039,
//	 Diamondback = 10040,
//	 King_Snake = 10041,
//	 Imperial_Plaid = 10042,
//	 Overtake = 10043,
//	 Racing_Green = 10044,
//	 Amphibious = 10045,
//	 Bronze_Morph = 10046,
//	 Omega = 10047,
//	 Vice = 10048,
//	 POW = 10049,
//	 Turtle = 10050,
//	 Transport = 10051,
//	 Polygon = 10052,
//	 Cobalt_Skulls = 10053,
//	 Overprint = 10054,
//	 Duct_Tape = 10055,
//	 Arboreal = 10056,
//	 Emerald = 10057,
//	 Mangrove = 10058,
//	 Rattler = 10059,
//	 Case_Hardened = 10060,
//	 Crimson_Web = 10061,
//	 Buckshot = 10062,
//	 Fade = 10063,
//	 Mogul = 10064,
//};

enum ItemDefinitionIndex
{
	WEAPON_INVALID = -1,
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5 = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SHIELD,
	WEAPON_SCAR20,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_SNOWBALL,
	WEAPON_BUMPMINE,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_CLASSIC = 503,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_PARACORD = 517,
	WEAPON_KNIFE_SURVIVAL = 518,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
	WEAPON_KNIFE_NOMAD = 521,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER,
	WEAPON_KNIFE_SKELETON = 525,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA = 5035,
	BARE_HANDS = 69,
	TOOL_AXE = 75,
	TOOL_HAMMER = 76,
	TOOL_WRENCH = 78,
	SPECTRAL_SHIV = 80,
};

enum ClassId {
	ClassId_CAI_BaseNPC = 0,
	ClassId_CAK47,
	ClassId_CBaseAnimating,
	ClassId_CBaseAnimatingOverlay,
	ClassId_CBaseAttributableItem,
	ClassId_CBaseButton,
	ClassId_CBaseCombatCharacter,
	ClassId_CBaseCombatWeapon,
	ClassId_CBaseCSGrenade,
	ClassId_CBaseCSGrenadeProjectile,
	ClassId_CBaseDoor,
	ClassId_CBaseEntity,
	ClassId_CBaseFlex,
	ClassId_CBaseGrenade,
	ClassId_CBaseParticleEntity,
	ClassId_CBasePlayer,
	ClassId_CBasePropDoor,
	ClassId_CBaseTeamObjectiveResource,
	ClassId_CBaseTempEntity,
	ClassId_CBaseToggle,
	ClassId_CBaseTrigger,
	ClassId_CBaseViewModel,
	ClassId_CBaseVPhysicsTrigger,
	ClassId_CBaseWeaponWorldModel,
	ClassId_CBeam,
	ClassId_CBeamSpotlight,
	ClassId_CBoneFollower,
	ClassId_CBRC4Target,
	ClassId_CBreachCharge,
	ClassId_CBreachChargeProjectile,
	ClassId_CBreakableProp,
	ClassId_CBreakableSurface,
	ClassId_CBumpMine,
	ClassId_CBumpMineProjectile,
	ClassId_CC4,
	ClassId_CCascadeLight,
	ClassId_CChicken,
	ClassId_CColorCorrection,
	ClassId_CColorCorrectionVolume,
	ClassId_CCSGameRulesProxy,
	ClassId_CCSPlayer,
	ClassId_CCSPlayerResource,
	ClassId_CCSRagdoll,
	ClassId_CCSTeam,
	ClassId_CDangerZone,
	ClassId_CDangerZoneController,
	ClassId_CDEagle,
	ClassId_CDecoyGrenade,
	ClassId_CDecoyProjectile,
	ClassId_CDrone,
	ClassId_CDronegun,
	ClassId_CDynamicLight,
	ClassId_CDynamicProp,
	ClassId_CEconEntity,
	ClassId_CEconWearable,
	ClassId_CEmbers,
	ClassId_CEntityDissolve,
	ClassId_CEntityFlame,
	ClassId_CEntityFreezing,
	ClassId_CEntityParticleTrail,
	ClassId_CEnvAmbientLight,
	ClassId_CEnvDetailController,
	ClassId_CEnvDOFController,
	ClassId_CEnvGasCanister,
	ClassId_CEnvParticleScript,
	ClassId_CEnvProjectedTexture,
	ClassId_CEnvQuadraticBeam,
	ClassId_CEnvScreenEffect,
	ClassId_CEnvScreenOverlay,
	ClassId_CEnvTonemapController,
	ClassId_CEnvWind,
	ClassId_CFEPlayerDecal,
	ClassId_CFireCrackerBlast,
	ClassId_CFireSmoke,
	ClassId_CFireTrail,
	ClassId_CFish,
	ClassId_CFists,
	ClassId_CFlashbang,
	ClassId_CFogController,
	ClassId_CFootstepControl,
	ClassId_CFunc_Dust,
	ClassId_CFunc_LOD,
	ClassId_CFuncAreaPortalWindow,
	ClassId_CFuncBrush,
	ClassId_CFuncConveyor,
	ClassId_CFuncLadder,
	ClassId_CFuncMonitor,
	ClassId_CFuncMoveLinear,
	ClassId_CFuncOccluder,
	ClassId_CFuncReflectiveGlass,
	ClassId_CFuncRotating,
	ClassId_CFuncSmokeVolume,
	ClassId_CFuncTrackTrain,
	ClassId_CGameRulesProxy,
	ClassId_CGrassBurn,
	ClassId_CHandleTest,
	ClassId_CHEGrenade,
	ClassId_CHostage,
	ClassId_CHostageCarriableProp,
	ClassId_CIncendiaryGrenade,
	ClassId_CInferno,
	ClassId_CInfoLadderDismount,
	ClassId_CInfoMapRegion,
	ClassId_CInfoOverlayAccessor,
	ClassId_CItem_Healthshot,
	ClassId_CItemCash,
	ClassId_CItemDogtags,
	ClassId_CKnife,
	ClassId_CKnifeGG,
	ClassId_CLightGlow,
	ClassId_CMaterialModifyControl,
	ClassId_CMelee,
	ClassId_CMolotovGrenade,
	ClassId_CMolotovProjectile,
	ClassId_CMovieDisplay,
	ClassId_CParadropChopper,
	ClassId_CParticleFire,
	ClassId_CParticlePerformanceMonitor,
	ClassId_CParticleSystem,
	ClassId_CPhysBox,
	ClassId_CPhysBoxMultiplayer,
	ClassId_CPhysicsProp,
	ClassId_CPhysicsPropMultiplayer,
	ClassId_CPhysMagnet,
	ClassId_CPhysPropAmmoBox,
	ClassId_CPhysPropLootCrate,
	ClassId_CPhysPropRadarJammer,
	ClassId_CPhysPropWeaponUpgrade,
	ClassId_CPlantedC4,
	ClassId_CPlasma,
	ClassId_CPlayerPing,
	ClassId_CPlayerResource,
	ClassId_CPointCamera,
	ClassId_CPointCommentaryNode,
	ClassId_CPointWorldText,
	ClassId_CPoseController,
	ClassId_CPostProcessController,
	ClassId_CPrecipitation,
	ClassId_CPrecipitationBlocker,
	ClassId_CPredictedViewModel,
	ClassId_CProp_Hallucination,
	ClassId_CPropCounter,
	ClassId_CPropDoorRotating,
	ClassId_CPropJeep,
	ClassId_CPropVehicleDriveable,
	ClassId_CRagdollManager,
	ClassId_CRagdollProp,
	ClassId_CRagdollPropAttached,
	ClassId_CRopeKeyframe,
	ClassId_CSCAR17,
	ClassId_CSceneEntity,
	ClassId_CSensorGrenade,
	ClassId_CSensorGrenadeProjectile,
	ClassId_CShadowControl,
	ClassId_CSlideshowDisplay,
	ClassId_CSmokeGrenade,
	ClassId_CSmokeGrenadeProjectile,
	ClassId_CSmokeStack,
	ClassId_CSnowball,
	ClassId_CSnowballPile,
	ClassId_CSnowballProjectile,
	ClassId_CSpatialEntity,
	ClassId_CSpotlightEnd,
	ClassId_CSprite,
	ClassId_CSpriteOriented,
	ClassId_CSpriteTrail,
	ClassId_CStatueProp,
	ClassId_CSteamJet,
	ClassId_CSun,
	ClassId_CSunlightShadowControl,
	ClassId_CSurvivalSpawnChopper,
	ClassId_CTablet,
	ClassId_CTeam,
	ClassId_CTeamplayRoundBasedRulesProxy,
	ClassId_CTEArmorRicochet,
	ClassId_CTEBaseBeam,
	ClassId_CTEBeamEntPoint,
	ClassId_CTEBeamEnts,
	ClassId_CTEBeamFollow,
	ClassId_CTEBeamLaser,
	ClassId_CTEBeamPoints,
	ClassId_CTEBeamRing,
	ClassId_CTEBeamRingPoint,
	ClassId_CTEBeamSpline,
	ClassId_CTEBloodSprite,
	ClassId_CTEBloodStream,
	ClassId_CTEBreakModel,
	ClassId_CTEBSPDecal,
	ClassId_CTEBubbles,
	ClassId_CTEBubbleTrail,
	ClassId_CTEClientProjectile,
	ClassId_CTEDecal,
	ClassId_CTEDust,
	ClassId_CTEDynamicLight,
	ClassId_CTEEffectDispatch,
	ClassId_CTEEnergySplash,
	ClassId_CTEExplosion,
	ClassId_CTEFireBullets,
	ClassId_CTEFizz,
	ClassId_CTEFootprintDecal,
	ClassId_CTEFoundryHelpers,
	ClassId_CTEGaussExplosion,
	ClassId_CTEGlowSprite,
	ClassId_CTEImpact,
	ClassId_CTEKillPlayerAttachments,
	ClassId_CTELargeFunnel,
	ClassId_CTEMetalSparks,
	ClassId_CTEMuzzleFlash,
	ClassId_CTEParticleSystem,
	ClassId_CTEPhysicsProp,
	ClassId_CTEPlantBomb,
	ClassId_CTEPlayerAnimEvent,
	ClassId_CTEPlayerDecal,
	ClassId_CTEProjectedDecal,
	ClassId_CTERadioIcon,
	ClassId_CTEShatterSurface,
	ClassId_CTEShowLine,
	ClassId_CTesla,
	ClassId_CTESmoke,
	ClassId_CTESparks,
	ClassId_CTESprite,
	ClassId_CTESpriteSpray,
	ClassId_CTest_ProxyToggle_Networkable,
	ClassId_CTestTraceline,
	ClassId_CTEWorldDecal,
	ClassId_CTriggerPlayerMovement,
	ClassId_CTriggerSoundOperator,
	ClassId_CVGuiScreen,
	ClassId_CVoteController,
	ClassId_CWaterBullet,
	ClassId_CWaterLODControl,
	ClassId_CWeaponAug,
	ClassId_CWeaponAWP,
	ClassId_CWeaponBaseItem,
	ClassId_CWeaponBizon,
	ClassId_CWeaponCSBase,
	ClassId_CWeaponCSBaseGun,
	ClassId_CWeaponCycler,
	ClassId_CWeaponElite,
	ClassId_CWeaponFamas,
	ClassId_CWeaponFiveSeven,
	ClassId_CWeaponG3SG1,
	ClassId_CWeaponGalil,
	ClassId_CWeaponGalilAR,
	ClassId_CWeaponGlock,
	ClassId_CWeaponHKP2000,
	ClassId_CWeaponM249,
	ClassId_CWeaponM3,
	ClassId_CWeaponM4A1,
	ClassId_CWeaponMAC10,
	ClassId_CWeaponMag7,
	ClassId_CWeaponMP5Navy,
	ClassId_CWeaponMP7,
	ClassId_CWeaponMP9,
	ClassId_CWeaponNegev,
	ClassId_CWeaponNOVA,
	ClassId_CWeaponP228,
	ClassId_CWeaponP250,
	ClassId_CWeaponP90,
	ClassId_CWeaponSawedoff,
	ClassId_CWeaponSCAR20,
	ClassId_CWeaponScout,
	ClassId_CWeaponSG550,
	ClassId_CWeaponSG552,
	ClassId_CWeaponSG556,
	ClassId_CWeaponShield,
	ClassId_CWeaponSSG08,
	ClassId_CWeaponTaser,
	ClassId_CWeaponTec9,
	ClassId_CWeaponTMP,
	ClassId_CWeaponUMP45,
	ClassId_CWeaponUSP,
	ClassId_CWeaponXM1014,
	ClassId_CWorld,
	ClassId_CWorldVguiText,
	ClassId_DustTrail,
	ClassId_MovieExplosion,
	ClassId_ParticleSmokeGrenade,
	ClassId_RocketTrail,
	ClassId_SmokeTrail,
	ClassId_SporeExplosion,
	ClassId_SporeTrail,
};


enum ECSPlayerBones
{
    PELVIS = 0,
    SPINE_0,
    SPINE_1,
    SPINE_2,
    SPINE_3,
    NECK_0,
    HEAD_0,
    CLAVICLE_L,
    ARM_UPPER_L,
    ARM_LOWER_L,
    HAND_L,
    FINGER_MIDDLE_META_L,
    FINGER_MIDDLE_0_L,
    FINGER_MIDDLE_1_L,
    FINGER_MIDDLE_2_L,
    FINGER_PINKY_META_L,
    FINGER_PINKY_0_L,
    FINGER_PINKY_1_L,
    FINGER_PINKY_2_L,
    FINGER_INDEX_META_L,
    FINGER_INDEX_0_L,
    FINGER_INDEX_1_L,
    FINGER_INDEX_2_L,
    FINGER_THUMB_0_L,
    FINGER_THUMB_1_L,
    FINGER_THUMB_2_L,
    FINGER_RING_META_L,
    FINGER_RING_0_L,
    FINGER_RING_1_L,
    FINGER_RING_2_L,
    WEAPON_HAND_L,
    ARM_LOWER_L_TWIST,
    ARM_LOWER_L_TWIST1,
    ARM_UPPER_L_TWIST,
    ARM_UPPER_L_TWIST1,
    CLAVICLE_R,
    ARM_UPPER_R,
    ARM_LOWER_R,
    HAND_R,
    FINGER_MIDDLE_META_R,
    FINGER_MIDDLE_0_R,
    FINGER_MIDDLE_1_R,
    FINGER_MIDDLE_2_R,
    FINGER_PINKY_META_R,
    FINGER_PINKY_0_R,
    FINGER_PINKY_1_R,
    FINGER_PINKY_2_R,
    FINGER_INDEX_META_R,
    FINGER_INDEX_0_R,
    FINGER_INDEX_1_R,
    FINGER_INDEX_2_R,
    FINGER_THUMB_0_R,
    FINGER_THUMB_1_R,
    FINGER_THUMB_2_R,
    FINGER_RING_META_R,
    FINGER_RING_0_R,
    FINGER_RING_1_R,
    FINGER_RING_2_R,
    WEAPON_HAND_R,
    ARM_LOWER_R_TWIST,
    ARM_LOWER_R_TWIST1,
    ARM_UPPER_R_TWIST,
    ARM_UPPER_R_TWIST1,
    LEG_UPPER_L,
    LEG_LOWER_L,
    ANKLE_L,
    BALL_L,
    LFOOT_LOCK,
    LEG_UPPER_L_TWIST,
    LEG_UPPER_L_TWIST1,
    LEG_UPPER_R,
    LEG_LOWER_R,
    ANKLE_R,
    BALL_R,
    RFOOT_LOCK,
    LEG_UPPER_R_TWIST,
    LEG_UPPER_R_TWIST1,
    FINGER_PINKY_L_END,
    FINGER_PINKY_R_END,
    VALVEBIPED_WEAPON_BONE,
    LH_IK_DRIVER,
    PRIMARY_JIGGLE_JNT,
    MAX_ECSPLAYERBONES
};

enum EntityFlags
{
    FL_ONGROUND = (1 << 0),
    FL_DUCKING = (1 << 1),
    FL_WATERJUMP = (1 << 2),
    FL_ONTRAIN = (1 << 3),
    FL_INRAIN = (1 << 4),
    FL_FROZEN = (1 << 5),
    FL_ATCONTROLS = (1 << 6),
    FL_CLIENT = (1 << 7),
    FL_FAKECLIENT = (1 << 8),
    MAX_ENTITYFLAGS
};

enum LifeState : unsigned char
{
    LIFE_ALIVE = 0,// alive
    LIFE_DYING = 1, // playing death animation or still falling off of a ledge waiting to hit ground
    LIFE_DEAD = 2, // dead. lying still.
    MAX_LIFESTATE
};

enum WeaponSound_t
{
    EMPTY,
    SINGLE,
    SINGLE_NPC,
    WPN_DOUBLE, // Can't be "DOUBLE" because windows.h uses it.
    DOUBLE_NPC,
    BURST,
    RELOAD,
    RELOAD_NPC,
    MELEE_MISS,
    MELEE_HIT,
    MELEE_HIT_WORLD,
    SPECIAL1,
    SPECIAL2,
    SPECIAL3,
    TAUNT,
    FAST_RELOAD,
    // Add new shoot sound types here
    REVERSE_THE_NEW_SOUND,
    NUM_SHOOT_SOUND_TYPES,
    MAX_WEAPONSOUND
};

enum MoveType_t
{
    MOVETYPE_NONE = 0,
    MOVETYPE_ISOMETRIC,
    MOVETYPE_WALK,
    MOVETYPE_STEP,
    MOVETYPE_FLY,
    MOVETYPE_FLYGRAVITY,
    MOVETYPE_VPHYSICS,
    MOVETYPE_PUSH,
    MOVETYPE_NOCLIP,
    MOVETYPE_LADDER,
    MOVETYPE_OBSERVER,
    MOVETYPE_CUSTOM,
    MOVETYPE_LAST = MOVETYPE_CUSTOM,
    MOVETYPE_MAX_BITS = 4,
    MAX_MOVETYPE
};

enum Skins
{
	MP7_Groundwater = 2,
	CandyApple = 3,
	ForestDDPAT = 5,
	ArcticCamo = 6,
	DesertStorm = 8,
	BengalTiger = 9,
	Copperhead = 10,
	Skulls = 11,
	CrimsonWeb = 12,
	BlueStreak = 13,
	RedLaminate = 14,
	Gunsmoke = 15,
	JungleTiger = 16,
	UranDDPAT = 17,
	Virus = 20,
	GraniteMarleized = 21,
	ContrastSpray = 22,
	ForestLeaves = 25,
	LichenDashed = 26,
	BoneMask = 27,
	AUG_AnodizedNavy = 28,
	SnakeCamo = 30,
	Silver = 32,
	MP9_HotRod = 33,
	MetallicDDPAT = 34,
	Ossified = 36,
	Blaze = 37,
	Fade = 38,
	Bulldozer = 39,
	Night = 40,
	Copper = 41,
	BlueSteel = 42,
	Stained = 43,
	CaseHardened = 44,
	Contractor = 46,
	Colony = 47,
	DragonTattoo = 48,
	LightningStrike = 51,
	Slaughter = 59,
	DarkWater = 60,
	Hypnotic = 61,
	Bloomstick = 62,
	ColdBlooded = 67,
	CaronFier = 70,
	Scorpion = 71,
	SafariMesh = 72,
	Wings = 73,
	PolarCamo = 74,
	BlizzardMarleized = 75,
	WinterForest = 76,
	BorealForest = 77,
	ForestNight = 78,
	OrangeDDPAT = 83,
	PinkDDPAT = 84,
	Mudder = 90,
	Cyanospatter = 92,
	Caramel = 93,
	Grassland = 95,
	BlueSpruce = 96,
	Ultraviolet = 98,
	GLOCK_SandDune = 99,
	Storm = 100,
	TEC9_Tornado = 101,
	Whiteout = 102,
	GrasslandLeaves = 104,
	PolarMesh = 107,
	Condemned = 110,
	GlacierMesh = 111,
	SandMesh = 116,
	SageSpray = 119,
	JungleSpray = 122,
	SandSpray = 124,
	UranPerforated = 135,
	WavesPerforated = 136,
	OrangePeel = 141,
	UranMasked = 143,
	JungleDashed = 147,
	SandDashed = 148,
	UranDashed = 149,
	XM_Jungle = 151,
	Demolition = 153,
	Afterimage = 154,
	BulletRain = 155,
	DeathyKitty = 156,
	SCAR20_Palm = 157,
	Walnut = 158,
	Brass = 159,
	Splash = 162,
	ModernHunter = 164,
	SplashJam = 165,
	BlazeOrange = 166,
	M4A4_RadiationHazard = 167,
	TEC9_NuclearThreat = 168,
	P90_FalloutWarning = 169,
	Predator = 170,
	IrradiatedAlert = 171,
	BlackLaminate = 172,
	BOOM = 174,
	Scorched = 175,
	FadedZera = 176,
	Memento = 177,
	Doomkitty = 178,
	TEC9_NuclearThreat_2 = 179,
	FireSerpent = 180,
	AWP_Corticera = 181,
	EmeraldDragon = 182,
	Overgrowth = 183,
	P2000_Corticera = 184,
	GoldenKoi = 185,
	WaveSpray = 186,
	Zirka = 187,
	Graven = 188,
	M4A1S_BrightWater = 189,
	BlackLima = 190,
	Tempest = 191,
	Shattered = 192,
	BonePile = 193,
	Spitfire = 194,
	Demeter = 195,
	SCAR20_Emerald = 196,
	AUG_AnodizedNavy_2 = 197,
	Hazard = 198,
	DrySeason = 199,
	MayanDreams = 200,
	NEGEV_Palm = 201,
	JungleDDPAT = 202,
	RustCoat = 203,
	Mosaico = 204,
	XM_Jungle_2 = 205,
	TEC9_Tornado_2 = 206,
	Facets = 207,
	GLOCK_SandDune_2 = 208,
	MP7_Groundwater_2 = 209,
	AnodizedGunmetal = 210,
	P2000_OceanFoam = 211,
	AWP_Graphite = 212,
	P2000_OceanFoam_2 = 213,
	NOVA_Graphite = 214,
	X_Ray = 215,
	BlueTitanium = 216,
	BloodTiger = 217,
	Hexane = 218,
	Hive = 219,
	Hemogloin = 220,
	Serum = 221,
	BloodintheWater = 222,
	Nightshade = 223,
	WaterSigil = 224,
	GhostCamo = 225,
	BlueLaminate = 226,
	ElectricHive = 227,
	BlindSpot = 228,
	AzureZera = 229,
	SteelDisruption = 230,
	CoaltDisruption = 231,
	SCAR20_CrimsonWeb = 232,
	TropicalStorm = 233,
	AshWood = 234,
	VariCamo = 235,
	NightOps = 236,
	UranRule = 237,
	VariCamoBlue = 238,
	CaliCamo = 240,
	HuntingBlind = 241,
	ArmyMesh = 242,
	GatorMesh = 243,
	Teardown = 244,
	ArmyRecon = 245,
	P2000_AmberFade = 246,
	SG553_DamascusSteel = 247,
	RedQuartz = 248,
	CoaltQuartz = 249,
	FullStop = 250,
	PitViper = 251,
	SilverQuartz = 252,
	AcidFade = 253,
	CZ75A_Nitro = 254,
	M4A4_Asiimov = 255,
	TheKraken = 256,
	M4A1S_Guardian = 257,
	Mehndi = 258,
	AWP_Redline = 259,
	FAMAS_Pulse = 260,
	Marina = 261,
	RoseIron = 262,
	RisingSkull = 263,
	GALILAR_Sandstorm = 264,
	FIVESEVEN_Kami = 265,
	Magma = 266,
	CoaltHalftone = 267,
	TreadPlate = 268,
	TheFuschiaIsNow = 269,
	Victoria = 270,
	Undertow = 271,
	TitaniumBit = 272,
	Heirloom = 273,
	CopperGalaxy = 274,
	RedFragCam = 275,
	Panther = 276,
	Stainless = 277,
	BlueFissure = 278,
	AWP_Asiimov = 279,
	Chameleon = 280,
	Corporal = 281,
	AK47_Redline = 282,
	Trigon = 283,
	MAC10_Heat = 284,
	Terrain = 285,
	NOVA_Antique = 286,
	SG553_Pulse = 287,
	Sergeant = 288,
	TEC9_Sandstorm = 289,
	USPS_Guardian = 290,
	MAG7_HeavenGuard = 291,
	DeathRattle = 293,
	GreenApple = 294,
	Franklin = 295,
	Meteorite = 296,
	Tuxedo = 297,
	ArmySheen = 298,
	CagedSteel = 299,
	EmeraldPinstripe = 300,
	AtomicAlloy = 301,
	Vulcan = 302,
	Isaac = 303,
	Slashed = 304,
	AUG_Torque = 305,
	PPBIZON_Antique = 306,
	Retriution = 307,
	GalilAR_Kami = 308,
	Howl = 309,
	Curse = 310,
	DesertWarfare = 311,
	SCAR20_Cyrex = 312,
	Orion = 313,
	XM1014_HeavenGuard = 314,
	PoisonDart = 315,
	Jaguar = 316,
	Bratatat = 317,
	RoadRash = 318,
	Detour = 319,
	RedPython = 320,
	MasterPiece = 321,
	CZ75A_Nitro_2 = 322,
	RustCoat_2 = 323,
	Chalice = 325,
	Knight = 326,
	Chainmail = 327,
	HandCannon = 328,
	DarkAge = 329,
	Briar = 330,
	RoyalBlue = 332,
	Indigo = 333,
	Twist = 334,
	Module = 335,
	M4A4_Desert_Strike = 336,
	Tatter = 337,
	Pulse = 338,
	Caiman = 339,
	JetSet = 340,
	AK47_FirstClass = 341,
	Leather = 342,
	Commuter = 343,
	DragonLore = 344,
	SAWEDOFF_FirstClass = 345,
	CoachClass = 346,
	Pilot = 347,
	RedLeather = 348,
	Osiris = 349,
	Tigris = 350,
	Conspiracy = 351,
	FowlPlay = 352,
	WaterElemental = 353,
	UranHazard = 354,
	NEGEV_Desert_Strike = 355,
	Koi = 356,
	Ivory = 357,
	Supernova = 358,
	P90_Asiimov = 359,
	M4A1S_Cyrex = 360,
	Ayss = 361,
	Layrinth = 362,
	Traveler = 363,
	BusinessClass = 364,
	OlivePlaid = 365,
	GreenPlaid = 366,
	Reactor = 367,
	SettingSun = 368,
	NuclearWaste = 369,
	BoneMachine = 370,
	Styx = 371,
	NuclearGarden = 372,
	Contamination = 373,
	Toxic = 374,
	AUG_RadiationHazard = 375,
	ChemicalGreen = 376,
	HotShot = 377,
	SG553_FalloutWarning = 378,
	Cererus = 379,
	AK47_WastelandRebel = 380,
	Grinder = 381,
	Murky = 382,
	Basilisk = 383,
	Griffin = 384,
	Firestarter = 385,
	Dart = 386,
	UrbanHazard = 387,
	P250_Cartel = 388,
	FireElemental = 389,
	Highwayman = 390,
	Cardiac = 391,
	Delusion = 392,
	Tranquility = 393,
	AK47_Cartel = 394,
	AWP_Manowar = 395,
	UranShock = 396,
	Naga = 397,
	Chatterox = 398,
	Catacoms = 399,
	DragonKing = 400,
	SystemLock = 401,
	Malachite = 402,
	DeadlyPoison = 403,
	Muertos = 404,
	Serenity = 405,
	Grotto = 406,
	Quicksilver = 407,
	TigerTooth = 409,
	DamascusSteel_DARK = 411,
	DamascusSteel_BRIGHT = 410,
	Marble_Fade = 413,
	RustCoat_3 = 414,
	Doppler_RUBY = 415,
	Doppler_SAPPHIRE = 416,
	Doppler_BLACKPEARL = 417,
	Doppler_PHASE1 = 418,
	Doppler_PHASE2 = 419,
	Doppler_PHASE3 = 420,
	Doppler_PHASE4 = 421,
	AK47_EliteBuild = 422,
	ArmorCore = 423,
	WormGod = 424,
	BronzeDeco = 425,
	P250_Valence = 426,
	MonkeyBusiness = 427,
	Eco = 428,
	Djinn = 429,
	M4A1S_HyperBeast = 430,
	MAG7_Heat = 431,
	NEGEV_Manowar = 432,
	NeonRider = 433,
	Origami = 434,
	PolePosition = 435,
	GrandPrix = 436,
	TwilightGalaxy = 437,
	Chronos = 438,
	Hades = 439,
	IcarusFell = 440,
	MinotaursLabyrinth = 441,
	Asterion = 442,
	Pathfinder = 443,
	Daedalus = 444,
	M4A1S_HotRod = 445,
	Medusa = 446,
	Duelist = 447,
	MP9_PandorasBox = 448,
	Poseidon = 449,
	MooninLira = 450,
	SuninLeo = 451,
	ShippingForecast = 452,
	CZ7A_Emerald = 453,
	ParaGreen = 454,
	AkihabaraAccept = 455,
	Hydroponic = 456,
	BamooPrint = 457,
	BamooShadow = 458,
	BamooForest = 459,
	AquaTerrace = 460,
	CounterTerrace = 462,
	Terrace = 463,
	NeonKimono = 464,
	OrangeKimono = 465,
	CrimsonKimono = 466,
	MintKimono = 467,
	MidnightStorm = 468,
	SunsetStorm = 469,
	SunsetStorm_2 = 470,
	Dayreak = 471,
	ImpactDrill = 472,
	Seaird = 473,
	AquamarineRevenge = 474,
	AWP_HyperBeast = 475,
	YellowJacket = 476,
	NeuralNet = 477,
	RocketPop = 478,
	BunsenBurner = 479,
	EvilDaimyo = 480,
	Nemesis = 481,
	RuyPoisonDart = 482,
	Loudmouth = 483,
	Ranger = 484,
	Handgun = 485,
	P90_EliteBuild = 486,
	SG553_Cyrex = 487,
	Riot = 488,
	USPS_Torque = 489,
	FrontsideMisty = 490,
	DualingDragons = 491,
	SurvivorZ = 492,
	Flux = 493,
	StoneCold = 494,
	Wraiths = 495,
	NeulaCrusader = 496,
	GoldenCoil = 497,
	Rangeen = 498,
	CoaltCore = 499,
	SpecialDelivery = 500,
	Wingshot = 501,
	GreenMarine = 502,
	BigIron = 503,
	KillConfirmed = 504,
	XM1014_Scumria = 505,
	PointDisarray = 506,
	Ricochet = 507,
	FuelRod = 508,
	Corinthian = 509,
	Retroution = 510,
	TheExecutioner = 511,
	RoyalPaladin = 512,
	PowerLoader = 514,
	Imperial = 515,
	Shapewood = 516,
	Yorick = 517,
	Outreak = 518,
	TigerMoth = 519,
	Avalanche = 520,
	TecluBurner = 521,
	R8_Fade = 522,
	R8_AmberFade = 523,
	AK47_FuelInjector = 524,
	EliteBuild = 525,
	PhoticZone = 526,
	KumichoDragon = 527,
	Cartel = 528,
	FAMAS_Valence = 529,
	Triumvirate = 530,
	RoyalLegion = 532,
	TheBattlestar = 533,
	LapisGator = 534,
	Praetorian = 535,
	Impire = 536,
	NOVA_HyperBeast = 537,
	Necropos = 538,
	Jamiya = 539,
	LeadConduit = 540,
	Doppler_1 = 617,
	Doppler_2 = 618,
	Doppler_3 = 619,
	Ultraviolet_1 = 620,
	Ultraviolet_2 = 621,
	FleetFlock = 541,
	JudgementofAnuis = 542,
	RedAstor = 543,
	Ventilators = 544,
	OrangeCrash = 545,
	Firefight = 546,
	Spectre = 547,
	Chanticos_Fire = 548,
	Bioleak = 549,
	Oceanic = 550,
	P250_Asiimov = 551,
	Fuar = 552,
	Atlas = 553,
	GhostCrusader = 554,
	Re_Entry = 555,
	PrimalSaer = 556,
	BlackTie = 557,
	Lore_BAYONET = 558,
	Lore_FLIP = 559,
	Lore_GUT = 560,
	Lore_KARAMBIT = 561,
	Lore_M9BAYONET = 562,
	BlackLaminate_BAYONET = 563,
	BlackLaminate_FLIP = 564,
	BlackLaminate_GUT = 565,
	BlackLaminate_KARAMBIT = 566,
	BlackLaminate_M9BAYONET = 567,
	GammaDoppler_EMERALD = 568,
	GammaDoppler_PHASE1 = 569,
	GammaDoppler_PHASE2 = 570,
	GammaDoppler_PHASE3 = 571,
	GammaDoppler_PHASE4 = 572,
	Autotronic_BAYONET = 573,
	Autotronic_FLIP = 574,
	Autotronic_GUT = 575,
	Autotronic_KARAMBIT = 576,
	Autotronic_M9BAYONET = 577,
	BrightWater = 578,
	BrightWater_M9BAYONET = 579,
	Freehand = 580,
	Freehand_M9BAYONET = 581,
	Freehand_KARAMBIT = 582,
	Aristocrat = 583,
	Phoos = 584,
	ViolentDaimyo = 585,
	GLOCK_WastelandRebel = 586,
	M4A1S_MechaIndustries = 587,
	DESERT_EAGLE_MechaIndustries = 805,
	DesolateSpace = 588,
	Carnivore = 589,
	Exo = 590,
	ImperialDragon = 591,
	IronClad = 592,
	Chopper = 593,
	Harvester = 594,
	Reoot = 595,
	Limelight = 596,
	SCAR20_Bloodsport = 597,
	Aerial = 598,
	IceCap = 599,
	NeonRevolution = 600,
	SydMead = 601,
	Imprint = 602,
	Directive = 603,
	RollCage = 604,
	FIVESEVEN_Scumria = 605,
	Ventilator = 606,
	Weasel = 607,
	Petroglyph = 608,
	Airlock = 609,
	Dazzle = 610,
	Grim = 611,
	Powercore = 612,
	Triarch = 613,
	TEC9_FuelInjector = 614,
	Briefing = 615,
	Slipstream = 616,
	Polymer = 622,
	Ironwork = 623,
	Dragonfire = 624,
	RoyalConsorts = 625,
	FAMAS_MechaIndustries = 626,
	Cirrus = 627,
	Stinger = 628,
	BlackSand = 629,
	SandScale = 630,
	Flashack = 631,
	BuzzKill = 632,
	Sonar = 633,
	Gila = 634,
	Turf = 635,
	ShallowGrave = 636,
	USPS_Cyrex = 637,
	WastelandPrincess = 638,
	AK47_Bloodsport = 639,
	FeverDream = 640,
	JungleSlipstream = 641,
	SCAR20_Blueprint = 642,
	Xiangliu = 643,
	Decimator = 644,
	OxideBlaze = 645,
	Capillary = 646,
	CrimsonTsunami = 647,
	EmeraldPoisonDart = 648,
	Akoen = 649,
	Ripple = 650,
	LastDive = 651,
	Scaffold = 652,
	USPS_Neo_Noir = 653,
	Seasons = 654,
	Zander = 655,
	OritMk01 = 656,
	USPS_Blueprint = 657,
	CoraStrike = 658,
	Macare = 659,
	FIVESEVEN_HyperBeast = 660,
	SugarRush = 661,
	OniTaiji = 662,
	Briefing_2 = 663,
	Hellfire = 664,
	Aloha = 665,
	HardWater = 666,
	Woodsman = 667,
	RedRock = 668,
	DeathGrip = 669,
	sHead = 670,
	CutOut = 671,
	MetalFlowers = 672,
	Morris = 673,
	Triqua = 674,
	TheEmpress = 675,
	HighRoller = 676,
	Hunter = 677,
	SeeYaLater = 678,
	Goo = 679,
	OffWorld = 680,
	LeadedGlass = 681,
	Oceanic_2 = 682,
	LlamaCannon = 683,
	CrackedOpal = 684,
	JungleSlipstream_2 = 685,
	Phantom = 686,
	Tacticat = 687,
	Exposure = 688,
	Ziggy = 689,
	Stymphalian = 690,
	Mortis = 691,
	NightRiot = 692,
	FlameTest = 693,
	Moonrise = 694,
	M4A1S_Neo_Noir = 695,
	MP7_Bloodsport = 696,
	BlackSand_2 = 697,
	Lionfish = 698,
	WildSix = 699,
	UranHazard_2 = 700,
	Grip = 701,
	Aloha_2 = 702,
	SWAG_7 = 703,
	ArcticWolf = 704,
	Cortex = 705,
	OxideBlaze_2 = 706
};
