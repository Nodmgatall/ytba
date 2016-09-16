#include "context_menu.hpp"
#include "../components/component_terrain_type.hpp"
#include "../urho3d_extensions/EntityNode.hpp"
#include <glm/glm.hpp>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/UIEvents.h>
#include <iostream>

ContextMenu::ContextMenu(Urho3D::Context *context) : Urho3D::Object(context), m_time_open(0.0) {

    m_context_menu_root = GetSubsystem<Urho3D::UI>()->GetRoot();
    m_ui_manager = UIManager(context_, GetSubsystem<Urho3D::ResourceCache>(), m_context_menu_root);
    m_button_width = 30;
    m_button_height = 30;
}

void ContextMenu::subscribe_to_events() {

    SubscribeToEvent(Urho3D::E_UPDATE, URHO3D_HANDLER(ContextMenu, update));
    SubscribeToEvent(Urho3D::E_UIMOUSECLICK, URHO3D_HANDLER(ContextMenu, HandleControlClicked));
}

void ContextMenu::HandleControlClicked(Urho3D::StringHash eventType,
                                       Urho3D::VariantMap &eventData) {
    std::cout << "we are here LOL" << std::endl;
    Urho3D::UIElement *clicked =
        static_cast<Urho3D::UIElement *>(eventData[Urho3D::UIMouseClick::P_ELEMENT].GetPtr());
    if (clicked) {

        std::cout << "rofl" << std::endl;
        auto clicked_iter = m_ui_manager.m_task_map.find(clicked->GetName());
        if (clicked_iter != m_ui_manager.m_task_map.end()) {
            clicked_iter->second();
        }
    }
}

void ContextMenu::update(Urho3D::StringHash event_type, Urho3D::VariantMap &event_data) {
    m_time_open += event_data[Urho3D::Update::P_TIMESTEP].GetFloat();
}

std::vector<Urho3D::Vector2> ContextMenu::calculate_button_positions(int number_of_buttons) {

    std::vector<Urho3D::Vector2> results;

    double min_distance_to_center = 50;
    double degree_per_button = 360 / number_of_buttons;

    Urho3D::Vector2 start_vector =
        Urho3D::Vector2(0, min_distance_to_center);
    for (int i = 0; i < number_of_buttons; i++) {
        double cos_deg = cos(glm::radians(i * degree_per_button));
        double sin_deg = sin(glm::radians(i * degree_per_button));

        double result_x = start_vector.x_ * cos_deg - start_vector.y_ * sin_deg;
        double result_y = start_vector.x_ * sin_deg + start_vector.y_ * cos_deg;
        std::cout << sqrt(result_x * result_x + result_y * result_y) << " " << i *degree_per_button  <<std::endl;
        results.push_back(Urho3D::Vector2(result_x , result_y) - get_offset_to_center() );
    }
    return results;
}

Urho3D::Vector2 ContextMenu::get_offset_to_center() {
    return Urho3D::Vector2(m_button_width / 2, m_button_height / 2);
}

Urho3D::Button *ContextMenu::create_info_button() {
    Urho3D::Button *info_button = m_ui_manager.create_button("Info", m_button_width, m_button_height);
    m_ui_manager.add_task(info_button, [this]() {
        std::cout << "DUMMY: this should open the info menu" << std::endl;
        m_something_selected = true;
    });
    return info_button;
}

Urho3D::Button *ContextMenu::create_remove_button() {
    Urho3D::Button *remove_button = m_ui_manager.create_button("Remove", m_button_width, m_button_height);
    m_ui_manager.add_task(remove_button, [this]() {
        m_selected_node->Remove();
        m_something_selected = true;
        std::cout << "removing stuff " << std::endl;
    });
    return remove_button;
}

Urho3D::Button *ContextMenu::create_forbid_button() {
    Urho3D::Button *forbid_button = m_ui_manager.create_button("Forbid", m_button_width, m_button_height);
    m_ui_manager.add_task(forbid_button, [this]() {
        std::cout << "DUMMY: this node should now be forbidden to walk on" << std::endl;
        m_something_selected = true;
    });
    return forbid_button;
}

void ContextMenu::set_positions(int number_of_buttons) {
    std::vector<Urho3D::Vector2> positions = calculate_button_positions(number_of_buttons);
    for (unsigned long i = 0; i < positions.size(); i++) {
        m_buttons[i]->SetPosition(positions[i].x_ + m_pos.x_, positions[i].y_ + m_pos.y_);
        std::cout << "X: " << positions[i].x_ + m_pos.x_ << " Y: " << positions[i].y_ + m_pos.y_
                  << std::endl;
    }
}

void ContextMenu::add_nodes_to_ui() {
    for (auto button : m_buttons) {
        std::cout << button->GetName().CString() << std::endl;
        m_context_menu_root->AddChild(button);
    }
}

void ContextMenu::create_context_buttons(Urho3D::Node *node) {
    subscribe_to_events();
    m_selected_node = (EntityNode *)node;
    m_pos = GetSubsystem<Urho3D::UI>()->GetCursorPosition();
    int number_of_buttons = 1;
    m_buttons.push_back(create_info_button());
    std::cout << m_buttons.size() << "TSAFTWEASDAS" << std::endl;
    if (m_selected_node->get_entity()->has_component<terrain_type>()) {
        number_of_buttons += 2;
        m_buttons.push_back(create_remove_button());
        m_buttons.push_back(create_forbid_button());
    }
    set_positions(number_of_buttons);
    add_nodes_to_ui();
}

void ContextMenu::clear() {
    for (auto button : m_buttons) {
        button->Remove();
    }
    m_buttons.clear();
    UnsubscribeFromAllEvents();
}

bool ContextMenu::get_selection_status()
{
    return m_something_selected;
}

void ContextMenu::reset()
{
    clear();
    m_something_selected = false;
}

const Urho3D::TypeInfo *ContextMenu::GetTypeInfo() const {
    return GetTypeInfoStatic();
}

const Urho3D::String &ContextMenu::GetTypeName() const {
    return GetTypeInfo()->GetTypeName();
}
