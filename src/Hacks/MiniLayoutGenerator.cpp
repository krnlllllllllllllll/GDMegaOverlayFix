#include <Geode/Geode.hpp>
#include <Geode/ui/Layout.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class MiniLayoutGenerator : public CCLayer {
public:
    static MiniLayoutGenerator* create() {
        auto ret = new MiniLayoutGenerator();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init() override {
        if (!CCLayer::init()) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // Background
        auto bg = CCLayerColor::create({0, 0, 0, 120});
        this->addChild(bg);

        // Main layout container
        auto root = ui::VBox::create()
            ->setPadding(10)
            ->setGap(8)
            ->setID("mini-layout-root");

        // Title
        root->add(ui::Text::create("Mini Layout Generator", 24));

        // Position inputs
        root->add(ui::TextInput::create("X Position", "0")->setID("pos-x"));
        root->add(ui::TextInput::create("Y Position", "0")->setID("pos-y"));

        // Scale input
        root->add(ui::TextInput::create("Scale", "1")->setID("scale"));

        // Color picker (simple RGB)
        root->add(ui::TextInput::create("R", "255")->setID("col-r"));
        root->add(ui::TextInput::create("G", "255")->setID("col-g"));
        root->add(ui::TextInput::create("B", "255")->setID("col-b"));

        // Preview button
        root->add(ui::Button::create("Preview", [this] {
            previewObject();
        }));

        // Close button
        root->add(ui::Button::create("Close", [this] {
            this->removeFromParent();
        }));

        // Add layout to screen
        auto wrapper = ui::CenterLayout::create(root);
        wrapper->setContentSize(winSize);
        this->addChild(wrapper);

        return true;
    }

    void previewObject() {
        auto x = std::stof(ui::TextInput::get("pos-x")->getString());
        auto y = std::stof(ui::TextInput::get("pos-y")->getString());
        auto s = std::stof(ui::TextInput::get("scale")->getString());

        auto r = std::stoi(ui::TextInput::get("col-r")->getString());
        auto g = std::stoi(ui::TextInput::get("col-g")->getString());
        auto b = std::stoi(ui::TextInput::get("col-b")->getString());

        auto sprite = CCSprite::create("square.png");
        sprite->setPosition({x, y});
        sprite->setScale(s);
        sprite->setColor({(GLubyte)r, (GLubyte)g, (GLubyte)b});

        this->addChild(sprite, 999);
    }
};

class $modify(EditorUI_MiniLayoutButton, EditorUI) {
    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel)) return false;

        // Add a button to open the layout generator
        auto btn = CCMenuItemSpriteExtra::create(
            CCSprite::create("GJ_plusBtn_001.png"),
            this,
            menu_selector(EditorUI_MiniLayoutButton::openMiniLayout)
        );

        btn->setPosition({50, 50});
        this->m_buttonMenu->addChild(btn);

        return true;
    }

    void openMiniLayout(CCObject*) {
        auto layer = MiniLayoutGenerator::create();
        CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 999);
    }
};
