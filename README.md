## Highlighted features
- Component based system
- Multi SDL input system, Bind SDL codes to functionality
- Collision system using colliders of PhysX
- Resource management, Textures and Sound only get loaded in once
- A 3D rendered world of 2D png’s with DirectX11
- HUD using ImGui, Automatically updates by binding memory addresses
- Sound with SoLoud

## Required libs
- Use Vcpkg to automatically install all needed 
- Download “vcpkg package manager” in visual studio installer
- $git clone https://github.com/microsoft/vcpkg.git 
- $cd vcpkg 
- $bootstrap-vcpkg.bat
- Libraries can also be manually installed.
- Put the required libraries in you IDE and cmake will find them.
- Required libs: SDL2, Stb, Glm, PhysX, ImGui and any version of DirectX11

## Manual
*How-To-Build - Visual Studio*
1. Open the Cmake project with visual studio by right clicking in the folder and selecting “Open with visual studio”.
![App Screenshot](https://github.com/KnipTang/ReVengine/blob/main/DocumentationImages/HowToBuild1.png)

3. In the Visual Studio IDE, Select Tools < Command line < Developer Command Prompt.
![App Screenshot](https://github.com/KnipTang/ReVengine/blob/main/DocumentationImages/HowToBuild2.png)

4. In the Developer command windows, execute $vcpkg install.
![App Screenshot](https://github.com/KnipTang/ReVengine/blob/main/DocumentationImages/HowToBuild3.png)

5. Wait until all the libraries have been downloaded and then close Visual Studio. Open it again with the same method as step 1 and wait until the output window has finished building. Once finished ReVengine-Game.exe will be build and able to execute.
![App Screenshot](https://github.com/KnipTang/ReVengine/blob/main/DocumentationImages/HowToBuild4.png)

## Docmumentation - Getting-Started
**Basics**
In Game.cpp you will find a standard given function that returns a scene object. This object will be created and passed to the main game loop.

You can add game objects to this scene object. These game objects and only these objects will be processed/executed during run time. Every game object has transform component by default.
```
Rev::GameObject* exampleObject = new Rev::GameObject{}; 
scene->addGameObject(exampleObject);
```

Components can be added to game objects with the AddComponent function.
```
GameObject->AddComponent<Component class name>(GameObject, Component constructor arguments)
player->addComponent<Rev::CompCollision>(player.get(), physicsHandle, false, false, glm::vec3{0.1f, 1, 0.1f});
```
Custom components can be created by inheriting from BaseComponent. Functions like Update and Render can be overwritten to create custom behaviors. Examples of this can be found in the ReVengine-Engine/GameObjects/Components.

**Render Component**
Firstly, create Texture object by calling the load function of the resource management singleton object. Include a name for this texture and the filepath of the png file that you want to render.
```
Rev::Texture* enemyTexture = Rev::Rev_CoreSystems::pResourceManager->LoadResource("Enemy", enemyDoomFilePath);
```
Create a standard shader or create your own custom shader by inheriting from BaseShader
```
Rev::TextureShader* textureShader = new Rev::TextureShader{};
```
Besides a texture and shader, a render component needs a camera component to calculate the view matrix. A standard camera component can be passed in as an argument or a camera component that is linked to another game object can be used.
```
Floor->addComponent<Rev::CompRender>(Floor, player.cameraComp, textureShader, floorTexture);
```

**Input Component**
An input component can be added to a game object and used to bind SDL scancodes for keys and SDL button for mouse to lambda functionality.  
```
inputComp->BindKeyAction(SDL_SCANCODE_W, [playerTrans]() { playerTrans->MoveForward(1); });
```

**Collision Component**
Adding a collision component will add a collider to that game object. This component needs a physics handle. You can get this physics handle by calling GetPhysicsHandle on the current scene you want to render the object in.
```
scene->getPhysicsHandle(); 
```
When two colliders collide the OnContact function of each of those colliders will execute. You can set the functionality of every collider component by calling the SetOnContactFunction. This function will take a lambda with a collision component as parameter. This parameter is the collision component of the object it collides with. Because of this parameter, functionality for both the object itself and the object it collides with can be set. 
```
Rev::CompCollision& bulletColl = *bullet->addComponent<Rev::CompCollision>(bullet, physicsHandle});
bulletColl.SetOnContactFunction(
	Rev::CompCollision* other) {
	Rev::GameObject& obj = *other->GetGameObject();
	if (obj.m_Tag == "Enemy") obj.Destroy();
});
```

**Sound**
The sound functionality is part of the Rev_CoreSystems. Mp3 and Wav are both supported file formats. A file only needs to be loaded once and can be played infinitely after.

To load in a sound file firstly include Rev_CoreSystems.h and Sound/Rev_Sound.h. Call the sound object of the core systems and the load function of the sound library. This function takes in a string “name”. This name will be used later to play the sound. As second argument, it takes the file path and file to the sound.
```
Rev::Rev_CoreSystems::pRevSound->LoadSound("pew", resourceFolder + SoundPew);
```
Once loaded in, the sound can be played from anywhere by including the Rev_CoreSystems header and calling the PlayRevSound function with the sound name.
```
Rev::Rev_CoreSystems::pRevSound->PlayRevSound("pew");
```

**HUD**
The HUD is also part of the Rev_CoreSystems header. By including this header and Rendering/HUD/UI.h you can start subscribing elements to the HUD.

To display anything on the HUD, call the function SubscribeElement of the Rev_CoreSystems pUI object. This function takes in a string and the memory address of a float value. This results in the values of the HUD automatically updating when the float value from that memory address get manipulated.
```
Rev::Rev_CoreSystems::pUI->SubscribeElement("Health: ", &healthPlayerComp->GetHealth());
```
![App Screenshot](https://github.com/KnipTang/ReVengine/blob/main/DocumentationImages/HUDHealth.png)

**Adding game objects to a scene during runtime**
You can get a handle to the global scene manager in the Rev_CoreSystems. From this handle you can get the current active scene of a scene by its unique ID or its tag. This way you can simply call the AddGameObject function.
```
Rev::Rev_CoreSystems::pSceneManager->GetSceneByTag(“GameScene”)->addGameObject(bullet);
```

**Event / Game loop**
![App Screenshot](https://github.com/KnipTang/ReVengine/blob/main/DocumentationImages/GameLoop.png)

## Report and Critical Reflection
**Component based Gameobjects**
I can honestly say that I’m proud of my gameobject-component system. I have made systems like these before, but they always had some deadly quirks. These past systems mostly failed because I ran away from more complex concepts. 

This time, I took my time and rediscovered the wonderful world of templates. I even took it a step further by learning about concepts and template arguments. 

I used template arguments in my AddComponent function to be able to have arguments in the constructor of the components the user is trying to add. Because of the nature of templates, no error codes would be collected when the user provides wrong arguments to a component. These arguments only get validated while compiling.

**Graphics API / Renderer**
I never setup a graphics API myself before this project. I went with DirectX11 for this project because I feel like it is a good combination of difficulty while still being low level. Doing this for this project took me a long time. In the process of doing so I relearned various basic graphics programming concepts I believed to have understood before. I believe the time and effort I put into this part of the engine will be worth it in the long term of my software development career. 

DirectX has their own math library and enforces you to use this while working with their API. Because I openly used the glm library intended to be used by the engine and user, multiple conversions from glm types to DirectX types must be made nearly every frame. I tried to limit this by using dirty flags and only updating curtained parts when necessary. But I still believe at this point that it would be better to stick with one math library for your whole engine or abstract the graphics specific libraries used away to only a specific portion of the engine. 

**Input**
When I finished the input system, I was initially satisfied with my approach. I have a global input object and subscribe input components to this object. Every frame, the input object loops over all the input components and checks if a curtained SDL code that is bound to a lambda using an unordered map is actively pressed. 

While actively using this approach I realized that there was no reason to make this a component. Behaviour you want to execute when a certain key or mouse gets pressed should not be specifically linked to one game object. The input component also has no use case of any of the overwritable functions like update or render other components take great use in. Therefore, I believe a better approach would be to have one global input manager object and input objects that can be freely made and added or removed to the input manager freely. 

Another minor but still noticeable observation I made every time I interacted with my own input system was the forced need to include SDL headers. While this is not an issue, I would rather abstract any SDL dependency away from my user and make my own enum class that I would later convert to SDL specific scancodes in the backend.

**Collision / Physics?**
In previous projects I always ran away from using any physics or collision libraries. In my last game engine, I even went as far as spending two weeks making my own collision system. This system sadly fell apart when being exposed to certain edge cases. 

Therefore, I wanted to use a library for collision detection for this engine. After looking over the available options there are on the market I went with PhysX because it’s the most used one in the AAA industry and has the best documentation I could find compared to my other options. After setting it up and computing some colliders I was pleasantly surprised with the existence of Nvidia’s debug tool PhysX Visual Debugger, where I could visualize all the colliders in real time! 

After messing around with PhysX some more I came to the realization that the library had way more to offer than I needed and locked itself up in its own actor and transform ecosystem. Earlier in the project I made my own transform component. Every gameobject standardly gets assigned one of these. This made it rather complex to work with a physics library that had its own transform, while I only needed the collision detection functionality of said library. There is no practically way in the PhysX library where I could disable the physics functionality of the colliders while still being able to detect collisions. I ended up checking for each gameobject that had a collider if their transform changed, and if so to update the PhysX transform. This way both different transforms kept in sync with each other.

Once this main issue was resolved I made a collision component where the user can set the functionality when two colliders collide with each other. The user can manipulate both the object itself as well as the object it collides with.
In a potential remake of this project, I would not make my own transform component and just fully stick with the physics and transform logic of PhysX. I believe that when I would abstract the PhysX library away from the user, the library has way more to offer to my user than I could every develop on my own.

**Camera**
In past projects I used provided camera systems and view matrixes without equally grasping the mathematics behind these. I gave myself a couple days to sit down to make my own implementation and understand every step from position and rotation to view matrix.

Issue 1: A camera component can be added to any gameobject the user pleases. This functionality doesn’t make sense as long as there is no correct way to handle the existence of multiple cameras.

Issue 2: Besides this the camera component always must be passed in every render component to calculate the view matrix of this object. This does not make sense since the view matrix of a camera component is the same regardless of what object needs to be rendered.

I could resolve both issues by having one camera manager object. Every Camera component that would be made could subscribe to this camera manager. In the render components a reference to the view matrix of a specific camera could be grabbed from this manager and easily changed when the active camera would change during runtime. 

**Optimizations**
These are the first optimization patterns I would implement if I would continue working on this engine.

*Memory pool*
Because the primary use case of my engine is doom like fps game. An optimization pattern like a memory pool is essential. Instead of allocating every bullet shot the moment it gets fired, it would be a better idea to allocate a certain number of bullets from the start and just enable/disable them the moment you need them. This way the bullets memory is reusable and there is no unnecessary computing to be done during runtime.

*Instance rendering / Fly weight pattern*
When starting up my example “doom” game I load in around 100 if the same floor tiles. The texture of this floor tile only gets loaded in once because of the resource management of textures in my engine, but all other components of the floor gameobject get computed separately again for each tile. This is a lot of unnecessary computing for an object that could just be rendered as the same object. This would be a perfect use case of instance rendering, a fairly beginner graphics programming technique.

For mass rendering of objects that are mostly the same but have some variants among them. The flyweight pattern could be an amazing pick.

I would love to implement these and abstract them away from the user to a degree that these patterns get applied without the user even realizing it. 
