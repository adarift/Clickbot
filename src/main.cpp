#include <iostream>
#include "includes.hpp"
#include "hk/PlayLayer.hpp"
#include "clickbot/Clickbot.hpp"

using namespace MegaHackExt;

bool Hooks::PlayLayer::m_inGame;
bool Hooks::PlayLayer::m_enabled;
bool Hooks::PlayLayer::m_PCNoiseEnabled;
double Hooks::PlayLayer::m_clickVolume;

namespace GUI
{
    Window *window = Window::Create("Clickbot");
    CheckBox *enabled = CheckBox::Create("Enabled");
	Spinner *volume = Spinner::Create(nullptr, "%");
    Label *version = Label::Create("Version: 1.1");
	Label *volumeLabel = Label::Create("Click volume");
}

void MH_CALL OnClickVolume(MegaHackExt::Spinner *obj, double value)
{
	if (value >= 201)
	{
		GUI::volume->set(200, false);
		Hooks::PlayLayer::m_clickVolume = value;
	} else if (value < 0)
	{
		GUI::volume->set(0, false);
		Hooks::PlayLayer::m_clickVolume = value;
	} else {
		Hooks::PlayLayer::m_clickVolume = value;
	}
}


DWORD MainThread(LPVOID lpParam)
{
	#ifdef CLICKBOT_DEVMODE
	AllocConsole();
	SetConsoleTitleA("Debug console");
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	#endif

	GUI::enabled->setCallback([](CheckBox *obj, bool b) {Hooks::PlayLayer::m_enabled = b;});
	GUI::volume->setCallback(OnClickVolume);
	GUI::volume->set(100, true);
	
	//GUI::PCNoise->setCallback([](CheckBox *obj, bool b) {Hooks::PlayLayer::m_PCNoiseEnabled = b;});
    
    GUI::window->add(GUI::enabled);
	GUI::window->add(HorizontalLayout::Create(GUI::volumeLabel, GUI::volume));
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