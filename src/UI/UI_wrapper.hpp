#ifndef UI_WRAPPER_HPP
#define UI_WRAPPER_HPP
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/ListView.h>
#include <Urho3D/UI/Menu.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/UI/CheckBox.h>
#include <memory>

#include <map>
#include <string>
class UIFactory {
  public:
    Urho3D::Context *m_context;
    Urho3D::Font *m_std_font;
    std::map<std::string, Urho3D::Font *> m_fonts;
    Urho3D::Color m_std_text_color;
    std::map<std::string, Urho3D::Color> m_text_colors;
    Urho3D::XMLFile *m_std_style;
    Urho3D::UIElement *m_root;
    UIFactory();
    UIFactory(Urho3D::Context *Context, Urho3D::Font *std_font, Urho3D::Color std_color,
              Urho3D::XMLFile *std_style, Urho3D::UIElement *root);

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
};
#endif
