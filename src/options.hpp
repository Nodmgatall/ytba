#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/UI/UI.h>
#include <map>
#include <string>
#include <utility>

class Options : public Urho3D::Object {
  public:
    Options(Urho3D::Context *context);

    void save();
    bool load();
    void discard();
    void apply();

    bool get_fullscreen();
    void set_fullscreen(bool fullscreen);

  private:
    Urho3D::Graphics *m_graphics;
    Urho3D::UI *m_ui;
    Urho3D::Input *m_input;
    bool v_sync;
    bool full_screen;

    int x_resolution;
    int y_resolution;
    std::string ini_file_name;
    const Urho3D::TypeInfo *GetTypeInfo() const;
    const Urho3D::String &GetTypeName() const;
    Urho3D::StringHash GetType() const {
        return GetTypeName();
    };
};
#endif
