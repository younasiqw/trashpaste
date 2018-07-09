#include "Hooks.h"
#include "Render.h"
#include "SDK.h"
#include "AntiLeak.h"
#include "recvproxy.h"
#include "Misc.h"
#include "Interfaces.h"
#include "Global.h"

bool unload;

bool on_dll_attach(void* base)
{
InitialiseInterfaces();
g_Netvars->GetNetvars();
g_Render->SetupFonts();
hooks::initialize();
hooks::SetupColors();
NetvarHook();

while (unload == false)
{
Sleep(1000);
}


UnloadProxy();
hooks::cleanup();

Sleep(2000);
FreeLibraryAndExitThread((HMODULE)base, 0);
}

bool on_dll_detach()
{
UnloadProxy();
hooks::cleanup();
return 1;
}

BOOL WINAPI DllMain(
_In_      HINSTANCE hinstDll,
_In_      DWORD     fdwReason,
_In_opt_	LPVOID    lpvReserved
)
{
switch (fdwReason) {
case DLL_PROCESS_ATTACH:
CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)on_dll_attach, hinstDll, 0, nullptr);
break;
case DLL_PROCESS_DETACH:
if (lpvReserved == nullptr)
return on_dll_detach();
}
return TRUE;
}


void CAntiLeak::ErasePE()
{
	char *pBaseAddr = (char*)GetModuleHandle(NULL);
	DWORD dwOldProtect = 0;
	VirtualProtect(pBaseAddr, 4096, PAGE_READWRITE, &dwOldProtect);
	ZeroMemory(pBaseAddr, 4096);
	VirtualProtect(pBaseAddr, 4096, dwOldProtect, &dwOldProtect);
}


























/*#include "Interfaces.h"
#include "Hooks.h"
#include "Render.h"
#include "SDK.h"

#include "recvproxy.h"
#include "Misc.h"

bool unload;

bool on_dll_attach(void* base)
{
    InitialiseInterfaces();
    g_Netvars->GetNetvars();
    g_Render->SetupFonts();
    hooks::initialize();
    NetvarHook();

    while (unload == false)
    {
        Sleep(1000);
    }


    UnloadProxy();
    hooks::cleanup();

    Sleep(2000);
    FreeLibraryAndExitThread((HMODULE)base, 0);
}

bool on_dll_detach()
{
    UnloadProxy();
    hooks::cleanup();
    return 1;
}

BOOL WINAPI DllMain(
    _In_      HINSTANCE hinstDll,
    _In_      DWORD     fdwReason,
    _In_opt_	LPVOID    lpvReserved
)
{
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)on_dll_attach, hinstDll, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        if (lpvReserved == nullptr)
            return on_dll_detach();
    }
    return TRUE;
}*/