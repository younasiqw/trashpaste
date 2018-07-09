	#pragma once
#include "HookIncludes.h"
#include <map>
#include "Entities.h"

/*
   ___ _    ___  ___ ___   _   _ ___   _____   _____ ___
  / __| |  / _ \/ __| __| | | | | _ \ | __\ \ / / __/ __|
 | (__| |_| (_) \__ \ _|  | |_| |   / | _| \ V /| _|\__ \
  \___|____\___/|___/___|  \___/|_|_\ |___| |_| |___|___/

  __   _____  _   _   ___   ___  _  _ _ _____  __      ___   _  _ _  _   _     ___ ___ ___   _____ _  _ ___ ___
  \ \ / / _ \| | | | |   \ / _ \| \| ( )_   _| \ \    / /_\ | \| | \| | /_\   / __| __| __| |_   _| || |_ _/ __|
   \ V / (_) | |_| | | |) | (_) | .` |/  | |    \ \/\/ / _ \| .` | .` |/ _ \  \__ \ _|| _|    | | | __ || |\__ \
    |_| \___/ \___/  |___/ \___/|_|\_|   |_|     \_/\_/_/ \_\_|\_|_|\_/_/ \_\ |___/___|___|   |_| |_||_|___|___/

*/

int GetEstimatedServerTickCount(float latency)
{
	return (int)floorf(float((float)((float)(latency) / (float)((uintptr_t)&g_Globals->interval_per_tick)) + 0.5) + 1 + (int)((uintptr_t)&g_Globals->tickcount));
}

namespace Globals
{
	bool ManualRight;
	bool ManualLeft;
	int Shots;
	int missedshots;
	bool shouldflip;
	bool ySwitch;
	bool error;
	float RealAngle;
	float FakeAngle;
}

float oldlowerbodyyaw = 0;
#define FLOW_OUTGOING	0
#define FLOW_INCOMING	1
#define MAX_FLOWS		2
struct ResolveData
{
	int ShotsFiredAtTarget = 0;
	int shotCount;
	int shotCountLog;
	float logFailCount;
	float shotCountTime = 0.f;
	QAngle LastAnglesHit;
	QAngle AdjustedAngles = QAngle(0, 0, 0);
	QAngle LastAttemptedAngles = QAngle(0, 0, 0);
	int MissedShots = 0;
	float loggedLBYDelta;
	bool didhitHS;
	bool didhit;
	int useLoggedAngles = true;
};

inline float ClampYaw(float yaw) {
	while (yaw > 180.f)
		yaw -= 360.f;
	while (yaw < -180.f)
		yaw += 360.f;
	return yaw;
}

std::map<int, ResolveData> PlayerData;

float pelvisVelocity[5][65] = { 0.0f };
float pelvisMaxVelocityLog[5][6] = { 0.0f };
float pelvisAverageVelocity[5] = { 0.0f };
int pelvisCalculationCounter[25] = { 0 };
int lastPelvis[65] = { 0 };
float *deltaDiffName[6];
float lastDeltaOver120[120];
float *curtime;

bool lbyDeltaOver120(int plID)
{

	if (lastDeltaOver120[plID] && pelvisAverageVelocity[plID] > 3.f)
		deltaDiffName[plID] = curtime;
	else if (pelvisAverageVelocity[plID] > 6.f && curtime - deltaDiffName[plID] > .1f)
	{
		deltaDiffName[plID] = curtime;
		lastDeltaOver120[plID] = true;
	}
	else if (!lastDeltaOver120[plID] && pelvisAverageVelocity[plID] < 3.f)
		deltaDiffName[plID] = curtime;
	else if (pelvisAverageVelocity[plID] < 3.f && curtime - deltaDiffName[plID] > .1f)
	{
		deltaDiffName[plID] = curtime;
		lastDeltaOver120[plID] = false;
	}
	return lastDeltaOver120[plID];
}

bool didLBYUpdate(C_BaseEntity* player) {
	int curTarget = player->GetIndex();
	float storedLBYFromUpdate[64];
	float oldStoredCurtime[64];
	float firstBreak[64];
	float lbyUpdate[64];

	double cTime = (rand() % 420) / 360.0;

	if ((player->GetVelocity().Length2D() > 1.f && storedLBYFromUpdate[curTarget] != player->GetLowerBodyYaw()) || player->GetVelocity().Length2D() > 25)
	{
		oldStoredCurtime[curTarget] = cTime + 0.22f;
		firstBreak[curTarget] = false;
		storedLBYFromUpdate[curTarget] = player->GetLowerBodyYaw();
		lbyUpdate[player->GetIndex()] = true;
		return true;
	}


	lbyUpdate[player->GetIndex()] = false;
	return false;
}

void Resolver3()
{

	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

	for (auto i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
	{
		C_BaseEntity* pEnt = g_EntityList->GetClientEntity(i);
		if (!pEnt) continue;

		if ((pEnt == pLocal)) continue;

		if (pEnt->IsDormant()) continue;

		player_info_t pTemp;

		if (!g_Engine->GetPlayerInfo(i, &pTemp))
			continue;
		auto FYaw = pEnt->GetLowerBodyYaw();
		auto pitch = pEnt->GetEyeAngles()->x;

			pEnt->GetEyeAngles()->y = FYaw;
			float PlayerIsMoving = abs(pEnt->GetVelocity().Length2D());
			bool bLowerBodyUpdated = false;
			bool IsUsingFakeAngles = false;

			if (oldlowerbodyyaw != FYaw)
			{
				bLowerBodyUpdated = true;
			}
			float bodyeyedelta = fabs(pEnt->GetEyeAngles()->y - pEnt->GetLowerBodyYaw());
			if (PlayerIsMoving || bLowerBodyUpdated)
			{
				pEnt->GetEyeAngles()->y = FYaw;
				oldlowerbodyyaw = pEnt->GetEyeAngles()->y;

				IsUsingFakeAngles = false;
			}
			else
			{
				if (bodyeyedelta > 35.0f)
				{
					pEnt->GetEyeAngles()->y = oldlowerbodyyaw;
					IsUsingFakeAngles = true;
				}
				else
				{
					IsUsingFakeAngles = false;
				}
			}
			if (IsUsingFakeAngles)
			{
				pEnt->GetEyeAngles()->y += 45;
			}

			if (pEnt->GetVelocity().Length2D() > 36)
			{
				pEnt->GetEyeAngles()->y = pEnt->GetLowerBodyYaw();
			}

			if (g_Options.Ragebot.ResolverOverride && GetAsyncKeyState(g_Options.Ragebot.ResolverOverrideKey))
			{
				if (pEnt->GetVelocity().Length2D() < 35)
				{
					pEnt->GetEyeAngles()->y = pEnt->GetLowerBodyYaw() + g_Options.Ragebot.ResolverOverrideSlider;
				}
			}

		if (g_Options.Ragebot.ResolverOverride && GetAsyncKeyState(g_Options.Ragebot.ResolverOverrideKey))
		{
			if (pEnt->GetVelocity().Length2D() < 36)
			{
				pEnt->GetEyeAngles()->y = pEnt->GetLowerBodyYaw() + g_Options.Ragebot.ResolverOverrideSlider;
			}
		}
	}
}

int C_BaseEntity::GetSequenceActivity(int sequence)
{
	auto hdr = g_ModelInfo->GetStudiomodel(this->GetModel());

	if (!hdr)
		return -1;



	static auto client = GetModuleHandleW(L"client.dll");
	static auto getSequenceActivity = (DWORD)U::pattern_scan(client, "55 8B EC 83 7D 08 FF 56 8B F1 74 3D");
	static auto GetSequenceActivity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>(getSequenceActivity);

	return GetSequenceActivity(this, hdr, sequence);
}

AnimationLayer *C_BaseEntity::GetAnimOverlays()
{

	return *(AnimationLayer**)((DWORD)this + 10608);
}

AnimationLayer *C_BaseEntity::GetAnimOverlay(int i)
{
	if (i < 15)
		return &GetAnimOverlays()[i];
}

void AnimResolver()
{

	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	bool HurensohnBricht = false;
	for (auto i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
	{
		C_BaseEntity* pEnt = g_EntityList->GetClientEntity(i);
		if (!pEnt) continue;

		if ((pEnt == pLocal)) continue;

		if (pEnt->IsDormant()) continue;

		player_info_t pTemp;

		if (!g_Engine->GetPlayerInfo(i, &pTemp))
			continue;
		auto FYaw = pEnt->GetLowerBodyYaw();
		auto pitch = pEnt->GetEyeAngles()->x;

		if (g_Options.Ragebot.ResolverMolver == false)
		{
			pEnt->GetEyeAngles()->y = FYaw;
			float PlayerIsMoving = abs(pEnt->GetVelocity().Length2D());
			bool bLowerBodyUpdated = false;
			bool IsUsingFakeAngles = false;

			if (oldlowerbodyyaw != FYaw)
			{
				bLowerBodyUpdated = true;
			}
			float bodyeyedelta = fabs(pEnt->GetEyeAngles()->y - pEnt->GetLowerBodyYaw());
			if (PlayerIsMoving || bLowerBodyUpdated)
			{
				pEnt->GetEyeAngles()->y = FYaw;
				oldlowerbodyyaw = pEnt->GetEyeAngles()->y;

				IsUsingFakeAngles = false;
			}
			else
			{
				if (bodyeyedelta > 35.0f)
				{
					pEnt->GetEyeAngles()->y = oldlowerbodyyaw;
					IsUsingFakeAngles = true;
				}
				else
				{
					IsUsingFakeAngles = false;
				}
			}
			if (IsUsingFakeAngles)
			{
				pEnt->GetEyeAngles()->y += 45;
			}

			if (pEnt->GetVelocity().Length2D() > 36)
			{
				pEnt->GetEyeAngles()->y = pEnt->GetLowerBodyYaw();
			}

			if (g_Options.Ragebot.ResolverOverride && GetAsyncKeyState(g_Options.Ragebot.ResolverOverrideKey))
			{
				if (pEnt->GetVelocity().Length2D() < 35)
				{
					pEnt->GetEyeAngles()->y = pEnt->GetLowerBodyYaw() + g_Options.Ragebot.ResolverOverrideSlider;
				}
			}
		}

		if (g_Options.Ragebot.ResolverOverride && GetAsyncKeyState(g_Options.Ragebot.ResolverOverrideKey))
		{
			if (pEnt->GetVelocity().Length2D() < 36)
			{
				pEnt->GetEyeAngles()->y = pEnt->GetLowerBodyYaw() + g_Options.Ragebot.ResolverOverrideSlider;
			}
		}
	}

	for (auto i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
	{
		C_BaseEntity* pEnt = g_EntityList->GetClientEntity(i);
		if (!pEnt) continue;

		if ((pEnt == pLocal)) continue;

		if (pEnt->IsDormant()) continue;

		player_info_t pTemp;

		if (!g_Engine->GetPlayerInfo(i, &pTemp))
			continue;

		int layerCount = pEnt->GetNumAnimOverlays();

		float OldLBY = 0;


		for (int i = 0; i < layerCount; i++)
		{
			AnimationLayer *currentLayer = pEnt->GetAnimOverlay(3);
			const int activity = pEnt->GetSequenceActivity(currentLayer->m_nSequence);

			if (g_Options.Ragebot.ResolverMolver)
			{
				if (activity == 973 && currentLayer->m_flWeight >= 0.05f)
				{
					pEnt->GetEyeAngles()->y = OldLBY;
				}
				if (activity == 979 && pEnt->GetVelocity().Length2D() < 36 && currentLayer->m_flWeight == 1.f)
				{
					pEnt->GetEyeAngles()->y = pEnt->GetLowerBodyYaw();
				}
				else if (activity == 980 || activity == 979 && currentLayer->m_flWeight == 0.f && currentLayer->m_flCycle >= 0.970000)
				{
					pEnt->GetEyeAngles()->y = pEnt->GetLowerBodyYaw();
					OldLBY = pEnt->GetLowerBodyYaw();
				}

				if (g_Options.Ragebot.ResolverOverride && GetAsyncKeyState(g_Options.Ragebot.ResolverOverrideKey))
				{
					if (pEnt->GetVelocity().Length2D() < 36)
					{
						pEnt->GetEyeAngles()->y = pEnt->GetLowerBodyYaw() + g_Options.Ragebot.ResolverOverrideSlider;
					}
				}
			}
			
		}
	}
}