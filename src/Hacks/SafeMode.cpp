#include "SafeMode.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/binding/FMODAudioEngine.hpp>

#include "../Settings.hpp"
#include "../Common.h"

using namespace geode::prelude;
using namespace SafeMode;

class $modify(EndLevelLayer_SafeMode, EndLevelLayer) {
public:
    void customSetup() {
        EndLevelLayer::customSetup();

        if (
            !Settings::get<bool>("level/safe_mode/enabled") ||
            !Settings::get<bool>("level/safe_mode/endscreen_enabled")
        ) return;

        // EndLevelLayer children:
        // [0] = main content layer
        auto layer = static_cast<CCLayer*>(this->getChildren()->objectAtIndex(0));

        CCLabelBMFont* endScreenMessageLabel = nullptr;
        TextArea* endScreenTextArea = nullptr;

        CCObject* obj;
        CC
