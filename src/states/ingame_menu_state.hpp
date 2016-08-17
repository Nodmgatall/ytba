#ifndef INGAME_MENU_STATE_HPP
#define INGAME_MENU_STATE_HPP
#include "../events/state_events.hpp"
#include "state.hpp"
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/Container/Ptr.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>

class IngameMenuState : public GameState {
  public:
    std::map<std::string, Urho3D::SharedPtr<Urho3D::UIElement>> b_p;
    IngameMenuState(Urho3D::Context *context);
    ~IngameMenuState();
    void HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);
    void HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);
    void HandleControlClicked(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandleOnHoverBegin(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandleStartButtonReleased(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);
    void Start();
    void Stop();
    void create_ui();
    void subscribe_to_events();
    void unsubscribe_events();
    virtual const Urho3D::TypeInfo *GetTypeInfo() const;
    virtual const Urho3D::String &GetTypeName() const;

  private:
};

#endif
