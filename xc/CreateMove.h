#pragma once
#include "HookIncludes.h"
#include "Misc.h"
#include "MovementRecorder.h"
#include "RageBot.h"
#include "LegitBot.h"
#include "GrenadePrediction.h"
#include "LagComp.h"
#include "ESP.h"

using create_move_t = void(__thiscall *)(IBaseClientDLL *, int, float, bool);
QAngle qLastTickAngles = QAngle(0.0f, 0.0f, 0.0f);
void __stdcall CHLCreateMove(int sequence_number, float input_sample_frametime, bool active, bool& bSendPacket)
{
	static auto ofunc = hooks::client.get_original<create_move_t>(22);
	ofunc(g_CHLClient, sequence_number, input_sample_frametime, active);
	C_BaseEntity *local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	CInput::CUserCmd *cmd = g_Input->GetUserCmd(0, sequence_number);

	if (!cmd)
		return;

	if (!cmd->command_number)
		return;

	static float next_time = 0;
	static float ticksBetween = 1.125f;
	static float ticksBetween2 = 0.22f; // lby tick
	if (!Globals::ySwitch && local->IsAlive() && local->GetVelocity().Length2D() == 0)
	{

		float TickStuff = TICKS_TO_TIME(local->GetTickBase());

		Globals::shouldflip = false;

		bool moveFlip;

		if (next_time - TICKS_TO_TIME(local->GetTickBase()) > ticksBetween)
		{
			next_time = 0;
		}

		if (local->GetVelocity().Length2D() > 0.1)
		{
			moveFlip = true;
		}

		if (local->GetVelocity().Length2D() == 0 && !moveFlip)
		{
			if (TickStuff > next_time + ticksBetween)
			{
				next_time = TickStuff + TICKS_TO_TIME(1);
				Globals::shouldflip = true;
			}
		}
		else if (moveFlip && local->GetVelocity().Length2D() == 0)
		{
			if (TickStuff > next_time + ticksBetween2)
			{
				next_time = TickStuff + TICKS_TO_TIME(1);
				Globals::shouldflip = true;
				moveFlip = false;
			}
		}
	}

	CInput::CVerifiedUserCmd *verifiedCommands = *(CInput::CVerifiedUserCmd **)(reinterpret_cast< uint32_t >(g_Input) + 0xF0);
	CInput::CVerifiedUserCmd *verified = &verifiedCommands[sequence_number % 150];
	if (!verified)
		return;

	if (!local)
		return;
	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	backtracking->legitBackTrack(cmd, local);
	backtracking->rageBacktrack(cmd, local);



	RankReveal(cmd);

	misc::instance().OnCreateMove(cmd, local);
	legitbot::instance().OnCreateMove(cmd, local);
	ragebot::instance().OnCreateMove(cmd, bSendPacket);

	grenade_prediction::instance().Tick(cmd->buttons);

    if (local->GetVelocity().Length2D() < 1 && g_Options.Ragebot.FakeLagMoveOnly && g_Options.Ragebot.FakeLag || g_Options.Ragebot.FakeLagMoveOnly == false && g_Options.Ragebot.FakeLag == false || g_Options.Ragebot.FakeLag == false && g_Options.Ragebot.FakeLagMoveOnly)
    {
        if (!bSendPacket && g_Options.Ragebot.YawFake) qLastTickAngles = cmd->viewangles;
        else if (bSendPacket && !g_Options.Ragebot.YawFake) qLastTickAngles = cmd->viewangles;
    }
   
    if (g_Options.Ragebot.FakeLag && local->GetVelocity().Length2D() > 1 && g_Options.Ragebot.FakeLagMoveOnly || g_Options.Ragebot.FakeLag && g_Options.Ragebot.FakeLagMoveOnly == false)
    {
        bool GibtsNicht;
        //if (!bSendPacket && GibtsNicht) qLastTickAngles = cmd->viewangles;
       // else if (bSendPacket && !GibtsNicht) qLastTickAngles = cmd->viewangles;

		if (!bSendPacket && !Globals::ySwitch) qLastTickAngles = cmd->viewangles;
		else if (bSendPacket && Globals::ySwitch) qLastTickAngles = cmd->viewangles;
    }

	if (!sanitize_angles(cmd->viewangles))
		return;

	movementfix(oldAngle, cmd);
	clampMovement(cmd);

	verified->m_cmd = *cmd;
	verified->m_crc = cmd->GetChecksum();

	if (Globals::ySwitch) {
		Globals::FakeAngle = cmd->viewangles.y;
	}
	else {
		Globals::RealAngle = cmd->viewangles.y;
	}
}
#pragma warning(disable : 4409)
__declspec(naked) void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	__asm
	{
		PUSH	EBP
		MOV		EBP, ESP
		PUSH	EBX
		LEA		ECX, [ESP]
		PUSH	ECX
		PUSH	active
		PUSH	input_sample_frametime
		PUSH	sequence_number
		CALL	CHLCreateMove
		POP		EBX
		POP		EBP
		RETN	0xC
	}
}