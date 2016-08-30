#ifndef COMPONENT_DRAWABLE
#define COMPONENT_DRAWABLE
#include "entityx/entityx.h"
#include <Urho3D/Core/Object.h>
#include <Urho3D/Graphics/Drawable.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <string>
#include <map>
struct test_comp : entityx::Component<test_comp> {
    Urho3D::Node *m_node;
    test_comp(Urho3D::Node *node) : m_node(node) {
    }
};



class TestSystem : public entityx::System<TestSystem> {
  public:
    void update(entityx::EntityManager &ent_mng, entityx::EventManager &evt,
                entityx::TimeDelta dt) override {
        entityx::ComponentHandle<test_comp> entity;
        int cnt = 0;
        for (entityx::Entity ent : ent_mng.entities_with_components(entity)) {
            (void)ent;
            cnt++;
        }
        std::cout << "Entity count: " << cnt << std::endl;
    };
};

#endif
