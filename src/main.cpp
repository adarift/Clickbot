#include <iostream>
#include "includes.hpp"
#include "hk/PlayLayer.hpp"
#include "clickbot/Clickbot.hpp"

using namespace MegaHackExt;

bool Hooks::PlayLayer::m_inGame;
bool Hooks::PlayLayer::m_enabled;
bool Hooks::PlayLayer::m_PCNoiseEnabled;

namespace GUI
{
    Window *window = Window::Create("Clickbot");
    CheckBox *enabled = CheckBox::Create("Enabled");
    Label *version = Label::Create("Version: 1.0");
}



DWORD MainThread(LPVOID lpParam)
{
	/*
	AllocConsole();
	SetConsoleTitleA("Debug console");
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	*/
	GUI::enabled->setCallback([](CheckBox *obj, bool b) {Hooks::PlayLayer::m_enabled = b;});
    
    GUI::window->add(GUI::enabled);
    GUI::window->add(GUI::version);

	Client::commit(GUI::window);

    MH_Initialize();

    Hooks::PlayLayer::initHooks();

    MH_EnableHook(MH_ALL_HOOKS);
	

	return S_OK;
}

DWORD __stdcall DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0x1000, reinterpret_cast<LPTHREAD_START_ROUTINE>(&MainThread), NULL, 0, NULL);
		break;

	default:
		break;
	}

	return TRUE;
}