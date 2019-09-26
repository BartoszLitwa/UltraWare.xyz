#pragma once
#include "Includes.h"

class Autowall
{
public:

	void TraceLine(Vector& absStart, Vector& absEnd, unsigned int mask, IClientEntity* ignore, CGameTrace* ptr);

	void ClipTraceToPlayers(Vector& absStart, Vector absEnd, unsigned int mask, ITraceFilter* filter, CGameTrace* tr);

	void GetBulletTypeParameters(float& maxRange, float& maxDistance, char* bulletType, bool sv_penetration_type);

	bool IsBreakableEntity(IClientEntity* entity);

	void ScaleDamage(CGameTrace& enterTrace, CCSWeaponInfo* weaponData, float& currentDamage);

	bool TraceToExit(CGameTrace& enterTrace, CGameTrace& exitTrace, Vector startPosition, Vector direction);

	bool HandleBulletPenetration(CCSWeaponInfo* weaponData, CGameTrace& enterTrace, Vector& eyePosition, Vector direction, int& possibleHitsRemaining, float& currentDamage, float penetrationPower, bool sv_penetration_type, float ff_damage_reduction_bullets, float ff_damage_bullet_penetration);

	bool FireBullet(C_BaseCombatWeapon* pWeapon, Vector& direction, float& currentDamage);

	float CanHit(Vector& vecEyePos, Vector& point);

};

extern Autowall autowall;