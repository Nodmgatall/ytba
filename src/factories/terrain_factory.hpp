
#include "../sub_types/terrain_types.hpp"
#include "../urho3d_extensions//EntityNode.hpp"
#include "entityx/entityx.h"

#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
class TerrainFactory {
  private:
    Urho3D::Context *m_context;
    entityx::EntityManager *m_entity_manager;
    Urho3D::ResourceCache *m_cache;

  public:
    TerrainFactory(Urho3D::Context *context, entityx::EntityManager *entity_manager,
                   Urho3D::ResourceCache *cache)
        : m_context(context), m_entity_manager(entity_manager), m_cache(cache) {
    }

    EntityNode *create_stone_terrain(Urho3D::Vector3 pos) {
        EntityNode *new_node = new EntityNode(m_context, m_entity_manager);
        new_node->SetPosition(pos);
        Urho3D::StaticModel *boxObject = new_node->CreateComponent<Urho3D::StaticModel>();
        boxObject->SetModel(m_cache->GetResource<Urho3D::Model>("Models/Box.mdl"));

        boxObject->SetMaterial(m_cache->GetResource<Urho3D::Material>("Materials/Mushroom.xml"));
        boxObject->SetCastShadows(true);
        new_node->assign<terrain_type>("Stone", STONE);
        return new_node;
    }
};
