#include "AudioChannelControl.h"
#include "../Common.h"

#include <Geode/Geode.hpp>
#include <Geode/fmod/fmod.hpp>
#include <Geode/fmod/fmod_dsp_effects.h>

#include <Geode/modify/PlayLayer.hpp>
#include <Geode/binding/FMODAudioEngine.hpp>

using namespace geode::prelude;

FMOD_RESULT AudioChannelControl::setVolumeHook(FMOD::Channel* channel, float volume) {
    FMOD::Sound* sound = nullptr;
    channel->getCurrentSound(&sound);
    if (sound) {
        float freq = 0.f;
        sound->getDefaults(&freq, nullptr);
        channel->setFrequency(freq * speed);
    }
    return channel->setVolume(volume);
}

void AudioChannelControl::set(float frequency) {
    speed = frequency;

    FMOD::Channel* audioChannel = nullptr;
    auto system = FMODAudioEngine::sharedEngine()->m_system;

    for (int i = 0; i < 2; i++) {
        system->getChannel(126 + i, &audioChannel);
        if (audioChannel) {
            FMOD::Sound* sound = nullptr;
            audioChannel->getCurrentSound(&sound);
            if (sound) {
                float freq = 0.f;
                sound->getDefaults(&freq, nullptr);
                audioChannel->setFrequency(freq * frequency);
            }
        }
    }
}

void AudioChannelControl::setPitch(float pitch) {
    auto system = FMODAudioEngine::sharedEngine()->m_system;
    FMOD::ChannelGroup* group = nullptr;
    system->getMasterChannelGroup(&group);

    static FMOD::DSP* pitchShifter = nullptr;

    if (pitchShifter) {
        group->removeDSP(pitchShifter);
        pitchShifter->release();
        pitchShifter = nullptr;
    }

    if (pitch == 1.f)
        return;

    system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &pitchShifter);
    pitchShifter->setParameterFloat(FMOD_DSP_PITCHSHIFT_FFTSIZE, 4096);
    pitchShifter->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, pitch);
    group->addDSP(0, pitchShifter);
}

class $modify(PlayLayer_AudioChannelControl, PlayLayer) {
public:
    void resetLevel() {
        Common::onAudioSpeedChange();
        PlayLayer::resetLevel();
    }
};
