#ifndef CONTEXT_MENU_HPP
#define CONTEXT_MENU_HPP

#include "../urho3d_extensions/EntityNode.hpp"

#include <Urho3D/Core/Object.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/UI.h>

#include <iostream>
#include <string>
#include <vector>

class ContextMenu : Urho3D::Object {

  public:
    ContextMenu(EntityNode *node);

  private:
    bool is_something_selected();
    void update(Urho3D::StringHash event_type, Urho3D::VariantMap &event_data);
    float m_time_open;
    bool m_something_selected;
    int m_number_of_options;
    int m_button_dimensions;
    int m_angle_between_buttons;

    Urho3D::UI *m_ui;
    std::vector<Urho3D::Vector2> calculate_button_positions();
    EntityNode *m_selected_node;
    Urho3D::UIElement *m_context_menu_root;
    std::vector<Urho3D::Button *> m_buttons;
};

#endif
