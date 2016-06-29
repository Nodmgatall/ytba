#ifndef STATE_HPP
#define STATE_HPP

#include "../events/state_events.hpp"
#include "../UI/ui_manager.hpp"
#include <vector>
#include <map>
#include <string>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Engine/Application.h>

#include <iostream>


class GameState : public Urho3D::Object {
  public:
    Urho3D::Node * m_state_root;

    UIManager ui_factory;

    std::map<std::string, Urho3D::SharedPtr<Urho3D::UIElement>> ui_elements;

    std::map<std::string, Urho3D::SharedPtr<Urho3D::Text>> texts;
    
    std::map<std::string, Urho3D::SharedPtr<Urho3D::Button>> buttons;

    GameState(Urho3D::Context *context) : Urho3D::Object(context) {
    }

    virtual ~GameState() {
            }

    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void unsubscribe_events() = 0;
    virtual void subscribe_to_events() = 0;

    virtual void HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data) = 0;

    virtual void HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data) = 0;
    void HandlePostUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandleRenderUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandlePostRenderUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandleEndFrame(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    virtual void HandleControlClicked(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData) = 0;
    
    void sendStateChangeEvent(int change_task, int state_type = -1)
    {
        Urho3D::VariantMap v_map;
        v_map[state_change::P_TASK] = change_task;
        v_map[state_change::P_STATE] = state_type;
        SendEvent(E_STATE_CHANGE, v_map);
    std::cout << "event send " << change_task << " "<< state_type<< std::endl;
    }
    
    virtual Urho3D::StringHash GetType() const {
        return GetTypename();
    };

    virtual Urho3D::StringHash GetBaseType() const {
        return GetTypename();
    };

    virtual const Urho3D::String &GetTypename() const {
        static Urho3D::String name("dummy_name");
        return name;
    }
};

#endif
