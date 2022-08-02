#ifndef __PLAYLAYER_HPP

#define __PLAYLAYER_HPP

#include "../includes.hpp"
#include "../clickbot/Clickbot.hpp"



namespace Hooks 
{
    namespace PlayLayer 
    {
        extern bool m_inGame;
        inline extern double releaseFix = -2;
        extern bool m_enabled;
        extern bool m_PCNoiseEnabled;

        extern double m_clickVolume;
        extern float m_PCNoiseVolume;

        inline extern bool inited = false;

        inline bool(__thiscall* init)(gd::PlayLayer* self, void* GJGameLevel);
        bool __fastcall hkInit(gd::PlayLayer* self, int edx, void* GJGameLevel);

        inline void(__thiscall* onQuit)(gd::PlayLayer* self);
	    void __fastcall hkOnQuit(gd::PlayLayer* self);

        inline bool(__thiscall* pushButton)(void* self, int state, bool player);
        bool __fastcall hkPushButton(void* self, uintptr_t, int state, bool player);

        inline bool(__thiscall* releaseButton)(void* self, int state, bool player);
        bool __fastcall hkReleaseButton(void* self, uintptr_t, int state, bool player);

        inline int(__thiscall* resetLevel)(void* self);
        int __fastcall hkReset(gd::PlayLayer* self);

        void initHooks();
    }
}

#endif