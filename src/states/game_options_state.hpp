#ifndef GAME_OPTIONS_HPP
#define GAME_OPTIONS_HPP

#include "../events/state_events.hpp"
#include "state.hpp"
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Window.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>

class GameOptionsState : public GameState {
  public:

    std::map<std::string, Urho3D::Window*> windows;

    GameOptionsState(Urho3D::Context *context);
    ~GameOptionsState();
    void HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);
    void HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);
    void HandleControlClicked(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandleOnHoverBegin(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandleStartButtonReleased(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);
    void Start();
    void Stop();
    void create_ui();
    void unsubscribe_events();
    void subscribe_to_events();
    virtual const Urho3D::TypeInfo *GetTypeInfo() const;
    virtual const Urho3D::String &GetTypeName() const;

  private:
};

#endif
