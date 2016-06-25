#ifndef GUI_HPP
#define GUI_HPP

#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Font.h>

#include <map>
#include <memory>
#include <string>
class Gui {
  public:
    Gui();
    ~Gui();


    void Init();

        private:
    std::map<std::string, std::unique_ptr<Urho3D::UIElement>> UI_elements;
};

#endif
