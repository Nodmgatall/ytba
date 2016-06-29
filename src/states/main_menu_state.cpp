#include "main_menu_state.hpp"
#include "../UI/ui_manager.hpp"
#include "../events/state_events.hpp"
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/UIEvents.h>
MainMenuState::MainMenuState(Urho3D::Context *context) : GameState(context) {

    Urho3D::ResourceCache *cache = GetSubsystem<Urho3D::ResourceCache>();
    ui_factory =
        UIManager(context_, cache->GetResource<Urho3D::Font>("Fonts/Anonymous Pro.ttf", 20),
                  Urho3D::Color(), cache->GetResource<Urho3D::XMLFile>("UI/DefaultStyle.xml"),
                  GetSubsystem<Urho3D::UI>()->GetRoot());
    create_ui();
}

MainMenuState::~MainMenuState() {

    Stop();
    ui_elements.clear();
}

void MainMenuState::Start() {

    GetSubsystem<Urho3D::Input>()->SetMouseVisible(true);
    GetSubsystem<Urho3D::Input>()->SetMouseGrabbed(false);

    Urho3D::UIElement *root = GetSubsystem<Urho3D::UI>()->GetRoot();

    root->AddChild(ui_elements["Exit"]);
    root->AddChild(ui_elements["Start"]);
    root->AddChild(ui_elements["Options"]);

    subscribe_to_events();
}

void MainMenuState::Stop() {

    for (auto ui_element : ui_elements) {
        ui_element.second->Remove();
    }
}

void MainMenuState::subscribe_to_events() {
    SubscribeToEvent(ui_elements["Exit"], Urho3D::E_HOVERBEGIN,
                     URHO3D_HANDLER(MainMenuState, HandleOnHoverBegin));
}

void MainMenuState::unsubscribe_events() {
    UnsubscribeFromAllEvents();
}
void MainMenuState::create_ui() {

    int main_button_width = 600;
    int main_button_height = 40;
    ui_elements["Exit"] =
        ui_factory.create_button("Exit", 400, 400, main_button_width, main_button_height);

    ui_elements["Start"] =
        ui_factory.create_button("Start", 400, 100, main_button_width, main_button_height);

    ui_elements["Options"] =
        ui_factory.create_button("Options", 400, 350, main_button_width, main_button_height);
}

void MainMenuState::HandleOnHoverBegin(Urho3D::StringHash eventType,
                                       Urho3D::VariantMap &event_data) {
    Urho3D::UIElement *element = static_cast<Urho3D::UIElement *>(event_data["Element"].GetPtr());
    std::cout << element->GetName().CString() << std::endl;
}

void MainMenuState::HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data) {
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

void MainMenuState::HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data) {
}

void MainMenuState::HandleControlClicked(Urho3D::StringHash eventType,
                                         Urho3D::VariantMap &event_data) {
    // Query the clicked UI element.
    Urho3D::UIElement *clicked =
        static_cast<Urho3D::UIElement *>(event_data[Urho3D::UIMouseClick::P_ELEMENT].GetPtr());
    if (clicked) {
        Urho3D::String clicked_name = clicked->GetName();
        if (clicked_name == "Start") { // check if the quit button was clicked
            sendStateChangeEvent(CHANGE, GAMEMAIN);
        }
        if (clicked_name == "Options") {
            sendStateChangeEvent(PUSH, OPTIONS);
        }
    }
}

const Urho3D::TypeInfo *MainMenuState::GetTypeInfo() const {
    return GetTypeInfoStatic();
}

const Urho3D::String &MainMenuState::GetTypeName() const {
    return GetTypeInfo()->GetTypeName();
}
