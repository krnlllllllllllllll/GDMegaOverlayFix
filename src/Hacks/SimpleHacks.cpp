#include "Common.h"
#include "Settings.hpp"

#include <Geode/Geode.hpp>
#include <Geode/modify/HardStreak.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(HardStreak) {
    void updateStroke(float dt) {
        if (Settings::get<bool>("player/trail/enabled", false)) {
            float trailSize = Settings::get<float>("player/trail/size", 1.f);
            MBO(float, this, 0x168) = trailSize;

            if (Settings::get<bool>("player/trail/color/enabled", false)) {
                float trailColor[3]{
                    Settings::get<float>("player/trail/color/r", 1.f),
                    Settings::get<float>("player/trail/color/g", 1.f),
                    Settings::get<float>("player/trail/color/b", 1.f)
                };

                this->setColor({
                    static_cast<GLubyte>(trailColor[0] * 255.f),
                    static_cast<GLubyte>(trailColor[1] * 255.f),
                    static_cast<GLubyte>(trailColor[2] * 255.f)
                });
            }
        }

        HardStreak::updateStroke(dt);
    }
};

class $modify(PlayLayer) {
public:
    struct Fields {
        Ref<geode::Patch> anticheatPatch;
    };

    void resetLevel() {
        bool instantComplete = Settings::get<bool>("level/instant_complete", false);

        if (instantComplete) {
            auto res = Mod::get()->patch(
                reinterpret_cast<void*>(base::get() + 0x2DDC03),
                { 0xEB, 0x53 }
            );

            if (res.isOk()) {
                m_fields->anticheatPatch = res.unwrap();
                m_fields->anticheatPatch->enable();
            }
        }

        PlayLayer::resetLevel();

        if (instantComplete && m_fields->anticheatPatch) {
            this->playPlatformerEndAnimationToPos({ 0.f, 105.f }, true);
            m_fields->anticheatPatch->disable();
        }
    }
};
