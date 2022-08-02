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

		Clickbot::now = std::chrono::system_clock::now();
		Clickbot::cycleTime = Clickbot::now - Clickbot::start;
		if (Clickbot::cycleTime.count() < 0.5f)
		{
			std::string path = Clickbot::pickRandomSoftClick();
			Clickbot::start = std::chrono::system_clock::now();
			std::cout << Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::clickSound);
		} else {
			std::string path = Clickbot::pickRandomClick();
			Clickbot::start = std::chrono::system_clock::now();
			Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::clickSound);
		}
		
        Clickbot::system->playSound(Clickbot::clickSound, nullptr, true, &Clickbot::clickChannel);
		Clickbot::clickChannel->setVolume((float)(m_clickVolume / 100));
		Clickbot::clickChannel->setPaused(false);
        Clickbot::system->update();
	}
    
	return pushButton(self, state, player);
}
bool __fastcall Hooks::PlayLayer::hkReleaseButton(void* self, uintptr_t, int state, bool player) {
    if (m_enabled)
    {
		if (releaseFix < 0)
		{
			releaseFix++;
			return releaseButton(self, state, player);
		} else {
			if (Clickbot::cycleTime.count() < 0.5f)
			{
				std::string path = Clickbot::pickRandomRelease();
				Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::releaseSound);
			} else {
				std::string path = Clickbot::pickRandomRelease();
				Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::releaseSound);
			}
			
			
			Clickbot::system->playSound(Clickbot::releaseSound, nullptr, true, &Clickbot::releaseChannel);
			Clickbot::releaseChannel->setVolume((float)(m_clickVolume / 100));
			Clickbot::releaseChannel->setPaused(false);
			Clickbot::system->update();
		}
    }
	return releaseButton(self, state, player);
}

bool __fastcall Hooks::PlayLayer::hkInit(gd::PlayLayer* self, int edx, void* GJGameLevel) {
    m_inGame = true;
	Clickbot::start = std::chrono::system_clock::now();
    
	return init(self, GJGameLevel);
}
void __fastcall Hooks::PlayLayer::hkOnQuit(gd::PlayLayer* self) {
    m_inGame = false;
	#ifdef CLICKBOT_DEVMODE
	system("cls");
	#endif
	releaseFix = -2;
	return onQuit(self);
}
int __fastcall Hooks::PlayLayer::hkReset(gd::PlayLayer* self) {
	releaseFix = -2;
	return resetLevel(self);
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
	MH_CreateHook(
		(PVOID)(base + 0x20BF00),
		Hooks::PlayLayer::hkReset,
		(LPVOID*)&Hooks::PlayLayer::resetLevel
	);
}