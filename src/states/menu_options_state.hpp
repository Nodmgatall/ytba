#include "options_state.hpp"
#include "../UI/UI_wrapper.hpp"
#include "../events/state_events.hpp"
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/DropDownList.h>

OptionState::OptionState(Urho3D::Context *context)
{
    GameState(context);
}

OptionState::~OptionState() {

    for (auto button : buttons) {
        button.second->Remove();
    }
    buttons.clear();
    for (auto ui_element : ui_elements) {
        ui_element.second->Remove();
    }
    ui_elements.clear();
    for (auto text: texts) {
        text.second->Remove();
    }
    texts.clear();
}

OptionState::start()
{
    
}

OptionState::create_ui()
{
   Urho3D::UIElement *resolutions = new Urho3D::DropDownList(context_);
   ui_elements["resolutions"] = resolutions;
   ui_elements["resolutions"]->AddItem()
}

