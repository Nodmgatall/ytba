#include "main_menu_state.hpp"

#include "../events/state_events.hpp"
MainMenuState::MainMenuState(Urho3D::Context *context) : GameState(context) {
}

void MainMenuState::handleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data) {
    int key = event_data[Urho3D::KeyDown::P_KEY].GetInt();

    Urho3D::VariantMap v;
    switch (key) {
    case Urho3D::KEY_ESC:
        v[state_change::P_TASK] = state_event_task::POP;
        SendEvent(E_STATE_CHANGE, v);
        break;
    default:
        std::cout << "key not set" << std::endl;
    }
}
void MainMenuState::handleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data) {
}

void MainMenuState::Start()
{

}
