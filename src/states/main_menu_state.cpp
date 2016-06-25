#include "main_menu_state.hpp"
#include "../UI/UI_wrapper.hpp"
#include "../events/state_events.hpp"
#include <Urho3D/UI/UIEvents.h>
MainMenuState::MainMenuState(Urho3D::Context *context) : GameState(context) {
}

MainMenuState::~MainMenuState() {

    std::cout << "deleting Main " << std::endl;
    for (auto button : buttons) {
        button.second->Remove();
    }
    buttons.clear();
    for (auto ui_element : ui_elements) {
        ui_element.second->Remove();
    }
    ui_elements.clear();
    for (auto text: texts) {
        text.second->Remove();
    }
    texts.clear();
}

void MainMenuState::Start() {

    GetSubsystem<Urho3D::Input>()->SetMouseVisible(true);
    GetSubsystem<Urho3D::Input>()->SetMouseGrabbed(false);

    buttons["exit"] = create_button(context_, "exit", "Button", 40, 40, 50, 50);

    buttons["start"] = create_button(context_, "start", "Button", 40, 40, 10, 10);

    GetSubsystem<Urho3D::UI>()->GetRoot()->AddChild(buttons["exit"]);
    GetSubsystem<Urho3D::UI>()->GetRoot()->AddChild(buttons["start"]);

    SubscribeToEvent(buttons["exit"], Urho3D::E_HOVERBEGIN,
                     URHO3D_HANDLER(MainMenuState, HandleOnHoverBegin));
}

void MainMenuState::HandleOnHoverBegin(Urho3D::StringHash eventType,
                                       Urho3D::VariantMap &event_data) {
    Urho3D::UIElement *element = static_cast<Urho3D::UIElement *>(event_data["Element"].GetPtr());
    std::cout << element->GetName().CString() << std::endl;
}

void MainMenuState::Stop() {
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
    if (clicked)
        if (clicked->GetName() == "start") { // check if the quit button was clicked
            sendStateChangeEvent(CHANGE, GAMEMAIN);
        }
}

const Urho3D::TypeInfo *MainMenuState::GetTypeInfo() const {
    return GetTypeInfoStatic();
}

const Urho3D::String &MainMenuState::GetTypeName() const {
    return GetTypeInfo()->GetTypeName();
}
