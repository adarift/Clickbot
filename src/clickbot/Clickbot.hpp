#ifndef __CLICKBOT_HPP
#define __CLICKBOT_HPP

#include "../includes.hpp"

namespace Clickbot
{
    std::string pickRandomClick();
    std::string pickRandomRelease();

    std::string pickRandomSoftClick();
    std::string pickRandomSoftRelease();

    static inline bool firstClick = false;
    static inline std::chrono::system_clock::time_point start, now;
    static inline std::chrono::duration<double> cycleTime;

    static inline FMOD::System* system;
    static inline FMOD::Channel* clickChannel;
    static inline FMOD::Sound* clickSound;
    static inline FMOD::Channel* releaseChannel;
    static inline FMOD::Sound* releaseSound;

    static inline FMOD::Channel* noiseChannel;
    static inline FMOD::Sound* noiseSound;
}

#endif