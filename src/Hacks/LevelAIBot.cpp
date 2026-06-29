#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class LevelAIBot {
public:
    // Simple heuristic: jump when close to an object
    bool shouldJump(PlayerObject* player, PlayLayer* layer) {
        auto pos = player->getPosition();
        float lookahead = 60.f; // distance ahead to scan

        CCArray* objs = layer->m_objects;
        CCObject* obj;
        CCARRAY_FOREACH(objs, obj) {
            auto gdObj = static_cast<GameObject*>(obj);
            auto objPos = gdObj->getPosition();

            if (objPos.x > pos.x && objPos.x < pos.x + lookahead) {
                // crude filter: spikes, saws, etc.
                if (gdObj->m_objectType == GameObjectType::Hazard ||
                    gdObj->m_objectType == GameObjectType::Slope) {
                    return true;
                }
            }
        }

        return false;
    }
};

static LevelAIBot g_bot;

class $modify(PlayLayer_AIBot, PlayLayer) {
public:
    void update(float dt) {
        PlayLayer::update(dt);

        // main player only for now
        auto player = this->m_player1;
        if (!player) return;

        // if bot thinks we should jump, press and hold
        if (g_bot.shouldJump(player, this)) {
            this->pushButton(PlayerButton::Jump);
        } else {
            this->releaseButton(PlayerButton::Jump);
        }
    }
};
