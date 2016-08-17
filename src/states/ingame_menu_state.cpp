#include "ingame_menu_state.hpp"
#include "../UI/ui_manager.hpp"
#include "../events/state_events.hpp"
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/UIEvents.h>
IngameMenuState::IngameMenuState(Urho3D::Context *context) : GameState(context) {

    Urho3D::ResourceCache *cache = GetSubsystem<Urho3D::ResourceCache>();
    ui_factory =
        UIManager(context_, cache->GetResource<Urho3D::Font>("Fonts/Anonymous Pro.ttf", 20),
                  Urho3D::Color(), cache->GetResource<Urho3D::XMLFile>("UI/DefaultStyle.xml"),
                  GetSubsystem<Urho3D::UI>()->GetRoot());
    create_ui();
}

IngameMenuState::~IngameMenuState() {

    for (auto ui_element : ui_elements) {
        std::cout << "lol" << std::endl;
        ui_element.second->RemoveAllChildren();
        ui_element.second->Remove();
    }

    ui_elements.clear();
}

void IngameMenuState::Start() {

    GetSubsystem<Urho3D::Input>()->SetMouseVisible(true);
    GetSubsystem<Urho3D::Input>()->SetMouseGrabbed(false);

    Urho3D::UIElement *root = GetSubsystem<Urho3D::UI>()->GetRoot();

    root->AddChild(ui_elements["Buttons"]);

    subscribe_to_events();
}

void IngameMenuState::Stop() {

    for (auto ui_element : ui_elements) {
        ui_element.second->RemoveAllChildren();
        ui_element.second->Remove();
    }
}

void IngameMenuState::subscribe_to_events() {
}

void IngameMenuState::unsubscribe_events() {
    UnsubscribeFromAllEvents();
}
void IngameMenuState::create_ui() {

    int main_button_width = 600;
    int main_button_height = 40;

    ui_elements["Buttons"] = ui_factory.create_collum(75);
    ui_elements["Buttons"]->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);
    ui_elements["Buttons"]->SetDefaultStyle(ui_factory.m_std_style);

    Urho3D::UIElement *start_buttons_container = ui_factory.create_collum(30);
    ui_elements["Buttons"]->AddChild(start_buttons_container);
    {
        start_buttons_container->AddChild(
            ui_factory.create_button("Resume", main_button_width, main_button_height));
        start_buttons_container->AddChild(
            ui_factory.create_button("Save", main_button_width, main_button_height));
        start_buttons_container->AddChild(
            ui_factory.create_button("Load", main_button_width, main_button_height));
    }
    ui_elements["Buttons"]->AddChild(
        ui_factory.create_button("Options", main_button_width, main_button_height));
    ui_elements["Buttons"]->AddChild(
        ui_factory.create_button("Exit", main_button_width, main_button_height));
    ui_elements["Buttons"]->AddChild(
        ui_factory.create_button("Exit to Desktop", main_button_width, main_button_height));
}

void IngameMenuState::HandleOnHoverBegin(Urho3D::StringHash eventType,
                                       Urho3D::VariantMap &event_data) {
    Urho3D::UIElement *element = static_cast<Urho3D::UIElement *>(event_data["Element"].GetPtr());
    std::cout << element->GetName().CString() << std::endl;
}

void IngameMenuState::HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data) {
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

void IngameMenuState::HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data) {
}

void IngameMenuState::HandleControlClicked(Urho3D::StringHash eventType,
                                         Urho3D::VariantMap &event_data) {
    // Query the clicked UI element.
    Urho3D::UIElement *clicked =
        static_cast<Urho3D::UIElement *>(event_data[Urho3D::UIMouseClick::P_ELEMENT].GetPtr());
    if (clicked) {
        Urho3D::String clicked_name = clicked->GetName();
        if (clicked_name == "Resume") { // check if the quit button was clicked
            sendStateChangeEvent(POP);
        }
        if (clicked_name == "Options") {
            sendStateChangeEvent(PUSH, OPTIONS);
        }
        if (clicked_name == "Exit") {
            sendStateChangeEvent(EXIT);
        }
        if (clicked_name == "Exit to Desktop") {
            sendStateChangeEvent(EXIT_TO_DESKTOP);
        }
        if (clicked_name == "Load") {
            std::cout << "NOT IMPLEMENTED: Load Button" << std::endl;
        }
        if (clicked_name == "Save") {
            std::cout << "NOT IMPLEMENTED: Load Button" << std::endl;
        }
    }
}

const Urho3D::TypeInfo *IngameMenuState::GetTypeInfo() const {
    return GetTypeInfoStatic();
}

const Urho3D::String &IngameMenuState::GetTypeName() const {
    return GetTypeInfo()->GetTypeName();
}
