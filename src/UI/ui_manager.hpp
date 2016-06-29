#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/CheckBox.h>
#include <Urho3D/UI/DropDownList.h>
#include <Urho3D/UI/ListView.h>
#include <Urho3D/UI/Menu.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Window.h>
#include <memory>

#include <functional>
#include <map>
#include <string>
#include <vector>
class UIManager {
  public:
    Urho3D::Context *m_context;
    Urho3D::Font *m_std_font;
    std::map<std::string, Urho3D::Font *> m_fonts;
    Urho3D::Color m_std_text_color;
    std::map<std::string, Urho3D::Color> m_text_colors;
    Urho3D::XMLFile *m_std_style;
    Urho3D::UIElement *m_root;
    std::map<Urho3D::String, std::function<void()>> m_task_map;
    std::map<Urho3D::String, Urho3D::UIElement*> m_sub_root_map;
    UIManager();
    UIManager(Urho3D::Context *Context, Urho3D::Font *std_font, Urho3D::Color std_color,
              Urho3D::XMLFile *std_style, Urho3D::UIElement *root);

    void add_task(Urho3D::UIElement *element, std::function<void()> func);
    Urho3D::UIElement *create_sub_root(Urho3D::String name,
                                              Urho3D::UIElement* parent); 
    Urho3D::Button *create_button(Urho3D::String name, int size_x, int size_y, int pos_x,
                                  int pos_y);

    Urho3D::Button *create_button(Urho3D::String name, int size_x, int size_y);

    Urho3D::Button *create_button(Urho3D::String name, Urho3D::HorizontalAlignment h_align,
                                  Urho3D::VerticalAlignment v_align, int size_x, int size_y);

    Urho3D::Text *create_text(Urho3D::String text_string, Urho3D::Color color,
                              Urho3D::HorizontalAlignment h_align,
                              Urho3D::VerticalAlignment v_align, Urho3D::Font *font);

    Urho3D::Text *create_text(Urho3D::String text_string, Urho3D::Color color,
                              Urho3D::HorizontalAlignment h_align,
                              Urho3D::VerticalAlignment v_align);

    Urho3D::Text *create_text(Urho3D::String text_string, Urho3D::Font *font);

    Urho3D::Text *create_text(Urho3D::String text_string);

    Urho3D::BorderImage *create_border_image(Urho3D::String name, int x_pos, int y_pos, int width,
                                             int height);

    Urho3D::BorderImage *create_border_image(Urho3D::String name,
                                             Urho3D::HorizontalAlignment h_align,
                                             Urho3D::VerticalAlignment v_align, int width,
                                             int height);
    Urho3D::Window *create_window(Urho3D::String name, Urho3D::HorizontalAlignment h_align,
                                  Urho3D::VerticalAlignment v_align, int width, int height);

    Urho3D::Menu *create_menu(Urho3D::String name, Urho3D::HorizontalAlignment h_align,
                              Urho3D::VerticalAlignment v_align, int width, int height);

    Urho3D::ListView *create_list_view(Urho3D::String name, Urho3D::HorizontalAlignment h_align,
                                       Urho3D::VerticalAlignment v_align, int width, int height);

    Urho3D::UIElement *create_option_text_pair(Urho3D::UIElement *option, Urho3D::String text);

    Urho3D::CheckBox *create_check_box(Urho3D::String name);

    Urho3D::UIElement *create_collum(int spaciing = 10);

    Urho3D::UIElement *create_row(int spacing = 10);

    Urho3D::DropDownList *create_drop_down_list(std::vector<Urho3D::UIElement *> items);
    Urho3D::DropDownList *create_drop_down_list(int width, int height,
                                                std::vector<Urho3D::UIElement *> items);
};
#endif
