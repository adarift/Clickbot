#include "PlayLayer.hpp"

bool __fastcall Hooks::PlayLayer::hkPushButton(void* self, uintptr_t, int state, bool player) {
    if (m_enabled)
    {
		if (!Hooks::PlayLayer::inited)
		{
			FMOD::System_Create(&Clickbot::system);
			Clickbot::system->init(1024 * 2, FMOD_INIT_NORMAL, nullptr);
			inited = true;
		}
		
        std::string path = Clickbot::pickRandomClick();
		std::cout << path << std::endl;


        Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::clickSound);
        Clickbot::system->playSound(Clickbot::clickSound, nullptr, false, &Clickbot::clickChannel);
        Clickbot::system->update();
		
	
	
	}
    
	return pushButton(self, state, player);
}
bool __fastcall Hooks::PlayLayer::hkReleaseButton(void* self, uintptr_t, int state, bool player) {
    if (m_enabled)
    {
        std::string path = Clickbot::pickRandomRelease();
		std::cout << path << std::endl;


		Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::releaseSound);
        Clickbot::system->playSound(Clickbot::releaseSound, nullptr, false, &Clickbot::releaseChannel);
        Clickbot::system->update();
    }
	return releaseButton(self, state, player);
}

bool __fastcall Hooks::PlayLayer::hkInit(gd::PlayLayer* self, int edx, void* GJGameLevel) {
    m_inGame = true;


    
	return init(self, GJGameLevel);
}
void __fastcall Hooks::PlayLayer::hkOnQuit(gd::PlayLayer* self) {
    m_inGame = false;
	system("cls");
	return onQuit(self);
}

void Hooks::PlayLayer::initHooks() {
	size_t base = (size_t)GetModuleHandle(0);
	MH_CreateHook(
		(PVOID)(base + 0x01FB780),
		Hooks::PlayLayer::hkInit,
		(LPVOID*)&Hooks::PlayLayer::init
	);
	MH_CreateHook(
		(PVOID)(base + 0x111500),
		Hooks::PlayLayer::hkPushButton,
		(LPVOID*)&Hooks::PlayLayer::pushButton
	);
	MH_CreateHook(
		(PVOID)(base + 0x111660),
		Hooks::PlayLayer::hkReleaseButton,
		(LPVOID*)&Hooks::PlayLayer::releaseButton
	);
	MH_CreateHook(
		(PVOID)(base + 0x20D810),
		Hooks::PlayLayer::hkOnQuit,
		(LPVOID*)&Hooks::PlayLayer::onQuit
    );
}