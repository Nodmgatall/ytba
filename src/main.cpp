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
#include "states/main_menu_state.hpp"
#include "states/main_game_state.hpp"
#include <memory>
#include <stack>
#include <string>
#include <sstream>

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Skybox.h>

using namespace Urho3D;
/**
* Using the convenient Application API we don't have
* to worry about initializing the engine or writing a main.
* You can probably mess around with initializing the engine
* and running a main manually, but this is convenient and portable.
*/
class MyApp : public Application {
  public:
    int framecount_;
    float time_;
    Urho3D::SharedPtr<Urho3D::Text> text_;
        std::stack<std::unique_ptr<GameState>> states;

    /**
    * This happens before the engine has been initialized
    * so it's usually minimal code setting defaults for
    * whatever instance variables you have.
    * You can also do this in the Setup method.
    */
    MyApp(Context *context) : Application(context), framecount_(0), time_(0) {
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
        states.push(std::make_unique<MainGameState>(context_));
        states.top()->Start();
            SubscribeToEvent(E_STATE_CHANGE, URHO3D_HANDLER(MyApp, HandleStateChange));
    }

    /**
    * Good place to get rid of any system resources that requires the
    * engine still initialized. You could do the rest in the destructor,
    * but there's no need, this method will get called when the engine stops,
    * for whatever reason (short of a segfault).
    */
    virtual void Stop() {
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
    void HandleKeyDown(StringHash eventType, VariantMap &eventData) {
        using namespace KeyDown;
        int key = eventData[P_KEY].GetInt();
        if (key == KEY_ESC)
            engine_->Exit();

        if (key == KEY_TAB) {
            GetSubsystem<Input>()->SetMouseVisible(!GetSubsystem<Input>()->IsMouseVisible());
            GetSubsystem<Input>()->SetMouseGrabbed(!GetSubsystem<Input>()->IsMouseGrabbed());
        }
    }

    /**
    * You can get these events from when ever the user interacts with the UI.
    */
    void HandleControlClicked(StringHash eventType, VariantMap &eventData) {
        // Query the clicked UI element.
        UIElement *clicked = static_cast<UIElement *>(eventData[UIMouseClick::P_ELEMENT].GetPtr());
        if (clicked)
            if (clicked->GetName() == "Button Quit") // check if the quit button was clicked
                engine_->Exit();
    }
    /**
    * Your non-rendering logic should be handled here.
    * This could be moving objects, checking collisions and reaction, etc.
    */
    void HandleUpdate(StringHash eventType, VariantMap &eventData) {
        float timeStep = eventData[Update::P_TIMESTEP].GetFloat();
        framecount_++;
        time_ += timeStep;
        states.top()->HandleUpdate(eventType, eventData);
    
        if (time_ >= 1) {
            std::string str;
            str.append(
                "Keys: tab = toggle mouse, AWSD = move camera, Shift = fast mode, Esc = quit.\n");
            {
                std::ostringstream ss;
                ss << framecount_;
                std::string s(ss.str());
                str.append(s.substr(0, 6));
            }
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
            String s(str.c_str(), str.size());
            text_->SetText(s);
            URHO3D_LOGINFO(s); // this show how to put stuff into the log
            framecount_ = 0;
            time_ = 0;
        }

        if(states.empty()) engine_->Exit();
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
        //scene_->GetComponent<Octree>()->DrawDebugGeometry(true);
    }
    /**
    * All good things must come to an end.
    */
    void HandleEndFrame(StringHash eventType, VariantMap &eventData) {
        // We really don't have anything useful to do here for this example.
        // Probably shouldn't be subscribing to events we don't care about.
    }

    void HandleStateChange(StringHash eventType, VariantMap &eventData) {
        switch (eventData[state_change::P_TASK].GetUInt()) 
        {
            case POP:
                states.pop();
                if(states.empty())
                {
                    engine_->Exit();
                }
                break;
            case PUSH:
                std::cout << "pushed" << std::endl;
        }
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
