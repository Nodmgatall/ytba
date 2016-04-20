#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "state.hpp"
#include "Urho3D/Input/Input.h"
#include "Urho3D/Input/InputEvents.h"
#include "../events/state_events.hpp"

#include <iostream>

class MainMenuState : public GameState {
  public:
    MainMenuState(Urho3D::Context *context);
    void handleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);
    void handleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &evemt_data);
    void Start();
    void Delete();

};

#endif
