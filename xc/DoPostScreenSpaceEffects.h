#pragma once
#include "HookIncludes.h"
using do_post_screen_space_effects_t = bool(__thiscall*)(void*, CViewSetup*);



bool _fastcall hkDoPostScreenSpaceEffects(void* ecx, void* edx, CViewSetup* pSetup)
{
	// Enemies
	float ered;
	float egreen;
	float eblue;

	ered = g_Options.Colors.espDrawGlowEnemies[0];
	egreen = g_Options.Colors.espDrawGlowEnemies[1];
	eblue = g_Options.Colors.espDrawGlowEnemies[2];

	float enewR = ered;
	float enewG = egreen;
	float enewB = eblue;

	// Teammates
	float tred;
	float tgreen;
	float tblue;

	tred = g_Options.Colors.espDrawGlowTeammates[0];
	tgreen = g_Options.Colors.espDrawGlowTeammates[1];
	tblue = g_Options.Colors.espDrawGlowTeammates[2];

	float tnewR = tred;
	float tnewG = tgreen;
	float tnewB = tblue;

	// Wep ESP
	float Wepred;
	float Wepgreen;
	float Wepblue;

	Wepred = g_Options.Colors.espDrawGlowWeapons[0];
	Wepgreen = g_Options.Colors.espDrawGlowWeapons[1];
	Wepblue = g_Options.Colors.espDrawGlowWeapons[2];

	float wnewR = Wepred;
	float wnewG = Wepgreen;
	float wnewB = Wepblue;



    static auto ofunc = hooks::clientmode.get_original<do_post_screen_space_effects_t>(44);

    IMaterial *pMatGlowColor = g_MaterialSystem->FindMaterial("dev/glow_color", TEXTURE_GROUP_OTHER, true);
    g_ModelRender->ForcedMaterialOverride(pMatGlowColor);

    if (g_Options.Visuals.Enabled && g_Options.Visuals.Glow && g_GlowObjManager && g_Engine->IsConnected())
    {
        auto local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
        if (local)
        {
            for (int i = 0; i < g_GlowObjManager->m_GlowObjectDefinitions.Count(); ++i)
            {
                if (g_GlowObjManager->m_GlowObjectDefinitions[i].IsUnused() || !g_GlowObjManager->m_GlowObjectDefinitions[i].getEnt())
                    continue;

                CGlowObjectManager::GlowObjectDefinition_t* glowEnt = &g_GlowObjManager->m_GlowObjectDefinitions[i];

                switch (glowEnt->getEnt()->GetClientClass()->m_ClassID)
                {
                default:
                        if (strstr(glowEnt->getEnt()->GetClientClass()->m_pNetworkName, ("CWeapon")))
                            //glowEnt->set(wnewR, wnewG, wnewB, 1.f);
							if (g_Options.Visuals.WeaponGlow == true)
								glowEnt->set(wnewR, wnewG, wnewB, 1.f);
							if (g_Options.Visuals.WeaponGlow == false)
								glowEnt->set(wnewR, wnewG, wnewB, 0.f);
                    break;
                case 1:
						if (g_Options.Visuals.WeaponGlow == true)
							glowEnt->set(wnewR, wnewG, wnewB, 1.f);
						if (g_Options.Visuals.WeaponGlow == false)
							glowEnt->set(wnewR, wnewG, wnewB, 0.f);
                    break;
                case 35:

                        if (g_Options.Visuals.Filter.EnemyOnly && glowEnt->getEnt()->GetTeamNum() == local->GetTeamNum())
                            break;

                        if (glowEnt->getEnt()->GetTeamNum() == local->GetTeamNum())
                            glowEnt->set(tnewR, tnewG, tnewB, 0.8f); // Teammates // 0.23921f, 0.55294f, 0.89019f, 0.8f
                        else if (glowEnt->getEnt()->GetTeamNum() != local->GetTeamNum())
                            glowEnt->set(enewR, enewG, enewB, 0.8f); // Enemies // 0.89019f, 0.23137f, 0.23137f, 0.7f
                    break;
                case 39:
                        //glowEnt->set(wnewR, wnewG, wnewB, 1.f);
						if (g_Options.Visuals.WeaponGlow == true)
							glowEnt->set(wnewR, wnewG, wnewB, 1.f);
						if (g_Options.Visuals.WeaponGlow == false)
							glowEnt->set(wnewR, wnewG, wnewB, 0.f);
                    break;
                }
            }
        }
    }
    return ofunc(ecx, pSetup);
}