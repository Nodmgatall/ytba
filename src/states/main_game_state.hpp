#ifndef MAIN_GAME_STATE_HPP
#define MAIN_GAME_STATE_HPP

#include "state.hpp"

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Skybox.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>

class MainGameState : public GameState {

  public:
    MainGameState(Urho3D::Context *context);
    ~MainGameState();
    void HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);
    void HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data);
    void HandleControlClicked(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void Start();
    void Stop();
    void unsubscribe_events();
    void subscribe_to_events();
    void create_ui();
    void create_side_bar();
    void create_right_click_menu(int mouse_x, int mouse_y);
    void destroy_right_click_menu();
    void start_select_gather(Urho3D::StringHash event_type, Urho3D::VariantMap &event_data);
    void start_select_chop(Urho3D::StringHash event_type, Urho3D::VariantMap &event_data);
    void HandlePressedReleased(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandleMenuHover(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandleMouseButtonUp(Urho3D::StringHash event_type, Urho3D::VariantMap &event_data);
    void HandleMouseButtonDown(Urho3D::StringHash event_type, Urho3D::VariantMap &event_data);
    virtual const Urho3D::TypeInfo *GetTypeInfo() const;
    virtual const Urho3D::String &GetTypeName() const;

  private:
    Urho3D::SharedPtr<Urho3D::Scene> scene_;
    Urho3D::SharedPtr<Urho3D::Node> boxNode_;
    Urho3D::Node *cameraNode_;
    bool m_right_mouse_button_down = false;
    double m_right_click_pressed_time = 0;
    bool m_something_selected = false;
    float m_time_step = 0;
    bool m_context_menu_open = false;
    bool m_build_menu_open = false;
};
#endif
