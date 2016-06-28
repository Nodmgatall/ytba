#include "../UI/UI_wrapper.hpp"
#include "../events/state_events.hpp"
#include "main_game_state.hpp"
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

GameOptionsState::OptionState(Urho3D::Context *context) : GameState(context) {
    Urho3D::ResourceCache *cache = GetSubsystem<Urho3D::ResourceCache>();
    ui_factory = UIFactory(
        context_, cache->GetResource<Urho3D::Font>("Fonts/Anonymous Pro.ttf", 20), Urho3D::Color());
}

GameOptionsState::~OptionState() {

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

GameOptionsState::start() {
}

GameOptionsState::create_ui() {

    Urho3D::UIElement *resolutions = new Urho3D::DropDownList(context_);
    ui_elements["resolutions"] = resolutions;
    ui_elements["resolutions"]->AddItem(
        create_text(context_, "1920 x 1080", Urho3D::Color(1, 1, 1)));
    ui_elements["resolutions"]->AddItem(
        create_text(context_, "1600 x 1280", Urho3D::Color(1, 1, 1)));
    ui_elements["resolutions"]->AddItem(
        create_text(context_, "1800 x 1440", Urho3D::Color(1, 1, 1)));
    ui_elements["resolutions"]->AddItem(
        create_text(context_, "2048 x 1152", Urho3D::Color(1, 1, 1)));
    ui_elements["resolutions"]->AddItem(
        create_text(context_, "1900 x 1600", Urho3D::Color(1, 1, 1)));
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
