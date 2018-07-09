#include "HookIncludes.h"
#include "HooksList.h"
#include "Listener.h"



namespace hooks
{
	vfunc_hook panel;
	vfunc_hook client;
	vfunc_hook clientmode;
	vfunc_hook modelrender;
	vfunc_hook prediction;
	vfunc_hook surface;
	vfunc_hook eventmanager;
	vfunc_hook d3d;
	vfunc_hook viewrender;
	vfunc_hook engine;
	vfunc_hook sv_cheats;

	void SetupColors()
	{
		G::ColorsForPicker.push_back(ColorP("Terrorist - Box Visible", g_Options.Colors.espVisT));
		G::ColorsForPicker.push_back(ColorP("Terrorist - Box Invisible", g_Options.Colors.espInvisT));
		G::ColorsForPicker.push_back(ColorP("Counter-Terrorist - Box Visible", g_Options.Colors.espVisCT));
		G::ColorsForPicker.push_back(ColorP("Counter-Terrorist - Box Invisible", g_Options.Colors.espInvisCT));

		G::ColorsForPicker.push_back(ColorP("Teammates - Glow", g_Options.Colors.espDrawGlowTeammates));
		G::ColorsForPicker.push_back(ColorP("Enemies - Glow", g_Options.Colors.espDrawGlowEnemies));
		G::ColorsForPicker.push_back(ColorP("Visuals - Weapon Glow", g_Options.Colors.espDrawGlowWeapons));

		G::ColorsForPicker.push_back(ColorP("Teammates - Draw Chams Invisible", g_Options.Colors.DrawChamsTeam));
		G::ColorsForPicker.push_back(ColorP("Enemies - Draw Chams Invisble", g_Options.Colors.DrawChamsNigger));
		G::ColorsForPicker.push_back(ColorP("Teammates - Draw Chams Visible", g_Options.Colors.DrawChamsTeamVisible));
		G::ColorsForPicker.push_back(ColorP("Enemies - Draw Chams Visible", g_Options.Colors.DrawChamsEnemyVisible));
		G::ColorsForPicker.push_back(ColorP("Visuals - Draw Hands", g_Options.Colors.DrawHands));
		G::ColorsForPicker.push_back(ColorP("Visuals - Draw Armor", g_Options.Colors.espDrawArmor));
		G::ColorsForPicker.push_back(ColorP("Visuals - Draw Health", g_Options.Colors.espDrawHealth));
		G::ColorsForPicker.push_back(ColorP("Visuals - Draw Bomb", g_Options.Colors.espDrawBomb));
		G::ColorsForPicker.push_back(ColorP("Visuals - Draw Drop", g_Options.Colors.espDrawDrop));
		G::ColorsForPicker.push_back(ColorP("Visuals - Draw Skeleton", g_Options.Colors.espDrawSkeleton));
		G::ColorsForPicker.push_back(ColorP("Visuals - Draw Backtrack", g_Options.Colors.espDrawBacktrack));
		G::ColorsForPicker.push_back(ColorP("Visuals - Draw aWall Indicator", g_Options.Colors.espDrawAwall));
		G::ColorsForPicker.push_back(ColorP("Visuals - Draw LBY Angle", g_Options.Colors.espDrawLBYAngle));
		G::ColorsForPicker.push_back(ColorP("Visuals - Draw Real Angle", g_Options.Colors.espDrawRealAngle));
		G::ColorsForPicker.push_back(ColorP("Visuals - Draw Fake Angle", g_Options.Colors.espDrawFakeAngle));

		G::ColorsForPicker.push_back(ColorP("GUI - Text", g_Options.Colors.GUIText));
		G::ColorsForPicker.push_back(ColorP("GUI - Button", g_Options.Colors.GUIButton));
		G::ColorsForPicker.push_back(ColorP("GUI - Hovered Button", g_Options.Colors.GUIButtonH));
		G::ColorsForPicker.push_back(ColorP("GUI - Active Button", g_Options.Colors.GUIButtonA));
		G::ColorsForPicker.push_back(ColorP("GUI - Window", g_Options.Colors.GUIWindow));
		G::ColorsForPicker.push_back(ColorP("GUI - Frame", g_Options.Colors.GUIFrame));
		G::ColorsForPicker.push_back(ColorP("GUI - Selected Text", g_Options.Colors.GUISelectedT));
		G::ColorsForPicker.push_back(ColorP("GUI - Header", g_Options.Colors.GUIHeader));
		G::ColorsForPicker.push_back(ColorP("GUI - Hovered Header", g_Options.Colors.GUIHeaderH));
		G::ColorsForPicker.push_back(ColorP("GUI - Active Header", g_Options.Colors.GUIHeaderA));
		G::ColorsForPicker.push_back(ColorP("GUI - Slider", g_Options.Colors.GUISlider));
		G::ColorsForPicker.push_back(ColorP("GUI - Combo Backround", g_Options.Colors.GUICombobg));
		G::ColorsForPicker.push_back(ColorP("GUI - Scrollbar", g_Options.Colors.GUIScrollbar));
		G::ColorsForPicker.push_back(ColorP("GUI - Scrollbar Backround", g_Options.Colors.GUIScrollbarbg));
		G::ColorsForPicker.push_back(ColorP("GUI - Checkmark", g_Options.Colors.GUICheckmark));
		
	}

	void initialize()
	{
		client.setup(g_CHLClient);
		client.hook_index(37, hkFrameStageNotify);
		client.hook_index(22, hkCreateMove);

		clientmode.setup(g_ClientMode);
		clientmode.hook_index(18, hkOverrideView);
		clientmode.hook_index(35, hkGetViewModelFOV);
		clientmode.hook_index(44, hkDoPostScreenSpaceEffects);

		panel.setup(g_Panel);
		panel.hook_index(41, hkPaintTraverse);

		modelrender.setup(g_ModelRender);
		modelrender.hook_index(21, hkDrawModelExecute);

		surface.setup(g_Surface);
		surface.hook_index(82, hkPlaySound);


		ConVar* sv_cheats_con = g_CVar->FindVar("sv_cheats");
		sv_cheats.setup(sv_cheats_con);
		sv_cheats.hook_index(13, hkSvCheatsGetBool);

		g_Engine->ClientCmd_Unrestricted("con_filter_enable 1;con_filter_text_out failed;"); // console filter for all dem skins errors

		m_present = U::pattern_scan(GetModuleHandleW(L"gameoverlayrenderer.dll"), "FF 15 ? ? ? ? 8B F8 85 DB") + 0x2;//big ( large ) obs bypass
		m_reset = U::pattern_scan(GetModuleHandleW(L"gameoverlayrenderer.dll"), "FF 15 ? ? ? ? 8B F8 85 FF 78 18") + 0x2;  //big ( large ) obs bypass



		oPresent = **reinterpret_cast<Present_T**>(m_present);
		oReset = **reinterpret_cast<Reset_t**>(m_reset);

		**reinterpret_cast<void***>(m_present) = reinterpret_cast<void*>(&hkPresent);
		**reinterpret_cast<void***>(m_reset) = reinterpret_cast<void*>(&hkReset);


		item_purchase::singleton()->initialize();


	}



	void cleanup()
	{
		item_purchase::singleton()->remove();
		client.unhook_all();
		prediction.unhook_all();
		clientmode.unhook_all();
		panel.unhook_all();
		modelrender.unhook_all();
		surface.unhook_all();
		viewrender.unhook_all();
		sv_cheats.unhook_all();
		engine.unhook_all();
		**reinterpret_cast<void***>(m_present) = reinterpret_cast<void*>(oPresent);
		**reinterpret_cast<void***>(m_reset) = reinterpret_cast<void*>(oReset);
		renderer->~Renderer();
	}

}