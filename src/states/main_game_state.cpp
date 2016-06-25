#include "main_game_state.hpp"
#include "../UI/UI_wrapper.hpp"
#include "../events/state_events.hpp"
#include "state.hpp"

#include <Urho3D/Core/Context.h>

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
}

MainGameState::~MainGameState() {

    for (auto button : buttons) {
        button.second->Remove();
    }
    buttons.clear();
    for (auto ui_element : ui_elements) {
        ui_element.second->Remove();
    }
    ui_elements.clear();
    for (auto text : texts) {
        text.second->Remove();
    }
    texts.clear();
}
void MainGameState::HandleControlClicked(Urho3D::StringHash eventType,
                                         Urho3D::VariantMap &eventData) {
    // Query the clicked UI element.
    Urho3D::UIElement *clicked =
        static_cast<Urho3D::UIElement *>(eventData[Urho3D::UIMouseClick::P_ELEMENT].GetPtr());
    if (clicked) {
        if (clicked->GetName() == "Button Quit") { // check if the quit button was clicked
            sendStateChangeEvent(POP);
        }
        if (clicked->GetName() == "Return To Mainmenu") {
            sendStateChangeEvent(CHANGE, MENUMAIN);
        }
        if (clicked->GetName() == "Pause") {
            sendStateChangeEvent(PUSH, GAMEPAUSE);
        }
        if (clicked->GetName() == "Options") {
            sendStateChangeEvent(PUSH, OPTIONS);
        }
        if(clicked->GetName() == "Resolutions")
        {
            std::cout << "resolutions clicked" << std::endl;
        }
    }
}

void MainGameState::Start() {
    // We will be needing to load resources.
    // All the resources used in this example comes with Urho3D.
    // If the engine can't find them, check the ResourcePrefixPath.
    Urho3D::ResourceCache *cache = GetSubsystem<Urho3D::ResourceCache>();

    Urho3D::Font *std_font = GetSubsystem<Urho3D::ResourceCache>()->GetResource<Urho3D::Font>(
        "Fonts/Anonymous Pro.ttf", 20);
    // Seems like the mouse must be in cursor mode before creating the UI or it won't work.
    GetSubsystem<Urho3D::Input>()->SetMouseVisible(true);
    GetSubsystem<Urho3D::Input>()->SetMouseGrabbed(false);
    texts["FPS_text"] = create_text(context_, "FPS COUNTER THIS IS", Urho3D::Color(0, 0, 0),
                                    Urho3D::HA_RIGHT, Urho3D::VA_TOP, std_font);
    GetSubsystem<Urho3D::UI>()->GetRoot()->AddChild(texts["FPS_text"]);

    // Let's use the default style that comes with Urho3D.
    // GetSubsystem<Urho3D::UI>()->GetRoot()->AddChild(texts["FPS_text"]);
    // Let's create some text to display.
    // Add a button, just as an interactive UI sample.
    buttons["Button Quit"] = create_button(context_, "Button Quit", "Button", 32, 32, 64, 64);
    // Note, must be part of the UI system before SetSize calls!
    GetSubsystem<Urho3D::UI>()->GetRoot()->AddChild(buttons["Button Quit"]);

    Urho3D::DropDownList *resolutions = new Urho3D::DropDownList(context_);

    ui_elements["resolutions"] = resolutions;
    resolutions->SetPosition(100,100);
    resolutions->SetStyle("DropDownList");
    resolutions->SetSize(100, 25);
    resolutions->SetName("Resolutions");
    resolutions->AddItem(create_text(context_, "1=========", std_font));
    resolutions->AddItem(create_text(context_, "21111111111", std_font));
    resolutions->AddItem(create_text(context_, "311122222222222", std_font));
    resolutions->AddItem(create_text(context_, "4222222222222222222222", std_font));
    resolutions->AddItem(create_text(context_, "5222222222", std_font));
    resolutions->AddItem(create_text(context_, "6222222222222", std_font));
    resolutions->AddItem(create_text(context_, "72222222222222", std_font));
GetSubsystem<Urho3D::UI>()->GetRoot()->AddChild(resolutions);
    // Now we can change the mouse mode.
    GetSubsystem<Urho3D::Input>()->SetMouseVisible(false);
    GetSubsystem<Urho3D::Input>()->SetMouseGrabbed(true);

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
    for (int x = -30; x < 30; x += 3)
        for (int y = 0; y < 60; y += 3) {
            Urho3D::Node *boxNode_ = scene_->CreateChild("Box");
            boxNode_->SetPosition(Urho3D::Vector3(x, -3, y));
            Urho3D::StaticModel *boxObject = boxNode_->CreateComponent<Urho3D::StaticModel>();
            boxObject->SetModel(cache->GetResource<Urho3D::Model>("Models/Box.mdl"));
            boxObject->SetMaterial(cache->GetResource<Urho3D::Material>("Materials/Stone.xml"));
            boxObject->SetCastShadows(true);
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

void MainGameState::HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData) {
    int key = eventData[Urho3D::KeyDown::P_KEY].GetInt();
    if (key == Urho3D::KEY_ESC) {
        sendStateChangeEvent(POP);
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
