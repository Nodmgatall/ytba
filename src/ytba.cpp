/**
* A simple Urho3D example in one (big) file.
* Copyright 2014 Peter Gebauer, 2015 gawag.
* Released under the same permissive MIT-license as Urho3D.
* https://raw.githubusercontent.com/urho3d/Urho3D/master/License.txt
*
* Why?
* Because A first "simple" example tutorial shouldn't require additional
* frameworks or special toolchains. This file along with Urho3D and a C++
* compiler should do it. (you might have to change the prefix path in
* MyApp::Setup)
* Many (like me) want to learn themselves and just get an overview
* without the overhead of understanding how the example is built.
* I hope this file covers the basics and is of use to you.
*/

#include "events/state_events.hpp"
#include "states/game_options_state.hpp"
#include "states/main_game_state.hpp"
#include "states/main_menu_state.hpp"
#include "states/state.hpp"
#include <memory>
#include <sstream>
#include <stack>
#include <string>

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/WorkQueue.h>
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

using namespace Urho3D;
/**
* Using the convenient Application API we don't have
* to worry about initializing the engine or writing a main.
* You can probably mess around with initializing the engine
* and running a main manually, but this is convenient and portable.
*/
class MyApp : public Application {
  public:
    std::unique_ptr<Urho3D::Text> fps_text;
    std::stack<std::shared_ptr<GameState>> states;
    float time_;
    int framecount_;

    /**
    * This happens before the engine has been initialized
    * so it's usually minimal code setting defaults for
    * whatever instance variables you have.
    * You can also do this in the Setup method.
    */
    MyApp(Context *context) : Application(context) {
    }

    /**
    * This method is called _before_ the engine has been initialized.
    * Thusly, we can setup the engine parameters before anything else
    * of engine importance happens (such as windows, search paths,
    * resolution and other things that might be user configurable).
    */
    virtual void Setup() {
        // These parameters should be self-explanatory.
        // See http://urho3d.github.io/documentation/1.32/_main_loop.html
        // for a more complete list.
        engineParameters_["FullScreen"] = false;
        engineParameters_["WindowWidth"] = 1280;
        engineParameters_["WindowHeight"] = 720;
        engineParameters_["WindowResizable"] = true;
        engineParameters_["ResourcePrefixPaths"] = "/usr/share/Urho3D/Resources/";
        // Override the resource prefix path to use. "If not specified then the
        // default prefix path is set to URHO3D_PREFIX_PATH environment
        // variable (if defined) or executable path."
        // By default mine was in /usr/local/share, change as needed.
        // Remember to use a TRAILING SLASH to your path! (for unknown reason)
        // engineParameters_["ResourcePrefixPath"] = "/usr/local/share/Urho3D/Bin/";
    }

    /**
    * This method is called _after_ the engine has been initialized.
    * This is where you set up your actual content, such as scenes,
    * models, controls and what not. Basically, anything that needs
    * the engine initialized and ready goes in here.
    */
    virtual void Start() {
        states.push(std::make_shared<MainMenuState>(context_));

        GetSubsystem<Urho3D::UI>()->GetRoot()->SetDefaultStyle(
            GetSubsystem<Urho3D::ResourceCache>()->GetResource<Urho3D::XMLFile>(
                "UI/DefaultStyle.xml"));

        SubscribeToEvent(E_STATE_CHANGE, URHO3D_HANDLER(MyApp, HandleStateChange));
        SubscribeToEvent(Urho3D::E_KEYDOWN, URHO3D_HANDLER(MyApp, HandleKeyDown));
        SubscribeToEvent(Urho3D::E_UIMOUSECLICK, URHO3D_HANDLER(MyApp, HandleControlClicked));
        SubscribeToEvent(Urho3D::E_UPDATE, URHO3D_HANDLER(MyApp, HandleUpdate));
        states.top()->Start();
    }

    /**
    * Good place to get rid of any system resources that requires the
    * engine still initialized. You could do the rest in the destructor,
    * but there's no need, this method will get called when the engine stops,
    * for whatever reason (short of a segfault).
    */
    virtual void Stop() {
    }
    void HandleControlClicked(StringHash eventType, VariantMap &event_data) {
        states.top()->HandleControlClicked(eventType, event_data);
    }
    /**
    * Every frame's life must begin somewhere. Here it is.
    */
    void HandleBeginFrame(StringHash eventType, VariantMap &eventData) {
        // We really don't have anything useful to do here for this example.
        // Probably shouldn't be subscribing to events we don't care about.
    }

    /**
    * Input from keyboard is handled here. I'm assuming that Input, if
    * available, will be handled before E_UPDATE.
    */
    void HandleKeyDown(StringHash eventType, VariantMap &event_data) {
        states.top()->HandleKeyDown(eventType, event_data);
    }

    /**
    * You can get these events from when ever the user interacts with the UI.
    */
    /**
* Your non-rendering logic should be handled here.
* This could be moving objects, checking collisions and reaction, etc.
*/
    void HandleUpdate(StringHash eventType, VariantMap &eventData) {
        /*
         * float timeStep = eventData[Urho3D::Update::P_TIMESTEP].GetFloat();
        framecount_++;
        time_ += timeStep;

        if (time_ >= 1) {
            std::string str;
            str.append(" frames in ");
            {
                std::ostringstream ss;
                ss << time_;
                std::string s(ss.str());
                str.append(s.substr(0, 6));
            }
            str.append(" seconds = ");
            {
                std::ostringstream ss;
                ss << (float)framecount_ / time_;
                std::string s(ss.str());
                str.append(s.substr(0, 6));
            }
            str.append(" fps");
            Urho3D::String s(str.c_str(), str.size());
            fps_text->SetText(s);
            URHO3D_LOGINFO(s); // this show how to put stuff into the log
            framecount_ = 0;
            time_ = 0;
        }
*/
        states.top()->HandleUpdate(eventType, eventData);
    }
    /**
    * Anything in the non-rendering logic that requires a second pass,
    * it might be well suited to be handled here.
    */
    void HandlePostUpdate(StringHash eventType, VariantMap &eventData) {
        // We really don't have anything useful to do here for this example.
        // Probably shouldn't be subscribing to events we don't care about.
    }
    /**
    * If you have any details you want to change before the viewport is
    * rendered, try putting it here.
    * See http://urho3d.github.io/documentation/1.32/_rendering.html
    * for details on how the rendering pipeline is setup.
    */
    void HandleRenderUpdate(StringHash eventType, VariantMap &eventData) {
        // We really don't have anything useful to do here for this example.
        // Probably shouldn't be subscribing to events we don't care about.
    }
    /**
    * After everything is rendered, there might still be things you wish
    * to add to the rendering. At this point you cannot modify the scene,
    * only post rendering is allowed. Good for adding things like debug
    * artifacts on screen or brush up lighting, etc.
    */
    void HandlePostRenderUpdate(StringHash eventType, VariantMap &eventData) {
        // We could draw some debuggy looking thing for the octree.
        // scene_->GetComponent<Octree>()->DrawDebugGeometry(true);
    }
    /**
    * All good things must come to an end.
    */
    void HandleEndFrame(StringHash eventType, VariantMap &eventData) {
        // states_to_delete.clear();
        // We really don't have anything useful to do here for this example.
        // Probably shouldn't be subscribing to events we don't care about.
    }

    std::shared_ptr<GameState> createState(unsigned int state_id) {
        switch (state_id) {
        case GAMEOVER:
            std::cout << "state creation for this type not implemented" << std::endl;
            break;
        case GAMEPAUSE:
            std::cout << "state creation for this type not implemented" << std::endl;
            break;
        case GAMEMAIN:
            return std::make_shared<MainGameState>(context_);
            break;
        case MENUMAIN:
            return std::make_shared<MainMenuState>(context_);
            break;

        case OPTIONS:
            return std::make_shared<GameOptionsState>(context_);
            break;
        default:
            std::cout << "state not found" << std::endl;
            exit(EXIT_FAILURE);
        }
        return NULL;
    }

    void HandleStateChange(StringHash eventType, VariantMap &eventData) {
        std::cout << "event caught" << std::endl;
        unsigned int task_id = eventData[state_change::P_TASK].GetUInt();
        unsigned int state_id = eventData[state_change::P_STATE].GetUInt();

        switch (task_id) {
        case POP:
            std::cout << "POP" << std::endl;
            states.top()->Stop();
            states.pop();
            if (states.empty()) {
                std::cout << "states is empty. shutting down" << std::endl;
                engine_->Exit();
                exit(EXIT_SUCCESS);
            }
            else
            {
                std::cout << "starting top" << std::endl;
                states.top()->Start();
                std::cout << "starting top" << std::endl;
            }
            break;

        case CHANGE:
            states.pop();
            states.push(createState(state_id));
            states.top()->Start();
            std::cout << "change " << std::endl;
            break;

        case PUSH:
            std::cout << "push: ";
            states.top()->unsubscribe_events();
            states.push(createState(state_id));
            states.top()->Start();
            break;
        }
        std::cout << states.size() << std::endl;
    }
};

/**
* This macro is expanded to (roughly, depending on OS) this:
*
* > int RunApplication()
* > {
* > Urho3D::SharedPtr<Urho3D::Context> context(new Urho3D::Context());
* > Urho3D::SharedPtr<className> application(new className(context));
* > return application->Run();
* > }
* >
* > int main(int argc, char** argv)
* > {
* > Urho3D::ParseArguments(argc, argv);
* > return function;
* > }
*/
URHO3D_DEFINE_APPLICATION_MAIN(MyApp)
