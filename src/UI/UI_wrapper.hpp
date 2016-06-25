#ifndef UI_WRAPPER_HPP
#define UI_WRAPPER_HPP

#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Text.h>
#include <memory>

inline static Urho3D::Button *create_button(Urho3D::Context *context, Urho3D::String name,
                                     Urho3D::String style, int size_x, int size_y, int pos_x,
                                     int pos_y) {
    Urho3D::Button *new_button = new Urho3D::Button(context);
    new_button->SetName(name);
    new_button->SetStyle(style);
    new_button->SetSize(size_x, size_y);
    new_button->SetPosition(pos_x, pos_y);

    return new_button;
}

inline static Urho3D::Button *create_button(Urho3D::Context *context, Urho3D::String name,
                                     Urho3D::String style, int size_x, int size_y) {
    Urho3D::Button *new_button = new Urho3D::Button(context);
    new_button->SetName(name);
    new_button->SetStyle(style);
    new_button->SetSize(size_x, size_y);

    return new_button;
}

inline static Urho3D::Text *create_text(Urho3D::Context *context, Urho3D::String text_string,
                                        Urho3D::Color color, Urho3D::HorizontalAlignment h_align,
                                        Urho3D::VerticalAlignment v_align, Urho3D::Font *font) {
    Urho3D::Text *new_text = new Urho3D::Text(context);
    new_text->SetText(text_string);
    new_text->SetStyle("Button");
    new_text->SetColor(color);
    new_text->SetAlignment(h_align, v_align);
    new_text->SetFont(font);

    return new_text;
}

inline static Urho3D::Text *create_text(Urho3D::Context *context, Urho3D::String text_string,
                                        Urho3D::Font *font) {
    Urho3D::Text *new_text = new Urho3D::Text(context);
    new_text->SetText(text_string);
    new_text->SetStyle("Text");
    new_text->SetColor(Urho3D::Color(0, 0, 0));
    new_text->SetFont(font);

    return new_text;
}

#endif
