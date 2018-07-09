#include "Configuration.hpp"
#include "Variables.h"
#include <winerror.h>
#pragma warning( disable : 4091)
#include <ShlObj.h>
#include <string>
#include <sstream>
void CConfig::Setup()
{

	// Ragebot
	SetupValue(g_Options.Ragebot.MainSwitch, false, ("Ragebot"), ("RageToggle"));
	SetupValue(g_Options.Ragebot.Enabled, false, ("Ragebot"), ("Enabled"));
	SetupValue(g_Options.Ragebot.AutoFire, false, ("Ragebot"), ("AutoFire"));

	//////////////////
	SetupValue(g_Options.Ragebot.RealCustomStaticRechts, false, ("Ragebot"), ("RealCustomStaticRechts"));
	SetupValue(g_Options.Ragebot.RealCustomJitterRechts, false, ("Ragebot"), ("RealCustomJitterRechts"));
	SetupValue(g_Options.Ragebot.RealCustomJitterLinks, false, ("Ragebot"), ("RealCustomJitterLinks"));
	SetupValue(g_Options.Ragebot.RealCustomStaticLinks, false, ("Ragebot"), ("RealCustomStaticLinks"));

	SetupValue(g_Options.Ragebot.RealCustomStaticRechtsAngle, 0, ("Ragebot"), ("RealCustomStaticRechtsAngle"));
	SetupValue(g_Options.Ragebot.RealCustomRechtsBisAngle, 0, ("Ragebot"), ("RealCustomRechtsBisAngle"));
	SetupValue(g_Options.Ragebot.RealCustomRechtsVonAngle, 0, ("Ragebot"), ("RealCustomRechtsVonAngle"));
	SetupValue(g_Options.Ragebot.RealCustomStaticLinksAngle, 0, ("Ragebot"), ("RealCustomStaticLinksAngle"));
	SetupValue(g_Options.Ragebot.RealCustomLinksVonAngle, 0, ("Ragebot"), ("RealCustomLinksVonAngle"));
	SetupValue(g_Options.Ragebot.RealCustomLinksBisAngle, 0, ("Ragebot"), ("RealCustomLinksBisAngle"));
	SetupValue(g_Options.Ragebot.LbyCustomLinks, 0, ("Ragebot"), ("LbyCustomLinks"));
	SetupValue(g_Options.Ragebot.LbyCustomRechts, 0, ("Ragebot"), ("LbyCustomRechts"));
	//////////////////

	SetupValue(g_Options.Ragebot.FOV, 0.f, ("Ragebot"), ("FOV"));
	SetupValue(g_Options.Ragebot.Silent, false, ("Ragebot"), ("Silent"));
	SetupValue(g_Options.Misc.AutoPistol, false, ("Ragebot"), ("AutoPistol"));

	SetupValue(g_Options.Ragebot.FriendlyFire, false, ("Ragebot"), ("FriendlyFire"));
	SetupValue(g_Options.Ragebot.Hitbox, 0, ("Ragebot"), ("Hitbox"));
	SetupValue(g_Options.Ragebot.Hitscan, 0, ("Ragebot"), ("Hitscan"));

	SetupValue(g_Options.Ragebot.AntiRecoil, false, ("Ragebot"), ("AntiRecoil"));
	SetupValue(g_Options.Ragebot.AutoRevolver, false, ("Ragebot"), ("AutoRevolver"));
	SetupValue(g_Options.Ragebot.AutoStop, false, ("Ragebot"), ("AutoStop"));
	SetupValue(g_Options.Ragebot.AutoCrouch, false, ("Ragebot"), ("AutoCrouch"));
	SetupValue(g_Options.Ragebot.AutoScope, false, ("Ragebot"), ("AutoScope"));
	SetupValue(g_Options.Ragebot.MinimumDamage, 0.f, ("Ragebot"), ("AutoWallDamage"));
	SetupValue(g_Options.Ragebot.Resolver, false, ("Ragebot"), ("Resolver"));
	SetupValue(g_Options.Ragebot.iResolver, 0, ("Ragebot"), ("iResolver"));
	SetupValue(g_Options.Ragebot.ResolverOverride, false, ("Ragebot"), ("ResolverOverride"));
	SetupValue(g_Options.Ragebot.ResolverOverrideKey, 0, ("Ragebot"), ("ResolverOverrideKey"));
	SetupValue(g_Options.Ragebot.ResolverOverrideSlider, 180.f, ("Ragebot"), ("ResolverOverrideSlider"));
	SetupValue(g_Options.Ragebot.LBYPrediction, false, ("Ragebot"), ("LBYPrediction"));
	SetupValue(g_Options.Ragebot.JumpScout, false, ("Ragebot"), ("JumpScout"));
	SetupValue(g_Options.Ragebot.rageBacktrack, false, ("Ragebot"), ("Backtrack"));

	SetupValue(g_Options.Ragebot.BoolFakewalk, false, ("Ragebot"), ("Fakewalk"));
	SetupValue(g_Options.Ragebot.IntFakewalk, 0, ("Ragebot"), ("FakewalkKey"));

	SetupValue(g_Options.Ragebot.rageBacktrackSlider, 0.f, ("Ragebot"), ("BacktrackSlider"));

	SetupValue(g_Options.Ragebot.MinimumDamageSniper, 0.f, ("Ragebot"), ("AutoWallDamageSniper"));
	SetupValue(g_Options.Ragebot.MinimumDamageScout, 0.f, ("Ragebot"), ("AutoWallDamageScout"));
	SetupValue(g_Options.Ragebot.MinimumDamageAWP, 0.f, ("Ragebot"), ("AutoWallDamageAWP"));
	SetupValue(g_Options.Ragebot.MinimumDamagePistol, 0.f, ("Ragebot"), ("AutoWallDamagePistol"));
	SetupValue(g_Options.Ragebot.MinimumDamageRifle, 0.f, ("Ragebot"), ("AutoWallDamageRifle"));
	SetupValue(g_Options.Ragebot.MinimumDamageHeavy, 0.f, ("Ragebot"), ("AutoWallDamageHeavy"));
	SetupValue(g_Options.Ragebot.MinimumDamageSmg, 0.f, ("Ragebot"), ("AutoWallDamageSmgs"));
	SetupValue(g_Options.Ragebot.MinimumDamageRevolver, 0.f, ("Ragebot"), ("AutoWallDamageRevolver"));
	SetupValue(g_Options.Ragebot.MinimumDamageShotgun, 0.f, ("Ragebot"), ("MinimumDamageShotgun"));
	SetupValue(g_Options.Ragebot.Hitchance, false, ("Ragebot"), ("HitChance"));
	SetupValue(g_Options.Ragebot.HitchanceSniper, 0.f, ("Ragebot"), ("HitChanceSniper"));
	SetupValue(g_Options.Ragebot.HitchanceScout, 0.f, ("Ragebot"), ("HitChanceScout"));
	SetupValue(g_Options.Ragebot.HitchanceAWP, 0.f, ("Ragebot"), ("HitChanceAWP"));
	SetupValue(g_Options.Ragebot.HitchancePistol, 0.f, ("Ragebot"), ("HitChancePistol"));
	SetupValue(g_Options.Ragebot.HitchanceHeavy, 0.f, ("Ragebot"), ("HitChanceHeavy"));
	SetupValue(g_Options.Ragebot.HitchanceSmgs, 0.f, ("Ragebot"), ("HitChanceSmgs"));
	SetupValue(g_Options.Ragebot.HitchanceRifle, 0.f, ("Ragebot"), ("HitChanceRifle"));
	SetupValue(g_Options.Ragebot.HitchanceRevolver, 0.f, ("Ragebot"), ("HitChanceRevolver"));
	SetupValue(g_Options.Ragebot.HitchanceShotgun, 0.f, ("Ragebot"), ("HitchanceShotgun"));
	SetupValue(g_Options.Ragebot.FakeLagFix, false, ("Ragebot"), ("FakeLagFix"));
	SetupValue(g_Options.Ragebot.Multipoint, false, ("Ragebot"), ("Multipoint"));

	SetupValue(g_Options.Ragebot.ExtendBacktrackValue, 0.f, ("Ragebot"), ("ExtendBacktrackValue"));
	SetupValue(g_Options.Ragebot.ExtendBacktrack, false, ("Ragebot"), ("ExtendBacktrack"));

	SetupValue(g_Options.Ragebot.FakeLagAmt, 0.f, ("Ragebot"), ("FakeLagAmt"));
	SetupValue(g_Options.Ragebot.FakeLag, false, ("Ragebot"), ("FakeLag"));
	SetupValue(g_Options.Ragebot.FakeLagMoveOnly, false, ("Ragebot"), ("FakeLagMoveOnly"));

	// Anti Aim
	SetupValue(g_Options.Ragebot.EnabledAntiAim, false, ("Ragebot"), ("AntiaimEnabled"));
	SetupValue(g_Options.Ragebot.YawFakeMoveEnabled, false, ("Ragebot"), ("YawFakeMoveEnabled"));
	SetupValue(g_Options.Ragebot.YawFakeMove, 0, ("AntiAim"), ("AntiaimYaw-fakemove"));

	SetupValue(g_Options.Ragebot.PitchAdder, 0, ("Ragebot"), ("PitchAdder"));
	SetupValue(g_Options.Ragebot.YawTrueAdder, 0, ("Ragebot"), ("YawTrueAdder"));
	SetupValue(g_Options.Ragebot.YawFakeAdder, 0, ("Ragebot"), ("YawFakeAdder"));
	SetupValue(g_Options.Ragebot.LBYRightAdder, 0, ("Ragebot"), ("LBYRightAdder"));
	SetupValue(g_Options.Ragebot.LBYLeftAdder, 0, ("Ragebot"), ("LBYLeftAdder"));

    SetupValue(g_Options.Ragebot.PreAAs, false, ("Ragebot"), ("Pre-set-AAs"));
    SetupValue(g_Options.Ragebot.Pitch, 0, ("Ragebot"), ("AntiaimPitch"));
    SetupValue(g_Options.Ragebot.YawTrue, 0, ("Ragebot"), ("AntiaimYaw-true"));
    SetupValue(g_Options.Ragebot.YawFake, 0, ("Ragebot"), ("AntiaimYaw-fake"));
    SetupValue(g_Options.Ragebot.AtTarget, false, ("Ragebot"), ("attargets"));
    SetupValue(g_Options.Ragebot.Edge, false, ("Ragebot"), ("edge"));
    SetupValue(g_Options.Ragebot.KnifeAA, false, ("Ragebot"), ("KnifeAA"));
    SetupValue(g_Options.Ragebot.BuilderAAs, false, ("Ragebot"), ("Builder-AAs"));
    SetupValue(g_Options.Ragebot.BuilderPitch, 0, ("Ragebot"), ("Builder-Pitch"));
    SetupValue(g_Options.Ragebot.BuilderReal, 0, ("Ragebot"), ("Builder-Yaw"));
    SetupValue(g_Options.Ragebot.BuilderFake, 0, ("Ragebot"), ("Builder-Fake"));
    SetupValue(g_Options.Ragebot.Jitter, false, ("Ragebot"), ("Builder-Jitter"));
    SetupValue(g_Options.Ragebot.JitterRange, 0, ("Ragebot"), ("Builder-Jitter-Range"));
    SetupValue(g_Options.Ragebot.FJitter, false, ("Ragebot"), ("Builder-fJitter"));
    SetupValue(g_Options.Ragebot.FJitterRange, 0, ("Ragebot"), ("Builder-fJitter-Range"));
    SetupValue(g_Options.Ragebot.LBYBreaker, false, ("Ragebot"), ("Builder-LBY-Breaker"));
	SetupValue(g_Options.Ragebot.bLbyBreaker, false, ("Ragebot"), ("bLbyBreaker"));
	SetupValue(g_Options.AntiAim.SwitchFakeLeft, VK_RIGHT, ("AntiAim"), ("SwitchFakeLeft"));
	SetupValue(g_Options.AntiAim.SwitchFakeRight, VK_LEFT, ("AntiAim"), ("SwitchFakeRight"));
	SetupValue(g_Options.Ragebot.YawTrueMove, 0, ("AntiAim"), ("AntiaimYaw-move"));
	SetupValue(g_Options.Ragebot.LegitAAReal, 0, ("Ragebot"), ("LegitAAReal"));
	SetupValue(g_Options.Ragebot.LegitAA, false, ("Ragebot"), ("LegitAA"));

	SetupValue(g_Options.Ragebot.fBaimIfHP, 0, ("Ragebot"), ("fBaimIfHP"));
	SetupValue(g_Options.Ragebot.bBaimIfHP, false, ("Ragebot"), ("bBaimIfHP"));

	//	Legitbot
	SetupValue(g_Options.Legitbot.MainSwitch, false, ("Legitbot"), ("LegitToggle"));
	SetupValue(g_Options.Legitbot.Aimbot.Enabled, false, ("Legitbot"), ("Enabled"));
	SetupValue(g_Options.Legitbot.backtrack, false, ("Legitbot"), ("Backtrack"));

	SetupValue(g_Options.Legitbot.Mainfov, 0.f, ("Legitbot"), ("FOV"));
	SetupValue(g_Options.Legitbot.MainSmooth, 1.f, ("Legitbot"), ("Speed"));
	SetupValue(g_Options.Legitbot.main_recoil_max, 0.f, ("Legitbot"), ("RCS-max"));

	SetupValue(g_Options.Legitbot.Pistolfov, 0.f, ("Legitbot"), ("FOV-Pistol"));
	SetupValue(g_Options.Legitbot.PistolSmooth, 1.f, ("Legitbot"), ("Speed-Pistol"));
	SetupValue(g_Options.Legitbot.pistol_recoil_max, 0.f, ("Legitbot"), ("RCS-max-pistol"));

	SetupValue(g_Options.Legitbot.Sniperfov, 0.f, ("Legitbot"), ("FOV-Sniper"));
	SetupValue(g_Options.Legitbot.SniperSmooth, 1.f, ("Legitbot"), ("Speed-Sniper"));
	SetupValue(g_Options.Legitbot.sniper_recoil_max, 0.f, ("Legitbot"), ("RCS-max-sniper"));

	SetupValue(g_Options.Legitbot.Triggerbot.Enabled, false, ("Triggerbot"), ("Enabled"));
	SetupValue(g_Options.Legitbot.Triggerbot.Key, 0, ("Triggerbot"), ("Key"));
	SetupValue(g_Options.Legitbot.Triggerbot.Delay, 1.f, ("Triggerbot"), ("Delay"));
	SetupValue(g_Options.Legitbot.Triggerbot.hitchance, 0.f, ("Triggerbot"), ("Hitchance"));

	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Head, false, ("Triggerbot"), ("FilterHead"));
	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Chest, false, ("Triggerbot"), ("FilterChest"));
	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Stomach, false, ("Triggerbot"), ("FilterStomach"));
	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Arms, false, ("Triggerbot"), ("FilterArms"));
	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Legs, false, ("Triggerbot"), ("FilterLegs"));


	// Visuals
	SetupValue(g_Options.Visuals.Enabled, false, ("Visuals"), ("VisualsEnabled"));
	SetupValue(g_Options.Visuals.Box, false, ("Visuals"), ("Box"));
	SetupValue(g_Options.Visuals.Name, false, ("Visuals"), ("Name"));
	SetupValue(g_Options.Visuals.Skeleton, false, ("Visuals"), ("Skeleton"));
	SetupValue(g_Options.Visuals.WireframeSmoke, false, ("Visuals"), ("WireframeSmoke"));
	SetupValue(g_Options.Visuals.LBYIndicatorOS, false, ("Visuals"), ("LBYIndicatorOS"));

	SetupValue(g_Options.Visuals.HasDefuser, false, ("Visuals"), ("HasDefuser"));
	SetupValue(g_Options.Visuals.HasHeavyArmor, false, ("Visuals"), ("HasHeavyArmor"));
	SetupValue(g_Options.Visuals.HasHelmet, false, ("Visuals"), ("HasHelmet"));
	SetupValue(g_Options.Visuals.ChromeModels, false, ("Visuals"), ("ChromeModels"));
	SetupValue(g_Options.Visuals.LSDVision, false, ("Visuals"), ("LSDVision"));
	SetupValue(g_Options.Visuals.DefuseTimer, false, ("Visuals"), ("DefuseTimer"));
	SetupValue(g_Options.Visuals.C4Timer, false, ("Visuals"), ("C4Timer"));
	SetupValue(g_Options.Visuals.AmmoInClip, false, ("Visuals"), ("AmmoInClip"));
	SetupValue(g_Options.Visuals.MoveType, false, ("Visuals"), ("MoveType"));
	SetupValue(g_Options.Visuals.HP, false, ("Visuals"), ("HP"));
	SetupValue(g_Options.Visuals.AP, false, ("Visuals"), ("AP"));
	SetupValue(g_Options.Visuals.Hands, 0, ("Visuals"), ("HandsMaterial"));
	SetupValue(g_Options.Visuals.WeaponMaterial, 0, ("Visuals"), ("WeaponMaterial"));
	SetupValue(g_Options.Visuals.bResolverESP, false, ("Visuals"), ("bResolverESP"));
	//SetupValue(g_Options.Visuals.KnifeMaterial, 0, ("Visuals"), ("KnifeMaterial"));

	SetupValue(g_Options.Visuals.HPNumber, false, ("Visuals"), ("HPNumber"));
	SetupValue(g_Options.Visuals.APNumber, false, ("Visuals"), ("APNumber"));

	SetupValue(g_Options.Visuals.Weapon, false, ("Visuals"), ("Weapon"));

	SetupValue(g_Options.Visuals.C4Planted, false, ("Visuals"), ("C4Planted"));

	SetupValue(g_Options.Visuals.RadarEngine, false, ("Visuals"), ("Radar"));
	SetupValue(g_Options.Visuals.RadarSpoof, false, ("Visuals"), ("RadarSpoof"));
	SetupValue(g_Options.Visuals.RemoveTextures, false, ("Visuals"), ("RemoveTextures"));

	SetupValue(g_Options.Visuals.AmbientRed, 0, ("Visuals"), ("AmbientRed"));
	SetupValue(g_Options.Visuals.AmbientBlue, 0, ("Visuals"), ("AmbientBlue"));
	SetupValue(g_Options.Visuals.AmbientGreen, 0, ("Visuals"), ("AmbientGreen"));

	SetupValue(g_Options.Visuals.RecoilTracking, .45, ("Visuals"), ("RecoilTracking"));
	SetupValue(g_Options.Visuals.ViewPunch, .055, ("Visuals"), ("ViewPunch"));

	SetupValue(g_Options.Visuals.Chams, false, ("Visuals"), ("Chams"));
	SetupValue(g_Options.Visuals.ChamsMode.Filter.XQZ, false, ("Visuals"), ("ChamsXQZ"));
	SetupValue(g_Options.Visuals.DLight, false, ("Visuals"), ("DLight"));
	SetupValue(g_Options.Visuals.SpreadCrosshair, false, ("Visuals"), ("SpreadCrosshair"));
	SetupValue(g_Options.Visuals.GrenadeESP, false, ("Visuals"), ("GrenadeESP"));
	SetupValue(g_Options.Visuals.Glow, false, ("Visuals"), ("Glow"));
	SetupValue(g_Options.Visuals.FOVChanger, 0.f, ("Visuals"), ("fovchanger"));
	SetupValue(g_Options.Visuals.viewmodelChanger, 68.f, ("Visuals"), ("viewmodel_fov"));
	SetupValue(g_Options.Visuals.OverrideScopedFOV, false, ("Visuals"), ("OverrideScopedFOV"));
	SetupValue(g_Options.Misc.Clantag1337, 0, ("Misc"), ("Clantag1337"));

	SetupValue(g_Options.Visuals.NoVisualRecoil, false, ("Visuals"), ("NoVisualRecoil"));
	SetupValue(g_Options.Visuals.NoFlash, false, ("Visuals"), ("NoFlash"));
	SetupValue(g_Options.Visuals.NoSmoke, false, ("Visuals"), ("NoSmoke"));

	SetupValue(g_Options.Visuals.RecoilESP, false, ("Visuals"), ("RecoilESP"));

	SetupValue(g_Options.Visuals.backtrack, false, ("Visuals"), ("DrawBacktrack"));
	SetupValue(g_Options.Visuals.noscopeborder, false, ("Visuals"), ("noscopeborder"));
	SetupValue(g_Options.Visuals.C4, false, ("Visuals"), ("C4"));
	SetupValue(g_Options.Visuals.GrenadePrediction, false, ("Visuals"), ("GrenadePrediction"));
	SetupValue(g_Options.Visuals.Money, false, ("Visuals"), ("Money"));
	SetupValue(g_Options.Misc.ThirdPerson, false, ("Visuals"), ("thirdperson"));
	SetupValue(g_Options.Misc.ThirdpersonKey, 0, ("Visuals"), ("thirdpersonKey"));
	SetupValue(g_Options.Visuals.Watermark, true, ("Visuals"), ("Watermark"));

	// Local HIER WEITER MAcHEN
	SetupValue(g_Options.Visuals.BoxLocal, false, ("Visuals"), ("BoxLocal"));
	SetupValue(g_Options.Visuals.NameLocal, false, ("Visuals"), ("NameLocal"));
	SetupValue(g_Options.Visuals.SkeletonLocal, false, ("Visuals"), ("SkeletonLocal"));
	SetupValue(g_Options.Visuals.HPLocal, false, ("Visuals"), ("HPLocal"));
	SetupValue(g_Options.Visuals.APLocal, false, ("Visuals"), ("APLocal"));
	SetupValue(g_Options.Visuals.IsScopedLocal, false, ("Visuals"), ("IsScopedLocal"));
	SetupValue(g_Options.Visuals.HasHelmetLocal, false, ("Visuals"), ("HasHelmetLocal"));
	SetupValue(g_Options.Visuals.HasDefuserLocal, false, ("Visuals"), ("HasDefuserLocal"));
	SetupValue(g_Options.Visuals.HasHeavyArmorLocal, false, ("Visuals"), ("HasHeavyArmorLocal"));
	SetupValue(g_Options.Visuals.HPNumberLocal, false, ("Visuals"), ("HPNumberLocal"));
	SetupValue(g_Options.Visuals.APNumberLocal, false, ("Visuals"), ("APNumberLocal"));
	SetupValue(g_Options.Visuals.MoneyLocal, false, ("Visuals"), ("MoneyLocal"));
	SetupValue(g_Options.Visuals.LBYIndicator, false, ("Visuals"), ("LBYIndicator"));
	SetupValue(g_Options.Visuals.MoveTypeLocal, false, ("Visuals"), ("MoveTypeLocal"));
	//

	SetupValue(g_Options.Visuals.IsScoped, false, ("Visuals"), ("IsScoped"));

	SetupValue(g_Options.Visuals.DrawAwall, false, ("Visuals"), ("DrawAwall"));
	SetupValue(g_Options.Visuals.angleLines, false, ("Visuals"), ("angleLines"));
	SetupValue(g_Options.Visuals.AngleText, false, ("Visuals"), ("AngleText"));
	SetupValue(g_Options.Visuals.Warnings, false, ("Visuals"), ("Warnings"));

	SetupValue(g_Options.Visuals.Filter.EnemyOnly, false, ("Visuals"), ("EnemyOnly"));
	SetupValue(g_Options.Visuals.Filter.LocalPlayer, false, ("Visuals"), ("LocalPlayer"));
	SetupValue(g_Options.Visuals.SniperCrosshair, false, ("Visuals"), ("SniperCrosshair"));
	// Misc
	SetupValue(g_Options.Misc.Bhop, false, ("Misc"), ("Bhop"));
	SetupValue(g_Options.Misc.AutoStrafe, false, ("Misc"), ("Autostrafe"));
	SetupValue(g_Options.Misc.SpecList, false, ("Misc"), ("speclist"));
	SetupValue(g_Options.Misc.ragequit, 0, ("Misc"), ("ragequit-key"));
	SetupValue(g_Options.Misc.syncclantag, false, ("Misc"), ("syncclantag"));
	SetupValue(g_Options.Misc.clantag, false, ("Misc"), ("clantag"));
	SetupValue(g_Options.Misc.AutoAccept, false, ("Misc"), ("AutoAccept"));
	SetupValue(g_Options.Misc.BuyLog, false, ("Misc"), ("BuyLog"));
	SetupValue(g_Options.Misc.spammer, false, ("Misc"), ("spammer"));
	SetupValue(g_Options.Misc.nightMode, false, ("Misc"), ("nightMode"));
	SetupValue(g_Options.Misc.SkyBoxChanger, 0, ("Misc"), ("SkyBoxChanger"));
	SetupValue(g_Options.Misc.Hitmarker, false, ("Misc"), ("Hitmarker"));
	SetupValue(g_Options.Misc.Hitsound, false, ("Misc"), ("Hitsound"));
	SetupValue(g_Options.Misc.Hitsounds, 0, ("Misc"), ("Hitsounds"));
	SetupValue(g_Options.Misc.SkinChangerToggle, false, ("Misc"), ("skinchangertoggle"));
	SetupValue(g_Options.Misc.silentstealer, false, ("Misc"), ("silentstealer"));
	SetupValue(g_Options.Misc.NoName, false, ("Misc"), ("NoName"));
	SetupValue(g_Options.Misc.RankReveal, false, ("Misc"), ("RankReveal"));
	SetupValue(g_Options.Misc.GamesenseMemeClantag, false, ("Misc"), ("GamesenseMemeClantag"));


	// Glove & Knife
	SetupValue(g_Options.Skinchanger.Enabled, false, ("Skinchanger"), ("Enabled"));
	SetupValue(g_Options.Skinchanger.StatTrak, false, ("Skinchanger"), ("StatTrak"));
	SetupValue(g_Options.Skinchanger.Knife, 0, ("SkinChanger"), ("Knife"));
	SetupValue(g_Options.Skinchanger.KnifeSkin, 0, ("SkinChanger"), ("KnifeSkin"));
	SetupValue(g_Options.Skinchanger.gloves, 0, ("SkinChanger"), ("gloves"));
	SetupValue(g_Options.Skinchanger.glovesskin, 0, ("SkinChanger"), ("glovesskin"));

	// Rifle
	SetupValue(g_Options.Skinchanger.AK47Skin, 0, ("SkinChanger"), ("AK47Skin"));
	SetupValue(g_Options.Skinchanger.M4A1SSkin, 0, ("SkinChanger"), ("M4A1SSkin"));
	SetupValue(g_Options.Skinchanger.M4A4Skin, 0, ("SkinChanger"), ("M4A4Skin"));
	SetupValue(g_Options.Skinchanger.AUGSkin, 0, ("SkinChanger"), ("AUGSkin"));
	SetupValue(g_Options.Skinchanger.FAMASSkin, 0, ("SkinChanger"), ("FAMASSkin"));
	SetupValue(g_Options.Skinchanger.GalilSkin, 0, ("SkinChanger"), ("GalilSkin"));

	// Sniper
	SetupValue(g_Options.Skinchanger.AWPSkin, 0, ("SkinChanger"), ("AWPSkin"));
	SetupValue(g_Options.Skinchanger.SSG08Skin, 0, ("SkinChanger"), ("SSG08Skin"));
	SetupValue(g_Options.Skinchanger.SCAR20Skin, 0, ("SkinChanger"), ("SCAR20Skin"));
	SetupValue(g_Options.Skinchanger.G3SG1Skin, 0, ("SkinChanger"), ("G3SG1Skin"));

	// SMG
	SetupValue(g_Options.Skinchanger.P90Skin, 0, ("SkinChanger"), ("P90Skin"));
	SetupValue(g_Options.Skinchanger.UMP45Skin, 0, ("SkinChanger"), ("UMP45Skin"));
	SetupValue(g_Options.Skinchanger.MP7Skin, 0, ("SkinChanger"), ("MP7Skin"));
	SetupValue(g_Options.Skinchanger.MP9Skin, 0, ("SkinChanger"), ("MP9Skin"));
	SetupValue(g_Options.Skinchanger.Mac10Skin, 0, ("SkinChanger"), ("Mac10Skin"));
	SetupValue(g_Options.Skinchanger.BizonSkin, 0, ("SkinChanger"), ("BizonSkin"));

	// Pistols
	SetupValue(g_Options.Skinchanger.GlockSkin, 0, ("SkinChanger"), ("GlockSkin"));
	SetupValue(g_Options.Skinchanger.USPSkin, 0, ("SkinChanger"), ("USPSkin"));
	SetupValue(g_Options.Skinchanger.DeagleSkin, 0, ("SkinChanger"), ("DeagleSkin"));
	SetupValue(g_Options.Skinchanger.tec9Skin, 0, ("SkinChanger"), ("tec9Skin"));
	SetupValue(g_Options.Skinchanger.P2000Skin, 0, ("SkinChanger"), ("P2000Skin"));
	SetupValue(g_Options.Skinchanger.P250Skin, 0, ("SkinChanger"), ("P250Skin"));
	SetupValue(g_Options.Skinchanger.RevolverSkin, 0, ("SkinChanger"), ("RevolverSkin"));
	SetupValue(g_Options.Skinchanger.DualBerettasSkin, 0, ("SkinChanger"), ("DualBerettasSkin"));

	// Shotguns
	SetupValue(g_Options.Skinchanger.NovaSkin, 0, ("SkinChanger"), ("NovaSkin"));
	SetupValue(g_Options.Skinchanger.SawedOffSkin, 0, ("SkinChanger"), ("SawedOffSkin"));
	SetupValue(g_Options.Skinchanger.Mag7Skin, 0, ("SkinChanger"), ("Mag7Skin"));
	SetupValue(g_Options.Skinchanger.XM1014Skin, 0, ("SkinChanger"), ("XM1014Skin"));

	// MG
	SetupValue(g_Options.Skinchanger.NegevSkin, 0, ("SkinChanger"), ("NegevSkin"));
	SetupValue(g_Options.Skinchanger.M249Skin, 0, ("SkinChanger"), ("M249Skin"));

	// dLight
	SetupValue(g_Options.Visuals.dLightR, 0, ("Visuals"), ("dLightR"));
	SetupValue(g_Options.Visuals.dLightG, 0, ("Visuals"), ("dLightG"));
	SetupValue(g_Options.Visuals.dLightB, 0, ("Visuals"), ("dLightB"));

	// Colors

	// GUI
	SetupValue(g_Options.Colors.GUIText[0], 0.90f, ("Colors"), ("GUIText1"));
	SetupValue(g_Options.Colors.GUIText[1], 0.90f, ("Colors"), ("GUIText2"));
	SetupValue(g_Options.Colors.GUIText[2], 0.90f, ("Colors"), ("GUIText3"));

	SetupValue(g_Options.Colors.GUIButton[0], 0.54f, ("Colors"), ("GUIButton1"));
	SetupValue(g_Options.Colors.GUIButton[1], 0.54f, ("Colors"), ("GUIButton2"));
	SetupValue(g_Options.Colors.GUIButton[2], 0.54f, ("Colors"), ("GUIButton3"));

	SetupValue(g_Options.Colors.GUIButtonH[0], 0.54f, ("Colors"), ("GUIButtonH1"));
	SetupValue(g_Options.Colors.GUIButtonH[1], 0.54f, ("Colors"), ("GUIButtonH2"));
	SetupValue(g_Options.Colors.GUIButtonH[2], 0.54f, ("Colors"), ("GUIButtonH3"));

	SetupValue(g_Options.Colors.GUIButtonA[0], 0.67f, ("Colors"), ("GUIButtonA1"));
	SetupValue(g_Options.Colors.GUIButtonA[1], 0.67f, ("Colors"), ("GUIButtonA2"));
	SetupValue(g_Options.Colors.GUIButtonA[2], 0.67f, ("Colors"), ("GUIButtonA3"));

	SetupValue(g_Options.Colors.GUIHeader[0], 0.39f, ("Colors"), ("GUIHeader1"));
	SetupValue(g_Options.Colors.GUIHeader[1], 0.39f, ("Colors"), ("GUIHeader2"));
	SetupValue(g_Options.Colors.GUIHeader[2], 0.39f, ("Colors"), ("GUIHeader3"));

	SetupValue(g_Options.Colors.GUIHeaderH[0], 0.34f, ("Colors"), ("GUIHeaderH1"));
	SetupValue(g_Options.Colors.GUIHeaderH[1], 0.34f, ("Colors"), ("GUIHeaderH2"));
	SetupValue(g_Options.Colors.GUIHeaderH[2], 0.34f, ("Colors"), ("GUIHeaderH3"));

	SetupValue(g_Options.Colors.GUIHeaderA[0], 0.39f, ("Colors"), ("GUIHeaderA1"));
	SetupValue(g_Options.Colors.GUIHeaderA[1], 0.39f, ("Colors"), ("GUIHeaderA2"));
	SetupValue(g_Options.Colors.GUIHeaderA[2], 0.39f, ("Colors"), ("GUIHeaderA3"));

	SetupValue(g_Options.Colors.GUICheckmark[0], 0.39f, ("Colors"), ("GUICheckmark1"));
	SetupValue(g_Options.Colors.GUICheckmark[1], 0.39f, ("Colors"), ("GUICheckmark2"));
	SetupValue(g_Options.Colors.GUICheckmark[2], 0.39f, ("Colors"), ("GUICheckmark3"));

	SetupValue(g_Options.Colors.GUISlider[0], 0.65f, ("Colors"), ("GUISlider1"));
	SetupValue(g_Options.Colors.GUISlider[1], 0.65f, ("Colors"), ("GUISlider2"));
	SetupValue(g_Options.Colors.GUISlider[2], 0.65f, ("Colors"), ("GUISlider3"));

	/*SetupValue(g_Options.Colors.GUISliderActive[0], 0.65f, ("Colors"), ("GUISliderActive1"));
	SetupValue(g_Options.Colors.GUISliderActive[1], 0.65f, ("Colors"), ("GUISliderActive2"));
	SetupValue(g_Options.Colors.GUISliderActive[2], 0.65f, ("Colors"), ("GUISliderActive3"));*/

	SetupValue(g_Options.Colors.GUICombobg[0], 0.39f, ("Colors"), ("GUICombobg1"));
	SetupValue(g_Options.Colors.GUICombobg[1], 0.39f, ("Colors"), ("GUICombobg2"));
	SetupValue(g_Options.Colors.GUICombobg[2], 0.39f, ("Colors"), ("GUICombobg3"));

	SetupValue(g_Options.Colors.GUIWindow[0], 0.29f, ("Colors"), ("GUIWindow1"));
	SetupValue(g_Options.Colors.GUIWindow[1], 0.29f, ("Colors"), ("GUIWindow2"));
	SetupValue(g_Options.Colors.GUIWindow[2], 0.29f, ("Colors"), ("GUIWindow3"));

	SetupValue(g_Options.Colors.GUIFrame[0], 0.54f, ("Colors"), ("GUIFrame1"));
	SetupValue(g_Options.Colors.GUIFrame[1], 0.54f, ("Colors"), ("GUIFrame2"));
	SetupValue(g_Options.Colors.GUIFrame[2], 0.54f, ("Colors"), ("GUIFrame3"));

	SetupValue(g_Options.Colors.GUIScrollbar[0], 0.65f, ("Colors"), ("GUIScrollbar1"));
	SetupValue(g_Options.Colors.GUIScrollbar[1], 0.65f, ("Colors"), ("GUIScrollbar2"));
	SetupValue(g_Options.Colors.GUIScrollbar[2], 0.65f, ("Colors"), ("GUIScrollbar3"));

	SetupValue(g_Options.Colors.GUIScrollbarbg[0], 0.39f, ("Colors"), ("GUIScrollbarbg1"));
	SetupValue(g_Options.Colors.GUIScrollbarbg[1], 0.39f, ("Colors"), ("GUIScrollbarbg2"));
	SetupValue(g_Options.Colors.GUIScrollbarbg[2], 0.39f, ("Colors"), ("GUIScrollbarbg3"));

	SetupValue(g_Options.Colors.GUICheckmark[0], 1.f, ("Colors"), ("GUICheckmark1"));
	SetupValue(g_Options.Colors.GUICheckmark[1], 1.f, ("Colors"), ("GUICheckmark2"));
	SetupValue(g_Options.Colors.GUICheckmark[2], 1.f, ("Colors"), ("GUICheckmark3"));

	// Box Visible CT
	SetupValue(g_Options.Colors.espVisCT[0], 0.f, ("Colors"), ("espVisCT1"));
	SetupValue(g_Options.Colors.espVisCT[1], 0.f, ("Colors"), ("espVisCT2"));
	SetupValue(g_Options.Colors.espVisCT[2], 0.f, ("Colors"), ("espVisCT3"));
	// Box Invisible CT
	SetupValue(g_Options.Colors.espInvisCT[0], 0.f, ("Colors"), ("espInvisCT1"));
	SetupValue(g_Options.Colors.espInvisCT[1], 0.f, ("Colors"), ("espInvisCT2"));
	SetupValue(g_Options.Colors.espInvisCT[2], 0.f, ("Colors"), ("espInvisCT3"));

	// Box Visible T
	SetupValue(g_Options.Colors.espVisT[0], 0.f, ("Colors"), ("espVisT1"));
	SetupValue(g_Options.Colors.espVisT[1], 0.f, ("Colors"), ("espVisT2"));
	SetupValue(g_Options.Colors.espVisT[2], 0.f, ("Colors"), ("espVisT3"));
	// Box Invisible T
	SetupValue(g_Options.Colors.espInvisT[0], 0.f, ("Colors"), ("espInvisT1"));
	SetupValue(g_Options.Colors.espInvisT[1], 0.f, ("Colors"), ("espInvisT2"));
	SetupValue(g_Options.Colors.espInvisT[2], 0.f, ("Colors"), ("espInvisT3"));

	// Health
	SetupValue(g_Options.Colors.espDrawHealth[0], 0.f, ("Colors"), ("DrawHealth1"));
	SetupValue(g_Options.Colors.espDrawHealth[1], 0.f, ("Colors"), ("DrawHealth2"));
	SetupValue(g_Options.Colors.espDrawHealth[2], 0.f, ("Colors"), ("DrawHealth3"));
	// Armor
	SetupValue(g_Options.Colors.espDrawArmor[0], 0.f, ("Colors"), ("DrawArmor1"));
	SetupValue(g_Options.Colors.espDrawArmor[1], 0.f, ("Colors"), ("DrawArmor2"));
	SetupValue(g_Options.Colors.espDrawArmor[2], 0.f, ("Colors"), ("DrawArmor3"));
	// Backtrack
	SetupValue(g_Options.Colors.espDrawBacktrack[0], 0.f, ("Colors"), ("DrawBacktrack1"));
	SetupValue(g_Options.Colors.espDrawBacktrack[1], 0.f, ("Colors"), ("DrawBacktrack2"));
	SetupValue(g_Options.Colors.espDrawBacktrack[2], 0.f, ("Colors"), ("DrawBacktrack3"));
	// Bomb Font
	SetupValue(g_Options.Colors.espDrawBomb[0], 1.f, ("Colors"), ("DrawBomb1"));
	SetupValue(g_Options.Colors.espDrawBomb[1], 1.f, ("Colors"), ("DrawBomb2"));
	SetupValue(g_Options.Colors.espDrawBomb[2], 0.f, ("Colors"), ("DrawBomb3"));
	// Drop Font
	SetupValue(g_Options.Colors.espDrawDrop[0], 1.f, ("Colors"), ("DrawDrop1"));
	SetupValue(g_Options.Colors.espDrawDrop[1], 1.f, ("Colors"), ("DrawDrop2"));
	SetupValue(g_Options.Colors.espDrawDrop[2], 1.f, ("Colors"), ("DrawDrop3"));
	// Draw Glow Enemy
	SetupValue(g_Options.Colors.espDrawGlowEnemies[0], 0.f, ("Colors"), ("DrawGlowEnemies1"));
	SetupValue(g_Options.Colors.espDrawGlowEnemies[1], 0.f, ("Colors"), ("DrawGlowEnemies2"));
	SetupValue(g_Options.Colors.espDrawGlowEnemies[2], 0.f, ("Colors"), ("DrawGlowEnemies3"));
	// Draw Glow Alleys
	SetupValue(g_Options.Colors.espDrawGlowTeammates[0], 0.f, ("Colors"), ("DrawGlowTeammates1"));
	SetupValue(g_Options.Colors.espDrawGlowTeammates[1], 0.f, ("Colors"), ("DrawGlowTeammates2"));
	SetupValue(g_Options.Colors.espDrawGlowTeammates[2], 0.f, ("Colors"), ("DrawGlowTeammates3"));
	// Draw Weapon Glow
	SetupValue(g_Options.Colors.espDrawGlowWeapons[0], 0.f, ("Colors"), ("espDrawGlowWeapons1"));
	SetupValue(g_Options.Colors.espDrawGlowWeapons[1], 0.f, ("Colors"), ("espDrawGlowWeapons2"));
	SetupValue(g_Options.Colors.espDrawGlowWeapons[2], 0.f, ("Colors"), ("espDrawGlowWeapons3"));
	// Draw Skeleton
	SetupValue(g_Options.Colors.espDrawSkeleton[0], 0.f, ("Colors"), ("DrawSkeleton1"));
	SetupValue(g_Options.Colors.espDrawSkeleton[1], 0.f, ("Colors"), ("DrawSkeleton2"));
	SetupValue(g_Options.Colors.espDrawSkeleton[2], 0.f, ("Colors"), ("DrawSkeleton3"));
	// Draw aWall
	SetupValue(g_Options.Colors.espDrawAwall[0], 0.f, ("Colors"), ("DrawaWall1"));
	SetupValue(g_Options.Colors.espDrawAwall[1], 0.f, ("Colors"), ("DrawaWall2"));
	SetupValue(g_Options.Colors.espDrawAwall[2], 0.f, ("Colors"), ("DrawaWall3"));
	// Draw Chams Enemies
	SetupValue(g_Options.Colors.DrawChamsNigger[0], 1.f, ("Colors"), ("DrawChamsNigger1"));
	SetupValue(g_Options.Colors.DrawChamsNigger[1], 0.25f, ("Colors"), ("DrawChamsNigger2"));
	SetupValue(g_Options.Colors.DrawChamsNigger[2], 0.25f, ("Colors"), ("DrawChamsNigger3"));
	// Draw Chams Teammates
	SetupValue(g_Options.Colors.DrawChamsTeam[0], 0.25f, ("Colors"), ("DrawChamsTeam1"));
	SetupValue(g_Options.Colors.DrawChamsTeam[1], 0.25f, ("Colors"), ("DrawChamsTeam2"));
	SetupValue(g_Options.Colors.DrawChamsTeam[2], 1.f, ("Colors"), ("DrawChamsTeam3"));
	// Draw Hands
	SetupValue(g_Options.Colors.DrawHands[0], 1.f, ("Colors"), ("DrawHands1"));
	SetupValue(g_Options.Colors.DrawHands[1], 1.f, ("Colors"), ("DrawHands2"));
	SetupValue(g_Options.Colors.DrawHands[2], 1.f, ("Colors"), ("DrawHands3"));

	///////////////////////
	///// Angle Lines /////
	///////////////////////

	// Draw LBY Angle
	SetupValue(g_Options.Colors.espDrawLBYAngle[0], 1.f, ("Colors"), ("espDrawLBYAngle1"));
	SetupValue(g_Options.Colors.espDrawLBYAngle[1], 1.f, ("Colors"), ("espDrawLBYAngle2"));
	SetupValue(g_Options.Colors.espDrawLBYAngle[2], 0.2f, ("Colors"), ("espDrawLBYAngle3"));
	// Draw Real Angle
	SetupValue(g_Options.Colors.espDrawRealAngle[0], 0.2f, ("Colors"), ("espDrawRealAngle1"));
	SetupValue(g_Options.Colors.espDrawRealAngle[1], 1.f, ("Colors"), ("espDrawRealAngle2"));
	SetupValue(g_Options.Colors.espDrawRealAngle[2], 0.2f, ("Colors"), ("espDrawRealAngle3"));
	// Draw Fake Angle
	SetupValue(g_Options.Colors.espDrawFakeAngle[0], 1.f, ("Colors"), ("espDrawFakeAngle1"));
	SetupValue(g_Options.Colors.espDrawFakeAngle[1], 1.f, ("Colors"), ("espDrawFakeAngle2"));
	SetupValue(g_Options.Colors.espDrawFakeAngle[2], 0.2f, ("Colors"), ("espDrawFakeAngle3"));
}

void CConfig::SetupValue(int &value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue<int>(category, name, &value));
}

void CConfig::SetupValue(float &value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue<float>(category, name, &value));
}

void CConfig::SetupValue(bool &value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue<bool>(category, name, &value));
}

void CConfig::SaveLegit()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\Legit.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::LoadLegit()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\Legit.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

void CConfig::SaveLegit2()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\Legit2.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::LoadLegit2()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\Legit2.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

void CConfig::SaveLegit3()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\Legit3.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::LoadLegit3()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\Legit3.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

void CConfig::SaveHVH()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\HVH.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::LoadHVH()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\HVH.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

void CConfig::SaveHVH2()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\HVH2.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::LoadHVH2()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\HVH2.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

void CConfig::SaveHVH3()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\HVH3.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::LoadHVH3()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\HVH3.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

void CConfig::SaveCustom()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\Custom.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::LoadCustom()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\Custom.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

void CConfig::SaveCustom2()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\Custom2.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::LoadCustom2()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\Custom2.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

void CConfig::SaveCustom3()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\Custom3.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::LoadCustom3()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\insertcheatname\\";
		file = std::string(path) + "\\insertcheatname\\Custom3.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}


CConfig* Config = new CConfig();
Variables g_Options;