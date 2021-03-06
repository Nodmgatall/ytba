#ifndef GAME_OPTIONS_HPP
#define GAME_OPTIONS_HPP

#include "../events/state_events.hpp"
#include "../options.hpp"
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
    std::map<std::string, Urho3D::Window *> windows;

    GameOptionsState(Urho3D::Context *context, std::unique_ptr<Options> const &options);
    ~GameOptionsState();
    void HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);
    void HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);
    void HandleControlClicked(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandleOnHoverBegin(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandleStartButtonReleased(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);
    void HandleCheckBoxClicked(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void Start();
    void Stop();
    void create_ui();
    void unsubscribe_events();
    void subscribe_to_events();
    void create_main_option_window();
    Urho3D::UIElement *setup_video_options();
    Urho3D::UIElement *setup_sound_options();
    void change_to_sound();
    void change_to_video();
    void discard_changes();
    void save_changes();
    std::unique_ptr<Options> const &m_options;
    virtual const Urho3D::TypeInfo *GetTypeInfo() const;
    virtual const Urho3D::String &GetTypeName() const;

  private:
};

#endif
