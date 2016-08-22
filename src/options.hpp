#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Graphics.h>
#include <map>
#include <string>
#include <utility>

class Options {
  public:
    Options(Urho3D::Graphics* graphics);

    void save();
    bool load();
    void discard();
    void apply();

    bool get_fullscreen();
    void set_fullscreen(bool fullscreen);
  private:
    Urho3D::Graphics* m_graphics;
    bool v_sync;
    bool full_screen;

    int x_resolution;
    int y_resolution;
        std::string ini_file_name;

};

#endif
