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
    subscribe_to_events();
}

MainGameState::~MainGameState() {

    ui_elements.clear();
}
void MainGameState::HandleControlClicked(Urho3D::StringHash eventType,
                                         Urho3D::VariantMap &eventData) {
    // Query the clicked UI element.
    // Urho3D::UIElement *clicked =
    //   static_cast<Urho3D::UIElement *>(eventData[Urho3D::UIMouseClick::P_ELEMENT].GetPtr());
}
void MainGameState::create_ui() {
    Urho3D::UIElement *root = GetSubsystem<Urho3D::UI>()->GetRoot();
    ui_elements["FPS_text"] = ui_factory.create_text("FPS COUNTER THIS IS", Urho3D::Color(0, 0, 0),
                                                     Urho3D::HA_RIGHT, Urho3D::VA_TOP);
    root->AddChild(ui_elements["FPS_text"]);
    root->AddChild(ui_factory.create_sub_root("right_click_menu", Urho3D::LM_VERTICAL));

    create_side_bar();
}

void MainGameState::create_right_click_menu(int mouse_x, int mouse_y) {
    Urho3D::Window *menu = ui_factory.create_window("right_click_menu");
    ui_factory.m_sub_root_map["right_click_menu"]->AddChild(menu);
    menu->SetLayout(Urho3D::LM_VERTICAL);

    std::cout << mouse_x << " " << mouse_y << std::endl;
    ui_factory.m_sub_root_map["right_click_menu"]->SetPosition(mouse_x, mouse_y);
    Urho3D::UIElement *button_row = ui_factory.create_row(0);
    menu->AddChild(button_row);
    Urho3D::UIElement *chop = ui_factory.create_button("Chop", 30, 30);
    SubscribeToEvent(chop,Urho3D::E_RELEASED,URHO3D_HANDLER(MainGameState,start_select_chop));
    button_row->AddChild(chop);
    Urho3D::UIElement *gather = ui_factory.create_button("Gather", 30, 30);
    button_row->AddChild(gather);
    Urho3D::UIElement *pl = ui_factory.create_button("Placeholder", 30, 30);
    SubscribeToEvent(gather,Urho3D::E_RELEASED,URHO3D_HANDLER(MainGameState,start_select_gather));
    button_row->AddChild(pl);
}
void MainGameState::start_select_chop(Urho3D::StringHash event_type, Urho3D::VariantMap &event_data)
{
    std::cout << "starting selection for choppinh" << std::endl;
}

void MainGameState::start_select_gather(Urho3D::StringHash event_type, Urho3D::VariantMap &event_data)
{
    std::cout << "starting selection for gathering" << std::endl;
}
void MainGameState::destroy_right_click_menu() {
    ui_factory.m_sub_root_map["right_click_menu"]->RemoveAllChildren();
}

void MainGameState::create_side_bar() {
    {
        Urho3D::UIElement *side_bar = ui_factory.create_collum(0);
        side_bar->SetDefaultStyle(ui_factory.m_std_style);
        {
            { // further menus that will be added to another menu
                Urho3D::Menu *wood = ui_factory.create_popup_menu(
                    "Wood", 150, 25,
                    {ui_factory.create_button("Sawmill"), ui_factory.create_button("Woodcuttert"),
                     ui_factory.create_button("Carpenter")},
                    150, 25);

                Urho3D::Menu *stone = ui_factory.create_popup_menu(
                    "Stone", 150, 25,
                    {ui_factory.create_button("Stonecutter"), ui_factory.create_button("Mason"),
                     ui_factory.create_button("Stonecarver")},
                    150, 25);
                Urho3D::Menu *cloth = ui_factory.create_popup_menu(
                    "Cloth", 150, 25,
                    {ui_factory.create_button("Weaver"), ui_factory.create_button("Tailor"),
                     ui_factory.create_button("RopeMaker")},
                    150, 25);
                Urho3D::Menu *leather = ui_factory.create_popup_menu(
                    "Leather", 150, 25,
                    {ui_factory.create_button("Tanner"), ui_factory.create_button("LeatherWorker"),
                     ui_factory.create_button("ArmorMaker")},
                    150, 25);
                Urho3D::Menu *cooking = ui_factory.create_popup_menu(
                    "Cooking", 150, 25,
                    {ui_factory.create_button("Butcher"), ui_factory.create_button("Mill"),
                     ui_factory.create_button("Bakery"), ui_factory.create_button("Kitchen"),
                     ui_factory.create_button("Smoker")},
                    150, 25);

                Urho3D::Menu *animals = ui_factory.create_popup_menu(
                    "Animals", 150, 25,
                    {ui_factory.create_button("Hunter"), ui_factory.create_button("Fishery"),
                     ui_factory.create_button("BeeKeper"), ui_factory.create_button("Herder")},
                    150, 25);

                Urho3D::Menu *drink = ui_factory.create_popup_menu(
                    "Drink", 150, 25,
                    {ui_factory.create_button("Brewery"), ui_factory.create_button("Meadery"),
                     ui_factory.create_button("TeaMaker"), ui_factory.create_button("Well")},
                    150, 25);

                Urho3D::Menu *gems = ui_factory.create_popup_menu(
                    "Gems", 150, 25,
                    {ui_factory.create_button("Gemcutter"), ui_factory.create_button("GemSetter")},
                    150, 25);

                Urho3D::Menu *metal = ui_factory.create_popup_menu(
                    "Metal", 150, 25,
                    {ui_factory.create_button("Forge"), ui_factory.create_button("ArmorSmith"),
                     ui_factory.create_button("WeaponSmith"), ui_factory.create_button("ToolSmith"),
                     ui_factory.create_button("Furnance"), ui_factory.create_button("WoodBurner")},
                    150, 25);
                Urho3D::Menu *workshops = ui_factory.create_popup_menu(
                    "Workshops", 50, 50,
                    {wood, stone, metal, gems, cooking, drink, animals, cloth, leather}, 150, 25);
                side_bar->AddChild(workshops);
            }
            { // further menus that will be added to another menu
                Urho3D::Menu *farming = ui_factory.create_popup_menu(
                    "Farming", 150, 25,
                    {ui_factory.create_button("Field"), ui_factory.create_button("Orchard"),
                     ui_factory.create_button("Pasture"), ui_factory.create_button("HoneyFarm"),
                     ui_factory.create_button("UndergroundField")},
                    150, 25);
                Urho3D::Menu *water = ui_factory.create_popup_menu(
                    "Water", 150, 25, {ui_factory.create_button("FreshWater"),
                                       ui_factory.create_button("FishingZone"),
                                       ui_factory.create_button("FishNursery")},
                    150, 25);

                Urho3D::Menu *social = ui_factory.create_popup_menu(
                    "Social", 150, 25,
                    {ui_factory.create_button("Tavern"), ui_factory.create_button("Hospital"),
                     ui_factory.create_button("Library"), ui_factory.create_button("MeetingHall"),
                     ui_factory.create_button("DiningHall")},
                    150, 25);

                Urho3D::Menu *military = ui_factory.create_popup_menu(
                    "Military", 150, 25,
                    {ui_factory.create_button("Burrow"), ui_factory.create_button("GuardZone"),
                     ui_factory.create_button("TrainingZone"),
                     ui_factory.create_button("Barracks")},
                    150, 25);

                Urho3D::Menu *stockpiles = ui_factory.create_popup_menu(
                    "Stockpiles", 150, 25,
                    {ui_factory.create_button("refuse"), ui_factory.create_button("dump"),
                     ui_factory.create_button("stockpile"), ui_factory.create_button("test")},
                    150, 25);
                Urho3D::Menu *designations = ui_factory.create_popup_menu(
                    "Designations", 50, 50, {farming, social, military, water, stockpiles}, 150,
                    25);
                side_bar->AddChild(designations);
            }
        }
        ui_elements["side_bar"] = side_bar;
    }
}

void MainGameState::unsubscribe_events() {
    UnsubscribeFromAllEvents();
}
void MainGameState::subscribe_to_events() {
    SubscribeToEvent(Urho3D::E_MOUSEBUTTONUP, URHO3D_HANDLER(MainGameState, HandleMouseButtonUp));
    SubscribeToEvent(Urho3D::E_MOUSEBUTTONDOWN,
                     URHO3D_HANDLER(MainGameState, HandleMouseButtonDown));
}

void MainGameState::HandleMenuHover(Urho3D::StringHash event_type, Urho3D::VariantMap &event_data) {
    Urho3D::Menu *hovered_menu = static_cast<Urho3D::Menu *>(event_data["Element"].GetPtr());
    hovered_menu->ShowPopup(true);
}

void MainGameState::HandlePressedReleased(Urho3D::StringHash eventType,
                                          Urho3D::VariantMap &eventData) {
    std::cout << "works " << std::endl;
}

void MainGameState::HandleMouseButtonUp(Urho3D::StringHash event_type,
                                        Urho3D::VariantMap &event_data) {
    if (event_data[Urho3D::MouseButtonUp::P_BUTTON] == Urho3D::MOUSEB_RIGHT) {
        m_right_mouse_button_down = false;
        if (m_something_selected) {
            std::cout << "open from context menu event" << std::endl;
        } else {

            std::cout << "open_menu" << std::endl;
            Urho3D::IntVector2 mouse_move = GetSubsystem<Urho3D::Input>()->GetMousePosition();
            create_right_click_menu(mouse_move.x_, mouse_move.y_);
            m_context_menu_open = false;
            m_build_menu_open = true;
        }
        m_right_click_pressed_time = 0.0;
    }

    if (event_data[Urho3D::MouseButtonUp::P_BUTTON] == Urho3D::MOUSEB_LEFT && m_build_menu_open) {
        destroy_right_click_menu();
        std::cout << "destroinh menu" << std::endl;
        m_build_menu_open = false;
    }
}
void MainGameState::HandleMouseButtonDown(Urho3D::StringHash event_type,
                                          Urho3D::VariantMap &event_data) {
    std::cout << "event_fired" << std::endl;
    if (event_data[Urho3D::MouseButtonDown::P_BUTTON] == Urho3D::MOUSEB_RIGHT) {
        if (m_build_menu_open) {
            destroy_right_click_menu();
            std::cout << "destroy old window" << std::endl;
        }
        m_right_mouse_button_down = true;
    }
}

void MainGameState::Start() {
    std::cout << "starting main game " << std::endl;
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
    boxObject->SetMaterial(cache->GetResource<Urho3D::Material>("Materials/Terrain.xml"));

    // Create a plane out of 900 boxes.
    //

    for (int x = -500; x < 500; x++)
        for (int y = -500; y < 500; y++) {
            int z = 0;
            if (sqrt(x * x + y * y) <
                200 +
                    4 * sin(5 * sin(6 * (glm::dot(glm::normalize(glm::vec2(x, y)),
                                                  glm::vec2(0, 1)))))) {
                Urho3D::Node *boxNode_ = scene_->CreateChild("Box");
                boxNode_->SetPosition(Urho3D::Vector3(x, -z, y));
                Urho3D::StaticModel *boxObject = boxNode_->CreateComponent<Urho3D::StaticModel>();
                boxObject->SetModel(cache->GetResource<Urho3D::Model>("Models/Box.mdl"));
                if (x % 2 == 0 && y % 2 == 0) {
                    boxObject->SetMaterial(
                        cache->GetResource<Urho3D::Material>("Materials/Mushroom.xml"));
                } else {

                    boxObject->SetMaterial(
                        cache->GetResource<Urho3D::Material>("Materials/NinjaSnowWar/Snow.xml"));
                }
                boxObject->SetCastShadows(true);
            }
        }

    // We need a camera from which the viewport can render.
    cameraNode_ = scene_->CreateChild("Camera");
    Urho3D::Camera *camera = cameraNode_->CreateComponent<Urho3D::Camera>();
    camera->SetFarClip(2000);
    cameraNode_->Pitch(45);
    cameraNode_->SetPosition(Urho3D::Vector3(0, 10, 1));

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
    float m_time_step = eventData[Urho3D::Update::P_TIMESTEP].GetFloat();
    // Movement speed as world units per second
    float MOVE_SPEED = 10.0f;
    // Mouse sensitivity as degrees per pixel
    // const float MOUSE_SENSITIVITY = 0.1f;

    // Rotate the box thingy.
    // A much nicer way of doing this would be with a LogicComponent.
    // With LogicComponents it is easy to control things like movement
    // and animation from some IDE, console or just in game.
    // Alas, it is out of the scope for our simple example.
    // boxNode_->Rotate(Quaternion(8*timeStep,16*timeStep,0));

    Urho3D::Input *input = GetSubsystem<Urho3D::Input>();
    if (m_right_mouse_button_down && !m_context_menu_open) {
        m_right_click_pressed_time += m_time_step;
        if (m_right_click_pressed_time > 0.3 && !m_context_menu_open) {
            std::cout << "opening context menu" << std::endl;
            m_context_menu_open = true;
            m_right_click_pressed_time = 0.0;
        }
    }

    if (input->GetQualifierDown(1)) // 1 is shift, 2 is ctrl, 4 is alt
        MOVE_SPEED *= 10;
    if (input->GetKeyDown('W'))
        cameraNode_->Translate(Urho3D::Vector3(0, 0.5, 0.5) * MOVE_SPEED * m_time_step);
    if (input->GetKeyDown('S'))
        cameraNode_->Translate(Urho3D::Vector3(0, -0.5, -0.5) * MOVE_SPEED * m_time_step);
    if (input->GetKeyDown('A'))
        cameraNode_->Translate(Urho3D::Vector3(-1, 0, 0) * MOVE_SPEED * m_time_step);
    if (input->GetKeyDown('D'))
        cameraNode_->Translate(Urho3D::Vector3(1, 0, 0) * MOVE_SPEED * m_time_step);

    if (!GetSubsystem<Urho3D::Input>()->IsMouseVisible()) {
        // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch
        // between -90 and 90 degrees
        /*
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
         }*/
    }
}
const Urho3D::TypeInfo *MainGameState::GetTypeInfo() const {
    return GetTypeInfoStatic();
}

const Urho3D::String &MainGameState::GetTypeName() const {
    return GetTypeInfo()->GetTypeName();
}
