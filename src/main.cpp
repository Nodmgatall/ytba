
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/UI/UI.h>

#include <iostream>
#include <entityx/entityx.h>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Urho3D {
class Node;
class Scene;
class Sprite;
}

using namespace Urho3D;
class testclass : public Application {
    URHO3D_OBJECT(testclass, Application);
    testclass(Context *context) : Application(context) {
    }

    void Setup()
    {
        engineParameters_["WindowTitle"] = "YTBA";
        engineParameters_["FullScreen"] = false;
        engineParameters_["Sound"] = false;
    std::cout << "small change " << std::endl;
    }

    void Start()
    {
        
    }

    void Stop()
    {
        engine->DumpResources(true);
    }
};

class ytba : public testclass {
URHO3D_DEFINE_APPLICATION_MAIN(ytba)
    ytba(Context *context) : testclass(context) {
    }
};
int main() {
    glm::vec2 lol(1.f, 2.f);
    glm::vec2 rofl(2.f, 3.f);
    std::cout << glm::to_string(lol + rofl) << std::endl;
    std::cout << "hello world" << std::endl;
    
    

    return 1;
}
