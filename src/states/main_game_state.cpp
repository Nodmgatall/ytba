#include "main_game_state.hpp"
#include "../../pcg-cpp/include/pcg_random.hpp"
#include "../UI/ui_manager.hpp"
#include "../events/state_events.hpp"
#include "state.hpp"
#include <Urho3D/Core/Context.h>
#include <glm/glm.hpp>

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

#include <Urho3D/UI/DropDownList.h>

#include <iostream>
#include <sstream>

MainGameState::MainGameState(Urho3D::Context *context) : GameState(context) {
    Urho3D::ResourceCache *cache = GetSubsystem<Urho3D::ResourceCache>();

    ui_factory =
        UIManager(context_, cache->GetResource<Urho3D::Font>("Fonts/Anonymous Pro.ttf", 20),
                  Urho3D::Color(), cache->GetResource<Urho3D::XMLFile>("UI/DefaultStyle.xml"),
                  GetSubsystem<Urho3D::UI>()->GetRoot());
    create_ui();
}

MainGameState::~MainGameState() {

    for (auto ui_element : ui_elements) {
        ui_element.second->Remove();
    }
    ui_elements.clear();
}
void MainGameState::HandleControlClicked(Urho3D::StringHash eventType,
                                         Urho3D::VariantMap &eventData) {
    // Query the clicked UI element.
   // Urho3D::UIElement *clicked =
     //   static_cast<Urho3D::UIElement *>(eventData[Urho3D::UIMouseClick::P_ELEMENT].GetPtr());
}
void MainGameState::create_ui() {
    ui_elements["FPS_text"] = ui_factory.create_text("FPS COUNTER THIS IS", Urho3D::Color(0, 0, 0),
                                                     Urho3D::HA_RIGHT, Urho3D::VA_TOP);
    GetSubsystem<Urho3D::UI>()->GetRoot()->AddChild(ui_elements["FPS_text"]);

    create_side_bar();
}

void MainGameState::create_side_bar() {
    {
        Urho3D::UIElement *side_bar = ui_factory.create_collum(0);
        side_bar->SetDefaultStyle(ui_factory.m_std_style);
        Urho3D::Menu *test = ui_factory.create_popup_menu(
            "popup_menu", 150, 25,
            {ui_factory.create_button("test"), ui_factory.create_button("test"),
             ui_factory.create_button("test"), ui_factory.create_button("test")},
            150, 25);

        Urho3D::Menu *test1 = ui_factory.create_popup_menu(
            "popup_menu1", 150, 25,
            {ui_factory.create_button("test"), ui_factory.create_button("test"),
             ui_factory.create_button("test"), ui_factory.create_button("test")},
            150, 25);

        Urho3D::Menu *test2 = ui_factory.create_popup_menu(
            "popup_menu2", 150, 25,
            {ui_factory.create_button("test"), ui_factory.create_button("test"),
             ui_factory.create_button("test"), ui_factory.create_button("test")},
            150, 25);
        Urho3D::Menu *test3 = ui_factory.create_popup_menu(
            "popup_menu3", 150, 25,
            {ui_factory.create_button("test"), ui_factory.create_button("test"),
             ui_factory.create_button("test"), ui_factory.create_button("test")},
            150, 25);
        Urho3D::Menu *test4 = ui_factory.create_popup_menu(
            "popup_menu4", 50, 50,
            {test, test1, test2, test3},
            150, 25);
        side_bar->AddChild(test4);
        Urho3D::Menu *test5 = ui_factory.create_popup_menu(
            "popup_menu5", 150, 25,
            {ui_factory.create_button("test"), ui_factory.create_button("test"),
             ui_factory.create_button("test"), ui_factory.create_button("test")},
            150, 25);

        Urho3D::Menu *test6 = ui_factory.create_popup_menu(
            "popup_menu6", 150, 25,
            {ui_factory.create_button("test"), ui_factory.create_button("test"),
             ui_factory.create_button("test"), ui_factory.create_button("test")},
            150, 25);

        Urho3D::Menu *test7 = ui_factory.create_popup_menu(
            "popup_menu7", 50, 50,
            {test5, test6},
            150, 25);
        side_bar->AddChild(test7);

        SubscribeToEvent(test2, Urho3D::E_HOVERBEGIN,
                         URHO3D_HANDLER(MainGameState, HandleMenuHover));
        ui_elements["side_bar"] = side_bar;
    }
}

void MainGameState::unsubscribe_events() {
}
void MainGameState::subscribe_to_events() {
}

void MainGameState::HandleMenuHover(Urho3D::StringHash event_type, Urho3D::VariantMap &event_data) {
    Urho3D::Menu *hovered_menu = static_cast<Urho3D::Menu *>(event_data["Element"].GetPtr());
    hovered_menu->ShowPopup(true);
}

void MainGameState::HandlePressedReleased(Urho3D::StringHash eventType,
                                          Urho3D::VariantMap &eventData) {
    std::cout << "works " << std::endl;
}

void MainGameState::Start() {
    Urho3D::ResourceCache *cache = GetSubsystem<Urho3D::ResourceCache>();
    // We will be needing to load resources.
    // All the resources used in this example comes with Urho3D.
    // If the engine can't find them, check the ResourcePrefixPath.

    // Seems like the mouse must be in cursor mode before creating the UI or it won't work.

    // Let's use the default style that comes with Urho3D.
    // GetSubsystem<Urho3D::UI>()->GetRoot()->AddChild(texts["FPS_text"]);
    // Let's create some text to display.
    // Add a button, just as an interactive UI sample.
    // Note, must be part of the UI system before SetSize calls!

    GetSubsystem<Urho3D::UI>()->GetRoot()->AddChild(ui_elements["Return To Mainmenu"]);
    GetSubsystem<Urho3D::UI>()->GetRoot()->AddChild(ui_elements["Options"]);
    GetSubsystem<Urho3D::UI>()->GetRoot()->AddChild(ui_elements["side_bar"]);

    // Now we can change the mouse mode.

    // Let's setup a scene to render.
    scene_ = new Urho3D::Scene(context_);
    // Let the scene have an Octree component!
    scene_->CreateComponent<Urho3D::Octree>();
    // Let's add an additional scene component for fun.
    scene_->CreateComponent<Urho3D::DebugRenderer>();

    // Let's put some sky in there.
    // Again, if the engine can't find these resources you need to check
    // the "ResourcePrefixPath". These files come with Urho3D.
    Urho3D::Node *skyNode = scene_->CreateChild("Sky");
    skyNode->SetScale(500.0f); // The scale actually does not matter
    Urho3D::Skybox *skybox = skyNode->CreateComponent<Urho3D::Skybox>();
    skybox->SetModel(cache->GetResource<Urho3D::Model>("Models/Box.mdl"));
    skybox->SetMaterial(cache->GetResource<Urho3D::Material>("Materials/Skybox.xml"));

    // Let's put a box in there.
    boxNode_ = scene_->CreateChild("Box");
    boxNode_->SetPosition(Urho3D::Vector3(0, 0, 5));
    Urho3D::StaticModel *boxObject = boxNode_->CreateComponent<Urho3D::StaticModel>();
    boxObject->SetModel(cache->GetResource<Urho3D::Model>("Models/Box.mdl"));
    boxObject->SetMaterial(cache->GetResource<Urho3D::Material>("Materials/Stone.xml"));

    // Create a plane out of 900 boxes.
    //

    for (int x = -500; x < 500; x++)
        for (int y = -500; y < 500; y++) {
            int z = 100;
            if (sqrt(x * x + y * y) <
                200 +
                    4 * sin(5 * sin(6 * (glm::dot(glm::normalize(glm::vec2(x, y)),
                                                  glm::vec2(0, 1)))))) {
                Urho3D::Node *boxNode_ = scene_->CreateChild("Box");
                boxNode_->SetPosition(Urho3D::Vector3(x, -z, y));
                Urho3D::StaticModel *boxObject = boxNode_->CreateComponent<Urho3D::StaticModel>();
                boxObject->SetModel(cache->GetResource<Urho3D::Model>("Models/Box.mdl"));
                boxObject->SetMaterial(cache->GetResource<Urho3D::Material>("Materials/Stone.xml"));
                boxObject->SetCastShadows(true);
            }
        }

    // We need a camera from which the viewport can render.
    cameraNode_ = scene_->CreateChild("Camera");
    Urho3D::Camera *camera = cameraNode_->CreateComponent<Urho3D::Camera>();
    camera->SetFarClip(2000);

    // Create two lights
    {
        Urho3D::Node *lightNode = scene_->CreateChild("Light");
        lightNode->SetPosition(Urho3D::Vector3(-5, 0, 10));
        Urho3D::Light *light = lightNode->CreateComponent<Urho3D::Light>();
        light->SetLightType(Urho3D::LIGHT_POINT);
        light->SetRange(50);
        light->SetBrightness(1.2);
        light->SetColor(Urho3D::Color(1, .5, .8, 1));
        light->SetCastShadows(true);
    }
    // add one to the camera node as well
    // Now we setup the viewport. Ofcourse, you can have more than one!
    Urho3D::Renderer *renderer = GetSubsystem<Urho3D::Renderer>();
    Urho3D::SharedPtr<Urho3D::Viewport> viewport(
        new Urho3D::Viewport(context_, scene_, cameraNode_->GetComponent<Urho3D::Camera>()));
    renderer->SetViewport(0, viewport);

    // We subscribe to the events we'd like to handle.
    // In this example we will be showing what most of them do,
    // but in reality you would only subscribe to the events
    // you really need to handle.
    // These are sort of subscribed in the order in which the engine
    // would send the events. Read each handler method's comment for
    // details.
    std::cout << "start main done" << std::endl;
}

void MainGameState::Stop() {
    std::cout << "not implemented : MainGameState::Stop()" << std::endl;
}

void MainGameState::HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData) {
    int key = eventData[Urho3D::KeyDown::P_KEY].GetInt();
    if (key == Urho3D::KEY_ESC) {
        sendStateChangeEvent(PUSH, INGAMEMENU);
        return;
    }
    if (key == Urho3D::KEY_TAB) {
        GetSubsystem<Urho3D::Input>()->SetMouseVisible(
            !GetSubsystem<Urho3D::Input>()->IsMouseVisible());
        GetSubsystem<Urho3D::Input>()->SetMouseGrabbed(
            !GetSubsystem<Urho3D::Input>()->IsMouseGrabbed());
    }
}

void MainGameState::HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData) {
    float timeStep = eventData[Urho3D::Update::P_TIMESTEP].GetFloat();
    // Movement speed as world units per second
    float MOVE_SPEED = 10.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    // Rotate the box thingy.
    // A much nicer way of doing this would be with a LogicComponent.
    // With LogicComponents it is easy to control things like movement
    // and animation from some IDE, console or just in game.
    // Alas, it is out of the scope for our simple example.
    // boxNode_->Rotate(Quaternion(8*timeStep,16*timeStep,0));

    Urho3D::Input *input = GetSubsystem<Urho3D::Input>();
    if (input->GetQualifierDown(1)) // 1 is shift, 2 is ctrl, 4 is alt
        MOVE_SPEED *= 10;
    if (input->GetKeyDown('W'))
        cameraNode_->Translate(Urho3D::Vector3(0, 0, 1) * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('S'))
        cameraNode_->Translate(Urho3D::Vector3(0, 0, -1) * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('A'))
        cameraNode_->Translate(Urho3D::Vector3(-1, 0, 0) * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('D'))
        cameraNode_->Translate(Urho3D::Vector3(1, 0, 0) * MOVE_SPEED * timeStep);

    if (!GetSubsystem<Urho3D::Input>()->IsMouseVisible()) {
        // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch
        // between -90 and 90 degrees
        Urho3D::IntVector2 mouseMove = input->GetMouseMove();
        // avoid the weird extrem values before moving the mouse
        if (mouseMove.x_ > -2000000000 && mouseMove.y_ > -2000000000) {
            static float yaw_ = 0;
            static float pitch_ = 0;
            yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
            pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
            pitch_ = Urho3D::Clamp(pitch_, -90.0f, 90.0f);
            // Reset rotation and set yaw and pitch again
            cameraNode_->SetDirection(Urho3D::Vector3::FORWARD);
            cameraNode_->Yaw(yaw_);
            cameraNode_->Pitch(pitch_);
        }
    }
}

const Urho3D::TypeInfo *MainGameState::GetTypeInfo() const {
    return GetTypeInfoStatic();
}

const Urho3D::String &MainGameState::GetTypeName() const {
    return GetTypeInfo()->GetTypeName();
}
