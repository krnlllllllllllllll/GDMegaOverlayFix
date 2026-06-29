#pragma once

#include <Geode/fmod/fmod.hpp>

namespace AudioChannelControl {
    inline float speed = 1.f;

    // Hook for adjusting volume + frequency
    FMOD_RESULT setVolumeHook(FMOD::Channel* channel, float volume);

    // Sets playback speed (frequency multiplier)
    void set(float frequency);

    // Applies pitch shifting DSP
    void setPitch(float pitch);
}
