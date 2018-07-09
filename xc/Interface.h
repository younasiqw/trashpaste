#pragma once
#include "Configuration.hpp"
#include "dropboxes.h"
#include "Variables.h"
#include "Tabs.h"
#include "Themes.h"

inline void RainbowMeme(int x, int y, int width, int height, float flSpeed)
{
	ImDrawList* window_draw_list = ImGui::GetWindowDrawList();
	static float flRainbow;

	Color colColor(0, 0, 0);

	flRainbow += flSpeed;

	if (flRainbow > 1.f) flRainbow = 0.f;

	for (int i = 0; i < width; i++)
	{
		float hue = (1.f / float(width)) * i;
		hue -= flRainbow;

		if (hue < 0.f) hue += 1.f;

		Color color = colColor.FromHSB(hue, 1.f, 1.f);

		window_draw_list->AddRectFilled(ImVec2(x + i, y), ImVec2(width, height), /* pCode */ ImColor(color.r(), color.g(), color.b(), color.a()));
	}
}

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
void RenderInterface() {


	static int page = 0;

	switch (g_Options.Menu.Theme)
	{
	case 0:
		RenderThemes();
		break;
	}

	//ImGui::PushFont(fTabs);
	ImGui::Begin("www.insertcheatname.com | build v13.37", &g_Options.Menu.Opened, ImVec2(803, 510), 1.0f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders);
	{
		const char* tabs[] = {
			"RAGEBOT",
			"LEGITBOT",
			"VISUALS",
			"MISCELLANEOUS",
			"COLORS"
		};

		for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
		{
			if (ImGui::Button(tabs[i], ImVec2(151, 36)))
				page = i;
			

			if (i < IM_ARRAYSIZE(tabs) - 1)
				ImGui::SameLine();
		}

		switch (page)
		{
		case 0:
			Tabs::RageTab();
			break;
		case 1:
			Tabs::LegitTab();
			break;
		case 2:
			Tabs::VisualsTab();
			break;
		case 3:
			Tabs::MiscTab();
			break;
		case 4:
			Tabs::ColorsTab();
			break;
		}

	}ImGui::End();

	if (g_Options.Misc.SkinChangerToggle)
	{ 
		ImGui::Begin("insertcheatname | skinchanger", &g_Options.Menu.Opened, ImVec2(290, 600), 0.95f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders);
		{
			Tabs::SkinsTab();
		}ImGui::End();
	}

	/*if (g_Options.Ragebot.YawTrue == 23)
	{
		ImGui::Begin("Custom LBY AA", &g_Options.Menu.Opened, ImVec2(290, 300), 0.95f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders);
		{
			Tabs::CustomAA();
		}ImGui::End();
	}*/

}
