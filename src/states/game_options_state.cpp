#include "game_options_state.hpp"
#include "../UI/ui_manager.hpp"
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
#include <Urho3D/UI/ListView.h>

GameOptionsState::GameOptionsState(Urho3D::Context *context) : GameState(context) {
    Urho3D::ResourceCache *cache = GetSubsystem<Urho3D::ResourceCache>();
    ui_factory =
        UIManager(context_, cache->GetResource<Urho3D::Font>("Fonts/Anonymous Pro.ttf", 20),
                  Urho3D::Color(), cache->GetResource<Urho3D::XMLFile>("UI/DefaultStyle.xml"),
                  GetSubsystem<Urho3D::UI>()->GetRoot());
    create_ui();
}

GameOptionsState::~GameOptionsState() {

    for (auto ui_element : ui_elements) {
        ui_element.second->Remove();
    }
    ui_elements.clear();
}

void GameOptionsState::Start() {

    Urho3D::UIElement *root = GetSubsystem<Urho3D::UI>()->GetRoot();

    for (auto ui_element : ui_elements) {

        root->AddChild(ui_element.second);
    }
}

void GameOptionsState::Stop() {
    // Urho3D::UIElement *root = GetSubsystem<Urho3D::UI>()->GetRoot();
    for (auto ui_element : ui_elements) {
        ui_element.second->RemoveAllChildren();
        ui_element.second->Remove();
    }
}
void GameOptionsState::unsubscribe_events() {
}
void GameOptionsState::subscribe_to_events() {
}
void GameOptionsState::create_ui() {

    // creating ui part and subparts
    create_main_option_window();
    ui_factory.m_sub_root_map["main_option_window"]->AddChild(setup_video_options());
}

void GameOptionsState::change_to_sound() {
    ui_factory.m_sub_root_map["main_option_window"]->RemoveAllChildren();
    ui_factory.m_sub_root_map["main_option_window"]->AddChild(setup_sound_options());
}
void GameOptionsState::change_to_video() {
    ui_factory.m_sub_root_map["main_option_window"]->RemoveAllChildren();
    ui_factory.m_sub_root_map["main_option_window"]->AddChild(setup_video_options());
}

void GameOptionsState::create_main_option_window() {
    Urho3D::Window *option_main_window = ui_factory.create_window(
        "main_option_window", Urho3D::HA_CENTER, Urho3D::VA_CENTER, 700, 600);
    option_main_window->SetLayout(Urho3D::LM_VERTICAL, 1);
    option_main_window->SetStyleAuto();
    {
        Urho3D::UIElement *split = ui_factory.create_collum();
        option_main_window->AddChild(split);
        {
            Urho3D::UIElement *reiter = ui_factory.create_row(0);
            reiter->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_TOP);
            split->AddChild(reiter);
            {
                Urho3D::UIElement *button;
                
                button = ui_factory.create_button("Video", 100, 25);
                reiter->AddChild(button);
                ui_factory.add_task(button, [=](){this->change_to_video();});
                
                button = ui_factory.create_button("Sound", 100, 25);
                reiter->AddChild(button);
                ui_factory.add_task(button, [=](){this->change_to_sound();});
                
                reiter->AddChild(ui_factory.create_button("Game", 100, 25));
                
                reiter->AddChild(ui_factory.create_button("plhold", 100, 25));
             
                reiter->AddChild(ui_factory.create_button("plhold", 100, 25));
            }
            Urho3D::UIElement *sub_root = ui_factory.create_sub_root("root_node_options", option_main_window); 
            sub_root->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_BOTTOM);
            sub_root->SetLayout(Urho3D::LM_VERTICAL, 1);
            split->AddChild(sub_root);
        }
    }
    ui_elements["main_option_window"] = option_main_window;
}
Urho3D::UIElement *GameOptionsState::setup_sound_options() {
    Urho3D::UIElement *main_collum = ui_factory.create_window(
        "main_option_border", Urho3D::HA_CENTER, Urho3D::VA_CENTER, 700, 600);
    main_collum->SetName("SoundOptions");
    main_collum->SetLayout(Urho3D::LM_VERTICAL, 25, Urho3D::IntRect(10, 10, 10, 10));
    main_collum->SetStyleAuto();
    {
        Urho3D::UIElement *split = ui_factory.create_row();
        split->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_BOTTOM);
        main_collum->AddChild(split);
        {
            Urho3D::UIElement *colum1 = ui_factory.create_collum();
            split->AddChild(colum1);
            {
                Urho3D::DropDownList *resolutions = ui_factory.create_drop_down_list(
                    125, 25,
                    {ui_factory.create_text("device 1"), ui_factory.create_text("1600 x 1280"),
                     ui_factory.create_text("1800 x 1440"), ui_factory.create_text("2048 x 1152"),
                     ui_factory.create_text("1900 x 1600")});

                colum1->AddChild(ui_factory.create_option_text_pair(resolutions, "resolution"));
                colum1->AddChild(ui_factory.create_option_text_pair(
                    ui_factory.create_check_box("Option1"), "description1"));
                colum1->AddChild(ui_factory.create_option_text_pair(
                    ui_factory.create_check_box("Option4"), "description4"));
            }
            Urho3D::UIElement *colum2 = ui_factory.create_collum();
            split->AddChild(colum2);
            {
                colum2->AddChild(ui_factory.create_option_text_pair(
                    ui_factory.create_check_box("Option2"), "description2"));
                colum2->AddChild(ui_factory.create_option_text_pair(
                    ui_factory.create_check_box("sourround"), "enable sourround"));
                colum2->AddChild(ui_factory.create_option_text_pair(
                    ui_factory.create_check_box("option3"), "description3"));
            }
        }
        Urho3D::UIElement *bottom_row = ui_factory.create_row();
        bottom_row->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_BOTTOM);
        main_collum->AddChild(bottom_row);
        {
            bottom_row->AddChild(
                ui_factory.create_button("Discard", Urho3D::HA_CENTER, Urho3D::VA_BOTTOM, 100, 25));
            bottom_row->AddChild(
                ui_factory.create_button("Save", Urho3D::HA_CENTER, Urho3D::VA_BOTTOM, 100, 25));
        }
    }
    // Setting all the things we want

    return main_collum;
}

Urho3D::UIElement *GameOptionsState::setup_video_options() {

    // Brackets serve no other purpose than getting some order and visibility in here
    Urho3D::UIElement *main_collum = ui_factory.create_window(
        "main_option_border", Urho3D::HA_CENTER, Urho3D::VA_CENTER, 700, 600);
    main_collum->SetName("VideoOptions");
    main_collum->SetLayout(Urho3D::LM_VERTICAL, 25, Urho3D::IntRect(10, 10, 10, 10));
    main_collum->SetStyleAuto();
    {
        Urho3D::UIElement *split = ui_factory.create_row();
        split->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_BOTTOM);
        main_collum->AddChild(split);
        {
            Urho3D::UIElement *colum1 = ui_factory.create_collum();
            split->AddChild(colum1);
            {
                Urho3D::DropDownList *resolutions = ui_factory.create_drop_down_list(
                    125, 25,
                    {ui_factory.create_text("1920 x 1080"), ui_factory.create_text("1600 x 1280"),
                     ui_factory.create_text("1800 x 1440"), ui_factory.create_text("2048 x 1152"),
                     ui_factory.create_text("1900 x 1600")});

                colum1->AddChild(ui_factory.create_option_text_pair(resolutions, "resolution"));
                colum1->AddChild(ui_factory.create_option_text_pair(
                    ui_factory.create_check_box("Option1"), "description1"));
                colum1->AddChild(ui_factory.create_option_text_pair(
                    ui_factory.create_check_box("Option4"), "description4"));
            }
            Urho3D::UIElement *colum2 = ui_factory.create_collum();
            split->AddChild(colum2);
            {
                colum2->AddChild(ui_factory.create_option_text_pair(
                    ui_factory.create_check_box("Option2"), "description2"));
                colum2->AddChild(ui_factory.create_option_text_pair(
                    ui_factory.create_check_box("VSync"), "enable VSync"));
                colum2->AddChild(ui_factory.create_option_text_pair(
                    ui_factory.create_check_box("option3"), "description3"));
            }
        }
        Urho3D::UIElement *bottom_row = ui_factory.create_row();
        bottom_row->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_BOTTOM);
        main_collum->AddChild(bottom_row);
        {
            bottom_row->AddChild(
                ui_factory.create_button("Discard", Urho3D::HA_CENTER, Urho3D::VA_BOTTOM, 100, 25));
            bottom_row->AddChild(
                ui_factory.create_button("Save", Urho3D::HA_CENTER, Urho3D::VA_BOTTOM, 100, 25));
        }
    }
    // Setting all the things we want

    return main_collum;
}

void GameOptionsState::HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData) {
}

void GameOptionsState::HandleControlClicked(Urho3D::StringHash eventType,
                                            Urho3D::VariantMap &eventData) {
    Urho3D::UIElement *clicked =
        static_cast<Urho3D::UIElement *>(eventData[Urho3D::UIMouseClick::P_ELEMENT].GetPtr());
    if (clicked) {
        if (clicked->GetName() == "Discard") {
            sendStateChangeEvent(POP);
        }
        if (clicked->GetName() == "Save") {
            sendStateChangeEvent(POP);
        }
    }
    auto clicked_iter = ui_factory.m_task_map.find(clicked->GetName());
    if(clicked_iter != ui_factory.m_task_map.end())
    {
        clicked_iter->second();
    }
}
void GameOptionsState::HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &event_data) {
    int key = event_data[Urho3D::KeyDown::P_KEY].GetInt();

    Urho3D::VariantMap v;
    switch (key) {
    case Urho3D::KEY_ESC:
        sendStateChangeEvent(POP);
        break;
    default:
        std::cout << "key not set" << std::endl;
    }
}

const Urho3D::TypeInfo *GameOptionsState::GetTypeInfo() const {
    return GetTypeInfoStatic();
}

const Urho3D::String &GameOptionsState::GetTypeName() const {
    return GetTypeInfo()->GetTypeName();
}
