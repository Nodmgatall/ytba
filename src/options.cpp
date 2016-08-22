#include "options.hpp"
#include <Urho3D/Graphics/Graphics.h>
#include <utility>

#include <Urho3D/Engine/Application.h>
Options::Options(Urho3D::Graphics* graphics)
    : m_graphics(graphics) {
        full_screen = graphics->GetFullscreen();
}

bool Options::load() {

    return true;
}

void Options::save() {

    if(m_graphics->GetFullscreen() != full_screen)
    {
        m_graphics->ToggleFullscreen();
    }
}

void Options::discard() {
}

void Options::apply() {

    return;
}

bool Options::get_fullscreen()
{
    return full_screen;
}

void Options::set_fullscreen(bool fullscreen)
{
    full_screen = fullscreen; 
}
