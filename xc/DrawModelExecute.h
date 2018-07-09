
#pragma once
#include "HookIncludes.h"
#include "dropboxes.h"
typedef void(__thiscall* dme_t)(void*, void*, void*, const ModelRenderInfo_t&, matrix3x4*);

//float flColor[3] = { 0.89019f, 0.23137f, 0.23137f };

void __fastcall hkDrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld)
{
	//=================================
	float redweapon;
	float greenweapon;
	float blueweapon;

	redweapon = g_Options.Colors.DrawWeapon[0];
	greenweapon = g_Options.Colors.DrawWeapon[1];
	blueweapon = g_Options.Colors.DrawWeapon[2];
	//=================================
	float redhands;
	float greenhands;
	float bluehands;

	redhands = g_Options.Colors.DrawHands[0];
	greenhands = g_Options.Colors.DrawHands[1];
	bluehands = g_Options.Colors.DrawHands[2];
	//=================================
	float red;
	float green;
	float blue;

	red = g_Options.Colors.DrawChamsNigger[0];
	green = g_Options.Colors.DrawChamsNigger[1];
	blue = g_Options.Colors.DrawChamsNigger[2];
	//=================================
	float redteam;
	float greenteam;
	float blueteam;

	redteam = g_Options.Colors.DrawChamsTeam[0];
	greenteam = g_Options.Colors.DrawChamsTeam[1];
	blueteam = g_Options.Colors.DrawChamsTeam[2];
	//=================================

	float flColor[3] = { red, green, blue };
	float TeamColor[3] = { redteam, greenteam, blueteam };
	float HandColor[3] = { redhands, greenhands, bluehands };
	float SmokeColor[3] = { 1.f, .2f, .2f };

	static bool DontDraw = false;
	static auto ofunc = hooks::modelrender.get_original<dme_t>(21);
	if (g_Options.Visuals.Enabled)
	{

			static IMaterial* ignorez = CreateMaterial("VertexLitGeneric", "vgui/white_additive", true, true, true, true, true);
			static IMaterial* notignorez = CreateMaterial("VertexLitGeneric", "vgui/white_additive", false, true, true, true, true);
			DontDraw = false;

		const char * ModelName = g_ModelInfo->GetModelName((model_t*)pInfo.pModel);
		C_BaseEntity* pModelEntity = (C_BaseEntity*)g_EntityList->GetClientEntity(pInfo.entity_index);
		C_BaseEntity* pLocal = (C_BaseEntity*)g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());


		if (ModelName && g_Options.Visuals.Chams && strstr(ModelName, "models/player"))
		{
			if (pModelEntity && pLocal)
			{
				if (!g_Options.Visuals.Filter.EnemyOnly ||
					pModelEntity->GetTeamNum() != pLocal->GetTeamNum())
				{
					pModelEntity = g_EntityList->GetClientEntity(pInfo.entity_index);
					if (pModelEntity)
					{


						if (pModelEntity->IsAlive() && pModelEntity->GetHealth() > 0)
						{
							float alpha = 1.f;
							if (pModelEntity->HasGunGameImmunity())
								alpha = 0.5f;

							g_RenderView->SetColorModulation(flColor);
							g_RenderView->SetBlend(alpha);
							g_ModelRender->ForcedMaterialOverride(notignorez);
							ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

							g_RenderView->SetColorModulation(flColor);
							g_RenderView->SetBlend(alpha);

							if (g_Options.Visuals.ChamsMode.Filter.XQZ == false)
							{
								g_ModelRender->ForcedMaterialOverride(notignorez);
							}
							if (g_Options.Visuals.ChamsMode.Filter.XQZ == true)
							{
								g_ModelRender->ForcedMaterialOverride(ignorez);
							}

						}

					}
				}
			if (g_Options.Visuals.Filter.EnemyOnly == false)
				{
					if (pModelEntity->GetTeamNum() == pLocal->GetTeamNum())
					{
						pModelEntity = g_EntityList->GetClientEntity(pInfo.entity_index);
						if (pModelEntity)
						{


							if (pModelEntity->IsAlive() && pModelEntity->GetHealth() > 0)
							{
								float alpha = 1.f;
								if (pModelEntity->HasGunGameImmunity())
									alpha = 0.5f;

								g_RenderView->SetColorModulation(TeamColor);
								g_RenderView->SetBlend(alpha);
								g_ModelRender->ForcedMaterialOverride(notignorez);
								ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

								g_RenderView->SetColorModulation(TeamColor);
								g_RenderView->SetBlend(alpha);

								if (g_Options.Visuals.ChamsMode.Filter.XQZ == false)
								{
									g_ModelRender->ForcedMaterialOverride(notignorez);
								}
								if (g_Options.Visuals.ChamsMode.Filter.XQZ == true)
								{
									g_ModelRender->ForcedMaterialOverride(ignorez);
								}

							}

						}
					}
				}
			}
		}

		/*else if (g_Options.Visuals.Chams && g_Options.Visuals.WeaponChams && strstr(ModelName, "_dropped.mdl"))
		{
			if (g_Options.Visuals.ChamsMode.Filter.XQZ == false)
			{
				ForceMaterial(Color(redweapon, greenweapon, blueweapon), notignorez);
			}

			if (g_Options.Visuals.ChamsMode.Filter.XQZ == true)
			{
				ForceMaterial(Color(redweapon, greenweapon, blueweapon), ignorez);
			}
		}

		else if (g_Options.Visuals.Chams && g_Options.Visuals.WeaponsWorld && strstr(ModelName, "_dropped.mdl"))
		{
			ForceMaterial(Color(255, 255, 255), notignorez);
		}*/


		// =================================================================================================

		if (g_Options.Visuals.WeaponMaterial && strstr(ModelName, "models/weapons/v_knife") || strstr(ModelName, "models/weapons/v_pi") || strstr(ModelName, "models/weapons/v_rif") || strstr(ModelName, "models/weapons/v_mach") || strstr(ModelName, "models/weapons/v_smg") || strstr(ModelName, "models/weapons/v_snip") || strstr(ModelName, "models/weapons/v_shot"))
		{
			if (g_Options.Visuals.WeaponMaterial == 1)
			{
				DontDraw = true;
			}
			if (g_Options.Visuals.WeaponMaterial == 2)
			{
				g_ModelRender->ForcedMaterialOverride(notignorez);
				g_RenderView->SetColorModulation(HandColor);
				g_RenderView->SetBlend(1.f);

			}
			if (g_Options.Visuals.WeaponMaterial == 3)
			{
				IMaterial* Weapons = g_MaterialSystem->FindMaterial("models/player/ct_fbi/ct_fbi_glass", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Weapons);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.WeaponMaterial == 4)
			{
				IMaterial* Weapons = g_MaterialSystem->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Weapons);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.WeaponMaterial == 5)
			{
				IMaterial* Weapons = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Weapons);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.WeaponMaterial == 6)
			{
				IMaterial* Weapons = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/gold", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Weapons);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.WeaponMaterial == 7)
			{
				IMaterial* Weapons = g_MaterialSystem->FindMaterial("models/gibs/glass/glass", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Weapons);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.WeaponMaterial == 8)
			{
				IMaterial* Weapons = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/gloss", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Weapons);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.WeaponMaterial == 9)
			{
				IMaterial* Weapons = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/velvet", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Weapons);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.WeaponMaterial == 10)
			{
				IMaterial* Weapons = g_MaterialSystem->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Weapons);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.WeaponMaterial == 11)
			{
				IMaterial* Weapons = g_MaterialSystem->FindMaterial(ModelName, "Model textures");
				Weapons->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
				g_ModelRender->ForcedMaterialOverride(Weapons);
			}
			if (g_Options.Visuals.WeaponMaterial == 12)
			{
				IMaterial* Weapons = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Weapons);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.WeaponMaterial == 13)
			{
				IMaterial* Weapons = g_MaterialSystem->FindMaterial("models/inventory_items/dogtags/dogtags_outline", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Weapons);
				g_RenderView->SetBlend(1.f);
			}
		}

		if (g_Options.Visuals.Hands && strstr(ModelName, "arms"))
		{
			if (g_Options.Visuals.Hands == 1)
			{
				DontDraw = true;
			}
			if (g_Options.Visuals.Hands == 2)
			{
				g_ModelRender->ForcedMaterialOverride(notignorez);
				g_RenderView->SetColorModulation(HandColor);
				g_RenderView->SetBlend(1.f);

			}
			if (g_Options.Visuals.Hands == 3)
			{
				IMaterial* Hands = g_MaterialSystem->FindMaterial("models/player/ct_fbi/ct_fbi_glass", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Hands);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.Hands == 4)
			{
				IMaterial* Hands = g_MaterialSystem->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Hands);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.Hands == 5)
			{
				IMaterial* Hands = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Hands);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.Hands == 6)
			{
				IMaterial* Hands = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/gold", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Hands);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.Hands == 7)
			{
				IMaterial* Hands = g_MaterialSystem->FindMaterial("models/gibs/glass/glass", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Hands);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.Hands == 8)
			{
				IMaterial* Hands = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/gloss", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Hands);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.Hands == 9)
			{
				IMaterial* Hands = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/velvet", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Hands);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.Hands == 10)
			{
				IMaterial* Hands = g_MaterialSystem->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Hands);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.Hands == 11)
			{
				IMaterial* Hands = g_MaterialSystem->FindMaterial(ModelName, "Model textures");
				Hands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
				g_ModelRender->ForcedMaterialOverride(Hands);
			}
			if (g_Options.Visuals.Hands == 12)
			{
				IMaterial* Hands = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Hands);
				g_RenderView->SetBlend(1.f);
			}
			if (g_Options.Visuals.Hands == 13)
			{
				IMaterial* Hands = g_MaterialSystem->FindMaterial("models/inventory_items/dogtags/dogtags_outline", "Model textures");
				g_ModelRender->ForcedMaterialOverride(Hands);
				g_RenderView->SetBlend(1.f);
			}
		}

		for (auto mat_s : vistasmoke_mats)
		{
			if (g_Options.Visuals.WireframeSmoke)
			{
				IMaterial* mat = g_MaterialSystem->FindMaterial(mat_s, TEXTURE_GROUP_OTHER);
				mat->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			}
		}
	}
	if (!DontDraw)
		ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
	g_ModelRender->ForcedMaterialOverride(NULL);
}