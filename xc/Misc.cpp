#include "Misc.h"
#include "Interfaces.h"
#include "Render.h"
#include <time.h>
#include "BaseClient.h"

bool mbspotteddefined = false;
DWORD m_bSpotted;
std::string animatedclantag;
int iLastTime;
bool bDone=false;
void misc::OnCreateMove(CInput::CUserCmd *cmd, C_BaseEntity *local)
{
	if (g_Options.Visuals.RadarEngine && g_Engine->IsInGame())
	{
		for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
		{
			if (!mbspotteddefined)
			{
				mbspotteddefined = true;
				m_bSpotted = NetVarManager->GetOffset("DT_BaseEntity", "m_bSpotted");
			}
			C_BaseEntity *entity = g_EntityList->GetClientEntity(i);
			if (entity && !entity->IsDormant())
			{
				*(char*)((DWORD)(entity)+m_bSpotted) = 1;
			}
		}
	}

    if (g_Options.Misc.Bhop && local->IsAlive())
    {
        if (cmd->buttons & IN_JUMP && !(local->GetMoveType() & MOVETYPE_LADDER))
        {

            int iFlags = local->GetFlags();
            if (!(iFlags & FL_ONGROUND))
                cmd->buttons &= ~IN_JUMP;
        }
    }

	if (g_Options.Misc.AutoStrafe)
		AutoStrafe(cmd, local);

	if (g_Options.Misc.AutoPistol)
		AutoPistol(cmd, local);

	if (g_Options.Misc.syncclantag)
	{
		switch (int(g_Globals->curtime * 2.4) % 27)
		{
			case 0: setclantag(XorStr("U")); break;
			case 1: setclantag(XorStr("U ")); break;
			case 2: setclantag(XorStr("U G")); break;
			case 3: setclantag(XorStr("U GA")); break;
			case 4: setclantag(XorStr("U GAY")); break;
			}
	}

	if (g_Options.Misc.clantag)
	{
		setclantag(XorStr("insertcheatname.com"));
	}

	switch (g_Options.Misc.Clantag1337)
	{
	case 1:
		setclantag(XorStr(""));
		break;
	case 2:
		setclantag(XorStr("[ADMIN]"));
		break;
	case 3:
		setclantag(XorStr("[OWNER]"));
		break;
	case 4:
		setclantag(XorStr("TRAITOR"));
		break;
	case 5:
		setclantag(XorStr("INNOCENT"));
		break;
	}

	if (g_Options.Misc.GamesenseMemeClantag)
	{
		switch (int(g_Globals->curtime * 2.4) % 27)
		{
		case 0:setclantag(XorStr("              ga")); break;
		case 1:setclantag(XorStr("            game")); break;
		case 2:setclantag(XorStr("          gamesn")); break;
		case 3:setclantag(XorStr("        gamesnak")); break;
		case 4:setclantag(XorStr("       gamesnake")); break;
		case 5:setclantag(XorStr("      gamesnake ")); break;
		case 6:setclantag(XorStr("     gamesnake  ")); break;
		case 7:setclantag(XorStr("    gamesnake   ")); break;
		case 8:setclantag(XorStr("    gamesnake   ")); break;
		case 9:setclantag(XorStr("    gamesnake   ")); break;
		case 10:setclantag(XorStr("   gamesnake    ")); break;
		case 11:setclantag(XorStr("  gamesnake     ")); break;
		case 12:setclantag(XorStr(" gamesnake      ")); break;
		case 13:setclantag(XorStr("gamesnake       ")); break;
		case 14:setclantag(XorStr("mesnake         ")); break;
		case 15:setclantag(XorStr("snake           ")); break;
		case 16:setclantag(XorStr("ake             ")); break;
		case 17:setclantag(XorStr("e               ")); break;
		case 18:setclantag(XorStr("                ")); break;
		}
	}


    if (!g_Options.Misc.animatedclantag && animatedclantag.c_str() != G::AnimatedClantag)
    {
        animatedclantag = G::AnimatedClantag;
    }
    if (g_Options.Misc.animatedclantag && animatedclantag.length() > 1)
    {
        if (int(g_Globals->curtime) != iLastTime)
        {
            auto length = animatedclantag.length();
            animatedclantag.insert(0, 1, animatedclantag[length - 2]);
            animatedclantag.erase(length - 1, 1);

            setclantag(animatedclantag.c_str());
            iLastTime = int(g_Globals->curtime);
        }
    }

	if (g_Options.Misc.iNameSpam)
	{
		if (!(g_Engine->IsConnected() && g_Engine->IsInGame()))
			return;
		int NameSpam = g_Options.Misc.iNameSpam;
		switch (NameSpam)
		{
			static bool Spam;

		case 0:
			return;
			break;
		case 1:
				SetName("insertcheatname.com-");
				SetName("-insertcheatname.com");
				SetName("insertcheatname.com-");
				SetName("-insertcheatname.com");
				SetName("insertcheatname.com-");
				SetName("-insertcheatname.com");
				SetName("insertcheatname.com-");
				SetName("-insertcheatname.com");
				SetName("insertcheatname.com-");
		case 2:
			if (Spam)
			{
				SetName(" ™\n™\n™\n™\n™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™ ");
				Spam = false;
			}
			else
			{
				SetName("™\n™\n™\n™\n™\n™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™ ");
				Spam = true;
			}
			Spam != Spam;
			break;
		case 3:
			if (Spam)
			{
				SetName("---------------------------/-------------------------/----------------------insertcheatname--------------/--------------------/------------------------------");
					Spam = false;
			}
			else
			{
				SetName("---------------------------/-------------------------/----------------------insertcheatname--------------/--------------------/------------------------------");
				Spam = true;
			}
			Spam != Spam;
			break;
		case 4:
			if (Spam)
			{
				SetName("™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n");
				Spam = false;
			}
			else
			{
				SetName("™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n™\n");
				Spam = true;
			}
			Spam != Spam;
			break;
		}

		}
	if (g_Options.Misc.NoName)
	{
		static ConVar* name = g_CVar->FindVar("name");
		if (name)
		{
			*(int*)((DWORD)&name->fnChangeCallback + 0xC) = NULL;
			name->SetValue("\n­­­");
		}
	}

    if (g_Options.Misc.namespam)
    {
        char name[151];
        char fucked_char = static_cast<char>(-1);
        for (auto i = 0; i <= 150; i++)
            name[i] = fucked_char;

        const char nick[14] = "ugay";
        memcpy(name, nick, 14);

        SetName(name);
    }
    static size_t lastTime = 0;
    static int counter = 0;
    if (GetTickCount() > lastTime)
    {

        counter = counter + 1;
        if (counter > 5)
            counter = 0;
        if (g_Options.Misc.spammer)
        {
            SayInChat(xanList[counter]);
        }

        lastTime = GetTickCount() + 850;


    }

    if(g_Options.Misc.silentstealer)
    {
        bool bDidMeme = false;
        int iNameIndex = -1;
        char chName[130];
        static ConVar* name = g_CVar->FindVar("name");
        {
            for (int iPlayerIndex = 0; iPlayerIndex < g_Engine->GetMaxClients(); iPlayerIndex++)
            {
                C_BaseEntity *pEntity = g_EntityList->GetClientEntity(iPlayerIndex);
                if (!pEntity || pEntity == local || iPlayerIndex == g_Engine->GetLocalPlayer())
                    continue;
                if (rand() % 3 == 1)
                {
                    iNameIndex = pEntity->GetIndex();
                    bDidMeme = true;
                }
            }
            if (bDidMeme)
            {
                player_info_t pInfo;
                g_Engine->GetPlayerInfo(iNameIndex, &pInfo);
                sprintf(chName, "%s ", pInfo.name);
                name->SetValue(chName);
            }
        }
    }
}

void misc::AutoPistol(CInput::CUserCmd *pCmd, C_BaseEntity *local)
{
	C_BaseEntity* pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
	// Auto Pistol
	static bool WasFiring = false;
	if (pWeapon != nullptr)
	{
		if (MiscFunctions::IsPistol(pWeapon) && g_Options.Misc.AutoPistol && pWeapon->m_AttributeManager()->m_Item()->GetItemDefinitionIndex() != 64)
		{
			if (pCmd->buttons & IN_ATTACK && !MiscFunctions::IsKnife(pWeapon) && !MiscFunctions::IsGrenade(pWeapon))
			{
				if (WasFiring)
				{
					pCmd->buttons &= ~IN_ATTACK;
				}
			}

			WasFiring = pCmd->buttons & IN_ATTACK ? true : false;
		}
	}
}


void misc::AutoStrafe(CInput::CUserCmd *cmd, C_BaseEntity *local)
{

	QAngle oldangles; g_Engine->GetViewAngles(oldangles);
	static float move = 450;
	float s_move = move * 0.5065f;
	if (local->GetMoveType() & (MOVETYPE_NOCLIP | MOVETYPE_LADDER))
		return;
	if (cmd->buttons & (IN_FORWARD | IN_MOVERIGHT | IN_MOVELEFT | IN_BACK))
		return;

	if (cmd->buttons & IN_JUMP || !(local->GetFlags() & FL_ONGROUND))
	{
		cmd->forwardmove = move * 0.015f;
		cmd->sidemove += (float)(((cmd->tick_count % 2) * 2) - 1) * s_move;

		if (cmd->mousedx)
			cmd->sidemove = (float)clamp(cmd->mousedx, -1, 1) * s_move;

		static float strafe = cmd->viewangles.y;

		float rt = cmd->viewangles.y, rotation;
		rotation = strafe - rt;

		if (rotation < FloatNegate(g_Globals->interval_per_tick))
			cmd->sidemove = -s_move;

		if (rotation > g_Globals->interval_per_tick)
			cmd->sidemove = s_move;

		strafe = rt;
	}
	movementfix(oldangles, cmd);
}
