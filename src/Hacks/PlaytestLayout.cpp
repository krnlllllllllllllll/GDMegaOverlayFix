#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/ui/Layout.hpp>

using namespace geode::prelude;

class $modify(EditorUI_PlaytestLayout, EditorUI) {
    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel))
            return false;

        // Find Playtest button
        auto playBtn = this->getChildByID("play-test-button");
        if (playBtn) {
            playBtn->addClickCallback([this] {
                openLayoutBuilder();
            });
        }

        return true;
    }

    void openLayoutBuilder() {
        auto layer = ui::Layer::create();

        auto builder = ui::VBox::create()
            ->setPadding(10)
            ->setGap(8)
            ->setID("layout-builder");

        builder->add(ui::TextInput::create("X Position", Mod::get()->getSetting("layout-x")->get<float>()));
        builder->add(ui::TextInput::create("Y Position", Mod::get()->getSetting("layout-y")->get<float>()));
        builder->add(ui::TextInput::create("Scale", Mod::get()->getSetting("layout-scale")->get<float>()));

        builder->add(ui::Button::create("Save", [this] {
            Mod::get()->setSetting("layout-x", getInput("layout-x"));
            Mod::get()->setSetting("layout-y", getInput("layout-y"));
            Mod::get()->setSetting("layout-scale", getInput("layout-scale"));
        }));

        layer->addChild(builder);
        CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 999);
    }

    float getInput(const std::string& id) {
        auto input = ui::TextInput::get(id);
        return std::stof(input->getString());
    }
};
