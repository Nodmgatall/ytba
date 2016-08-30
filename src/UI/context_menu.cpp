#include "context_menu.hpp"
#include "../urho3d_extensions/EntityNode.hpp"
#include <Urho3D/Core/CoreEvents.h>

ContextMenu::ContextMenu(EntityNode *node)
    : m_time_open(0.0), m_selected_node(node)
{
    SubscribeToEvent(Urho3D::E_UPDATE, URHO3D_HANDLER(ContextMenu, update));
}

void ContextMenu::update(Urho3D::StringHash event_type, Urho3D::VariantMap &event_data)
{
    m_time_open += event_data[Urho3D::Update::P_TIMESTEP].GetFloat();
}


