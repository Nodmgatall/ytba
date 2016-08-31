#ifndef ENTITY_NODE_HPP
#define ENTITY_NODE_HPP

#include <Urho3D/Scene/Node.h>
#include "entityx/entityx.h"
#include "../components/component_test.hpp"

class EntityNode : public Urho3D::Node {
  public:
    EntityNode(Urho3D::Context *context, entityx::EntityManager *entity_manager) : Node(context) {
        m_entity = entity_manager->create();
        m_entity.assign<test_comp>(this);
    }

    ~EntityNode() {
        m_entity.destroy();
    }
    template <typename C, typename... args>
    entityx::ComponentHandle<C> assign(args... a) {
        return m_entity.assign<C>(a...);
    }
    
    entityx::Entity* get_entity()
    {
        return &m_entity;
    }     

  private:
    entityx::Entity m_entity;
};


#endif

