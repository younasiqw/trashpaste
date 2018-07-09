#pragma once

extern void RenderInterface();

struct ColorP
{
public:
	const char* Name;
	float* Ccolor;

	ColorP(const char* name, float* color)
	{
		this->Name = name;
		this->Ccolor = color;
	}
};

struct Variables
{

	Variables()
	{

	}

	struct Ragebot_s
	{
		bool ResolverOverride;
		int ResolverOverrideKey;
		float ResolverOverrideSlider;
		bool MainSwitch;
		bool 	Enabled;
		bool 	AutoFire;
		float 	FOV;
		bool 	Silent;
		int KeyPress;
		int FakewalkKey;
		bool Fakewalk;
		bool bLbyBreaker;
		bool AimStep;
		bool AutoRevolver;
		bool Head;
		bool Stomach;
		bool Arms;
		bool Chest;
		bool Legs;
		bool LegitAA;
		int LegitAAReal;
		//AA Builder
		bool	BuilderAAs;
		bool	Jitter;
		bool	FJitter;
		bool	LBYBreaker;
		float	BuilderReal;
		float	BuilderFake;
		float	BuilderPitch;
		float	JitterRange;
		float	FJitterRange;


		bool	EnabledAntiAim;
		int		SubAATabs;
		bool	PreAAs;
		int		Pitch;
		int		YawTrue;
		int		YawFake;
		int		YawFakeMove;
		int		YawTrueMove;
		float	PitchAdder;
		float	YawTrueAdder;
		float	YawFakeAdder;
		float	YawFakeMoveAdder;
		float   YawTrueMoveAdder;
		bool    YawFakeMoveEnabled;
		bool	AtTarget;
		bool	Edge;
		bool	KnifeAA;
		bool FakeLag;
		float FakeLagAmt;
		bool fakelag_adaptive;
		bool KaJucktNicht = false;
		bool	rageBacktrack;
		int		rageBacktrackSlider;
		float	YawAdd;
		float	FYawAdd;
		bool ResolverMolver = false;

		/////////////
		bool RealCustomStaticRechts;
		bool RealCustomJitterRechts;
		bool RealCustomJitterLinks;
		bool RealCustomStaticLinks;

		float RealCustomStaticRechtsAngle;
		float RealCustomRechtsVonAngle;
		float RealCustomRechtsBisAngle;

		float RealCustomStaticLinksAngle;
		float RealCustomLinksVonAngle;
		float RealCustomLinksBisAngle;

		float LbyCustomLinks;
		float LbyCustomRechts;
		/////////////



		bool	FriendlyFire;
		int		Hitbox;
		int		Hitscan;
		float	Pointscale;
		bool	Multipoint;
		float	Multipoints;

		bool BoolFakewalk;
		int IntFakewalk;

		bool AntiRecoil;
		bool AutoWall;
		bool AutoStop;
		bool AutoCrouch;
		bool AutoScope;
		float MinimumDamage;
		//bool Hitchance;
		//float HitchanceAmount;
		float	MinimumDamageSniper;
		float	MinimumDamageScout;
		float	MinimumDamageAWP;
		float	MinimumDamageRifle;
		float	MinimumDamagePistol;
		bool LBYPrediction;
		float	MinimumDamageHeavy;
		float	MinimumDamageSmg;
		float	MinimumDamageRevolver;
		float	MinimumDamageShotgun;
		bool	Hitchance;
		float	HitchanceSniper;
		bool PitchResolver;
		float	HitchanceScout;
		float	HitchanceAWP;
		float	HitchancePistol;
		float	HitchanceRifle;
		float	HitchanceHeavy;
		float	HitchanceSmgs;
		float	HitchanceRevolver;
		bool InfoWindows;
		float	HitchanceShotgun;
		bool Resolver;
		int iResolver;
		bool Bruteforce;
		bool LbyFix;
		bool pResolver;
		bool FakeLagMoveOnly;
		bool AdvancedResolver;
		bool FakeLagFix;
		float LBYRightAdder;
		float LBYLeftAdder;
		bool JumpScout;
		bool playerlist;
		bool bBaimIfHP;
		float fBaimIfHP;
		int BAIMkey;

		float NasaSlider;
		bool ExtendBacktrack;
		float ExtendBacktrackValue;
		int NasaKey;
		bool NasaBool;
		bool NasaAlternative;
	} Ragebot;

	struct AntiAim
	{
		//bool MainSwitch;

		bool	EnabledAntiAim;
		int		Pitch;
		int		YawTrue;
		int		YawFake;
		bool	AtTarget;
		bool	Edge;
		int SwitchFakeRight;
		int SwitchFakeLeft;
		bool KnifeAA;
		float YawAdd;
		float FYawAdd;
		bool bFakeWalk;
		int iFakeWalkKey;
	} AntiAim;

	struct
	{
		bool MainSwitch;
		bool backtrack;
		bool LegitAA;
		int LegitAAType;
		int AimAssistHitbox;
		struct
		{
			bool 	Enabled;
			bool AutoPistol;
			bool	Resolver;

		} Aimbot;


		int MainKey = 1;
		float MainSmooth;
		float Mainfov;
		float main_random_smooth;
		float main_recoil_min;
		float main_recoil_max;
		float main_randomized_angle;



		int PistolKey = 1;
		float Pistolfov;
		float PistolSmooth;
		float pistol_random_smooth;
		float pistol_recoil_min;
		float pistol_recoil_max;
		float pistol_randomized_angle;
		int PistolHitbox;



		int SniperKey = 1;
		float Sniperfov;
		float SniperSmooth;
		float sniper_random_smooth;
		float sniper_recoil_min;
		float sniper_recoil_max;
		float sniper_randomized_angle;


		struct
		{
			bool	Enabled;
			float Delay;
			int Key;
			float hitchance;
			struct
			{
				bool Head;
				bool Arms;
				bool Chest;
				bool Stomach;
				bool Legs;
			} Filter;

		} Triggerbot;

	} Legitbot;

	struct
	{
		bool 	Enabled;

		bool SkeletonLocal;
		bool NameLocal;
		bool HPNumberLocal;
		bool HPLocal;
		bool APNumberLocal;
		bool APLocal;
		bool IsScopedLocal;
		bool HasDefuserLocal;
		bool AmmoBarLocal;
		bool HasHelmetLocal;
		bool HasHeavyArmorLocal;
		bool backtrackLocal;
		bool WeaponLocal;
		bool MoveTypeLocal;
		bool MoneyLocal;
		bool BoxLocal;

		bool Box;
		bool Name;
		bool HP;
		bool HPNumber;
		bool Weight;
		bool AP;
		bool APNumber;
		bool Weapon;
		bool Money;
		bool Info;
		bool Chams;
		bool ChamVis;
		bool WeaponChams;
		bool AmmoBar;
		bool ChamsInvis;
		bool Skeleton;
		int SkeletonColor;
		bool AimSpot;
		bool DLight;
		bool SpreadCrosshair;
		bool GrenadeTrajectory;
		bool SniperCrosshair;
		bool ShowHits;
		bool GrenadeESP;
		bool C4;
		bool IsScoped;
		bool HasDefuser;
		bool HasHelmet;
		bool HasGunGameImmunity;
		bool HasHeavyArmor;
		bool LBYInfo;
		bool DrawAwall;
		bool angleLines;

		bool bResolverESP;
		int iResolverESP = 0;

		bool Glow;

		bool NoVisualRecoil;
		int Hands;
		int Weapons;
		float FOVChanger;
		float viewmodelChanger;
		bool NoFlash;
		bool NoSmoke;
		bool FakeChams;
		bool Time;
		bool Watermark = true;
		bool backtrack;
		bool LBYIndicator;
		bool LBYIndicatorOS;
		bool C4Timer;
		bool DefuseTimer;
		bool Radar;
		bool RadarEngine;
		bool RadarSpoof;
		//int Radar;
		bool speclist2;

		bool AmbientColor;
		float AmbientRed;
		float AmbientGreen;
		float AmbientBlue;

		bool money;
		int BackTrackColor;
		bool Ammo;
		bool C4TimerScreen;
		float ViewPunch;
		float RecoilTracking;
		float LBYLaenge;
		float RealLaenge;
		float FakeLaenge;
		bool RecoilESP;

		bool C4World;
		bool WeaponsWorld;
		bool AmmoInClip;
		bool C4Planted;
		bool WeaponGlow;
		int WeaponMaterial;
		int KnifeMaterial;
		bool noscopeborder;
		bool Warnings;
		bool WireframeSmoke;
		bool ChromeModels;
		bool AngleText;
		bool LSDVision;
		bool GhostChams;
		int ChamsMaterial;
		bool MoveType;
		bool RemoveTextures;
		bool GrenadePrediction;

		float dLightR;
		float dLightB;
		float dLightG;
		bool OverrideScopedFOV;
		bool No3rdPersonXhair;
		float dLightRadius;

		struct
		{
			bool Players;
			bool EnemyOnly;
			bool LocalPlayer;
		} Filter;

		struct
		{
			struct
			{
				bool XQZ;
			} Filter;
		} ChamsMode;

		struct
		{
			bool Players;
			bool EnemyOnly;
			bool LocalPlayer;
			bool Weapons;
		} GlowFilter;

	} Visuals;

	struct
	{
		bool silentstealer;
		int ragequit;
		bool 	Bhop;
		bool 	AutoStrafe;
		float MinVel;
		int		AirStuckKey;
		int lagexploit;
		int lagexploitmultiplier = 3;
		float lagexploitvalue;
		float FakeLag;
		bool AdaptiveFakeLag;
		bool nightMode;
		int NameSpammer;
		bool NameChangerFix;
		int		ChatSpamMode;
		bool ClantagChanger;
		int ClanTagSpeed;
		bool syncclantag;
		bool clantag;
		int Clantag1337;
		int	iNameSpam;
		bool SpecList;
		bool FPSBooster;
		int SkyBoxChanger;
		bool EnableAutoBuyWeapons;
		int AutoBuyWeapons;
		bool namespam;
		bool spammer;
		int ThirdpersonKey = 0;
		bool ThirdPerson;
		bool Ranks;
		int AutoDefuse;
		bool Spam;
		bool isRecording;
		bool isReplaying;
		bool RecordPath;
		bool AutoAccept;
		bool SpoofConfirmation = false;
		bool animatedclantag = false;
		int  customtab;
		bool SkinChangerToggle = false;
		bool BuyLog;
		bool AutoPistol;
		bool RankReveal;
		bool Hitsound;
		int Hitsounds;
		int nightModeStyle;
		bool Hitmarker;
		bool ChatCrash;
		bool NoName;
		bool GamesenseMemeClantag;



	} Misc;
	struct
	{
		bool Enabled;
		int Knife;
		int gloves;
		int glovesskin;
		int KnifeSkin;
		int AK47Skin;
		int M4A1SSkin;
		int DualBerettasSkin;
		int M4A4Skin;
		int AUGSkin;
		int FAMASSkin;
		int AWPSkin;
		int SSG08Skin;
		int SCAR20Skin;
		int P90Skin;
		int UMP45Skin;
		int GlockSkin;
		int GalilSkin;
		int M249Skin;
		int Mac10Skin;
		int XM1014Skin;
		int NegevSkin;
		int NovaSkin;
		int SawedOffSkin;
		int BizonSkin;
		int Mag7Skin;
		int MP9Skin;
		int MP7Skin;
		int USPSkin;
		int DeagleSkin;
		int FiveSevenSkin;
		int G3SG1Skin;
		int RevolverSkin;
		int tec9Skin;
		int P2000Skin;
		int P250Skin;
		bool StatTrak;
		int STValue;
	} Skinchanger;

	struct
	{
		bool	Opened = false;
		int 	Key;
		bool	Ragebot = false;
		bool	Legitbot = false;
		bool	Visual = false;
		bool	Misc = false;
		int		ConfigFile = 0;
		int		Theme = 0;
		bool	Colors = false;
		int		iRageSubTab = 0; 
		int		iTab = -1;
	} Menu;

	struct
	{
		float espVisT[3] = { 0.9f, 0.2f, 0.2f };
		float espInvisT[3] = { 0.7f, 0.1f, 0.1f };
		float espVisCT[3] = { 0.9f, 0.2f, 0.2f };
		float espInvisCT[3] = { 0.7f, 0.1f, 0.1f };

		float espDrawGlowTeammates[3] = { 0.7f, 0.1f, 0.1f };
		float espDrawGlowEnemies[3] = { 0.7f, 0.1f, 0.1f };
		float espDrawGlowWeapons[3] = { 0.7f, 0.1f, 0.1f };

		float chamsPlyrTVis[3] = { 0.9f,0.4f,0.f };
		float chamsPlyrTInvis[3] = { 0.9f, 0.0f, 0.f };
		float chamsPlyrCTVis[3] = { 0.f,0.4f,0.9f };
		float chamsPlyrCTInvis[3] = { 0.f,0.0f,0.9f };

		float espDrawArmor[3] = { 0.4f, 0.2f, 1.f };
		float espDrawHealth[3] = { 1.f, 0.2f, 0.4f };
		float espDrawDrop[3] = { 0.9f, 0.2f, 0.2f };
		float espDrawBomb[3] = { 0.9f, 0.2f, 0.2f };
		float espDrawBacktrack[3] = { 0.9f, 0.2f, 0.2f };
		float espDrawSkeleton[3] = { 0.9f, 0.2f, 0.2f };
		float espDrawAwall[3] = { 0.9f, 0.2f, 0.2f };
		float DrawChamsNigger[3] = { 0.9f, 0.2f, 0.2f };
		float DrawChamsTeam[3] = { 0.9f, 0.2f, 0.2f };
		float DrawChamsEnemyVisible[3] = { 0.9f, 0.2f, 0.2f };
		float DrawChamsTeamVisible[3] = { 0.9f, 0.2f, 0.2f };
		float DrawWeapon[3] = { 0.9f, 0.2f, 0.2f };
		float DrawHands[3] = { 0.9f, 0.2f, 0.2f };

		float espDrawFakeAngle[3] = { 1.f, 0.2f, 0.2f };
		float espDrawRealAngle[3] = { 0.2f, 1.f, 0.2f };
		float espDrawLBYAngle[3] = { 1.f, 1.f, 0.2f };

		float GUIText[3] = { 0.90f, 0.90f, 0.90f };
		float GUIButton[3] = { 0.54f, 0.54f, 0.54f };
		float GUIButtonH[3] = { 0.54f, 0.54f, 0.54f };
		float GUIButtonA[3] = { 0.67f, 0.67f, 0.67f };
		float GUIWindow[3] = { 0.29f, 0.29f, 0.29f };
		float GUIFrame[3] = { 0.54f, 0.54f, 0.54f };
		float GUISlider[3] = { 0.65f, 0.65f, 0.65f };
		//float GUISliderActive[3] = { 0.65f, 0.65f, 0.65f };
		float GUICheckmark[3] = { 1.f, 1.f, 1.f };
		float GUISelectedT[3] = { 0.39f, 0.39f, 0.39f };
		float GUICombobg[3] = { 0.20f, 0.20f, 0.20f };
		float GUIHeader[3] = { 0.39f, 0.39f, 0.39f };
		float GUIHeaderH[3] = { 0.34f, 0.34f, 0.34f };
		float GUIHeaderA[3] = { 0.39f, 0.39f, 0.39f };
		float GUIScrollbar[3] = { 0.65f, 0.65f, 0.65f };
		float GUIScrollbarbg[3] = { 0.39f, 0.39f, 0.39f };

	} Colors;
};

extern Variables g_Options;