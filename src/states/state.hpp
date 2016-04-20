#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Engine/Application.h>

class GameState : public Urho3D::Object {
  public:
    std::vector<Urho3D::Node *> nodes;

    std::vector<Urho3D::UIElement *> ui_elements;

    GameState(Urho3D::Context *context) : Urho3D::Object(context) {
    }

    virtual ~GameState() {
        for (auto e : ui_elements) {
            e->Remove();
        }
        ui_elements.clear();

        for (auto n : nodes) {
            n->Remove();
        }
        nodes.clear();
    }

    virtual void Start() = 0;
    void HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);

    void HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);

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
