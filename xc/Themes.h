#pragma once
#include "Interface.h"
#include <d3d9.h>
#include "Global.h"

ImFont* fkek;
ImFont* fDefault;

void RenderDefault(IDirect3DDevice9* pDevice)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = 1.f / 60.f;
	D3DDEVICE_CREATION_PARAMETERS d3dcp{ 0 };
	pDevice->GetCreationParameters(&d3dcp);



	auto& style = ImGui::GetStyle();

	ImFont* fDefault = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13.0f);
	fkek = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13.0f);

}

void RenderThemes()
{

	ImGuiStyle& style = ImGui::GetStyle();
	G::extra_flags = 0;
	style.Alpha = 1.0f;             // Global alpha applies to everything in ImGui
	style.WindowPadding = ImVec2(8, 8);      // Padding within a window
	style.WindowMinSize = ImVec2(32, 32);    // Minimum window size
	style.WindowRounding = 0.0f;    // 9.0         // Radius of window corners rounding. Set to 0.0f to have rectangular windows
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);// Alignment for title bar text
	style.ChildWindowRounding = 0.0f;             // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows
	style.FramePadding = ImVec2(4, 3);      // Padding within a framed rectangle (used by most widgets)
	style.FrameRounding = 0.0f;             // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
	style.ItemSpacing = ImVec2(8, 4);      // Horizontal and vertical spacing between widgets/lines
	style.ItemInnerSpacing = ImVec2(4, 4);      // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
	style.TouchExtraPadding = ImVec2(0, 0);      // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't 
	style.IndentSpacing = 21.0f;            // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
	style.ColumnsMinSpacing = 6.0f;             // Minimum horizontal spacing between two columns
	style.ScrollbarSize = 16.0f;            // Width of the vertical scrollbar, Height of the horizontal scrollbar
	style.ScrollbarRounding = 0.0f;   //9.0          // Radius of grab corners rounding for scrollbar
	style.GrabMinSize = 10.0f;            // Minimum width/height of a grab box for slider/scrollbar
	style.GrabRounding = 0.0f;             // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);// Alignment of button text when button is larger than text.
	style.DisplayWindowPadding = ImVec2(22, 22);    // Window positions are clamped to be visible within the display area by at least this amount. Only covers regular 
	style.DisplaySafeAreaPadding = ImVec2(4, 4);      // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as 
	style.AntiAliasedLines = true;             // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
	style.AntiAliasedShapes = true;             // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
	style.CurveTessellationTol = 1.25f;            // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce 

												   // Texts
	float textr;
	float textg;
	float textb;

	textr = g_Options.Colors.GUIText[0];
	textg = g_Options.Colors.GUIText[1];
	textb = g_Options.Colors.GUIText[2];

	// Buttons
	float buttonr;
	float buttong;
	float buttonb;

	buttonr = g_Options.Colors.GUIButton[0];
	buttong = g_Options.Colors.GUIButton[1];
	buttonb = g_Options.Colors.GUIButton[2];

	// Hovered Buttons
	float buttonhr;
	float buttonhg;
	float buttonhb;

	buttonhr = g_Options.Colors.GUIButtonH[0];
	buttonhg = g_Options.Colors.GUIButtonH[1];
	buttonhb = g_Options.Colors.GUIButtonH[2];

	// Active Buttons
	float buttonar;
	float buttonag;
	float buttonab;

	buttonar = g_Options.Colors.GUIButtonA[0];
	buttonag = g_Options.Colors.GUIButtonA[1];
	buttonab = g_Options.Colors.GUIButtonA[2];

	// Headers
	float headerr;
	float headerg;
	float headerb;

	headerr = g_Options.Colors.GUIHeader[0];
	headerg = g_Options.Colors.GUIHeader[1];
	headerb = g_Options.Colors.GUIHeader[2];

	// Hovered Headers
	float headerhr;
	float headerhg;
	float headerhb;

	headerhr = g_Options.Colors.GUIHeaderH[0];
	headerhg = g_Options.Colors.GUIHeaderH[1];
	headerhb = g_Options.Colors.GUIHeaderH[2];

	// Active Headers
	float headerar;
	float headerag;
	float headerab;

	headerar = g_Options.Colors.GUIHeaderA[0];
	headerag = g_Options.Colors.GUIHeaderA[1];
	headerab = g_Options.Colors.GUIHeaderA[2];

	// Selected Text
	float selectedtextr;
	float selectedtextg;
	float selectedtextb;

	selectedtextr = g_Options.Colors.GUISelectedT[0];
	selectedtextg = g_Options.Colors.GUISelectedT[1];
	selectedtextb = g_Options.Colors.GUISelectedT[2];

	// Window
	float windowr;
	float windowg;
	float windowb;

	windowr = g_Options.Colors.GUIWindow[0];
	windowg = g_Options.Colors.GUIWindow[1];
	windowb = g_Options.Colors.GUIWindow[2];

	// Frame
	float framer;
	float frameg;
	float frameb;

	framer = g_Options.Colors.GUIFrame[0];
	frameg = g_Options.Colors.GUIFrame[1];
	frameb = g_Options.Colors.GUIFrame[2];

	// Slider
	float sliderr;
	float sliderg;
	float sliderb;

	sliderr = g_Options.Colors.GUISlider[0];
	sliderg = g_Options.Colors.GUISlider[1];
	sliderb = g_Options.Colors.GUISlider[2];

	// Slider Active
	/*float slideractiver;
	float slideractiveg;
	float slideractiveb;

	slideractiver = g_Options.Colors.GUISliderActive[0];
	slideractiveg = g_Options.Colors.GUISliderActive[1];
	slideractiveb = g_Options.Colors.GUISliderActive[2];*/

	// Checkmark
	float checkmarkr;
	float checkmarkg;
	float checkmarkb;

	checkmarkr = g_Options.Colors.GUICheckmark[0];
	checkmarkg = g_Options.Colors.GUICheckmark[1];
	checkmarkb = g_Options.Colors.GUICheckmark[2];

	// Combo BG
	float combobgr;
	float combobgg;
	float combobgb;

	combobgr = g_Options.Colors.GUICombobg[0];
	combobgg = g_Options.Colors.GUICombobg[1];
	combobgb = g_Options.Colors.GUICombobg[2];

	// Scrollbar
	float scrollbarr;
	float scrollbarg;
	float scrollbarb;

	scrollbarr = g_Options.Colors.GUIScrollbar[0];
	scrollbarg = g_Options.Colors.GUIScrollbar[1];
	scrollbarb = g_Options.Colors.GUIScrollbar[2];

	// Scrollbar Backround
	float scrollbarbgr;
	float scrollbarbgg;
	float scrollbarbgb;

	scrollbarbgr = g_Options.Colors.GUIScrollbarbg[0];
	scrollbarbgg = g_Options.Colors.GUIScrollbarbg[1];
	scrollbarbgb = g_Options.Colors.GUIScrollbarbg[2];


	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(textr, textg, textb, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(textr, textg, textb, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(windowr, windowb, windowg, 1.00f);
	colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.40f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(framer, frameg, frameb, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.54f, 0.54f, 0.54f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.54f, 0.54f, 0.54f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(windowr, windowb, windowg, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(windowr, windowb, windowg, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(windowr, windowb, windowg, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(scrollbarbgr, scrollbarbgg, scrollbarbgb, 1.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(scrollbarr, scrollbarg, scrollbarb, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(scrollbarr, scrollbarg, scrollbarb, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(scrollbarr, scrollbarg, scrollbarb, 1.00f);
	colors[ImGuiCol_ComboBg] = ImVec4(combobgr, combobgg, combobgb, 0.99f);
	colors[ImGuiCol_CheckMark] = ImVec4(checkmarkr, checkmarkg, checkmarkb, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(sliderr, sliderg, sliderb, 0.30f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(sliderr, sliderg, sliderb, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(buttonr, buttong, buttonb, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(buttonhr, buttonhg, buttonhb, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(buttonar, buttonag, buttonab, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(headerr, headerg, headerb, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(headerhr, headerhg, headerhb, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(headerar, headerag, headerab, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	colors[ImGuiCol_CloseButton] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
	colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
	colors[ImGuiCol_CloseButtonActive] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(selectedtextr, selectedtextg, selectedtextb, 1.00f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}