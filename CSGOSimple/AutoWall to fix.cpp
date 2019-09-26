#include "AutoWall.hpp"

#define CHAR_TEX_FLESH		'F'
#define CHAR_TEX_GRATE		'G'
#define CHAR_TEX_PLASTIC	'L'
#define CHAR_TEX_METAL		'M'
#define CHAR_TEX_CARDBOARD	'U'
#define CHAR_TEX_WOOD		'W'
#define CHAR_TEX_GLASS		'Y'

Autowall autowall;
////////////////////////////////////// Traces //////////////////////////////////////
void Autowall::TraceLine(Vector& absStart, Vector& absEnd, unsigned int mask, IClientEntity* ignore, CGameTrace* ptr)
{
	Ray_t ray;
	ray.Init(absStart, absEnd);
	CTraceFilter filter;
	filter.pSkip = ignore;

	g_EngineTrace->TraceRay(ray, mask, &filter, ptr);
}
void __stdcall dummy(void*, void*, void*) {}

void Autowall::ClipTraceToPlayers(Vector& absStart, Vector absEnd, unsigned int mask, ITraceFilter* filter, CGameTrace* tr)
{
	//TODO: Un-ASM this
#ifdef _WIN32
	_asm
	{
		mov eax, filter
		lea ecx, tr
		push ecx
		push eax
		push mask
		lea edx, absEnd
		lea ecx, absStart
		call UTIL_ClipTraceToPlayers
		add esp, 0xC
	}
#else
	UTIL_ClipTraceToPlayers(absStart, absEnd, mask, filter, tr, 60.f, 0.f);
#endif

	reinterpret_cast<void(__fastcall*)(Vector&, Vector&, unsigned int, ITraceFilter*, CGameTrace*)>(UTIL_ClipTraceToPlayers)
		(absStart, absEnd, mask, filter, tr);
	reinterpret_cast<void(__cdecl*)(void*, void*, void*)>(&dummy)(tr, tr, tr);
}

////////////////////////////////////// Legacy Functions //////////////////////////////////////
void Autowall::GetBulletTypeParameters(float& maxRange, float& maxDistance, char* bulletType, bool sv_penetration_type)
{
	if (sv_penetration_type)
	{
		maxRange = 35.0;
		maxDistance = 3000.0;
	}
	else
	{
		//Play tribune to framerate. Thanks, stringcompare
		//Regardless I doubt anyone will use the old penetration system anyway; so it won't matter much.
		if (!strcmp(bulletType, "BULLET_PLAYER_338MAG"))
		{
			maxRange = 45.0;
			maxDistance = 8000.0;
		}
		if (!strcmp(bulletType, "BULLET_PLAYER_762MM"))
		{
			maxRange = 39.0;
			maxDistance = 5000.0;
		}
		if (!strcmp(bulletType, "BULLET_PLAYER_556MM") || !strcmp(bulletType, "BULLET_PLAYER_556MM_SMALL") || !strcmp(bulletType, "BULLET_PLAYER_556MM_BOX"))
		{
			maxRange = 35.0;
			maxDistance = 4000.0;
		}
		if (!strcmp(bulletType, "BULLET_PLAYER_57MM"))
		{
			maxRange = 30.0;
			maxDistance = 2000.0;
		}
		if (!strcmp(bulletType, "BULLET_PLAYER_50AE"))
		{
			maxRange = 30.0;
			maxDistance = 1000.0;
		}
		if (!strcmp(bulletType,  "BULLET_PLAYER_357SIG") || !strcmp(bulletType,  "BULLET_PLAYER_357SIG_SMALL") || !strcmp(bulletType,  "BULLET_PLAYER_357SIG_P250") 
			|| !strcmp(bulletType,  "BULLET_PLAYER_357SIG_MIN"))
		{
			maxRange = 25.0;
			maxDistance = 800.0;
		}
		if (!strcmp(bulletType,  "BULLET_PLAYER_9MM"))
		{
			maxRange = 21.0;
			maxDistance = 800.0;
		}
		if (!strcmp(bulletType,  "BULLET_PLAYER_45ACP"))
		{
			maxRange = 15.0;
			maxDistance = 500.0;
		}
		if (!strcmp(bulletType,  "BULLET_PLAYER_BUCKSHOT"))
		{
			maxRange = 0.0;
			maxDistance = 0.0;
		}
	}
}

////////////////////////////////////// Misc Functions //////////////////////////////////////
bool Autowall::IsBreakableEntity(IClientEntity* entity)
{
	if (!entity || entity->EntIndex() == 0)
		return false;

	//m_takeDamage isn't properly set when using the signature.
	//Back it up, set it to true, then restore.
	int takeDamageBackup = ((C_BaseEntity*)entity)->m_takeDamage();

	ClientClass* pClass = entity->GetClientClass();

	//				 '       ''     '      '   '
	//			    01234567890123456     012345678
	//Check against CBreakableSurface and CBaseDoor

	//Windows etc. are CBrekableSurface
	//Large garage door in Office is CBaseDoor and it get's reported as a breakable when it is not one
	//This is seperate from "CPropDoorRotating", which is a normal door.
	//Normally you would also check for "CFuncBrush" but it was acting oddly so I removed it. It's below if interested.
	//((clientClass->m_pNetworkName[1]) != 'F' || (clientClass->m_pNetworkName[4]) != 'c' || (clientClass->m_pNetworkName[5]) != 'B' || (clientClass->m_pNetworkName[9]) != 'h')

	if ((pClass->m_pNetworkName[1] == 'B' && pClass->m_pNetworkName[9] == 'e' && pClass->m_pNetworkName[10] == 'S' && pClass->m_pNetworkName[16] == 'e')
		|| (pClass->m_pNetworkName[1] != 'B' || pClass->m_pNetworkName[5] != 'D'))
		((C_BaseEntity*)entity)->m_takeDamage() = 2;  //DAMAGE_YES

	bool breakable = IsBreakableEntity(entity);
	((C_BaseEntity*)entity)->m_takeDamage() = takeDamageBackup;

	return breakable;
}

void Autowall::ScaleDamage(CGameTrace& enterTrace, CCSWeaponInfo* weaponData, float& currentDamage)
{
	//Cred. to N0xius for reversing this.
	//TODO: _xAE^; look into reversing this yourself sometime

	bool hasHeavyArmor = ((C_BasePlayer*)enterTrace.hit_entity)->m_bHasHeavyArmor();
	int armorValue = ((C_BasePlayer*)enterTrace.hit_entity)->m_ArmorValue();
	int hitGroup = enterTrace.hitgroup;

	//Fuck making a new function, lambda beste. ~ Does the person have armor on for the hitbox checked?
	auto IsArmored = [&enterTrace]()->bool
	{
		C_BasePlayer* targetEntity = (C_BasePlayer*)enterTrace.hit_entity;
		switch (enterTrace.hitgroup)
		{
		case HITGROUP_HEAD:
			return !!(C_BasePlayer*)targetEntity->m_bHasHelmet(); //Fuck compiler errors - force-convert it to a bool via (!!)
		case HITGROUP_GENERIC:
		case HITGROUP_CHEST:
		case HITGROUP_STOMACH:
		case HITGROUP_LEFTARM:
		case HITGROUP_RIGHTARM:
			return true;
		default:
			return false;
		}
	};

	switch (hitGroup)
	{
	case HITGROUP_HEAD:
		currentDamage *= hasHeavyArmor ? 2.f : 4.f; //Heavy Armor does 1/2 damage
		break;
	case HITGROUP_STOMACH:
		currentDamage *= 1.25f;
		break;
	case HITGROUP_LEFTLEG:
	case HITGROUP_RIGHTLEG:
		currentDamage *= 0.75f;
		break;
	default:
		break;
	}

	if (armorValue > 0 && IsArmored())
	{
		float bonusValue = 1.f, armorBonusRatio = 0.5f, armorRatio = weaponData->flArmorRatio / 2.f;

		//Damage gets modified for heavy armor users
		if (hasHeavyArmor)
		{
			armorBonusRatio = 0.33f;
			armorRatio *= 0.5f;
			bonusValue = 0.33f;
		}

		auto NewDamage = currentDamage * armorRatio;

		if (hasHeavyArmor)
			NewDamage *= 0.85f;

		if (((currentDamage - (currentDamage * armorRatio)) * (bonusValue * armorBonusRatio)) > armorValue)
			NewDamage = currentDamage - (armorValue / armorBonusRatio);

		currentDamage = NewDamage;
	}
}

////////////////////////////////////// Main Autowall Functions //////////////////////////////////////
bool Autowall::TraceToExit(CGameTrace& enterTrace, CGameTrace& exitTrace, Vector startPosition, Vector direction)
{
	/*
	Masks used:
	MASK_SHOT_HULL					 = 0x600400B
	CONTENTS_HITBOX					 = 0x40000000
	MASK_SHOT_HULL | CONTENTS_HITBOX = 0x4600400B
	*/

	Vector start, end;
	float maxDistance = 90.f, rayExtension = 4.f, currentDistance = 0;
	int firstContents = 0;

	while (currentDistance <= maxDistance)
	{
		//Add extra distance to our ray
		currentDistance += rayExtension;

		//Multiply the direction vector to the distance so we go outwards, add our position to it.
		start = startPosition + direction * currentDistance;

		if (!firstContents)
			firstContents = g_EngineTrace->GetPointContents(start, MASK_SHOT_HULL | CONTENTS_HITBOX, nullptr); /*0x4600400B*/
		int pointContents = g_EngineTrace->GetPointContents(start, MASK_SHOT_HULL | CONTENTS_HITBOX, nullptr);

		if (!(pointContents & MASK_SHOT_HULL) || pointContents & CONTENTS_HITBOX && pointContents != firstContents) /*0x600400B, *0x40000000*/
		{
			//Let's setup our end position by deducting the direction by the extra added distance
			end = start - (direction * rayExtension);

			//Let's cast a ray from our start pos to the end pos
			TraceLine(start, end, MASK_SHOT_HULL | CONTENTS_HITBOX, nullptr, &exitTrace);

			//Let's check if a hitbox is in-front of our enemy and if they are behind of a solid wall
			if (exitTrace.startsolid && exitTrace.surface.flags & SURF_HITBOX)
			{
				TraceLine(start, startPosition, MASK_SHOT_HULL, exitTrace.hit_entity, &exitTrace);

				if (exitTrace.DidHit() && !exitTrace.startsolid)
				{
					start = exitTrace.endpos;
					return true;
				}

				continue;
			}

			//Can we hit? Is the wall solid?
			if (exitTrace.DidHit() && !exitTrace.startsolid)
			{

				//Is the wall a breakable? If so, let's shoot through it.
				if (Autowall::IsBreakableEntity(enterTrace.hit_entity) && Autowall::IsBreakableEntity(exitTrace.hit_entity))
					return true;

				if (enterTrace.surface.flags & SURF_NODRAW || !(exitTrace.surface.flags & SURF_NODRAW) && (exitTrace.plane.normal.Dot(direction) <= 1.f))
				{
					float multAmount = exitTrace.fraction * 4.f;
					start -= direction * multAmount;
					return true;
				}

				continue;
			}

			if (!exitTrace.DidHit() || exitTrace.startsolid)
			{
				if (enterTrace.DidHitNonWorldEntity() && Autowall::IsBreakableEntity(enterTrace.hit_entity))
				{
					exitTrace = enterTrace;
					exitTrace.endpos = start + direction;
					return true;
				}

				continue;
			}
		}
	}
	return false;
}

bool Autowall::HandleBulletPenetration(CCSWeaponInfo* weaponData, CGameTrace& enterTrace, Vector& eyePosition, Vector direction, int& possibleHitsRemaining, float& currentDamage, float penetrationPower, bool sv_penetration_type, float ff_damage_reduction_bullets, float ff_damage_bullet_penetration)
{
	//Because there's been issues regarding this- putting this here.
	if (&currentDamage == nullptr)
		throw std::invalid_argument("currentDamage is null!");

	if (!g_LocalPlayer)
		return false;
	CGameTrace exitTrace;
	C_BaseEntity* pEnemy = (C_BasePlayer*)enterTrace.hit_entity;
	surfacedata_t* enterSurfaceData = g_PhysSurface->GetSurfaceData(enterTrace.surface.surfaceProps);
	int enterMaterial = enterSurfaceData->game.material;

	float enterSurfPenetrationModifier = enterSurfaceData->game.flPenetrationModifier;
	float enterDamageModifier = enterSurfaceData->game.flDamageModifier;
	float thickness, modifier, lostDamage, finalDamageModifier, combinedPenetrationModifier;
	bool isSolidSurf = ((enterTrace.contents >> 3) & CONTENTS_SOLID);
	bool isLightSurf = ((enterTrace.surface.flags >> 7) & SURF_LIGHT);

	if (possibleHitsRemaining <= 0
		//Test for "DE_CACHE/DE_CACHE_TELA_03" as the entering surface and "CS_ITALY/CR_MISCWOOD2B" as the exiting surface.
		//Fixes a wall in de_cache which seems to be broken in some way. Although bullet penetration is not recorded to go through this wall
		//Decals can be seen of bullets within the glass behind of the enemy. Hacky method, but works.
		//You might want to have a check for this to only be activated on de_cache.
		|| (enterTrace.surface.name == (const char*)0x2227c261 && exitTrace.surface.name == (const char*)0x2227c868)
		|| (!possibleHitsRemaining && !isLightSurf && !isSolidSurf && enterMaterial != CHAR_TEX_GRATE && enterMaterial != CHAR_TEX_GLASS)
		|| weaponData->flPenetration <= 0.f
		|| !TraceToExit(enterTrace, exitTrace, enterTrace.endpos, direction)
		&& !(g_EngineTrace->GetPointContents(enterTrace.endpos, MASK_SHOT_HULL, nullptr) & MASK_SHOT_HULL))
		return false;

	surfacedata_t* exitSurfaceData = g_PhysSurface->GetSurfaceData(exitTrace.surface.surfaceProps);
	int exitMaterial = exitSurfaceData->game.material;
	float exitSurfPenetrationModifier = exitSurfaceData->game.flPenetrationModifier;
	float exitDamageModifier = exitSurfaceData->game.flDamageModifier;

	//Are we using the newer penetration system?
	if (sv_penetration_type)
	{
		if (enterMaterial == CHAR_TEX_GRATE || enterMaterial == CHAR_TEX_GLASS)
		{
			combinedPenetrationModifier = 3.f;
			finalDamageModifier = 0.05f;
		}
		else if (isSolidSurf || isLightSurf)
		{
			combinedPenetrationModifier = 1.f;
			finalDamageModifier = 0.16f;
		}
		else if (enterMaterial == CHAR_TEX_FLESH && (g_LocalPlayer->m_iTeamNum() == pEnemy->m_iTeamNum() && ff_damage_reduction_bullets == 0.f)) //TODO: Team check config 
		{ 
			//Look's like you aren't shooting through your teammate today
			if (ff_damage_bullet_penetration == 0.f)
				return false;

			//Let's shoot through teammates and get kicked for teamdmg! Whatever, atleast we did damage to the enemy. I call that a win.
			combinedPenetrationModifier = ff_damage_bullet_penetration;
			finalDamageModifier = 0.16f;
		}
		else
		{
			combinedPenetrationModifier = (enterSurfPenetrationModifier + exitSurfPenetrationModifier) / 2.f;
			finalDamageModifier = 0.16f;
		}

		//Do our materials line up?
		if (enterMaterial == exitMaterial)
		{
			if (exitMaterial == CHAR_TEX_CARDBOARD || exitMaterial == CHAR_TEX_WOOD)
				combinedPenetrationModifier = 3.f;
			else if (exitMaterial == CHAR_TEX_PLASTIC)
				combinedPenetrationModifier = 2.f;
		}

		//Calculate thickness of the wall by getting the length of the range of the trace and squaring
		thickness = (exitTrace.endpos - enterTrace.endpos).LengthSqr();
		modifier = fmaxf(1.f / combinedPenetrationModifier, 0.f);

		//This calculates how much damage we've lost depending on thickness of the wall, our penetration, damage, and the modifiers set earlier
		lostDamage = fmaxf(
			((modifier * thickness) / 24.f)
			+ ((currentDamage * finalDamageModifier)
				+ (fmaxf(3.75f / penetrationPower, 0.f) * 3.f * modifier)), 0.f);

		//Did we loose too much damage?
		if (lostDamage > currentDamage)
			return false;

		//We can't use any of the damage that we've lost
		if (lostDamage > 0.f)
			currentDamage -= lostDamage;

		//Do we still have enough damage to deal?
		if (currentDamage < 1.f)
			return false;

		eyePosition = exitTrace.endpos;
		--possibleHitsRemaining;

		return true;
	}
	else //Legacy penetration system
	{
		combinedPenetrationModifier = 1.f;

		if (isSolidSurf || isLightSurf)
			finalDamageModifier = 0.99f; //Good meme :^)
		else
		{
			finalDamageModifier = fminf(enterDamageModifier, exitDamageModifier);
			combinedPenetrationModifier = fminf(enterSurfPenetrationModifier, exitSurfPenetrationModifier);
		}

		if (enterMaterial == exitMaterial && (exitMaterial == CHAR_TEX_METAL || exitMaterial == CHAR_TEX_WOOD))
			combinedPenetrationModifier += combinedPenetrationModifier;

		thickness = (exitTrace.endpos - enterTrace.endpos).LengthSqr();

		if (sqrt(thickness) <= combinedPenetrationModifier * penetrationPower)
		{
			currentDamage *= finalDamageModifier;
			eyePosition = exitTrace.endpos;
			--possibleHitsRemaining;

			return true;
		}

		return false;
	}
}

bool Autowall::FireBullet(C_BaseCombatWeapon* pWeapon, Vector& direction, float& currentDamage)
{
	if (!pWeapon)
		return false;

	if (!g_LocalPlayer)
		return false;
	bool sv_penetration_type;
	//	  Current bullet travel Power to penetrate Distance to penetrate Range               Player bullet reduction convars			  Amount to extend ray by
	float currentDistance = 0.f, penetrationPower, penetrationDistance, maxRange, ff_damage_reduction_bullets, ff_damage_bullet_penetration, rayExtension = 40.f;
	Vector eyePosition = g_LocalPlayer->GetEyePos();

	//For being superiour when the server owners think your autowall isn't well reversed. Imagine a meme HvH server with the old penetration system- pff
	static ConVar* penetrationSystem = g_CVar->FindVar( "sv_penetration_type");
	static ConVar* damageReductionBullets = g_CVar->FindVar( "ff_damage_reduction_bullets");
	static ConVar* damageBulletPenetration = g_CVar->FindVar( "ff_damage_bullet_penetration");

	sv_penetration_type = penetrationSystem->GetBool();
	ff_damage_reduction_bullets = damageReductionBullets->GetFloat();
	ff_damage_bullet_penetration = damageBulletPenetration->GetFloat();

	CCSWeaponInfo* weaponData = pWeapon->GetCSWeaponData();
	CGameTrace enterTrace;

	//We should be skipping localplayer when casting a ray to players.
	CTraceFilter filter;
	filter.pSkip = g_LocalPlayer;

	if (!weaponData)
		return false;

	maxRange = weaponData->flRange;

	GetBulletTypeParameters(penetrationPower, penetrationDistance, "BULLET_PLAYER_556MM"/*BULLET_PLAYER_556MM = just for running it should be weaponData->BulletType*/, sv_penetration_type);

	if (sv_penetration_type)
		penetrationPower = weaponData->flPenetration;

	//This gets set in FX_Firebullets to 4 as a pass-through value.
	//CS:GO has a maximum of 4 surfaces a bullet can pass-through before it 100% stops.
	//Excerpt from Valve: https://steamcommunity.com/sharedfiles/filedetails/?id=275573090
	//"The total number of surfaces any bullet can penetrate in a single flight is capped at 4." -CS:GO Official
	int possibleHitsRemaining = 4;

	//Set our current damage to what our gun's initial damage reports it will do
	currentDamage = weaponData->iDamage;

	//If our damage is greater than (or equal to) 1, and we can shoot, let's shoot.
	while (possibleHitsRemaining > 0 && currentDamage >= 1.f)
	{
		//Calculate max bullet range
		maxRange -= currentDistance;

		//Create endpoint of bullet
		Vector end = eyePosition + direction * maxRange;

		TraceLine(eyePosition, end, MASK_SHOT_HULL | CONTENTS_HITBOX, g_LocalPlayer, &enterTrace);
		Autowall::ClipTraceToPlayers(eyePosition, end + direction * rayExtension, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &enterTrace);

		//We have to do this *after* tracing to the player.
		surfacedata_t* enterSurfaceData = g_PhysSurface->GetSurfaceData(enterTrace.surface.surfaceProps);
		float enterSurfPenetrationModifier = enterSurfaceData->game.flPenetrationModifier;
		int enterMaterial = enterSurfaceData->game.material;

		//"Fraction == 1" means that we didn't hit anything. We don't want that- so let's break on it.
		if (enterTrace.fraction == 1.f)
			break;

		//calculate the damage based on the distance the bullet traveled.
		currentDistance += enterTrace.fraction * maxRange;

		//Let's make our damage drops off the further away the bullet is.
		currentDamage *= pow(weaponData->flRangeModifier, (currentDistance / 500.f));

		//Sanity checking / Can we actually shoot through?
		if (currentDistance > penetrationDistance && weaponData->flPenetration > 0.f || enterSurfPenetrationModifier < 0.1f)
			break;

		//This looks gay as fuck if we put it into 1 long line of code.
		bool canDoDamage = (enterTrace.hitgroup != HITGROUP_GEAR && enterTrace.hitgroup != HITGROUP_GENERIC);
		bool isPlayer = ((enterTrace.hit_entity)->GetClientClass()->m_ClassID == ClassId_CCSPlayer);
		bool isEnemy = (((C_BasePlayer*)g_LocalPlayer)->m_iTeamNum() != ((C_BasePlayer*)enterTrace.hit_entity)->m_iTeamNum());
		bool onTeam = (((C_BasePlayer*)enterTrace.hit_entity)->m_iTeamNum() == (int32_t)3 || ((C_BasePlayer*)enterTrace.hit_entity)->m_iTeamNum() == (int32_t)2); //3 Team ct 2 team t

		//TODO: Team check config
		if ((canDoDamage && isPlayer && isEnemy) && onTeam)
		{
			ScaleDamage(enterTrace, weaponData, currentDamage);
			return true;
		}

		//Calling HandleBulletPenetration here reduces our penetrationCounter, and if it returns true, we can't shoot through it.
		if (!HandleBulletPenetration(weaponData, enterTrace, eyePosition, direction, possibleHitsRemaining, currentDamage, penetrationPower, sv_penetration_type, ff_damage_reduction_bullets, ff_damage_bullet_penetration))
			break;
	}
	return false;
}

////////////////////////////////////// Usage Calls //////////////////////////////////////
float Autowall::CanHit(Vector& vecEyePos, Vector& point)
{
	if(!g_LocalPlayer)//If localplayer isn't avaliable, just return as "too thick"
		return 1.f; 
	QAngle angles; Vector direction;
	Vector tmp = point - g_LocalPlayer->GetEyePos();
	float currentDamage = 0;

	Math::VectorAngles(tmp, angles);
	Math::AngleVectors(angles, direction);
	direction.NormalizeInPlace();

	if (FireBullet(g_LocalPlayer->m_hActiveWeapon(), direction, currentDamage))
		return currentDamage;
	return -1; //That wall is just a bit too thick buddy
}