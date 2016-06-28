#include "game_options_state.hpp"
#include "../UI/UI_wrapper.hpp"
#include "../events/state_events.hpp"
#include "state.hpp"

#include <Urho3D/Core/Context.h>

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Skybox.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>

#include <Urho3D/UI/DropDownList.h>
#include <Urho3D/UI/ListView.h>

GameOptionsState::GameOptionsState(Urho3D::Context *context) : GameState(context) {
    Urho3D::ResourceCache *cache = GetSubsystem<Urho3D::ResourceCache>();
    ui_factory =
        UIFactory(context_, cache->GetResource<Urho3D::Font>("Fonts/Anonymous Pro.ttf", 20),
                  Urho3D::Color(), cache->GetResource<Urho3D::XMLFile>("UI/DefaultStyle.xml"),
                  GetSubsystem<Urho3D::UI>()->GetRoot());
    create_ui();
}

GameOptionsState::~GameOptionsState() {

    for (auto button : buttons) {
        button.second->Remove();
    }
    buttons.clear();
    for (auto ui_element : ui_elements) {
        ui_element.second->Remove();
    }
    ui_elements.clear();
    for (auto text : texts) {
        text.second->Remove();
    }
    texts.clear();
}

void GameOptionsState::Start() {

    Urho3D::UIElement *root = GetSubsystem<Urho3D::UI>()->GetRoot();

    for (auto ui_element : ui_elements) {

        root->AddChild(ui_element.second);
    }

    for (auto ui_element : buttons) {
        root->AddChild(ui_element.second);
    }
    for (auto ui_element : windows) {
        root->AddChild(ui_element.second);
    }
}

void GameOptionsState::Stop() {
    // Urho3D::UIElement *root = GetSubsystem<Urho3D::UI>()->GetRoot();

    for (auto ui_element : windows) {
        ui_element.second->RemoveAllChildren();
        ui_element.second->Remove();
    }
}
void GameOptionsState::unsubscribe_events() {
}
void GameOptionsState::subscribe_to_events() {
}
void GameOptionsState::create_ui() {

    // creating ui part and subparts
    Urho3D::Window *option_main_window = ui_factory.create_window(
        "main_option_border", Urho3D::HA_CENTER, Urho3D::VA_CENTER, 700, 600);

    Urho3D::DropDownList *resolutions = new Urho3D::DropDownList(context_);
    Urho3D::UIElement *colum1 = new Urho3D::UIElement(context_);
    Urho3D::UIElement *colum2 = new Urho3D::UIElement(context_);
    Urho3D::UIElement *bottom_row = new Urho3D::UIElement(context_);
    Urho3D::UIElement *split = new Urho3D::UIElement(context_);

    // setting default for top level uielement so that all others
    // can acces the default style
    option_main_window->SetDefaultStyle(ui_factory.m_std_style);

    // setting element hierachie from top to bottom
    // important: do in right order and after setting default
    // otherwise the style will not be available vor all elements
    option_main_window->AddChild(split);
    option_main_window->AddChild(bottom_row);

    split->AddChild(colum1);
    split->AddChild(colum2);

    colum1->AddChild(
            ui_factory.create_option_text_pair(resolutions, "resolution"));
    colum1->AddChild(
        ui_factory.create_option_text_pair(ui_factory.create_check_box("Option1"), "description"));
    colum2->AddChild(
        ui_factory.create_option_text_pair(ui_factory.create_check_box("Option2"), "description"));
    colum2->AddChild(
        ui_factory.create_option_text_pair(ui_factory.create_check_box("VSync"), "enable VSync"));

    colum2->AddChild(
        ui_factory.create_option_text_pair(ui_factory.create_check_box("VSync"), "enable VSync"));
    bottom_row->AddChild(
        ui_factory.create_button("Save", Urho3D::HA_CENTER, Urho3D::VA_BOTTOM, 100, 25));
    // Setting all the things we want
    option_main_window->SetBorder(Urho3D::IntRect(10, 10, 10, 10));
    option_main_window->SetLayout(Urho3D::LM_VERTICAL, 25, Urho3D::IntRect(10, 10, 10, 10));
    option_main_window->SetStyleAuto();

    split->SetLayout(Urho3D::LM_HORIZONTAL, 10, Urho3D::IntRect(10, 10, 10, 10));
    split->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_BOTTOM);

    colum1->SetLayout(Urho3D::LM_VERTICAL, 10, Urho3D::IntRect(10, 10, 10, 10));
    colum2->SetLayout(Urho3D::LM_VERTICAL, 10, Urho3D::IntRect(10, 10, 10, 10));

    bottom_row->SetLayout(Urho3D::LM_HORIZONTAL, 10, Urho3D::IntRect(10, 10, 10, 10));
    bottom_row->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_BOTTOM);
    bottom_row->SetStyleAuto();

    resolutions->AddItem(ui_factory.create_text("1920 x 1080"));
    resolutions->AddItem(ui_factory.create_text("1600 x 1280"));
    resolutions->AddItem(ui_factory.create_text("1800 x 1440"));
    resolutions->AddItem(ui_factory.create_text("2048 x 1152"));
    resolutions->AddItem(ui_factory.create_text("1900 x 1600"));
    resolutions->SetFixedSize(125, 25);
    resolutions->SetStyleAuto();

    windows["main_option_window"] = option_main_window;
}
void GameOptionsState::HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData) {
}

void GameOptionsState::HandleControlClicked(Urho3D::StringHash eventType,
                                            Urho3D::VariantMap &eventData) {
    Urho3D::UIElement *clicked =
        static_cast<Urho3D::UIElement *>(eventData[Urho3D::UIMouseClick::P_ELEMENT].GetPtr());
    if (clicked) {
        if (clicked->GetName() == "A") {
            std::cout << "resolutions clicked" << std::endl;
        }
        if (clicked->GetName() == "B") {
            std::cout << "dbl clicked" << std::endl;
        }
    }
}
void GameOptionsState::HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data) {
    int key = event_data[Urho3D::KeyDown::P_KEY].GetInt();

    Urho3D::VariantMap v;
    switch (key) {
    case Urho3D::KEY_ESC:
        sendStateChangeEvent(POP);
        break;
    default:
        std::cout << "key not set" << std::endl;
    }
}

const Urho3D::TypeInfo *GameOptionsState::GetTypeInfo() const {
    return GetTypeInfoStatic();
}

const Urho3D::String &GameOptionsState::GetTypeName() const {
    return GetTypeInfo()->GetTypeName();
}
