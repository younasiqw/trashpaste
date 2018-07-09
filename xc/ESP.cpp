
#include "ESP.h"
#include "Interfaces.h"
#include "Render.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include "GrenadePrediction.h"
#include "LagComp.h"
#include "Autowall.h"



visuals::visuals()
{
	BombCarrier = nullptr;
}

int width = 0;
int height = 0;
bool done = false;

void visuals::OnPaintTraverse(C_BaseEntity* local)
{
	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

	float red;
	float green;
	float blue;

	red = g_Options.Colors.espDrawBacktrack[0];
	green = g_Options.Colors.espDrawBacktrack[1];
	blue = g_Options.Colors.espDrawBacktrack[2];

	float newR = red * 255;
	float newG = green * 255;
	float newB = blue * 255;

	if (g_Options.Misc.Hitmarker)
	{
		if (g_Engine->IsInGame() && g_Engine->IsConnected() && local->IsAlive())
		{
			Hitmarker();
		}
	}

	if (g_Options.Visuals.Enabled)
	{
		if (g_Options.Visuals.angleLines && pLocal->IsAlive())
			angleLines();

		if (g_Options.Visuals.DrawAwall && pLocal->IsAlive())
			DrawAwall();
	}

	/*if (g_Options.Visuals.SpecList2)
	speclist2();*/

	for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
	{
		C_BaseEntity *entity = g_EntityList->GetClientEntity(i);
		player_info_t pinfo;
		if (entity == local && local->IsAlive() && g_Engine->GetPlayerInfo(g_Engine->GetLocalPlayer(), &pinfo))
		{
			if (g_Input->m_fCameraInThirdPerson && g_Options.Visuals.Enabled)
			{
				Vector max = entity->GetCollideable()->OBBMaxs();
				Vector pos, pos3D;
				Vector top, top3D;
				pos3D = entity->GetOrigin();
				top3D = pos3D + Vector(0, 0, max.z);

				if (!g_Render->WorldToScreen(pos3D, pos) || !g_Render->WorldToScreen(top3D, top))
					return;

				float height = (pos.y - top.y);
				float width = height / 4.f;
				int bottom = 0;
				if (g_Options.Visuals.BoxLocal && g_Options.Visuals.Filter.LocalPlayer)
				{
					Color color;
					color = GetPlayerColor(entity, local);
					PlayerBox(top.x, top.y, width, height, color);
				}

				if (g_Options.Visuals.HPLocal && g_Options.Visuals.Filter.LocalPlayer)
					DrawHealth(pos, top, local->GetHealth());

				if (g_Options.Visuals.APLocal && g_Options.Visuals.Filter.LocalPlayer)
					DrawArmor(pos, top, local->ArmorValue());

				/*if (g_Options.Visuals.IsScopedLocal && entity->IsScoped() && g_Options.Visuals.Filter.LocalPlayer)
				g_Render->DrawString2(g_Render->font.ESP, (int)top.x, (int)top.y - 24, Color::Red(), FONT_CENTER, "Scoped");*/

				if (g_Options.Visuals.NameLocal && g_Options.Visuals.Filter.LocalPlayer)
					g_Render->DrawString2(g_Render->font.ESP, (int)top.x, (int)top.y - 6, Color::White(), FONT_CENTER, pinfo.name);

				if (g_Options.Visuals.SkeletonLocal && g_Options.Visuals.Filter.LocalPlayer)
					DrawSkeleton(entity);

				/*if (g_Options.Visuals.HasHelmetLocal && entity->HasHelmet() && g_Options.Visuals.Filter.LocalPlayer)
				{
				g_Render->DrawString2(g_Render->font.ESP, (int)top.x, int(top.y + height + 8 + (10 * bottom++)), Color::Red(), FONT_CENTER, "H+K");
				i++;
				}*/

				if (g_Options.Visuals.HasDefuserLocal && entity->hasDefuser() && g_Options.Visuals.Filter.LocalPlayer)
				{
					g_Render->DrawString2(g_Render->font.ESP, (int)top.x, int(top.y + height + 8 + (10 * bottom++)), Color::APCyan(), FONT_CENTER, "Kit");
					i++;
				}


				/*if (g_Options.Visuals.HasHeavyArmorLocal && entity->m_bHasHeavyArmor() && g_Options.Visuals.Filter.LocalPlayer)
				{
				g_Render->DrawString2(g_Render->font.ESP, (int)top.x, int(top.y + height + 8 + (10 * bottom++)), Color::Red(), FONT_CENTER, "Heavy Armor");
				i++;
				}*/

				int SeiteWeischt = 0;
				int Seite = 0;

				if (g_Options.Visuals.MoveTypeLocal && g_Options.Visuals.Filter.LocalPlayer)
				{
					if (entity->GetVelocity().Length2D() > 1)
					{
						//g_Render->Textf(int(top.x + width + 5), int(top.y - 3 + (10 * SeiteWeischt++)), Color(0, 255, 0, 255), g_Render->font.ESP, "Moving");
						g_Render->Textf(int(top.x + width + 5), int(top.y - 3 + (10 * SeiteWeischt++)), Color(0, 255, 0, 255), g_Render->font.ESP, "Moving");
						Seite++;
					}
					else
					{
						//g_Render->Textf(int(top.x + width + 5), int(top.y - 3 + (10 * SeiteWeischt++)), Color(255, 0, 0, 255), g_Render->font.ESP, "Standing");
						g_Render->Textf(int(top.x + width + 5), int(top.y - 3 + (10 * SeiteWeischt++)), Color(255, 0, 0, 255), g_Render->font.ESP, "Standing");
						Seite++;
					}
				}

				if (g_Options.Visuals.HasHelmetLocal && g_Options.Visuals.Filter.LocalPlayer)
				{
					g_Render->Textf(int(top.x + width + 4.5), int(top.y - 3 + (10 * SeiteWeischt++)), Color(255, 255, 255, 255), g_Render->font.ESP, "HK", entity->HasHelmet());
					Seite++;
				}

				if (g_Options.Visuals.HPNumberLocal && g_Options.Visuals.Filter.LocalPlayer)
				{
					g_Render->Textf(int(top.x + width + 3), int(top.y - 3 + (10 * SeiteWeischt++)), Color(255, 0, 0, 255), g_Render->font.ESP, "%i HP", entity->GetHealth());
					Seite++;
				}

				if (g_Options.Visuals.APNumberLocal && g_Options.Visuals.Filter.LocalPlayer)
				{
					g_Render->Textf(int(top.x + width + 3), int(top.y - 3 + (10 * SeiteWeischt++)), Color(0, 233, 255, 255), g_Render->font.ESP, "%i AP", entity->ArmorValue());
					Seite++;
				}

				if (g_Options.Visuals.MoneyLocal && g_Options.Visuals.Filter.LocalPlayer)
				{
					g_Render->Textf(int(top.x + width + 3), int(top.y - 3 + (10 * SeiteWeischt++)), Color(255, 255, 255, 255), g_Render->font.ESP, "%i $", entity->GetMoney());
					Seite++;
				}
			}
		}
		if (entity && entity != local && !entity->IsDormant())
		{
			if (g_Engine->GetPlayerInfo(i, &pinfo) && entity->IsAlive())
			{
				if (g_Options.Legitbot.backtrack)
				{
					if (local->IsAlive())
					{
						for (int t = 0; t < 12; ++t)
						{
							Vector screenbacktrack[128][12];

							if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimulationTime())
							{
								if (g_Options.Visuals.backtrack && g_Render->WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
								{
									{
										g_Surface->DrawSetColor(Color(newR, newG, newB, 255));
									}
									g_Surface->DrawOutlinedRect(screenbacktrack[i][t].x, screenbacktrack[i][t].y, screenbacktrack[i][t].x + 4, screenbacktrack[i][t].y + 2);

								}
							}
						}
					}
					else
					{
						memset(&headPositions[0][0], 0, sizeof(headPositions));
					}
				}
				if (g_Options.Ragebot.rageBacktrack)
				{
					if (local->IsAlive())
					{
						for (int t = 0; t < 12; ++t)
						{
							Vector screenbacktrack[128][12];

							if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimulationTime())
							{
								if (g_Options.Visuals.backtrack && g_Render->WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
								{
									{
										g_Surface->DrawSetColor(Color(newR, newG, newB, 255));

										g_Surface->DrawOutlinedRect(screenbacktrack[i][t].x, screenbacktrack[i][t].y, screenbacktrack[i][t].x + 4, screenbacktrack[i][t].y + 2);

									}
								}
							}
						}
					}
					else
					{
						memset(&headPositions[0][0], 0, sizeof(headPositions));
					}
				}
				if (g_Options.Visuals.Enabled)
				{
					if (g_Options.Visuals.DLight)
						DLight(local, entity);

					DrawPlayer(entity, pinfo, local);

				}

			}
			if (g_Options.Visuals.Enabled)
			{
				ClientClass* cClass = (ClientClass*)entity->GetClientClass();
				if (g_Options.Visuals.Weapon && cClass->m_ClassID != (int)ClassID::CBaseWeaponWorldModel && ((strstr(cClass->m_pNetworkName, "Weapon") || cClass->m_ClassID == (int)ClassID::CDEagle || cClass->m_ClassID == (int)ClassID::CAK47)))
				{
					DrawDrop(entity);
				}
				if (g_Options.Visuals.Enabled)
				{
					if (cClass->m_ClassID == (int)ClassID::CPlantedC4)
						DrawBombPlanted(entity, local);
				}
				if (cClass->m_ClassID == (int)ClassID::CC4)
					DrawBomb(entity, cClass);
				if (g_Options.Visuals.GrenadeESP && strstr(cClass->m_pNetworkName, "Projectile"))
				{
					DrawThrowable(entity);
				}
			}
		}
	}
	if (g_Options.Misc.SpecList) SpecList(local);
	//if (g_Options.Visuals.speclist2) speclist2();

	NightMode();
	grenade_prediction::instance().Paint();
	if (g_Options.Visuals.Enabled) // Main Switch and u know
	{
		if (g_Options.Visuals.SpreadCrosshair)
		{
			g_Engine->GetScreenSize(width, height);
			if (local && g_Engine->IsConnected() && g_Engine->IsInGame() && local->IsAlive())
			{
				g_Engine->ClientCmd_Unrestricted("crosshair 0");
				static Vector ViewAngles;
				g_Engine->GetViewAngles(ViewAngles);
				ViewAngles += local->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

				static Vector fowardVec;
				AngleVectors(ViewAngles, &fowardVec);
				fowardVec *= 10000;

				// Get ray start / end
				Vector start = local->GetOrigin() + local->GetViewOffset();
				Vector end = start + fowardVec, endScreen;

				CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(local->GetActiveWeaponHandle());
				float cone = pWeapon->GetSpread() + pWeapon->GetInaccuracy();
				if (cone > 0.0f)
				{
					if (cone < 0.01f) cone = 0.01f;
					float size = (cone * height) * 0.7f;
					Color color(255, 0, 0, 100);

					if (g_Render->WorldToScreen(end, endScreen))
					{
						g_Render->OutlineCircle(endScreen.x, endScreen.y, (int)size, 34, color);
					}
				}
			}
		}
		else
		{
			g_Engine->ClientCmd_Unrestricted("crosshair 1");
		}

			if (g_Input->m_fCameraInThirdPerson)
			{
				g_Engine->ClientCmd_Unrestricted("crosshair 0");
			}
			else
			{
				g_Engine->ClientCmd_Unrestricted("crosshair 1");
			}

		// Shows xHair even with Sniper
		if (g_Options.Visuals.SniperCrosshair) // xhair for all ya needs
		{
			static auto weapon_debug_spread_show = g_CVar->FindVar("weapon_debug_spread_show");
			weapon_debug_spread_show->SetValue(3);
		}
		else
		{
			static auto weapon_debug_spread_show = g_CVar->FindVar("weapon_debug_spread_show");
			weapon_debug_spread_show->SetValue(0);
		}
		// Removes Textures
		if (g_Options.Visuals.RemoveTextures)
		{
			static auto mat_drawgray = g_CVar->FindVar("mat_drawgray");
			mat_drawgray->SetValue(1);
		}
		else
		{
			static auto mat_drawgray = g_CVar->FindVar("mat_drawgray");
			mat_drawgray->SetValue(0);
		}
		// Radar
		if (g_Options.Visuals.RadarSpoof)
		{
			static auto mp_radar_showall = g_CVar->FindVar("mp_radar_showall");
			mp_radar_showall->SetValue(1);
		}
		else
		{
			static auto mp_radar_showall = g_CVar->FindVar("mp_radar_showall");
			mp_radar_showall->SetValue(0);
		}

		// Chrome Models
		if (g_Options.Visuals.ChromeModels)
		{
			static auto r_showenvcubemap = g_CVar->FindVar("r_showenvcubemap");
			r_showenvcubemap->SetValue(1);
		}
		else
		{
			static auto r_showenvcubemap = g_CVar->FindVar("r_showenvcubemap");
			r_showenvcubemap->SetValue(0);
		}
		// Recoil Tracking oof
		if (g_Options.Visuals.RecoilESP)
		{
			static auto cl_crosshair_recoil = g_CVar->FindVar("cl_crosshair_recoil");
			cl_crosshair_recoil->SetValue(1);
		}
		else
		{
			static auto cl_crosshair_recoil = g_CVar->FindVar("cl_crosshair_recoil");
			cl_crosshair_recoil->SetValue(0);
		}

		// LSD Vision
		if (g_Options.Visuals.LSDVision)
		{
			static auto mat_showmiplevels = g_CVar->FindVar("mat_showmiplevels");
			mat_showmiplevels->SetValue(1);
		}
		else
		{
			static auto mat_showmiplevels = g_CVar->FindVar("mat_showmiplevels");
			mat_showmiplevels->SetValue(0);
		}

		// Red
		if (g_Options.Visuals.AmbientColor)
		{
			static auto mat_ambient_light_r = g_CVar->FindVar("mat_ambient_light_r");
			mat_ambient_light_r->SetValue(g_Options.Visuals.AmbientRed);
		}
		else
		{
			static auto mat_ambient_light_r = g_CVar->FindVar("mat_ambient_light_r");
			mat_ambient_light_r->SetValue(0);
		}
		// Green
		if (g_Options.Visuals.AmbientColor)
		{
			static auto mat_ambient_light_g = g_CVar->FindVar("mat_ambient_light_g");
			mat_ambient_light_g->SetValue(g_Options.Visuals.AmbientGreen);
		}
		else
		{
			static auto weapon_debug_spread_show = g_CVar->FindVar("mat_ambient_light_g");
			weapon_debug_spread_show->SetValue(0);
		}
		// Blue
		if (g_Options.Visuals.AmbientColor)
		{
			static auto mat_ambient_light_b = g_CVar->FindVar("mat_ambient_light_b");
			mat_ambient_light_b->SetValue(g_Options.Visuals.AmbientBlue);
		}
		else
		{
			static auto weapon_debug_spread_show = g_CVar->FindVar("mat_ambient_light_b");
			weapon_debug_spread_show->SetValue(0);
		}
	}
	///////////////////////////////////////
	//if (g_Options.Visuals.NoVisualRecoil)
	{
		static auto weapon_recoil_view_punch_extra = g_CVar->FindVar("weapon_recoil_view_punch_extra");
		weapon_recoil_view_punch_extra->SetValue(g_Options.Visuals.ViewPunch);
	}

	//if (g_Options.Visuals.NoVisualRecoil)
	{
		static auto view_recoil_tracking = g_CVar->FindVar("view_recoil_tracking");
		view_recoil_tracking->SetValue(g_Options.Visuals.RecoilTracking);
	}

}


std::string CleanItemName(std::string name)
{
	std::string Name = name;
	// Tidy up the weapon Name
	if (Name[0] == 'C')
		Name.erase(Name.begin());

	// Remove the word Weapon
	auto startOfWeap = Name.find("Weapon");
	if (startOfWeap != std::string::npos)
		Name.erase(Name.begin() + startOfWeap, Name.begin() + startOfWeap + 6);

	return Name;
}

wchar_t* CharToWideChar(const char* text)
{
	size_t size = strlen(text) + 1;
	wchar_t* wa = new wchar_t[size];
	mbstowcs_s(NULL, wa, size / 4, text, size);
	return wa;
}


C_CSPlayerResource* playerresources;
void visuals::DrawPlayer(C_BaseEntity* entity, player_info_t pinfo, C_BaseEntity* local)
{
	Vector max = entity->GetCollideable()->OBBMaxs();
	Vector pos, pos3D;
	Vector top, top3D;
	pos3D = entity->GetOrigin();
	top3D = pos3D + Vector(0, 0, max.z);

	if (!g_Render->WorldToScreen(pos3D, pos) || !g_Render->WorldToScreen(top3D, top))
		return;

	float height = (pos.y - top.y);
	float width = height / 4.f;

	Color color;

	if (g_Options.Visuals.Filter.EnemyOnly && (entity->GetTeamNum() == local->GetTeamNum()))
		return;
	color = GetPlayerColor(entity, local);
	if (g_Engine->IsConnected() && g_Engine->IsInGame())
	{
		if (g_Options.Visuals.Box)
			PlayerBox(top.x, top.y, width, height, color);

		if (g_Options.Visuals.HP)
			DrawHealth(pos, top, entity->GetHealth());

		if (g_Options.Visuals.AP)
			DrawArmor(pos, top, entity->ArmorValue());

		if (g_Options.Visuals.Skeleton)
			DrawSkeleton(entity);

		if (g_Options.Visuals.Name)
			g_Render->DrawString2(g_Render->font.ESP, (int)top.x, (int)top.y - 6, Color::White(), FONT_CENTER, pinfo.name);
	}
	int bottom = 0;

	/*auto m_AnimOverlay = entity->GetAnimationOverlay();

	for (int i = 0; i < 14; i++)
	{
	char sequence_string[64];
	sprintf_s(sequence_string, sizeof(sequence_string) - 1, "%d | %d", i, m_AnimOverlay.m_pElements[i].Sequence);
	g_Render->DrawString2(g_Render->font.ESP, top.x + 20 + height, top.y + 10 * i, Color::White(), FONT_LEFT, sequence_string);
	}*/

	std::vector<std::string> weapon;
	std::vector<std::string> bomb;
	std::vector<std::string> rank;
	std::vector<std::string> wins;

	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(entity->GetActiveWeaponHandle());
	if (g_Options.Visuals.Weapon && pWeapon)
	{
		int weapon_id = pWeapon->m_AttributeManager()->m_Item()->GetItemDefinitionIndex();

		auto weapon_name = ItemDefinitionIndexToString(weapon_id);
		weapon.push_back(weapon_name);
	}

	if (g_Options.Visuals.C4 && entity == BombCarrier)
	{
		bomb.push_back("Bomb");
	}

	int i = 0;
	if (g_Options.Visuals.Weapon)
	{
		for (auto Text : weapon)
		{
			g_Render->DrawString2(g_Render->font.ESP, (int)top.x, int(top.y + height + 8 + (10 * bottom++)), Color::White(), FONT_CENTER, "%s", Text.c_str());
			i++;
		}
	}
	if (g_Options.Visuals.C4) // bomb carrier
	{
		for (auto Text : bomb)
		{
			g_Render->DrawString2(g_Render->font.ESP, (int)top.x, int(top.y + height + 8 + (10 * bottom++)), Color::Yellow(), FONT_CENTER, Text.c_str());
			i++;
		}
	}
	int top1 = 0;
	if (g_Options.Visuals.IsScoped && entity->IsScoped()) // above name esp
	{
		g_Render->DrawString2(g_Render->font.ESP, (int)top.x, (int)top.y - 24, Color::Red(), FONT_CENTER, "Scoped");
		i++;
	}

	/*if (g_Options.Visuals.HasHelmet && entity->HasHelmet())
	{
	g_Render->DrawString2(g_Render->font.ESP, (int)top.x, int(top.y + height + 8 + (10 * bottom++)), Color::Red(), FONT_CENTER, "H+K");
	i++;
	}*/

	if (g_Options.Visuals.HasDefuser && entity->hasDefuser())
	{
		g_Render->DrawString2(g_Render->font.ESP, (int)top.x, int(top.y + height + 8 + (10 * bottom++)), Color::APCyan(), FONT_CENTER, "Kit");
		i++;
	}

	/*if (g_Options.Visuals.HasHeavyArmor && entity->m_bHasHeavyArmor())
	{
	g_Render->DrawString2(g_Render->font.ESP, (int)top.x, int(top.y + height + 8 + (10 * bottom++)), Color::Red(), FONT_CENTER, "Heavy Armor");
	i++;
	}*/
	/*if (g_Options.Visuals.C4)
	{
	g_Render->DrawString2(g_Render->font.ESP, (int)top.x, int(top.y + height + 8 + (10 * bottom++)), Color::Purple(), FONT_CENTER, "Bomb");
	i++;
	}*/
	/////////	/////////	/////////	/////////	/////////	/////////	/////////	/////////	/////////	/////////	/////////	/////////	/////////
	int SeiteWeischt = 0;
	int Seite = 0;

	if (g_Options.Visuals.MoveType)
	{
		if (entity->GetVelocity().Length2D() > 1)
		{
			//g_Render->Textf(int(top.x + width + 5), int(top.y - 3 + (10 * SeiteWeischt++)), Color(0, 255, 0, 255), g_Render->font.ESP, "Moving");
			g_Render->Textf(int(top.x + width + 5), int(top.y - 3 + (10 * SeiteWeischt++)), Color(0, 255, 0, 255), g_Render->font.ESP, "Moving");
			Seite++;
		}
		else
		{
			//g_Render->Textf(int(top.x + width + 5), int(top.y - 3 + (10 * SeiteWeischt++)), Color(255, 0, 0, 255), g_Render->font.ESP, "Standing");
			g_Render->Textf(int(top.x + width + 5), int(top.y - 3 + (10 * SeiteWeischt++)), Color(255, 0, 0, 255), g_Render->font.ESP, "Standing");
			Seite++;
		}
	}

	if (g_Options.Visuals.HasHelmet)
	{
		g_Render->Textf(int(top.x + width + 4.5), int(top.y - 3 + (10 * SeiteWeischt++)), Color(255, 255, 255, 255), g_Render->font.ESP, "HK", entity->HasHelmet());
		Seite++;
	}

	if (g_Options.Visuals.HPNumber)
	{
		g_Render->Textf(int(top.x + width + 3), int(top.y - 3 + (10 * SeiteWeischt++)), Color(255, 0, 0, 255), g_Render->font.ESP, "%i HP", entity->GetHealth());
		Seite++;
	}

	if (g_Options.Visuals.APNumber)
	{
		g_Render->Textf(int(top.x + width + 3), int(top.y - 3 + (10 * SeiteWeischt++)), Color(0, 233, 255, 255), g_Render->font.ESP, "%i AP", entity->ArmorValue());
		Seite++;
	}

	if (g_Options.Visuals.Money)
	{
		g_Render->Textf(int(top.x + width + 3), int(top.y - 3 + (10 * SeiteWeischt++)), Color(255, 255, 255, 255), g_Render->font.ESP, "%i $", entity->GetMoney());
		Seite++;
	}

	if (g_Options.Visuals.AmmoInClip)
	{
	//std::string Clip = std::to_string(pWeapon->GetAmmoInClip());
	//g_Render->DrawString2(g_Render->font.ESP, int(top.x + width + 3), int(top.y - 23), Color::White(), FONT_RIGHT, Clip.c_str());

	//g_Render->Textf(int(top.x + width + 3), int(top.y - 23), Color(255, 255, 255, 255), g_Render->font.ESP, "[%i / %i]", pWeapon->GetAmmoInClip(), pWeapon->GetAmmoInReserve());
	}
}


void visuals::Draw()
{

	C_BaseEntity* pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

	for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
	{
		C_BaseEntity *pEntity;
		C_BaseEntity* pParentEnt = (g_EntityList->GetClientEntityFromHandle(i));
		player_info_t pinfo;

		if (pEntity &&  pEntity != pLocal && !pEntity->IsDormant())
		{
			if (g_Options.Visuals.Radar)
			{
				NetVarManager->GetOffset("DT_BaseEntity", "m_bSpotted");
				*(char*)((DWORD)(pEntity)+offsetz.DT_BaseEntity.m_bSpotted) = 1;
			}

			ClientClass* cClass = (ClientClass*)pEntity->GetClientClass();
		}

	}
}

void visuals::DrawSkeleton(C_BaseEntity* entity)
{
	/////////////////////////////////////
	float red;
	float green;
	float blue;

	red = g_Options.Colors.espDrawSkeleton[0];
	green = g_Options.Colors.espDrawSkeleton[1];
	blue = g_Options.Colors.espDrawSkeleton[2];

	float newR = red * 255;
	float newG = green * 255;
	float newB = blue * 255;
	/////////////////////////////////////

	studiohdr_t* pStudioHdr = g_ModelInfo->GetStudiomodel(entity->GetModel());

	if (!pStudioHdr)
		return;

	Vector vParent, vChild, sParent, sChild;

	for (int j = 0; j < pStudioHdr->numbones; j++)
	{
		mstudiobone_t* pBone = pStudioHdr->GetBone(j);

		if (pBone && (pBone->flags & 0x100) && (pBone->parent != -1))
		{
			vChild = entity->GetBonePos(j);
			vParent = entity->GetBonePos(pBone->parent);

			if (g_Render->WorldToScreen(vParent, sParent) && g_Render->WorldToScreen(vChild, sChild))
			{

				g_Render->Line(sParent.x, sParent.y, sChild.x, sChild.y, Color(newR, newG, newB, 255));


			}
		}
	}
}

void visuals::PlayerBox(float x, float y, float w, float h, Color clr)
{
	// ESP OUTLINE BOX
	g_Surface->DrawSetColor(clr);
	g_Surface->DrawOutlinedRect(int(x - w), int(y), int(x + w), int(y + h));
	g_Surface->DrawSetColor(Color::Black());

	//g_Surface->DrawOutlinedRect(int(x - w - 1), int(y - 1), int(x + w + 1), int(y + h + 1));
	//g_Surface->DrawOutlinedRect(int(x - w + 1), int(y + 1), int(x + w - 1), int(y + h - 1));
}

void visuals::angleLines()
{
	float red2;
	float green2;
	float blue2;

	red2 = g_Options.Colors.espDrawFakeAngle[0];
	green2 = g_Options.Colors.espDrawFakeAngle[1];
	blue2 = g_Options.Colors.espDrawFakeAngle[2];

	float newR2 = red2 * 255;
	float newG2 = green2 * 255;
	float newB2 = blue2 * 255;
	/////////////////////////////////////
	float red1;
	float green1;
	float blue1;

	red1 = g_Options.Colors.espDrawRealAngle[0];
	green1 = g_Options.Colors.espDrawRealAngle[1];
	blue1 = g_Options.Colors.espDrawRealAngle[2];

	float newRR = red1 * 255;
	float newGG = green1 * 255;
	float newBB = blue1 * 255;
	/////////////////////////////////////
	float red3;
	float green3;
	float blue3;

	red3 = g_Options.Colors.espDrawLBYAngle[0];
	green3 = g_Options.Colors.espDrawLBYAngle[1];
	blue3 = g_Options.Colors.espDrawLBYAngle[2];

	float newRR3 = red3 * 255;
	float newGG3 = green3 * 255;
	float newBB3 = blue3 * 255;
	/////////////////////////////////////

	/////////////////////////////////////

	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	filter.pSkip = pLocal;
	/////////////////////////////////////
	AngleVectors(QAngle(0, pLocal->GetLowerBodyYaw(), 0), &forward);
	src3D = pLocal->GetOrigin();
	dst3D = src3D + (forward * 30.f);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, 0, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;

	g_Render->Line(src.x, src.y, dst.x, dst.y, Color(newRR3, newGG3, newBB3, 255));
	if (g_Options.Visuals.AngleText)
	{
		g_Render->Text(dst.x, dst.y, Color(newRR3, newGG3, newBB3, 255), g_Render->font.ESP, "LBY");
	}
	/////////////////////////////////////
	AngleVectors(QAngle(0, Globals::RealAngle, 0), &forward);
	src3D = pLocal->GetOrigin();
	dst3D = src3D + (forward * 30.f);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, 0, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;

	g_Render->Line(src.x, src.y, dst.x, dst.y, Color(newRR, newGG, newBB, 255));
	if (g_Options.Visuals.AngleText)
	{
		g_Render->Text(dst.x, dst.y, Color(20, 220, 20, 220), g_Render->font.ESP, "REAL");
	}
	/////////////////////////////////////
	AngleVectors(QAngle(0, Globals::FakeAngle, 0), &forward);
	dst3D = src3D + (forward * 30.f);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, 0, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;

	g_Render->Line(src.x, src.y, dst.x, dst.y, Color(newR2, newB2, newG2, 255));
	if (g_Options.Visuals.AngleText)
	{
		g_Render->Text(dst.x, dst.y, Color(newR2, newB2, newG2, 220), g_Render->font.ESP, "FAKE");
	}
	/////////////////////////////////////
}

void visuals::DrawAwall()
{
	float red;
	float green;
	float blue;

	red = g_Options.Colors.espDrawAwall[0];
	green = g_Options.Colors.espDrawAwall[1];
	blue = g_Options.Colors.espDrawAwall[2];

	float rednigger = red * 255; // ZXC's Vater
	float greennigger = green * 255; // ZXC's Mutter
	float bluenigger = blue * 255; // Was kommt raus? Genau! ein Hurensohn Namens ZXC!

	int MidX;
	int MidY;
	g_Engine->GetScreenSize(MidX, MidY);

	int damage;
	if (CanWallbang(damage))
	{
		g_Render->Textf(MidX / 2, MidY / 2 + 6, Color(rednigger, greennigger, bluenigger, 255), g_Render->font.ESP, "DMG: %1i", damage);
	}
}

void visuals::Hitmarker()
{
	if (G::hitmarkeralpha < 0.f)
		G::hitmarkeralpha = 0.f;
	else if (G::hitmarkeralpha > 0.f)
		G::hitmarkeralpha -= 0.01f;

	int W, H;
	g_Engine->GetScreenSize(W, H);

	if (G::hitmarkeralpha > 0.f)
	{
		g_Render->Line(W / 2 - 10, H / 2 - 10, W / 2 - 5, H / 2 - 5, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 - 10, H / 2 + 10, W / 2 - 5, H / 2 + 5, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 + 10, H / 2 - 10, W / 2 + 5, H / 2 - 5, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 + 10, H / 2 + 10, W / 2 + 5, H / 2 + 5, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));

	}
}

Color visuals::GetPlayerColor(C_BaseEntity* entity, C_BaseEntity* local)
{

	// Visible T
	float vred;
	float vgreen;
	float vblue;

	vred = g_Options.Colors.espVisT[0];
	vgreen = g_Options.Colors.espVisT[1];
	vblue = g_Options.Colors.espVisT[2];

	float vnewR = vred * 255;
	float vnewG = vgreen * 255;
	float vnewB = vblue * 255;

	// Invisible T
	float ired;
	float igreen;
	float iblue;

	ired = g_Options.Colors.espInvisT[0];
	igreen = g_Options.Colors.espInvisT[1];
	iblue = g_Options.Colors.espInvisT[2];

	float inewR = ired * 255;
	float inewG = igreen * 255;
	float inewB = iblue * 255;

	// Visible CT
	float vired;
	float vigreen;
	float viblue;

	vired = g_Options.Colors.espVisCT[0];
	vigreen = g_Options.Colors.espVisCT[1];
	viblue = g_Options.Colors.espVisCT[2];

	float vinewR = vired * 255;
	float vinewG = vigreen * 255;
	float vinewB = viblue * 255;

	// Invisible CT
	float inred;
	float ingreen;
	float inblue;

	inred = g_Options.Colors.espInvisCT[0];
	ingreen = g_Options.Colors.espInvisCT[1];
	inblue = g_Options.Colors.espInvisCT[2];

	float innewR = inred * 255;
	float innewG = ingreen * 255;
	float innewB = inblue * 255;

	int TeamNum = entity->GetTeamNum();
	bool IsVis = MiscFunctions::IsVisible(local, entity, Head);

	Color color;
	// ESP BOX COLOR
	if (TeamNum == TEAM_CS_T)
	{
		if (IsVis)
			color = Color(vnewR, vnewG, vnewB, 255);
		else
			color = Color(inewR, inewG, inewB, 255);

	}
	else
	{

		if (IsVis)
			color = Color(vinewR, vinewG, vinewB, 255);
		else
			color = Color(innewR, innewG, innewB, 255);
	}


	return color;
}

void visuals::DrawHealth(C_BaseEntity* entity, visuals::ESPBox size)
{
	int health = entity->GetHealth();
	int HP = health;

	int hp = health;
	float r = float(255 - health * 2.55);
	float g = float(health * 2.55);
	hp = (size.h - ((size.h * hp) / 100));

	g_Render->Outline(int(size.x - 4), int(size.y + hp), (int)2, int(size.h - hp + 1), Color((int)r, (int)g, 0));
	g_Render->Outline(int(size.x - 5), int(size.y - 1), (int)3, int(size.h + 2), Color(0, 0, 0, 150));
}

void visuals::DrawHealth(Vector bot, Vector top, float health)
{
	float red;
	float green;
	float blue;

	red = g_Options.Colors.espDrawHealth[0];
	green = g_Options.Colors.espDrawHealth[1];
	blue = g_Options.Colors.espDrawHealth[2];

	float newR = red * 255;
	float newG = green * 255;
	float newB = blue * 255;

	float h = (bot.y - top.y);
	float offset = (h / 3) + 5;
	float w = h / 64.f;

	if (health > 100)
		health = 100;
	UINT hp = UINT(h - (UINT)((h * health) / 100)); // Percentage


													//int Red = int(255 - (health*2.55));
													//int Red = int(health*0);

	g_Render->DrawOutlinedRect(int((top.x - offset) - 1), int(top.y - 1), 3, int(h + 2), Color::Black());

	g_Render->Line(int((top.x - offset)), int(top.y + hp), int((top.x - offset)), int(top.y + h), Color(newR, newG, newB, 255));
}

void visuals::DrawArmor(C_BaseEntity* entity, visuals::ESPBox size)
{
	int armor = entity->ArmorValue();
	int AP = armor;
	if (AP > 100)
		AP = 100;
	int ap = armor;
	float r = float(255 - armor * 2.55);
	float g = float(armor * 2.55);
	ap = (size.h - ((size.h * ap) / 100));

	g_Render->Outline(int(size.x - 4), int(size.y + ap), (int)2, int(size.h - ap + 1), Color((int)r, (int)g, 0));
	g_Render->Outline(int(size.x - 5), int(size.y - 1), (int)3, int(size.h + 2), Color(0, 0, 0, 150));
}

void visuals::DrawArmor(Vector bot, Vector top, float armor)
{
	float red;
	float green;
	float blue;

	red = g_Options.Colors.espDrawArmor[0];
	green = g_Options.Colors.espDrawArmor[1];
	blue = g_Options.Colors.espDrawArmor[2];

	float newR = red * 255;
	float newG = green * 255;
	float newB = blue * 255;

	float h = (bot.y - top.y);
	float offset = (h / 4.f) + 5;
	float w = h / 64.f;

	if (armor > 100)
		armor = 100;
	UINT ap = UINT(h - (UINT)((h * armor) / 100)); // Percentage

												   //int Blue = int(255 - (armor*2.55));
												   //int Green = int(armor*0);

	g_Render->DrawOutlinedRect(int((top.x - offset) - 1), int(top.y - 1), 3, int(h + 2), Color::Black());

	g_Render->Line(int((top.x - offset)), int(top.y + ap), int((top.x - offset)), int(top.y + h), Color(newR, newG, newB, 255)); // COLOR
}

void visuals::DrawDrop(C_BaseEntity* entity)
{
	float red;
	float green;
	float blue;

	red = g_Options.Colors.espDrawDrop[0];
	green = g_Options.Colors.espDrawDrop[1];
	blue = g_Options.Colors.espDrawDrop[2];

	float newR = red * 255;
	float newG = green * 255;
	float newB = blue * 255;
	if (entity)
	{
		CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)entity;

		auto owner = pWeapon->GetOwnerHandle();

		if (owner > -1)
			return;

		Vector pos3D = entity->GetAbsOrigin2();

		if (pos3D.x == 0.0f && pos3D.y == 0.0f && pos3D.z == 0.0f)
			return;

		Vector pos;

		if (!g_Render->WorldToScreen(pos3D, pos))
			return;

		int weaponID = pWeapon->m_AttributeManager()->m_Item()->GetItemDefinitionIndex();
		auto weaponName = ItemDefinitionIndexToString(weaponID);


		g_Render->Text(pos.x, pos.y, Color(newR, newG, newB, 255), g_Render->font.DroppedGuns, weaponName);
	}
}

float damage;
char bombdamagestringdead[24];
char bombdamagestringalive[24];

void visuals::DrawBombPlanted(C_BaseEntity* entity, C_BaseEntity* local)
{
	BombCarrier = nullptr;

	Vector vOrig; Vector vScreen;
	vOrig = entity->GetOrigin();
	CCSBomb* Bomb = (CCSBomb*)entity;
	float flBlow = Bomb->GetC4BlowTime();
	float lifetime = flBlow - (g_Globals->interval_per_tick * local->GetTickBase());

	int width = 0;
	int height = 0;
	g_Engine->GetScreenSize(width, height);

	if (g_Options.Visuals.C4Timer)
	{
		if (g_Engine->IsConnected() && g_Engine->IsInGame()) //&& local->IsAlive())
		{
			if (lifetime > 0.01f && !Bomb->IsBombDefused())
			{
				g_Render->Textf(10, height / 2 - 30, Color(255, 0, 0, 255), g_Render->font.C4Timer, "C4: %.1f", lifetime);
			}
		}
	}

	if (g_Options.Visuals.DefuseTimer)
	{
		if (g_Engine->IsConnected() && g_Engine->IsInGame())
		{
			if (Bomb->GetBombDefuser() > 0)
			{
				float countdown = Bomb->GetC4DefuseCountDown() - (local->GetTickBase() * g_Globals->interval_per_tick);
				if (countdown > 0.01f)
				{
					if (lifetime > countdown)
					{
						g_Render->Textf(10, height / 2, Color(0, 233, 255, 255), g_Render->font.C4Timer, "Defusing: %.1f", countdown);
					}
				}
			}
		}
	}


	if (g_Options.Visuals.C4Planted)
	{
		if (g_Render->WorldToScreen(vOrig, vScreen))
		{
			if (g_Engine->IsConnected() && g_Engine->IsInGame()) //&& local->IsAlive())
			{
				float flDistance = local->GetEyePosition().DistTo(entity->GetEyePosition());
				float a = 450.7f;
				float b = 75.68f;
				float c = 789.2f;
				float d = ((flDistance - b) / c);
				float flDamage = a*exp(-d * d);
				////////////////////////////////////////////////
				float red;
				float green;
				float blue;

				red = g_Options.Colors.espDrawBomb[0];
				green = g_Options.Colors.espDrawBomb[1];
				blue = g_Options.Colors.espDrawBomb[2];

				float newR = red * 255;
				float newG = green * 255;
				float newB = blue * 255;
				////////////////////////////////////////////////
				damage = float((std::max)((int)ceilf(CSGO_Armor(flDamage, local->ArmorValue())), 0));

				sprintf_s(bombdamagestringdead, sizeof(bombdamagestringdead) - 1, "[C4]");
				//sprintf_s(bombdamagestringalive, sizeof(bombdamagestringalive) - 1, "C4 DMG: %.0f", local->GetHealth() + damage);
				if (lifetime > -2.f)
				{
					if (damage >= local->GetHealth())
					{
						g_Render->Text((int)vScreen.x, int(vScreen.y + 10), Color(newR, newG, newB, 255), g_Render->font.Defuse, bombdamagestringdead);
					}
				}
			}
		}
	}
}



void visuals::DrawBomb(C_BaseEntity* entity, ClientClass* cClass)
{
	// Null it out incase bomb has been dropped or planted
	BombCarrier = nullptr;
	CBaseCombatWeapon *BombWeapon = (CBaseCombatWeapon *)entity;
	Vector vOrig; Vector vScreen;
	vOrig = entity->GetOrigin();
	bool adopted = true;
	auto parent = BombWeapon->GetOwnerHandle();
	if (g_Engine->IsConnected() && g_Engine->IsInGame())
		if (parent || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
		{
			C_BaseEntity* pParentEnt = (g_EntityList->GetClientEntityFromHandle(parent));
			if (pParentEnt && pParentEnt->IsAlive())
			{
				BombCarrier = pParentEnt;
				adopted = false;
			}
		}
	if (g_Options.Visuals.Weapon) // dropped c4
	{
		if (adopted)
		{
			if (g_Render->WorldToScreen(vOrig, vScreen))
			{
				g_Render->Text((int)vScreen.x, (int)vScreen.y, Color(255, 255, 0, 255), g_Render->font.ESP, "C4");
			}
		}
	}
}

void visuals::DrawBox(visuals::ESPBox size, Color color)
{
	g_Render->Outline(size.x, size.y, size.w, size.h, color);
	g_Render->Outline(size.x - 1, size.y - 1, size.w + 2, size.h + 2, Color(10, 10, 10, 150));
	g_Render->Outline(size.x + 1, size.y + 1, size.w - 2, size.h - 2, Color(10, 10, 10, 150));
}

bool visuals::GetBox(C_BaseEntity* entity, visuals::ESPBox &result)
{
	// Variables
	Vector  vOrigin, min, max, sMin, sMax, sOrigin,
		flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	// Get the locations
	vOrigin = entity->GetOrigin();
	min = entity->collisionProperty()->GetMins() + vOrigin;
	max = entity->collisionProperty()->GetMaxs() + vOrigin;

	// Points of a 3d bounding box
	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };

	// Get screen positions
	if (!g_Render->WorldToScreen(points[3], flb) || !g_Render->WorldToScreen(points[5], brt)
		|| !g_Render->WorldToScreen(points[0], blb) || !g_Render->WorldToScreen(points[4], frt)
		|| !g_Render->WorldToScreen(points[2], frb) || !g_Render->WorldToScreen(points[1], brb)
		|| !g_Render->WorldToScreen(points[6], blt) || !g_Render->WorldToScreen(points[7], flt))
		return false;

	// Put them in an array (maybe start them off in one later for speed?)
	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	// Init this shit
	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	// Find the bounding corners for our box
	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	// Width / height
	result.x = (int)left;
	result.y = (int)top;
	result.w = int(right - left);
	result.h = int(bottom - top);
	result.gay = (int)top;

	return true;
}


void visuals::BoxAndText(C_BaseEntity* entity, std::string text)
{
	ESPBox Box;
	std::vector<std::string> Info;
	if (GetBox(entity, Box))
	{
		Info.push_back(text);
		if (g_Options.Visuals.GrenadeESP)
		{
			DrawBox(Box, Color(255, 255, 255, 255));
			int i = 0;
			for (auto kek : Info)
			{
				g_Render->Text(Box.x + 1, Box.y + 1, Color(255, 255, 255, 255), g_Render->font.ESP, kek.c_str());
				i++;
			}
		}
	}
}


void visuals::DrawThrowable(C_BaseEntity* throwable)
{
	model_t* nadeModel = (model_t*)throwable->GetModel();

	if (!nadeModel)
		return;

	studiohdr_t* hdr = g_ModelInfo->GetStudiomodel(nadeModel);

	if (!hdr)
		return;

	if (!strstr(hdr->name, "thrown") && !strstr(hdr->name, "dropped"))
		return;

	std::string nadeName = "Unknown Grenade";

	IMaterial* mats[32];
	g_ModelInfo->GetModelMaterials(nadeModel, hdr->numtextures, mats);

	for (int i = 0; i < hdr->numtextures; i++)
	{
		IMaterial* mat = mats[i];
		if (!mat)
			continue;

		if (strstr(mat->GetName(), "flashbang"))
		{
			nadeName = "Flashbang";
			break;
		}
		else if (strstr(mat->GetName(), "m67_grenade") || strstr(mat->GetName(), "hegrenade"))
		{
			nadeName = "Nade";
			break;
		}
		else if (strstr(mat->GetName(), "smoke"))
		{
			nadeName = "Smoke";
			break;
		}
		else if (strstr(mat->GetName(), "decoy"))
		{
			nadeName = "Decoy";
			break;
		}
		else if (strstr(mat->GetName(), "incendiary") || strstr(mat->GetName(), "molotov"))
		{
			nadeName = "Molotov";
			break;
		}
	}

	BoxAndText(throwable, nadeName);
}

void visuals::DLight(C_BaseEntity *local, C_BaseEntity* entity)
{
	player_info_t pinfo;
	if (local && entity && entity != local)
	{
		if (g_Engine->GetPlayerInfo(entity->GetIndex(), &pinfo) && entity->IsAlive() && !entity->IsDormant())
		{
			if (local->GetTeamNum() != entity->GetTeamNum())
			{
				dlight_t* pElight = g_Dlight->CL_AllocElight(entity->GetIndex());
				pElight->origin = entity->GetOrigin() + Vector(0.0f, 0.0f, 35.0f);
				pElight->radius = g_Options.Visuals.dLightRadius;
				pElight->color.b = g_Options.Visuals.dLightB; // 36
				pElight->color.g = g_Options.Visuals.dLightG; // 224
				pElight->color.r = g_Options.Visuals.dLightR; // 41
				pElight->die = g_Globals->curtime + 0.05f;
				pElight->decay = pElight->radius / 5.0f;
				pElight->key = entity->GetIndex();

				dlight_t* pDlight = g_Dlight->CL_AllocDlight(entity->GetIndex());
				pDlight->origin = entity->GetOrigin();
				pDlight->radius = g_Options.Visuals.dLightRadius;
				pDlight->color.b = g_Options.Visuals.dLightB; // 36
				pDlight->color.g = g_Options.Visuals.dLightG; // 224
				pDlight->color.r = g_Options.Visuals.dLightR; // 41
				pDlight->die = g_Globals->curtime + 0.05f;
				pDlight->decay = pDlight->radius; // / 5.0f;
				pDlight->key = entity->GetIndex();
			}
		}
	}
}

void visuals::NightMode()
{
	int SkyboxCombo = g_Options.Misc.nightModeStyle;
	static auto sv_skyname = g_CVar->FindVar("sv_skyname");

	if (g_Engine->IsInGame())
	{
		switch (SkyboxCombo)
		{
		case 0:
			break;
		case 1:
			sv_skyname->SetValue("cs_baggage_skybox_");
			break;
		case 2:
			sv_skyname->SetValue("cs_tibet");
			break;
		case 3:
			sv_skyname->SetValue("embassy");
			break;
		case 4:
			sv_skyname->SetValue("italy");
			break;
		case 5:
			sv_skyname->SetValue("jungle");
			break;
		case 6:
			sv_skyname->SetValue("office");
			break;
		case 7:
			sv_skyname->SetValue("sky_cs15_daylight01_hdr");
			break;
		case 8:
			sv_skyname->SetValue("sky_cs15_daylight02_hdr");
			break;
		case 9:
			sv_skyname->SetValue("sky_day02_05");
			break;
		case 10:
			sv_skyname->SetValue("nukeblank");
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
		}
	}

	if (g_Options.Misc.nightMode)
	{
		if (g_Engine->IsInGame())
		{
			if (!done)
			{
				//static auto sv_skyname = g_CVar->FindVar("sv_skyname");
				static auto r_DrawSpecificStaticProp = g_CVar->FindVar("r_DrawSpecificStaticProp");
				r_DrawSpecificStaticProp->SetValue(1);
				sv_skyname->SetValue("sky_csgo_night02");

				for (MaterialHandle_t i = g_MaterialSystem->FirstMaterial(); i != g_MaterialSystem->InvalidMaterial(); i = g_MaterialSystem->NextMaterial(i))
				{
					IMaterial *pMaterial = g_MaterialSystem->GetMaterial(i);

					if (!pMaterial)
						continue;

					const char* group = pMaterial->GetTextureGroupName();
					const char* name = pMaterial->GetName();

					if (strstr(group, "World textures"))
					{
						pMaterial->ColorModulate(0.05, 0.05, 0.05);
					}
					if (strstr(group, "StaticProp"))
					{
						pMaterial->ColorModulate(0.15, 0.15, 0.15);
					}
					if (strstr(name, "models/props/de_dust/palace_bigdome"))
					{
						pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					}
					if (strstr(name, "models/props/de_dust/palace_pillars"))
					{
						pMaterial->ColorModulate(0.15, 0.15, 0.15);
					}

					if (strstr(group, "Particle textures"))
					{
						pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					}
					done = true;
				}
			}
		}
	}
	else
	{
		if (done)
		{
			for (MaterialHandle_t i = g_MaterialSystem->FirstMaterial(); i != g_MaterialSystem->InvalidMaterial(); i = g_MaterialSystem->NextMaterial(i))
			{
				IMaterial *pMaterial = g_MaterialSystem->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, "StaticProp"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
			}
			done = false;
		}
	}
}

void visuals::SpecList(C_BaseEntity *local)
{

	RECT scrn = g_Render->GetViewport();
	int kapi = 0;

	if (local)
	{
		for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
		{
			// Get the entity
			C_BaseEntity *pEntity = g_EntityList->GetClientEntity(i);
			player_info_t pinfo;
			if (pEntity && pEntity != local)
			{
				if (g_Engine->GetPlayerInfo(i, &pinfo) && !pEntity->IsAlive() && !pEntity->IsDormant())
				{
					HANDLE obs = pEntity->GetObserverTargetHandle();
					if (obs)
					{
						C_BaseEntity *pTarget = g_EntityList->GetClientEntityFromHandle(obs);
						player_info_t pinfo2;
						if (pTarget && pTarget->GetIndex() == local->GetIndex())
						{
							if (g_Engine->GetPlayerInfo(pTarget->GetIndex(), &pinfo2))
							{
								g_Render->DrawString2(g_Render->font.Time, scrn.right - 168, (scrn.top) + (16 * kapi) + 20, Color(255, 255, 255, 255), FONT_LEFT, "-> %s <-", pinfo.name);
								kapi++;
							}
						}
					}
				}
			}
		}
	}
	//g_Render->DrawString2(g_Render->font.ESP, scrn.right - 98, (scrn.top) + 10, Color(255, 255, 255, 255), FONT_LEFT, "Watching you:");
}