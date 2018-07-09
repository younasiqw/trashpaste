#pragma once
#include "HookIncludes.h"
#include "Interfaces.h"
#include <ctime>
#include "ESP.h"
#include <string>
#include "Resolver.h"

typedef void(__thiscall* paint_traverse_t)(PVOID, unsigned int, bool, bool);


bool once = true;
bool once1 = false;
int width1 = 0;
int height1 = 0;
void __fastcall hkPaintTraverse(PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	static auto ofunc = hooks::panel.get_original<paint_traverse_t>(41);
	C_BaseEntity* local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	if (local != nullptr && local->IsAlive() && g_Options.Visuals.noscopeborder && !strcmp("HudZoom", g_Panel->GetName(vguiPanel)))
	{
		return;
	}
	ofunc(pPanels, vguiPanel, forceRepaint, allowForce);
	static unsigned int FocusOverlayPanel = 0;
	static bool FoundPanel = false;
	if (!FoundPanel)
	{
		PCHAR szPanelName = (PCHAR)g_Panel->GetName(vguiPanel);
		if (strstr(szPanelName, "FocusOverlayPanel"))
		{
			FocusOverlayPanel = vguiPanel;
			FoundPanel = true;
		}
	}
	else if (FocusOverlayPanel == vguiPanel)
	{
		if (g_Engine->IsConnected() && g_Engine->IsInGame())
		{
			static auto linegoesthrusmoke = U::FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x83\xEC\x08\x8B\x15\x00\x00\x00\x00\x0F\x57\xC0", "xxxxxxxx????xxx");
			static auto smokecout = *(DWORD*)(linegoesthrusmoke + 0x8);
			if (g_Options.Visuals.NoSmoke) *(int*)(smokecout) = 0;

			visuals::instance().OnPaintTraverse(local);

			auto m_flFlashDuration = NetVarManager->GetOffset("DT_CSPlayer", "m_flFlashDuration");
			auto m_flFlashMaxAlpha = NetVarManager->GetOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
			if (local != nullptr)
			{
				CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(local->GetActiveWeaponHandle());
				if (g_Options.Visuals.NoFlash)
				{
					*MakePtr(float*, local, m_flFlashDuration) = 0.f;
					*MakePtr(float*, local, m_flFlashMaxAlpha) = 0.f;
				}
				if (local && local->IsScoped() && g_Options.Visuals.noscopeborder && MiscFunctions::IsSniperScope(pWeapon))
				{
					int width = 0;
					int height = 0;
					g_Engine->GetScreenSize(width, height);

					int centerX = static_cast<int>(width * 0.5f);
					int centerY = static_cast<int>(height * 0.5f);
					g_Render->Line(0, centerY, width, centerY, Color(0, 0, 0, 255));
					g_Render->Line(centerX, 0, centerX, height, Color(0, 0, 0, 255));
				}
			}
		}

		if (!g_Engine->IsInGame()) {
			g_Options.Misc.NameChangerFix = false;
			g_Options.Misc.NameSpammer = 0;
			g_Options.Misc.ChatSpamMode = false;
			g_Options.Misc.namespam = false;
			g_Options.Misc.silentstealer = false;
		}

		if (g_Options.Visuals.angleLines == false)
		{
			g_Options.Visuals.AngleText = false;
		}

		if (g_Options.Ragebot.MainSwitch && !once)
		{
			g_Options.Legitbot.MainSwitch = false;
			once = !once;
		}

		if (g_Options.Legitbot.MainSwitch && once)
		{
			g_Options.Ragebot.MainSwitch = false;
			once = !once;
		}

		if (g_Options.Ragebot.PreAAs && !once)
		{
			g_Options.Ragebot.BuilderAAs = false;
			once = !once;
		}

		if (g_Options.Ragebot.BuilderAAs && once)
		{
			g_Options.Ragebot.PreAAs = false;
			once = !once;
		}

		if (g_Options.Ragebot.PreAAs && !once)
		{
			g_Options.Ragebot.LegitAA = false;
			once = !once;
		}

		if (g_Options.Ragebot.LegitAA && once)
		{
			g_Options.Ragebot.PreAAs = false;
			once = !once;
		}

		if (g_Options.Ragebot.LegitAA && !once)
		{
			g_Options.Ragebot.BuilderAAs = false;
			once = !once;
		}

		if (g_Options.Ragebot.BuilderAAs && once)
		{
			g_Options.Ragebot.LegitAA = false;
			once = !once;
		}

		if (g_Options.Ragebot.BuilderAAs && !once)
		{
			g_Options.Ragebot.LegitAA = false;
			once = !once;
		}

		if (g_Options.Ragebot.LegitAA && once)
		{
			g_Options.Ragebot.BuilderAAs = false;
			once = !once;
		}

		if (g_Options.Ragebot.RealCustomStaticLinks)
		{
			g_Options.Ragebot.RealCustomJitterLinks = false;
		}
		if (g_Options.Ragebot.RealCustomJitterLinks)
		{
			g_Options.Ragebot.RealCustomStaticLinks = false;
		}

		if (g_Options.Ragebot.RealCustomStaticRechts)
		{
			g_Options.Ragebot.RealCustomJitterRechts = false;
		}
		if (g_Options.Ragebot.RealCustomJitterRechts)
		{
			g_Options.Ragebot.RealCustomStaticRechts = false;
		}

		if (g_Options.Visuals.LBYInfo)
		{
			if (g_Engine->IsInGame() && g_Engine->IsConnected() && local->IsAlive())
			{
				std::string lby = "LBY: " + std::to_string(local->GetLowerBodyYaw());
				std::string anglesx = "Yaw: " + std::to_string(local->GetEyeAngles()->x);
				std::string anglesy = "Pitch: " + std::to_string(local->GetEyeAngles()->y == local->GetLowerBodyYaw());

				g_Render->DrawString2(g_Render->font.LBY, 120, 350, Color::Yellow(), FONT_RIGHT, lby.c_str()); // LBY
				g_Render->DrawString2(g_Render->font.LBY, 120, 370, Color::Green(), FONT_RIGHT, anglesx.c_str()); // Yaw
				g_Render->DrawString2(g_Render->font.LBY, 120, 390, Color::APCyan(), FONT_RIGHT, anglesy.c_str()); // Pitch
			}
		}

		if (g_Options.Visuals.Watermark)
		{
			g_Render->Textf(15, 15, Color(242, 255, 242, 242), g_Render->font.Logo, "DON'T EXPECT TOO MUCH");
			g_Render->Textf(15, 30, Color(242, 255, 242, 242), g_Render->font.Logo, "TRASHBUILD V13.37");		
		}

		if (g_Options.Visuals.Warnings)
		{
			/*
								  ____   _____ _____  
								 / __ \ / ____|  __ \ 
								| |  | | (___ | |  | |
								| |  | |\___ \| |  | |
								| |__| |____) | |__| |
								 \____/|_____/|_____/ 
                      
			*/
			///////////////////		Main Booleans	///////////////////
			bool RageTab = g_Options.Ragebot.MainSwitch;
			bool Aimbot = g_Options.Ragebot.Enabled;
			bool LegitTab = g_Options.Legitbot.MainSwitch;
			bool VisualsTab = g_Options.Visuals.Enabled;
			bool RageBacktrack = g_Options.Ragebot.rageBacktrack;
			bool LegitBacktrack = g_Options.Legitbot.backtrack;
			bool BacktrackAndRage = g_Options.Ragebot.rageBacktrack && g_Options.Ragebot.MainSwitch;
			bool BacktrackAndLegit = g_Options.Legitbot.backtrack && g_Options.Legitbot.MainSwitch;
			bool BacktrackDisabled = RageTab == false && LegitTab == false || RageBacktrack == false && LegitBacktrack == false || RageBacktrack && LegitTab && LegitBacktrack == false && RageTab == false || RageBacktrack == false && LegitTab == false && LegitBacktrack && RageTab;
			///////////////////		Anti-Aim Booleans	///////////////////
			bool PreAAs = g_Options.Ragebot.PreAAs;
			bool EnabledAntiAim = g_Options.Ragebot.EnabledAntiAim;
			bool BuilderAAs = g_Options.Ragebot.BuilderAAs;
			bool MoveAA = g_Options.Ragebot.YawFakeMoveEnabled;
			///////////////////////////////////////////////////////////////
			int RealYaw = g_Options.Ragebot.YawTrue;
			int FakeYaw = g_Options.Ragebot.YawFake;
			int MoveRealYaw = g_Options.Ragebot.YawTrueMove;
			int MoveFakeYaw = g_Options.Ragebot.YawFakeMove;
			///////////////////////////////////////////////////////////////

			///////////////////////////////////////////////////////////////

			///////////////////
			//// Positions ////
			///////////////////

			int MainXPos = 250;
			///////////////////
			int FovPosY = 45;
			int RagePosY = 60;
			int LegitPosY = 75;
			int VisualsPosY = 90;
			int AAPosY = 105;
			int MAAPosY = 120;
			int BacktrackPosY = 135;
			int GeneralYPos = 45;

			// Yaw True (real) Position //
			int YawTPosY = 180;
			// Yaw Fake Position //
			int YawFPosY = YawTPosY + 15;
			// Yaw True (real) Move Position //
			int YawTMPosY = YawFPosY + 15;
			// Yaw Fake Move Position //
			int YawFMPosY = YawTMPosY + 15;
			int Oof2 = 0;
			///////////////////////////////////////////////////////////////

			///////////////////////////////////////////////////////////////

			Color FovRed = { 255, 30, 30, 255};
			Color FovOrange = { 255, 120, 0, 255 };
			Color FovGreen = { 30, 255, 30, 255 };
			Color FovWhite = { 255, 255, 255, 255 };
			int Oof = 0;

			g_Render->Textf(MainXPos, GeneralYPos + (15* Oof++), Color(255, 255, 255, 255), g_Render->font.Logo, "FOV:");
			g_Render->Textf(MainXPos, GeneralYPos + (15 * Oof++), Color(255, 255, 255, 255), g_Render->font.Logo, "Ragebot:");
			g_Render->Textf(MainXPos, GeneralYPos + (15 * Oof++), Color(255, 255, 255, 255), g_Render->font.Logo, "Aimbot:");
			g_Render->Textf(MainXPos, GeneralYPos + (15 * Oof++), Color(255, 255, 255, 255), g_Render->font.Logo, "Backtrack:");
			g_Render->Textf(MainXPos, GeneralYPos + (15 * Oof++), Color(255, 255, 255, 255), g_Render->font.Logo, "Legitbot:");
			g_Render->Textf(MainXPos, GeneralYPos + (15 * Oof++), Color(255, 255, 255, 255), g_Render->font.Logo, "Visuals:");
			g_Render->Textf(MainXPos, GeneralYPos + (15 * Oof++), Color(255, 255, 255, 255), g_Render->font.Logo, "Anti-Aim:");
			g_Render->Textf(MainXPos, GeneralYPos + (15 * Oof++), Color(255, 255, 255, 255), g_Render->font.Logo, "Move AA:");

			/////////////////////////////////////// FOV INFO ////////////////////////////////////////////////////////

			if (g_Options.Ragebot.FOV > 89.9)
			{
				g_Render->Textf(315, FovPosY, Color(FovRed), g_Render->font.Logo, "%.0f", g_Options.Ragebot.FOV); // when > 180 = Red
			}
			if (g_Options.Ragebot.FOV < 89.9)
			{
				g_Render->Textf(315, FovPosY, Color(FovOrange), g_Render->font.Logo, "%.0f", g_Options.Ragebot.FOV); // when > 90 = Orange
			}
			if (g_Options.Ragebot.FOV < 45.1)
			{
				g_Render->Textf(315, FovPosY, Color(FovGreen), g_Render->font.Logo, "%.0f", g_Options.Ragebot.FOV); // when > 45 = Green
			}
			if (g_Options.Ragebot.FOV < 1)
			{
				g_Render->Textf(315, FovPosY, Color(FovWhite), g_Render->font.Logo, "%.0f", g_Options.Ragebot.FOV); // when < 1 = White
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// WAS GEMACHT AN DER DISABLE ENABLED KACKE AK

			if (RageTab)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (RageTab == false)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}

			if (Aimbot && RageTab)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (RageTab == false && Aimbot || RageTab == false && Aimbot == false || Aimbot == false)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}

			if (RageBacktrack && RageTab || LegitBacktrack && LegitTab)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (BacktrackDisabled)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}

			if (LegitTab)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (LegitTab == false)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}

			if (VisualsTab)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (VisualsTab == false)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}

			if (EnabledAntiAim)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (EnabledAntiAim == false)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}

			if (MoveAA)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (MoveAA == false)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}

			/*if (RageTab)
			{
				g_Render->Textf(315, 60 + (15* Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (g_Options.Ragebot.Enabled)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (LegitTab)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (VisualsTab)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (EnabledAntiAim && PreAAs || EnabledAntiAim && BuilderAAs)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (EnabledAntiAim && MoveAA)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}
			if (RageBacktrack && RageTab || LegitBacktrack && LegitTab)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 30, 30, 255), g_Render->font.Logo, "Enabled!");
			}

			if (RageTab == false)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}
			if (LegitTab == false)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}
			if (VisualsTab == false)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}
			if (EnabledAntiAim == false || PreAAs == false && BuilderAAs == false)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}
			if (EnabledAntiAim == false || MoveAA == false)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}
			if (BacktrackDisabled)
			{
				g_Render->Textf(315, 60 + (15 * Oof2++), Color(255, 255, 255, 255), g_Render->font.Logo, "Disabled");
			}*/

			/////////////////////////////////////// ANTI AIM INFO ////////////////////////////////////////////////////////

			switch (RealYaw)
			{
			case 0:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Off");
				break;
			case 1:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Sideways Jitter");
				break;
			case 2:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Slow Spin");
				break;
			case 3:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Fast Spin");
				break;
			case 4:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Backwards");
				break;
			case 5:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: LBY Break");
				break;
			case 6:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Back Jitter");
				break;
			case 7:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: LBY Jitter");
				break;
			case 8:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Random");
				break;
			case 9:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: 90/90 LBY");
				break;
			case 10:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Manual AA");
				break;
			case 11:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Manual AA Jitter");
				break;
			case 12:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: 165/90 LBY");
				break;
			case 13:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Sideways");
				break;
			case 14:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: 165/30 LBY");
				break;
			case 15:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: 165/30 LBY Jitter");
				break;
			case 16:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: 90/90 LBY Jitter");
				break;
			case 17:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Manual SMAC");
				break;
			case 18:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Sideways SMAC");
				break;
			case 19:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: 250/280 LBY Jitter");
				break;
			case 20:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Experimental");
				break;
			case 21:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: MasterLooser");
				break;
			case 22:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Experimental 2");
				break;
			case 23:
				g_Render->Textf(MainXPos, YawTPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Real Yaw: Custom");
				break;
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////

			switch (FakeYaw)
			{
			case 0:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Off");
				break;
			case 1:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Sideways Jitter");
				break;
			case 2:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Slow Spin");
				break;
			case 3:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Fast Spin");
				break;
			case 4:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Backwards");
				break;
			case 5:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: LBY Break");
				break;
			case 6:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Forward Jitter");
				break;
			case 7:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Jitter");
				break;
			case 8:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: LBY Jitter");
				break;
			case 9:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Forward");
				break;
			case 10:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Random Fake");
				break;
			case 11:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Inversed AA Jitter");
				break;
			case 12:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Inversed AA");
				break;
			case 13:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Sideways");
				break;
			case 14:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Manual SMAC");
				break;
			case 15:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Sideways SMAC");
				break;
			case 16:
				g_Render->Textf(MainXPos, YawFPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Fake Yaw: Half Spin");
				break;
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////

			switch (MoveRealYaw)
			{
			case 0:
				g_Render->Textf(MainXPos, YawTMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Real Yaw: Off");
				break;
			case 1:
				g_Render->Textf(MainXPos, YawTMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Real Yaw: Sideways Jitter");
				break;
			case 2:
				g_Render->Textf(MainXPos, YawTMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Real Yaw: Slow Spin");
				break;
			case 3:
				g_Render->Textf(MainXPos, YawTMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Real Yaw: Fast Spin");
				break;
			case 4:
				g_Render->Textf(MainXPos, YawTMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Real Yaw: Backwards");
				break;
			case 5:
				g_Render->Textf(MainXPos, YawTMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Real Yaw: Back Jitter");
				break;
			case 6:
				g_Render->Textf(MainXPos, YawTMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Real Yaw: Random");
				break;
			case 7:
				g_Render->Textf(MainXPos, YawTMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Real Yaw: Manual AA");
				break;
			case 8:
				g_Render->Textf(MainXPos, YawTMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Real Yaw: Manual AA Jitter");
				break;
			case 9:
				g_Render->Textf(MainXPos, YawTMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Real Yaw: Sideways");
				break;
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////

			switch (MoveFakeYaw)
			{
			case 0:
				g_Render->Textf(MainXPos, YawFMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Fake Yaw: Off");
				break;
			case 1:
				g_Render->Textf(MainXPos, YawFMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Fake Yaw: Sideways Jitter");
				break;
			case 2:
				g_Render->Textf(MainXPos, YawFMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Fake Yaw: Slow Spin");
				break;
			case 3:
				g_Render->Textf(MainXPos, YawFMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Fake Yaw: Fast Spin");
				break;
			case 4:
				g_Render->Textf(MainXPos, YawFMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Fake Yaw: Backwards");
				break;
			case 5:
				g_Render->Textf(MainXPos, YawFMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Fake Yaw: Forward Jitter");
				break;
			case 6:
				g_Render->Textf(MainXPos, YawFMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Fake Yaw: Jitter AA");
				break;
			case 7:
				g_Render->Textf(MainXPos, YawFMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Fake Yaw: Random Fake");
				break;
			case 8:
				g_Render->Textf(MainXPos, YawFMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Fake Yaw: Inversed AA Jitter");
				break;
			case 9:
				g_Render->Textf(MainXPos, YawFMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Fake Yaw: Inversed AA");
				break;
			case 10:
				g_Render->Textf(MainXPos, YawFMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Fake Yaw: Sideways");
				break;
			case 11:
				g_Render->Textf(MainXPos, YawFMPosY, Color(255, 255, 255, 255), g_Render->font.Logo, "Move Fake Yaw: Forward");
				break;
			}

		}

	}

}
