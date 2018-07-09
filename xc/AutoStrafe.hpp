#pragma once


#include "../CSGOMemes/ValveSDK/math/QAngle.hpp"
#include "../CSGOMemes/singleton.hpp"
#include "../CSGOMemes/ValveSDK/math/Vector.hpp"

class CUserCmd;
class C_BasePlayer;

QAngle GetAutostrafeView();

class auto_strafe
	: public singleton<auto_strafe>
{
public:
	void on_create_move(CUserCmd *pCmd, C_BasePlayer* local);
	void strafe(CUserCmd *pCmd, C_BasePlayer* local);
};