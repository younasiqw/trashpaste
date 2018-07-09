#pragma once
#include "IDirect3DDevice9.h"
#include "Themes.h"
#include "Global.h"
typedef void(*CL_FullUpdate_t) (void);
CL_FullUpdate_t CL_FullUpdate = nullptr;

void KnifeApplyCallbk()
{
	static auto CL_FullUpdate = reinterpret_cast<CL_FullUpdate_t>(U::FindPattern("engine.dll", reinterpret_cast<PBYTE>("\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x56\xFF\x50\x14\x8B\x34\x85"), "x????x????xxxxxxx"));
	CL_FullUpdate();
}

namespace Tabs
{

	/*
	_____            _____ ______
	|  __ \     /\   / ____|  ____|
	| |__) |   /  \ | |  __| |__
	|  _  /   / /\ \| | |_ |  __|
	| | \ \  / ____ \ |__| | |____
	|_|  \_\/_/    \_\_____|______|

	*/

	void RageTab()
	{
		//ImGui::PushFont(fkek);
		ImGui::BeginChild("Left Side", ImVec2(191, 435), true);
		{
			ImGui::PushFont(fkek);
			ImGui::Checkbox(XorStr("Enable Ragebot"), &g_Options.Ragebot.MainSwitch);
			{
				ImGui::Separator();


				ImGui::Checkbox(XorStr("Enable Aimbot"), &g_Options.Ragebot.Enabled);
				ImGui::Checkbox(XorStr("Auto Fire"), &g_Options.Ragebot.AutoFire);
				ImGui::SliderFloat(("Aimbot FOV"), &g_Options.Ragebot.FOV, 0.f, 180.f, "%.0f");
				ImGui::Checkbox(XorStr("Silent Aim"), &g_Options.Ragebot.Silent);
				ImGui::Separator();
				ImGui::Checkbox(XorStr("Resolver"), &g_Options.Ragebot.Resolver);
				if (g_Options.Ragebot.Resolver)
				{
					ImGui::Combo(XorStr(""), &g_Options.Ragebot.iResolver, Resolver, ARRAYSIZE(Resolver));
				}
				ImGui::Checkbox(XorStr("Override"), &g_Options.Ragebot.ResolverOverride);
				ImGui::SliderFloat(XorStr("Degree"), &g_Options.Ragebot.ResolverOverrideSlider, -180, 180, "%1.f");
				ImGui::Hotkey(XorStr("Key"), &g_Options.Ragebot.ResolverOverrideKey);
				ImGui::Separator();
				ImGui::Checkbox(XorStr("Friendly Fire"), &g_Options.Ragebot.FriendlyFire);
				ImGui::Separator();
				ImGui::Checkbox(XorStr("Auto Revolver"), &g_Options.Ragebot.AutoRevolver);
				ImGui::Checkbox(XorStr("Auto Stop"), &g_Options.Ragebot.AutoStop);
				ImGui::Checkbox(XorStr("Auto Crouch"), &g_Options.Ragebot.AutoCrouch);
				ImGui::Checkbox(XorStr("Auto Scope"), &g_Options.Ragebot.AutoScope);
				ImGui::Checkbox(XorStr("Jump Scout"), &g_Options.Ragebot.JumpScout);
				ImGui::Checkbox(XorStr("No Recoil"), &g_Options.Ragebot.AntiRecoil);

				ImGui::Separator();

				ImGui::Checkbox(XorStr("Lag Compensation"), &g_Options.Ragebot.FakeLagFix);
				ImGui::Checkbox(XorStr("Backtrack"), &g_Options.Ragebot.rageBacktrack);
				ImGui::SliderInt(("Backtrack"), &g_Options.Ragebot.rageBacktrackSlider, 0.f, 200.f, "%.1f ms");
				ImGui::Separator();
				ImGui::Checkbox(XorStr("Multipoint"), &g_Options.Ragebot.Multipoint);
				ImGui::Combo(XorStr("Hitbox"), &g_Options.Ragebot.Hitbox, aimBones, ARRAYSIZE(aimBones));
				ImGui::Combo(XorStr("Hitscan"), &g_Options.Ragebot.Hitscan, hitscan, ARRAYSIZE(hitscan));
				ImGui::Separator();
				ImGui::Checkbox(XorStr("Baim If HP lower"), &g_Options.Ragebot.bBaimIfHP);
				ImGui::SliderFloat(XorStr("than"), &g_Options.Ragebot.fBaimIfHP, 0, 100, "%1.f");
			}ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("Hitchance Side", ImVec2(191, 435), true);
			{
				ImGui::Checkbox(XorStr("Enable Hitchance"), &g_Options.Ragebot.Hitchance);
				ImGui::Separator();

				ImGui::Text("Hitchance");
				ImGui::Separator();
				ImGui::SliderFloat(XorStr("Pistols"), &g_Options.Ragebot.HitchancePistol, 0.f, 100.f, "%.1f");
				ImGui::SliderFloat(XorStr("Revolver & Deagle"), &g_Options.Ragebot.HitchanceRevolver, 0.f, 100.f, "%.1f");
				ImGui::SliderFloat(XorStr("Sub-Machine guns"), &g_Options.Ragebot.HitchanceSmgs, 0.f, 100.f, "%.1f");
				ImGui::SliderFloat(XorStr("Assault Rifles"), &g_Options.Ragebot.HitchanceRifle, 0.f, 100.f, "%.1f");
				ImGui::SliderFloat(XorStr("Machine guns"), &g_Options.Ragebot.HitchanceHeavy, 0.f, 100.f, "%.1f");
				ImGui::SliderFloat(XorStr("Scout"), &g_Options.Ragebot.HitchanceScout, 0.f, 100.f, "%.1f");
				ImGui::SliderFloat(XorStr("AWP"), &g_Options.Ragebot.HitchanceAWP, 0.f, 100.f, "%.1f");
				ImGui::SliderFloat(XorStr("Auto Sniper"), &g_Options.Ragebot.HitchanceSniper, 0.f, 100.f, "%.1f");
				ImGui::SliderFloat(XorStr("Shotgun"), &g_Options.Ragebot.HitchanceShotgun, 0.f, 100.f, "%.1f");


				ImGui::Separator();
				ImGui::SameLine();
				//ImGui::Text("");
				ImGui::Text("Autowall Min. Damage");
				ImGui::Separator();

				ImGui::SliderFloat(("Pistols "), &g_Options.Ragebot.MinimumDamagePistol, 1.f, 100.f, "%.2f");
				ImGui::SliderFloat(("Revolver & Deagle "), &g_Options.Ragebot.MinimumDamageRevolver, 1.f, 100.f, "%.2f");
				ImGui::SliderFloat(("Sub-Machine guns "), &g_Options.Ragebot.MinimumDamageSmg, 1.f, 100.f, "%.2f");
				ImGui::SliderFloat(("Assault Rifles "), &g_Options.Ragebot.MinimumDamageRifle, 1.f, 100.f, "%.2f");
				ImGui::SliderFloat(("Machine guns "), &g_Options.Ragebot.MinimumDamageHeavy, 1.f, 100.f, "%.2f");
				ImGui::SliderFloat(("Scout "), &g_Options.Ragebot.MinimumDamageScout, 1.f, 100.f, "%.2f");
				ImGui::SliderFloat(("AWP "), &g_Options.Ragebot.MinimumDamageAWP, 1.f, 100.f, "%.2f");
				ImGui::SliderFloat(("Auto Sniper "), &g_Options.Ragebot.MinimumDamageSniper, 1.f, 100.f, "%.2f");
				ImGui::SliderFloat(("Shotgun "), &g_Options.Ragebot.MinimumDamageShotgun, 1.f, 100.f, "%.2f");
			}ImGui::EndChild();


			ImGui::SameLine();

			ImGui::BeginChild("Pre-Set AA's", ImVec2(191, 435), true);
			{
				ImGui::Checkbox(XorStr("Enable Anti-Aim"), &g_Options.Ragebot.EnabledAntiAim);
				ImGui::Separator();
				ImGui::Checkbox(XorStr("Enable Preset"), &g_Options.Ragebot.PreAAs);
				ImGui::Combo(XorStr("Pitch"), &g_Options.Ragebot.Pitch, antiaimpitch, ARRAYSIZE(antiaimpitch));
				ImGui::SliderFloat(XorStr("Pitch Angles"), &g_Options.Ragebot.PitchAdder, -180, 180, "%1.f");
				ImGui::Combo(XorStr("Yaw"), &g_Options.Ragebot.YawTrue, antiaimyawtrue, ARRAYSIZE(antiaimyawtrue));
				ImGui::SliderFloat(XorStr("Real Angles"), &g_Options.Ragebot.YawTrueAdder, -180, 180, "%1.f");
				ImGui::Combo(XorStr("Fake-Yaw"), &g_Options.Ragebot.YawFake, antiaimyawfake, ARRAYSIZE(antiaimyawfake));
				ImGui::SliderFloat(XorStr("Fake Angles"), &g_Options.Ragebot.YawFakeAdder, -180, 180, "%1.f");
				ImGui::Separator();
				ImGui::Checkbox(XorStr("Move AA"), &g_Options.Ragebot.YawFakeMoveEnabled);
				ImGui::Combo(XorStr("Real Move"), &g_Options.Ragebot.YawTrueMove, antiaimyawtruemove, ARRAYSIZE(antiaimyawtruemove));
				ImGui::SliderFloat(XorStr("Real Move Angles"), &g_Options.Ragebot.YawTrueMoveAdder, -180, 180, "%1.f");
				ImGui::Combo(XorStr("Fake Move"), &g_Options.Ragebot.YawFakeMove, antiaimyawfakemove, ARRAYSIZE(antiaimyawfakemove));
				ImGui::SliderFloat(XorStr("Fake Move Angles"), &g_Options.Ragebot.YawFakeMoveAdder, -180, 180, "%1.f");
				ImGui::Separator();
				ImGui::Text("Anti-Aim Binds");
				ImGui::Hotkey(XorStr("Real Left"), &g_Options.AntiAim.SwitchFakeLeft);
				ImGui::Hotkey(XorStr("Real Right"), &g_Options.AntiAim.SwitchFakeRight);
				ImGui::Separator();
				ImGui::Checkbox(XorStr("Fakewalk"), &g_Options.Ragebot.BoolFakewalk);
				ImGui::Hotkey(XorStr("Key"), &g_Options.Ragebot.IntFakewalk);
				ImGui::Separator();
				ImGui::Text("Fakelag");
				ImGui::Checkbox(XorStr("Enable"), &g_Options.Ragebot.FakeLag);
				ImGui::Selectable(XorStr("while moving only"), &g_Options.Ragebot.FakeLagMoveOnly);
				ImGui::SliderFloat(XorStr("Fakelag Amount"), &g_Options.Ragebot.FakeLagAmt, 0, 14, "%1.f");

			}ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("Builder AA's", ImVec2(191, 435), true);
			{
				ImGui::Separator();
				ImGui::Text("Select 'Custom LBY' as Yaw");
				ImGui::Separator();
					ImGui::Checkbox("LBY Breaker", &g_Options.Ragebot.bLbyBreaker);
					ImGui::Separator();
					ImGui::Text("Static");
					ImGui::Separator();
					ImGui::Checkbox(("Static Left"), &g_Options.Ragebot.RealCustomStaticLinks);
					if (g_Options.Ragebot.RealCustomStaticLinks)
					{
						ImGui::SliderFloat(XorStr("Left"), &g_Options.Ragebot.RealCustomStaticLinksAngle, -180, 180, "%1.f");
					}

					ImGui::Checkbox(("Static Right"), &g_Options.Ragebot.RealCustomStaticRechts);
					if (g_Options.Ragebot.RealCustomStaticRechts)
					{
						ImGui::SliderFloat(XorStr("Right"), &g_Options.Ragebot.RealCustomStaticRechtsAngle, -180, 180, "%1.f");
					}
					ImGui::Separator();

					ImGui::Text("");
					ImGui::Separator();
					ImGui::Text("Jitter");
					ImGui::Separator();

					ImGui::Checkbox(("Jitter Left"), &g_Options.Ragebot.RealCustomJitterLinks);
					if (g_Options.Ragebot.RealCustomJitterLinks)
					{
						ImGui::SliderFloat(XorStr("Jitter Left Start"), &g_Options.Ragebot.RealCustomLinksVonAngle, -180, 180, "%1.f");
						ImGui::SliderFloat(XorStr("Jitter Left End"), &g_Options.Ragebot.RealCustomLinksBisAngle, -180, 180, "%1.f");
					}

					ImGui::Checkbox(("Jitter Right"), &g_Options.Ragebot.RealCustomJitterRechts);
					if (g_Options.Ragebot.RealCustomJitterRechts)
					{
						ImGui::SliderFloat(XorStr("Jitter Right Start"), &g_Options.Ragebot.RealCustomRechtsVonAngle, -180, 180, "%1.f");
						ImGui::SliderFloat(XorStr("Jitter Right End"), &g_Options.Ragebot.RealCustomRechtsBisAngle, -180, 180, "%1.f");
					}

					if (g_Options.Ragebot.bLbyBreaker)
					{
						ImGui::Separator();
						ImGui::Text("");
						ImGui::Separator();
						ImGui::Text("LBY");
						ImGui::Separator();
						ImGui::SliderFloat(XorStr("LBY Left"), &g_Options.Ragebot.LbyCustomLinks, -180, 180, "%1.f");
						ImGui::SliderFloat(XorStr("LBY Right"), &g_Options.Ragebot.LbyCustomRechts, -180, 180, "%1.f");
					}

				ImGui::Separator();
				ImGui::Text("");
				ImGui::Separator();
				ImGui::Text(XorStr("Miscellaneous"));
				ImGui::Separator();
				ImGui::Checkbox(XorStr("At Players"), &g_Options.AntiAim.AtTarget);
				ImGui::Checkbox(XorStr("Edge"), &g_Options.AntiAim.Edge);
				ImGui::Separator();
				ImGui::Checkbox(XorStr("Legit AA"), &g_Options.Ragebot.LegitAA);
				ImGui::Combo(XorStr("Type"), &g_Options.Ragebot.LegitAAReal, LegitAACombo, ARRAYSIZE(LegitAACombo));




			}ImGui::EndChild();
		}
	}

	/*
	_      ______ _____ _____ _______
	| |    |  ____/ ____|_   _|__   __|
	| |    | |__ | |  __  | |    | |
	| |    |  __|| | |_ | | |    | |
	| |____| |___| |__| |_| |_   | |
	|______|______\_____|_____|  |_|

	*/
	void LegitTab()
	{
		ImGui::PushFont(fkek);
		ImGui::BeginChild("General", ImVec2(191, 435), true);
		ImGui::Checkbox(XorStr("Active"), &g_Options.Legitbot.MainSwitch);
		{
			ImGui::Text(XorStr(""));
			ImGui::Text("General", ImVec2(172, 25));
			ImGui::Checkbox(XorStr("Enable Aimbot"), &g_Options.Legitbot.Aimbot.Enabled);

			ImGui::Checkbox(XorStr("Backtrack"), &g_Options.Legitbot.backtrack);

			ImGui::Text(""); // SPACE
			ImGui::Text(""); // SPACE

							 // TRIGGERBOT
			ImGui::Text("Triggerbot");
			ImGui::Checkbox(XorStr("Enable Triggerbot"), &g_Options.Legitbot.Triggerbot.Enabled);
			ImGui::SliderFloat(XorStr("Delay"), &g_Options.Legitbot.Triggerbot.Delay, 1.f, 150.f, "%.0f"); // DELAY 
			ImGui::SliderFloat(XorStr("Hitchance"), &g_Options.Legitbot.Triggerbot.hitchance, 0.f, 100.f, "%.0f"); // HITCHANCE
			ImGui::Hotkey(XorStr("Key##3"), &g_Options.Legitbot.Triggerbot.Key);

			ImGui::Text(XorStr("Filter"));
			ImGui::Selectable(XorStr(" Head"), &g_Options.Legitbot.Triggerbot.Filter.Head);
			ImGui::Selectable(XorStr(" Arms"), &g_Options.Legitbot.Triggerbot.Filter.Arms);
			ImGui::Selectable(XorStr(" Chest"), &g_Options.Legitbot.Triggerbot.Filter.Chest);
			ImGui::Selectable(XorStr(" Stomach"), &g_Options.Legitbot.Triggerbot.Filter.Stomach);
			ImGui::Selectable(XorStr(" Legs"), &g_Options.Legitbot.Triggerbot.Filter.Legs);

		}ImGui::EndChild();

		ImGui::SameLine();
		// PISTOLS
		ImGui::BeginChild("Pistols", ImVec2(191, 435), true);
		{
			ImGui::Text("Pistols", ImVec2(172, 25));
			ImGui::Text(""); // SPACE
			ImGui::SliderFloat(("Smooth"), &g_Options.Legitbot.PistolSmooth, 1.00f, 100.00f, "%.2f");
			ImGui::SliderFloat(("FOV"), &g_Options.Legitbot.Pistolfov, 0.00f, 30.00f, "%.2f"); // FOV
			ImGui::SliderFloat(("RCS"), &g_Options.Legitbot.pistol_recoil_max, 0.00f, 100.00f, "%.2f"); // RCS
																										

		}ImGui::EndChild();

		ImGui::SameLine();
		// RIFLES
		ImGui::BeginChild("Rifles", ImVec2(191, 435), true);
		{
			ImGui::Text("Rifles", ImVec2(172, 25));
			ImGui::Text(""); // SPACE
			ImGui::SliderFloat(("Smooth"), &g_Options.Legitbot.MainSmooth, 1.00f, 100.00f, "%.2f");
			ImGui::SliderFloat(("FOV"), &g_Options.Legitbot.Mainfov, 0.00f, 30.00f, "%.2f");
			ImGui::SliderFloat(("RCS"), &g_Options.Legitbot.main_recoil_max, 0.00f, 100.00f, "%.2f");

		}ImGui::EndChild();

		ImGui::SameLine();
		// SNIPERS
		ImGui::BeginChild("Snipers", ImVec2(191, 435), true);
		{
			ImGui::Text("Snipers", ImVec2(172, 25));
			ImGui::Text("");
			ImGui::SliderFloat(("Smooth"), &g_Options.Legitbot.SniperSmooth, 1.00f, 100.00f, "%.2f");
			ImGui::SliderFloat(("FOV"), &g_Options.Legitbot.Sniperfov, 0.00f, 30.00f, "%.2f");
			ImGui::SliderFloat(("RCS"), &g_Options.Legitbot.sniper_recoil_max, 0.00f, 100.00f, "%.2f");

		}ImGui::EndChild();


	}

	/*
	__      _______  _____ _    _         _       _____
	\ \    / /_   _|/ ____| |  | |  /\   | |     / ____|
	\ \  / /  | | | (___ | |  | | /  \  | |    | (___
	\ \/ /   | |  \___ \| |  | |/ /\ \ | |     \___ \
	\  /   _| |_ ____) | |__| / ____ \| |____ ____) |
	\/   |_____|_____/ \____/_/    \_\______|_____/

	*/

	void VisualsTab()
	{
		// VISUALS GENERAL
		ImGui::PushFont(fkek);
		ImGui::BeginChild("Main", ImVec2(265, 435), true);
		{
			ImGui::Columns(3, nullptr, false);
			ImGui::SetColumnOffset(1, 200);
			ImGui::Text("Visuals I", ImVec2(247, 25));
			ImGui::Checkbox(("Active"), &g_Options.Visuals.Enabled);
			ImGui::Separator();
			//ImGui::SameLine();
			{
				ImGui::Text(XorStr("General"));
				ImGui::Separator();//ImGui::SameLine();
				ImGui::Checkbox(XorStr("Local Player"), &g_Options.Visuals.Filter.LocalPlayer);
				ImGui::Checkbox(XorStr("Enemy Only"), &g_Options.Visuals.Filter.EnemyOnly);
				ImGui::Separator(); //ImGui::SameLine();
				ImGui::Text(XorStr("Helpful"));
				ImGui::Separator();//ImGui::SameLine();
				ImGui::Checkbox(XorStr("Engine Radar"), &g_Options.Visuals.RadarEngine);
				ImGui::Checkbox(XorStr("Spoof Radar"), &g_Options.Visuals.RadarSpoof);
				ImGui::Checkbox(XorStr("Grenade Prediction"), &g_Options.Visuals.GrenadePrediction);
				ImGui::Checkbox(XorStr("Sniper Crosshair"), &g_Options.Visuals.SniperCrosshair);
				ImGui::Checkbox(XorStr("Spread Crosshair"), &g_Options.Visuals.SpreadCrosshair);
				ImGui::Checkbox(XorStr("C4 Timer"), &g_Options.Visuals.C4Timer);
				ImGui::Checkbox(XorStr("Defuse Timer"), &g_Options.Visuals.DefuseTimer);
				ImGui::Checkbox(XorStr("Awall Indicator"), &g_Options.Visuals.DrawAwall);
				ImGui::Checkbox(XorStr("Recoil Tracking"), &g_Options.Visuals.RecoilESP);
				ImGui::Separator(); //ImGui::SameLine();
				ImGui::Text(XorStr("Anti-Aim"));
				ImGui::Separator();//ImGui::SameLine();
				ImGui::Checkbox(XorStr("Angle Lines"), &g_Options.Visuals.angleLines);
				ImGui::Checkbox(XorStr("Angle Text"), &g_Options.Visuals.AngleText);
				ImGui::Separator();//ImGui::SameLine();
				ImGui::Text(XorStr("Chams"));
				ImGui::Separator();//ImGui::SameLine();
				ImGui::Checkbox(XorStr("Chams"), &g_Options.Visuals.Chams);
				ImGui::Selectable(XorStr(" XQZ"), &g_Options.Visuals.ChamsMode.Filter.XQZ);
				ImGui::Separator(); //ImGui::SameLine();
				ImGui::Text(XorStr("Other"));
				ImGui::Separator();//ImGui::SameLine();
				ImGui::Checkbox(XorStr("Glow"), &g_Options.Visuals.Glow);
				ImGui::Checkbox(XorStr("Weapon Glow"), &g_Options.Visuals.WeaponGlow);
				ImGui::Checkbox(XorStr("Chrome Models"), &g_Options.Visuals.ChromeModels);
				ImGui::Checkbox(XorStr("Winter Mode"), &g_Options.Visuals.RemoveTextures);
				ImGui::Checkbox(XorStr("LSD Vision"), &g_Options.Visuals.LSDVision);
				ImGui::Checkbox(XorStr("Wireframe Smoke"), &g_Options.Visuals.WireframeSmoke);
				ImGui::Separator();//ImGui::SameLine();
				ImGui::Text(XorStr("Miscellaneous"));
				ImGui::Separator();//ImGui::SameLine();
				ImGui::Checkbox(XorStr("Watermark"), &g_Options.Visuals.Watermark);
				ImGui::Checkbox(XorStr("LBY Info"), &g_Options.Visuals.LBYInfo);
				ImGui::Checkbox(XorStr("Fancy Ass OSD"), &g_Options.Visuals.Warnings);
				ImGui::Separator();
				ImGui::Text(XorStr("Materials"));
				ImGui::Separator();
				ImGui::Combo("Arms", &g_Options.Visuals.Hands, materials, ARRAYSIZE(materials));
				ImGui::Combo("Weapon", &g_Options.Visuals.WeaponMaterial, materials, ARRAYSIZE(materials));

			}

		}ImGui::EndChild();

		ImGui::SameLine();
		//   VISUALS II
		ImGui::BeginChild("Second", ImVec2(265, 435), true);
		{
			ImGui::Text("Visuals II", ImVec2(247, 404), true);
			if (g_Options.Visuals.Filter.LocalPlayer)
			{
				ImGui::Separator();
				ImGui::Text("ESP on Local");
				ImGui::Separator();
				ImGui::Checkbox(XorStr("(Local) Box"), &g_Options.Visuals.BoxLocal);
				ImGui::Checkbox(XorStr("(Local) Skeleton"), &g_Options.Visuals.SkeletonLocal);
				ImGui::Checkbox(XorStr("(Local) Name"), &g_Options.Visuals.NameLocal);
				ImGui::Checkbox(XorStr("(Local) HP"), &g_Options.Visuals.HPNumberLocal);
				ImGui::Checkbox(XorStr("(Local) Healthbar"), &g_Options.Visuals.HPLocal);
				ImGui::Checkbox(XorStr("(Local) AP"), &g_Options.Visuals.APNumberLocal);
				ImGui::Checkbox(XorStr("(Local) Armorbar"), &g_Options.Visuals.APLocal);
				ImGui::Checkbox(XorStr("(Local) Scoped In"), &g_Options.Visuals.IsScopedLocal);
				ImGui::Checkbox(XorStr("(Local) Kit"), &g_Options.Visuals.HasDefuserLocal);
				ImGui::Checkbox(XorStr("(Local) Full Armor"), &g_Options.Visuals.HasHelmetLocal);
				ImGui::Checkbox(XorStr("(Local) Draw Backtrack"), &g_Options.Visuals.backtrackLocal);
				ImGui::Checkbox(XorStr("(Local) Weapon"), &g_Options.Visuals.WeaponLocal);
				ImGui::Checkbox(XorStr("(Local) Move Type"), &g_Options.Visuals.MoveTypeLocal);
				ImGui::Checkbox(XorStr("(Local) Money"), &g_Options.Visuals.MoneyLocal);
				ImGui::Separator();
				ImGui::Text("ESP on Entity");
				ImGui::Separator();
			}
			ImGui::Checkbox(XorStr("Box"), &g_Options.Visuals.Box);
			ImGui::Checkbox(XorStr("Skeleton"), &g_Options.Visuals.Skeleton);
			ImGui::Checkbox(XorStr("Name"), &g_Options.Visuals.Name);
			ImGui::Checkbox(XorStr("HP"), &g_Options.Visuals.HPNumber);
			ImGui::Checkbox(XorStr("Healthbar"), &g_Options.Visuals.HP);
			ImGui::Checkbox(XorStr("AP"), &g_Options.Visuals.APNumber);
			ImGui::Checkbox(XorStr("Armorbar"), &g_Options.Visuals.AP);
			ImGui::Checkbox(XorStr("Scoped In"), &g_Options.Visuals.IsScoped);
			ImGui::Checkbox(XorStr("Kit"), &g_Options.Visuals.HasDefuser);
			ImGui::Checkbox(XorStr("Full Armor"), &g_Options.Visuals.HasHelmet);
			ImGui::Checkbox(XorStr("Draw Backtrack"), &g_Options.Visuals.backtrack);
			ImGui::Checkbox(XorStr("Weapon"), &g_Options.Visuals.Weapon);
			//ImGui::Checkbox(XorStr("Ammo"), &g_Options.Visuals.AmmoInClip);
			ImGui::Checkbox(XorStr("Move Type"), &g_Options.Visuals.MoveType);
			ImGui::Checkbox(XorStr("Money"), &g_Options.Visuals.Money);
			ImGui::Checkbox(XorStr("C4 Carrier"), &g_Options.Visuals.C4);
			ImGui::Checkbox(XorStr("Planted C4"), &g_Options.Visuals.C4Planted);
			ImGui::Checkbox(XorStr("Grenade ESP"), &g_Options.Visuals.GrenadeESP);
			ImGui::Checkbox(XorStr("Resolver ESP"), &g_Options.Visuals.bResolverESP);


		}ImGui::EndChild();

		ImGui::SameLine();
		// VISUALS MISC
		ImGui::BeginChild("Third", ImVec2(242, 435), true);
		{
			ImGui::Text("Visuals III", ImVec2(224, 25));
			ImGui::Checkbox(XorStr("Ambient Color"), &g_Options.Visuals.AmbientColor);
			ImGui::SliderFloat(XorStr("Ambient Red"), &g_Options.Visuals.AmbientRed, 0.f, 10.f, "%.0f");
			ImGui::SliderFloat(XorStr("Ambient Green"), &g_Options.Visuals.AmbientGreen, 0.f, 10.f, "%.0f");
			ImGui::SliderFloat(XorStr("Ambient Blue"), &g_Options.Visuals.AmbientBlue, 0.f, 10.f, "%.0f");
			ImGui::Separator(); //ImGui::Text(""); 
			ImGui::Text("Visual Recoil");
			ImGui::SliderFloat(XorStr("View Punch"), &g_Options.Visuals.ViewPunch, 0.f, 0.055f, "%f");
			ImGui::SliderFloat(XorStr("Recoil Tracking"), &g_Options.Visuals.RecoilTracking, 0.f, 0.45f, "%f");
			ImGui::Separator(); //ImGui::Text(""); 
			ImGui::Text("FOV");
			ImGui::Checkbox(XorStr("Override Scope FOV"), &g_Options.Visuals.OverrideScopedFOV);
			ImGui::SliderFloat(XorStr("FOV Changer"), &g_Options.Visuals.FOVChanger, 0.f, 60.f, "%.0f");
			ImGui::SliderFloat(XorStr("Viewmodel FOV"), &g_Options.Visuals.viewmodelChanger, 0.f, 120.f, "%.0f");
			ImGui::Separator(); //ImGui::Text(""); 
			ImGui::Checkbox(XorStr("DLight"), &g_Options.Visuals.DLight);
			ImGui::SliderFloat(XorStr("DLight Radius"), &g_Options.Visuals.dLightRadius, 0.f, 500.f, "%.0f");
			ImGui::SliderFloat(XorStr("DLight R"), &g_Options.Visuals.dLightR, 0.f, 100.f, "%.0f");
			ImGui::SliderFloat(XorStr("DLight G"), &g_Options.Visuals.dLightG, 0.f, 100.f, "%.0f");
			ImGui::SliderFloat(XorStr("DLight B"), &g_Options.Visuals.dLightB, 0.f, 100.f, "%.0f");
			ImGui::Separator(); //ImGui::Text(""); 
			ImGui::Text(XorStr("Visuals Removal"));
			ImGui::Separator();
			ImGui::Checkbox(XorStr("Remove Flashes"), &g_Options.Visuals.NoFlash);
			ImGui::Checkbox(XorStr("Remove Smokes"), &g_Options.Visuals.NoSmoke);
			ImGui::Checkbox(XorStr("Remove Scope"), &g_Options.Visuals.noscopeborder);


		}ImGui::EndChild();

	}

	/*
	__  __ _____  _____  _____
	|  \/  |_   _|/ ____|/ ____|
	| \  / | | | | (___ | |
	| |\/| | | |  \___ \| |
	| |  | |_| |_ ____) | |____
	|_|  |_|_____|_____/ \_____|

	*/

	void MiscTab()
	{
		// FIRST COLUMN
		ImGui::PushFont(fkek);
		ImGui::BeginChild("Main", ImVec2(265, 435), true);
		{

			ImGui::Columns(3, nullptr, false);
			ImGui::SetColumnOffset(1, 200);
			ImGui::Checkbox("Name Stealer", &g_Options.Misc.silentstealer);
			ImGui::Checkbox("No Name", &g_Options.Misc.NoName);
			ImGui::Checkbox(XorStr("Night Mode"), &g_Options.Misc.nightMode);
			ImGui::Checkbox(XorStr("Spectator List"), &g_Options.Misc.SpecList);
			ImGui::Checkbox(XorStr("Auto Pistol"), &g_Options.Misc.AutoPistol);
			ImGui::Checkbox(XorStr("Buy Log"), &g_Options.Misc.BuyLog);
			ImGui::Checkbox(XorStr("Auto Accept"), &g_Options.Misc.AutoAccept);
			ImGui::Text(XorStr("Namespam"));
			ImGui::Combo("##nmespam", &g_Options.Misc.iNameSpam, iNameSpam, ARRAYSIZE(iNameSpam));
			ImGui::Combo("Skybox", &g_Options.Misc.nightModeStyle, skyboxesuffya, ARRAYSIZE(skyboxesuffya));
			ImGui::PushItemWidth(100);
			ImGui::Separator();
			ImGui::Text("Clantags");
			ImGui::Separator();
			ImGui::Checkbox(XorStr("Spammer"), &g_Options.Misc.spammer);
			ImGui::Checkbox(XorStr("Synced Clantag"), &g_Options.Misc.syncclantag);
			ImGui::Checkbox(XorStr("Static Clantag"), &g_Options.Misc.clantag);
			ImGui::Checkbox(XorStr("Gamememe Clantag"), &g_Options.Misc.GamesenseMemeClantag);
			ImGui::Combo(("Prank Clantags"), &g_Options.Misc.Clantag1337, clantags1337, ARRAYSIZE(clantags1337));
			ImGui::Separator();


		}ImGui::EndChild();

		ImGui::SameLine();
		// SECOND COLUMN
		ImGui::BeginChild("Second", ImVec2(265, 435), true);
		{
			ImGui::Checkbox("Skinchanger", &g_Options.Misc.SkinChangerToggle);
			ImGui::Checkbox("Rank Reveal", &g_Options.Misc.RankReveal);
			ImGui::Checkbox("Bunnyhop", &g_Options.Misc.Bhop);
			ImGui::Checkbox("Auto Strafe", &g_Options.Misc.AutoStrafe);
			ImGui::Checkbox("Hitmarker", &g_Options.Misc.Hitmarker);
			ImGui::Checkbox("Hitsound", &g_Options.Misc.Hitsound);
			ImGui::Combo(("Sounds"), &g_Options.Misc.Hitsounds, hitsounds, ARRAYSIZE(hitsounds));
			ImGui::Separator();
			ImGui::Text(XorStr("Thirdperson"));
			ImGui::Checkbox(XorStr("Enable"), &g_Options.Misc.ThirdPerson);
			ImGui::Hotkey(XorStr("Key"), &g_Options.Misc.ThirdpersonKey);
			ImGui::Separator();

		}ImGui::EndChild();

		ImGui::SameLine();
		// THIRD COLUMN
		ImGui::BeginChild("Config", ImVec2(242, 435), true);
		{
			//ImGui::Text("                            Configs                             ");
			//ImGui::Text("");

			if (ImGui::Button(XorStr("                           Unload                            ")))
			{
				g_Engine->ClientCmd_Unrestricted("cl_mouseenable 1");
				unload = true;
			}

			//ImGui::Text("");
			//ImGui::Text("Configs");
			ImGui::Separator();
			if (ImGui::Button("Save Legit I     "))
				Config->SaveLegit();
			ImGui::SameLine();
			if (ImGui::Button("Load Legit I     "))
				Config->LoadLegit();
			if (ImGui::Button("Save Legit II    "))
				Config->SaveLegit2();
			ImGui::SameLine();
			if (ImGui::Button("Load Legit II    "))
				Config->LoadLegit2();
			if (ImGui::Button("Save Legit III   "))
				Config->SaveLegit3();
			ImGui::SameLine();
			if (ImGui::Button("Load Legit III   "))
				Config->LoadLegit3();
			ImGui::Separator();
			if (ImGui::Button("Save HVH I      "))
				Config->SaveHVH();
			ImGui::SameLine();
			if (ImGui::Button("Load HVH I      "))
				Config->LoadHVH();
			if (ImGui::Button("Save HVH II     "))
				Config->SaveHVH2();
			ImGui::SameLine();
			if (ImGui::Button("Load HVH II     "))
				Config->LoadHVH2();
			if (ImGui::Button("Save HVH III    "))
				Config->SaveHVH3();
			ImGui::SameLine();
			if (ImGui::Button("Load HVH III    "))
				Config->LoadHVH3();
			ImGui::Separator();
			if (ImGui::Button("Save Custom I  "))
				Config->SaveCustom();
			ImGui::SameLine();
			if (ImGui::Button("Load Custom I  "))
				Config->LoadCustom();
			if (ImGui::Button("Save Custom II "))
				Config->SaveCustom2();
			ImGui::SameLine();
			if (ImGui::Button("Load Custom II "))
				Config->LoadCustom2();
			if (ImGui::Button("Save Custom III"))
				Config->SaveCustom3();
			ImGui::SameLine();
			if (ImGui::Button("Load Custom III"))
				Config->LoadCustom3();
			ImGui::Separator();

		}ImGui::EndChild();


	}

	/*
	_____ _  _______ _   _  _____
	/ ____| |/ /_   _| \ | |/ ____|
	| (___ | ' /  | | |  \| | (___
	\___ \|  <   | | | . ` |\___ \
	____) | . \ _| |_| |\  |____) |
	|_____/|_|\_\_____|_| \_|_____/

	*/

	void SkinsTab()
	{
		ImGui::PushFont(fkek);
		ImGui::BeginChild("Main", ImVec2(279, 565), true);
		{
			ImGui::Checkbox(("Enabled"), &g_Options.Skinchanger.Enabled);
			ImGui::SameLine();
			ImGui::PushItemWidth(150);
			if (ImGui::Button(("Update")))
			{
				KnifeApplyCallbk();
			}
			// KNIFE && GLOVE
			ImGui::Checkbox(XorStr("Stat-Trak"), &g_Options.Skinchanger.StatTrak);
			ImGui::Text("General");
			ImGui::Combo(("Knife Model"), &g_Options.Skinchanger.Knife, knives, ARRAYSIZE(knives));
			ImGui::Combo(("Knife Skin"), &g_Options.Skinchanger.KnifeSkin, knifeskins, ARRAYSIZE(knifeskins));
			ImGui::Combo(("Gloves"), &g_Options.Skinchanger.gloves, gloves, ARRAYSIZE(gloves));
			ImGui::Combo(("Gloves Skin"), &g_Options.Skinchanger.glovesskin, glovesskin, ARRAYSIZE(glovesskin)); //glove skins, we gotta add dat shit
																												 // PISTOLS
			ImGui::Text("Pistols");
			ImGui::Combo(("Glock-18"), &g_Options.Skinchanger.GlockSkin, glock, ARRAYSIZE(glock));
			ImGui::Combo(("USP-S"), &g_Options.Skinchanger.USPSkin, usp, ARRAYSIZE(usp));
			ImGui::Combo(("Deagle"), &g_Options.Skinchanger.DeagleSkin, deagle, ARRAYSIZE(deagle));
			ImGui::Combo(("TEC-9"), &g_Options.Skinchanger.tec9Skin, tec9, ARRAYSIZE(tec9));
			ImGui::Combo(("P2000"), &g_Options.Skinchanger.P2000Skin, p2000, ARRAYSIZE(p2000));
			ImGui::Combo(("P250"), &g_Options.Skinchanger.P250Skin, p250, ARRAYSIZE(p250));
			ImGui::Combo(("Revolver"), &g_Options.Skinchanger.RevolverSkin, revolver, ARRAYSIZE(revolver));
			ImGui::Combo(("Five-Seven"), &g_Options.Skinchanger.FiveSevenSkin, fiveseven, ARRAYSIZE(fiveseven));
			ImGui::Combo(("Dual Berettas"), &g_Options.Skinchanger.DualBerettasSkin, dualberettas, ARRAYSIZE(dualberettas));
			// SMGS
			ImGui::Text("SMG's");
			ImGui::Combo(("P90"), &g_Options.Skinchanger.P90Skin, p90, ARRAYSIZE(p90));
			ImGui::Combo(("UMP45"), &g_Options.Skinchanger.UMP45Skin, ump45, ARRAYSIZE(ump45));
			ImGui::Combo(("MAC10"), &g_Options.Skinchanger.Mac10Skin, mac10, ARRAYSIZE(mac10));
			ImGui::Combo(("Bizon"), &g_Options.Skinchanger.BizonSkin, bizon, ARRAYSIZE(bizon));
			ImGui::Combo(("MP9"), &g_Options.Skinchanger.MP9Skin, mp9, ARRAYSIZE(mp9));
			ImGui::Combo(("MP7"), &g_Options.Skinchanger.MP7Skin, mp7, ARRAYSIZE(mp7));
			// SNIPERS
			ImGui::Text("Snipers");
			ImGui::Combo(("AWP"), &g_Options.Skinchanger.AWPSkin, awp, ARRAYSIZE(awp));
			ImGui::Combo(("SSG08"), &g_Options.Skinchanger.SSG08Skin, ssg08, ARRAYSIZE(ssg08));
			ImGui::Combo(("G3SG1"), &g_Options.Skinchanger.G3SG1Skin, g3sg1, ARRAYSIZE(g3sg1));
			ImGui::Combo(("SCAR20"), &g_Options.Skinchanger.SCAR20Skin, scar20, ARRAYSIZE(scar20));
			// RIFLES
			ImGui::Text("Rifles");
			ImGui::Combo(("AK-47"), &g_Options.Skinchanger.AK47Skin, ak47, ARRAYSIZE(ak47));
			ImGui::Combo(("M4A1-S"), &g_Options.Skinchanger.M4A1SSkin, m4a1s, ARRAYSIZE(m4a1s));
			ImGui::Combo(("M4A4"), &g_Options.Skinchanger.M4A4Skin, m4a4, ARRAYSIZE(m4a4));
			ImGui::Combo(("AUG"), &g_Options.Skinchanger.AUGSkin, aug, ARRAYSIZE(aug));
			ImGui::Combo(("Famas"), &g_Options.Skinchanger.FAMASSkin, famas, ARRAYSIZE(famas));
			ImGui::Combo(("Galil"), &g_Options.Skinchanger.GalilSkin, galil, ARRAYSIZE(galil));
			// SHOTGUNS
			ImGui::Text("Shotguns");
			ImGui::Combo(("XM1014"), &g_Options.Skinchanger.XM1014Skin, xm1014, ARRAYSIZE(xm1014));
			ImGui::Combo(("Nova"), &g_Options.Skinchanger.NovaSkin, nova, ARRAYSIZE(nova));
			ImGui::Combo(("Mag-7"), &g_Options.Skinchanger.Mag7Skin, mag7, ARRAYSIZE(mag7));
			ImGui::Combo(("Sawed Off"), &g_Options.Skinchanger.SawedOffSkin, sawedoff, ARRAYSIZE(sawedoff));
			// MGs
			ImGui::Text("MG's");
			ImGui::Combo(("M249"), &g_Options.Skinchanger.M249Skin, m249, ARRAYSIZE(m249));
			ImGui::Combo(("Negev"), &g_Options.Skinchanger.NegevSkin, negev, ARRAYSIZE(negev));

		}ImGui::EndChild();
	}

	void ColorsTab()
	{
		ImGui::PushFont(fkek);
		ImGui::BeginChild("##visualscolors", ImVec2(788, 435), true);
		{
			static int selectedItem = 0;

			ImVec2 lastCursor = ImGui::GetCursorPos();


			ImGui::ListBoxHeader("##Colors - Visuals", ImVec2(330, 418));
			if (selectedItem == 0)
			{
				ImGui::Text("Selected: Terrorist - Box Visible");
			}
			else if (selectedItem == 1)
			{
				ImGui::Text("Selected: Terrorist - Box Invisible");
			}
			else if (selectedItem == 2)
			{
				ImGui::Text("Selected: Counter-Terrorist - Box Visible");
			}
			else if (selectedItem == 3)
			{
				ImGui::Text("Selected: Counter-Terrorist - Box Invisible");
			}
			else if (selectedItem == 4)
			{
				ImGui::Text("Selected: Teammates - Glow");
			}
			else if (selectedItem == 5)
			{
				ImGui::Text("Selected: Enemies - Glow");
			}
			else if (selectedItem == 6)
			{
				ImGui::Text("Selected: Visuals - Weapon Glow");
			}
			else if (selectedItem == 7)
			{
				ImGui::Text("Selected: Teammates - Draw Chams");
			}
			else if (selectedItem == 8)
			{
				ImGui::Text("Selected: Enemies - Draw Chams");
			}
			else if (selectedItem == 9)
			{
				ImGui::Text("Selected: Visuals - Draw Hands");
			}
			else if (selectedItem == 10)
			{
				ImGui::Text("Selected: Visuals - Draw Armor");
			}
			else if (selectedItem == 11)
			{
				ImGui::Text("Selected: Visuals - Draw Health");
			}
			else if (selectedItem == 12)
			{
				ImGui::Text("Selected: Visuals - Draw Bomb");
			}
			else if (selectedItem == 13)
			{
				ImGui::Text("Selected: Visuals - Draw Drop");
			}
			else if (selectedItem == 14)
			{
				ImGui::Text("Selected: Visuals - Draw Skeleton");
			}
			else if (selectedItem == 15)
			{
				ImGui::Text("Selected: Visuals - Draw Backtrack");
			}
			else if (selectedItem == 16)
			{
				ImGui::Text("Selected: Visuals - Draw aWall Indicator");
			}
			else if (selectedItem == 17)
			{
				ImGui::Text("Selected: Visuals - Draw Real Angle");
			}
			else if (selectedItem == 18)
			{
				ImGui::Text("Selected: Visuals - Draw Real Angle");
			}
			else if (selectedItem == 19)
			{
				ImGui::Text("Selected: Visuals - Draw Fake Angle");
			}
			else if (selectedItem == 20)
			{
				ImGui::Text("Selected: GUI - Text");
			}
			else if (selectedItem == 21)
			{
				ImGui::Text("Selected: GUI - Button");
			}
			else if (selectedItem == 22)
			{
				ImGui::Text("Selected: GUI - Hovered Button");
			}
			else if (selectedItem == 23)
			{
				ImGui::Text("Selected: GUI - Active Button");
			}
			else if (selectedItem == 24)
			{
				ImGui::Text("Selected: GUI - Window");
			}
			else if (selectedItem == 25)
			{
				ImGui::Text("Selected: GUI - Frame");
			}
			else if (selectedItem == 26)
			{
				ImGui::Text("Selected: GUI - Selected Text");
			}
			else if (selectedItem == 27)
			{
				ImGui::Text("Selected: GUI - Header");
			}
			else if (selectedItem == 28)
			{
				ImGui::Text("Selected: GUI - Hovered Header");
			}
			else if (selectedItem == 29)
			{
				ImGui::Text("Selected: GUI - Active Header");
			}
			else if (selectedItem == 30)
			{
				ImGui::Text("Selected: GUI - Slider");
			}
			else if (selectedItem == 31)
			{
				ImGui::Text("Selected: GUI - Combo Backround");
			}
			else if (selectedItem == 32)
			{
				ImGui::Text("Selected: GUI - Scrollbar");
			}
			else if (selectedItem == 33)
			{
				ImGui::Text("Selected: GUI - Scrollbar Backround");
			}
			else if (selectedItem == 34)
			{
				ImGui::Text("Selected: GUI - Checkmark");
			}
			ImGui::Text("____________________________________________________");
			for (int i = 0; i < G::ColorsForPicker.size(); i++)
			{

				bool selected = i == selectedItem;

				if (ImGui::Selectable(G::ColorsForPicker[i].Name, selected))
					selectedItem = i;
			}
			ImGui::ListBoxFooter();


			float nc = lastCursor.x + 260;
			ImGui::SetCursorPos(ImVec2(nc, lastCursor.y));

			ColorP col = G::ColorsForPicker[selectedItem];
			int r = (col.Ccolor[0] * 255.f);
			int g = (col.Ccolor[1] * 255.f);
			int b = (col.Ccolor[2] * 255.f);

			bool wip;

			ImGui::SetCursorPosX(nc);


			col.Ccolor[0] = r / 255.f;
			col.Ccolor[1] = g / 255.f;
			col.Ccolor[2] = b / 255.f;

			ImGui::SameLine();

			ImVec2 curPos = ImGui::GetCursorPos();
			ImVec2 curWindowPos = ImGui::GetWindowPos();
			curPos.x += curWindowPos.x;
			curPos.y += curWindowPos.y;

			ImGui::PushItemWidth(372);
			ImGui::ColorPicker3("##clr", col.Ccolor);

		}ImGui::EndChild();


	}
}
