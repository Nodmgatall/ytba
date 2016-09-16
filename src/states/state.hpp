#ifndef STATE_HPP
#define STATE_HPP

#include "../events/state_events.hpp"
#include "../UI/ui_manager.hpp"
#include <vector>
#include <map>
#include <string>
#include <Urho3D/Graphics/Graphics.h>
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
    Urho3D::Node * m_ui_root;

    Urho3D::UI* m_ui;
    Urho3D::Graphics* m_graphics;

    UIManager ui_factory;

    std::map<std::string, Urho3D::SharedPtr<Urho3D::UIElement>> ui_elements;

    std::map<std::string, Urho3D::SharedPtr<Urho3D::UIElement>> ui_sub_roots;
    
    GameState(Urho3D::Context *context) : Urho3D::Object(context) {
        m_ui = GetSubsystem<Urho3D::UI>();
        m_graphics = GetSubsystem<Urho3D::Graphics>();
    }

    virtual ~GameState() {
            }

    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void unsubscribe_events() = 0;
    virtual void subscribe_to_events() = 0;

    virtual void HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data) = 0;

    virtual void HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data) = 0;
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
