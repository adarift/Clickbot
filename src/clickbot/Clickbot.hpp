#ifndef __CLICKBOT_HPP
#define __CLICKBOT_HPP

#include "../includes.hpp"

namespace Clickbot
{
    std::string pickRandomClick();
    std::string pickRandomRelease();


    static inline FMOD::System* system;
    static inline FMOD::Channel* clickChannel;
    static inline FMOD::Sound* clickSound;
    static inline FMOD::Channel* releaseChannel;
    static inline FMOD::Sound* releaseSound;

}

#endif