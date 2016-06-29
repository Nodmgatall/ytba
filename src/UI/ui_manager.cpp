
#include "../UI/ui_manager.hpp"
#include <Urho3D/UI/BorderImage.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/ListView.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/DropDownList.h>
#include <memory>
#include <vector>

UIManager::UIManager() {
}

UIManager::UIManager(Urho3D::Context *context, Urho3D::Font *std_font, Urho3D::Color std_color,
                     Urho3D::XMLFile *std_style, Urho3D::UIElement *root)
    : m_context(context), m_std_font(std_font), m_std_text_color(std_color), m_std_style(std_style),
      m_root(root) {
}

Urho3D::Button *UIManager::create_button(Urho3D::String name, int pos_x, int pos_y, int size_x,
                                         int size_y) {
    Urho3D::Button *new_button = new Urho3D::Button(m_context);
    new_button->SetName(name);
    new_button->SetStyle("Button");
    new_button->SetFixedSize(size_x, size_y);
    new_button->SetPosition(pos_x, pos_y);
    new_button->AddChild(create_text(name));

    return new_button;
}

Urho3D::Button *UIManager::create_button(Urho3D::String name, int size_x, int size_y) {
    Urho3D::Button *new_button = new Urho3D::Button(m_context);
    new_button->SetName(name);
    new_button->SetStyle("Button");
    new_button->AddChild(create_text(name));
    new_button->SetFixedSize(size_x, size_y);
    new_button->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_BOTTOM);

    return new_button;
}

Urho3D::Button *UIManager::create_button(Urho3D::String name, Urho3D::HorizontalAlignment h_align,
                                         Urho3D::VerticalAlignment v_align, int size_x,
                                         int size_y) {
    Urho3D::Button *new_button = new Urho3D::Button(m_context);
    new_button->SetName(name);
    new_button->SetStyleAuto();
    new_button->AddChild(create_text(name));
    new_button->SetFixedSize(size_x, size_y);
    new_button->SetAlignment(h_align, v_align);

    return new_button;
}

Urho3D::Text *UIManager::create_text(Urho3D::String text_string, Urho3D::Color color,
                                     Urho3D::HorizontalAlignment h_align,
                                     Urho3D::VerticalAlignment v_align, Urho3D::Font *font) {
    Urho3D::Text *new_text = new Urho3D::Text(m_context);
    new_text->SetText(text_string);
    new_text->SetStyleAuto();
    new_text->SetColor(color);
    new_text->SetAlignment(h_align, v_align);
    new_text->SetFont(font);

    return new_text;
}
Urho3D::Text *UIManager::create_text(Urho3D::String text_string, Urho3D::Color color,
                                     Urho3D::HorizontalAlignment h_align,
                                     Urho3D::VerticalAlignment v_align) {
    Urho3D::Text *new_text = new Urho3D::Text(m_context);

    new_text->SetText(text_string);
    new_text->SetStyleAuto();
    new_text->SetColor(color);
    new_text->SetAlignment(h_align, v_align);
    new_text->SetFont(m_std_font);

    return new_text;
}
Urho3D::Text *UIManager::create_text(Urho3D::String text_string, Urho3D::Font *font) {
    Urho3D::Text *new_text = new Urho3D::Text(m_context);
    new_text->SetText(text_string);
    new_text->SetStyleAuto();
    new_text->SetColor(Urho3D::Color(0, 0, 0));
    new_text->SetFont(font);

    return new_text;
}
Urho3D::Text *UIManager::create_text(Urho3D::String text_string) {
    Urho3D::Text *new_text = new Urho3D::Text(m_context);
    new_text->SetText(text_string);
    new_text->SetStyleAuto();
    new_text->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);
    new_text->SetColor(Urho3D::Color(1, 1, 1));
    new_text->SetFont(m_std_font);

    return new_text;
}

Urho3D::BorderImage *UIManager::create_border_image(Urho3D::String name, int x_pos, int y_pos,
                                                    int width, int height) {
    Urho3D::BorderImage *new_border_image = new Urho3D::BorderImage(m_context);
    new_border_image->SetName(name);
    new_border_image->SetStyle("Button");
    new_border_image->SetPosition(x_pos, y_pos);
    new_border_image->SetSize(width, height);
    return new_border_image;
}

Urho3D::BorderImage *UIManager::create_border_image(Urho3D::String name,
                                                    Urho3D::HorizontalAlignment h_align,
                                                    Urho3D::VerticalAlignment v_align, int width,
                                                    int height) {
    Urho3D::BorderImage *new_border_image = new Urho3D::BorderImage(m_context);
    new_border_image->SetName(name);
    new_border_image->SetStyle("Image");
    new_border_image->SetAlignment(h_align, v_align);
    new_border_image->SetSize(width, height);
    return new_border_image;
}

Urho3D::Window *UIManager::create_window(Urho3D::String name, Urho3D::HorizontalAlignment h_align,
                                         Urho3D::VerticalAlignment v_align, int width, int height) {
    Urho3D::Window *new_window = new Urho3D::Window(m_context);

    new_window->SetDefaultStyle(m_std_style);
    new_window->SetName(name);
    new_window->SetAlignment(h_align, v_align);
    new_window->SetStyleAuto();
    return new_window;
}

Urho3D::Menu *UIManager::create_menu(Urho3D::String name, Urho3D::HorizontalAlignment h_align,
                                     Urho3D::VerticalAlignment v_align, int width, int height) {
    Urho3D::Menu *new_menu = new Urho3D::Menu(m_context);
    new_menu->SetName(name);
    new_menu->SetStyleAuto();
    new_menu->SetAlignment(h_align, v_align);
    new_menu->SetSize(width, height);
    return new_menu;
}

Urho3D::ListView *UIManager::create_list_view(Urho3D::String name,
                                              Urho3D::HorizontalAlignment h_align,
                                              Urho3D::VerticalAlignment v_align, int width,
                                              int height) {
    Urho3D::ListView *new_menu = new Urho3D::ListView(m_context);
    new_menu->SetName(name);
    new_menu->SetStyleAuto();
    new_menu->SetAlignment(h_align, v_align);
    new_menu->SetSize(width, height);
    return new_menu;
}

Urho3D::UIElement *UIManager::create_option_text_pair(Urho3D::UIElement *option,
                                                      Urho3D::String text) {
    Urho3D::UIElement *option_text_pair = new Urho3D::UIElement(m_context);
    option_text_pair->SetDefaultStyle(m_std_style);
    option_text_pair->AddChild(create_text(text));
    option_text_pair->AddChild(option);
    option_text_pair->SetLayout(Urho3D::LM_HORIZONTAL, 5);

    return option_text_pair;
}
Urho3D::CheckBox *UIManager::create_check_box(Urho3D::String name) {
    Urho3D::CheckBox *check_box = new Urho3D::CheckBox(m_context);
    check_box->SetName(name);
    check_box->SetStyleAuto();
    return check_box;
}
Urho3D::UIElement *UIManager::create_collum(int spacing) {

    Urho3D::UIElement *collum = new Urho3D::UIElement(m_context);
    collum->SetLayout(Urho3D::LM_VERTICAL, spacing, Urho3D::IntRect(10, 10, 10, 10));
    collum->SetStyleAuto();
    return collum;
}

Urho3D::UIElement *UIManager::create_row(int spacing) {

    Urho3D::UIElement *row = new Urho3D::UIElement(m_context);
    row->SetLayout(Urho3D::LM_HORIZONTAL, spacing, Urho3D::IntRect(10, 10, 10, 10));
    row->SetStyleAuto();
    return row;
}
Urho3D::DropDownList *UIManager::create_drop_down_list(std::vector<Urho3D::UIElement *> items) {
    Urho3D::DropDownList *drop_down_list = new Urho3D::DropDownList(m_context);
    drop_down_list->SetFixedSize(125, 25);
    drop_down_list->SetStyleAuto();
    for (auto elem : items) {
        drop_down_list->AddItem(elem);
    }
    return drop_down_list;
}
Urho3D::DropDownList *UIManager::create_drop_down_list(int width, int height,
                                                    std::vector<Urho3D::UIElement *> items) {
    Urho3D::DropDownList *drop_down_list = new Urho3D::DropDownList(m_context);
    drop_down_list->SetFixedSize(125, 25);
    drop_down_list->SetStyleAuto();
    for (auto elem : items) {
        drop_down_list->AddItem(elem);
    }
    return drop_down_list;
}
