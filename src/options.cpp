#include "options.hpp"
#include <Urho3D/Graphics/Graphics.h>
#include <utility>

#include <Urho3D/Engine/Application.h>
Options::Options(Urho3D::Context *context)
    : Urho3D::Object(context), m_graphics(GetSubsystem<Urho3D::Graphics>()),
      m_ui(GetSubsystem<Urho3D::UI>()), m_input(GetSubsystem<Urho3D::Input>()) {
    full_screen = m_graphics->GetFullscreen();
}

bool Options::load() {

    return true;
}

void Options::save() {

    if (m_graphics->GetFullscreen() != full_screen) {
        m_graphics->ToggleFullscreen();
    }
}

void Options::discard() {
}

void Options::apply() {

    return;
}

bool Options::get_fullscreen() {
    return full_screen;
}

void Options::set_fullscreen(bool fullscreen) {
    full_screen = fullscreen;
}

const Urho3D::TypeInfo *Options::GetTypeInfo() const {
    return GetTypeInfoStatic();
}

const Urho3D::String &Options::GetTypeName() const {
    return GetTypeInfo()->GetTypeName();
}
