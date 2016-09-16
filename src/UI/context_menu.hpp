#ifndef CONTEXT_MENU_HPP
#define CONTEXT_MENU_HPP

#include "../urho3d_extensions/EntityNode.hpp"
#include "ui_manager.hpp"

#include <Urho3D/Core/Object.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/UI.h>

#include <iostream>
#include <string>
#include <vector>

class ContextMenu : public Urho3D::Object {

  public:
    ContextMenu(Urho3D::Context *context);
    void create_context_buttons(Urho3D::Node *node);
    void clear();
    bool get_selection_status();
    void reset();

  private:
    bool is_something_selected();
    void update(Urho3D::StringHash event_type, Urho3D::VariantMap &event_data);
    void HandleControlClicked(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void  subscribe_to_events();
    float m_time_open;
    bool m_something_selected;
    int m_number_of_options;
    int m_button_dimensions;
    int m_angle_between_buttons;

    int m_button_width;
    int m_button_height;

    UIManager m_ui_manager;
    Urho3D::UI *m_ui;

    std::vector<Urho3D::Vector2> calculate_button_positions(int number_of_buttons);
    EntityNode *m_selected_node;
    Urho3D::UIElement *m_context_menu_root;
    std::vector<Urho3D::Button *> m_buttons;
    Urho3D::IntVector2 m_pos;
    Urho3D::Vector2 get_offset_to_center();
    Urho3D::Button *create_info_button();
    Urho3D::Button *create_remove_button();
    Urho3D::Button *create_forbid_button();
    void set_positions(int number_of_buttons);

    void add_nodes_to_ui();

    const Urho3D::TypeInfo *GetTypeInfo() const;
    const Urho3D::String &GetTypeName() const;
    Urho3D::StringHash GetType() const {
        return GetTypeName();
    };
};

#endif
