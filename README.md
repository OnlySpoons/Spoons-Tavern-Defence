Spoons: Tavern Defence

Change Log 02/05/2021 - Martin & Thomas
- Added ScoreEvent to increase the _score variable in game
- Added PlayerDamageEvent to do damage to the player
- Added Overworld class to handle initial load
- Tweaked classes to take model pointers instead of path strings, allowing for instancing
- Added wave system to Game
- Added function to disable enemy on death
- Tweaked classes to accomodate above changes


Change Log 01/05/2021 - Martin
- Added Zombie class
- Added Seek behaviour to follow a target.
- Added Align behaviour to face a target.
- Added BlendedSteering behaviour to blend between Seek and Align
- Tweaked some classes to accomodate AI behaviours


Change Log 28/04/2021 - Martin & Thomas
- Created a PhysicsEntity class to inherit from Entity to allow distiction between entities without physics
- Added Weapon class for weapons to inherit from
- Added AssaultRifle class to be the starting weapon
- Added raycasting to Physics
- Added jumping and firing to player
- Added DamageEvent for when a weapon is fired
- Tweaked transform class to fix issues with matrix calculations
- Tweaked gravity to address floatiness problem
- Fixed issue with renderScene where the passed camera was dereferenced incorrectly


Change Log 20/04/2021 - Martin & Thomas
- Fully implemented Bullet physics simulation and added gravity to all objects
- Box, Sphere, and Capsule colliders implemented as basic shape colliders
- Mesh collider implemented based on mesh data
- Compound collider implemented for objects with multiple meshes
- Player now uses a Capsule collider
- Added Bullet debug mode to Renderer which allows visualisation of the simulation in wireframe mode


Change Log 26/03/2021 - Thomas
- Added .h and .cpp files from Physics branch


Change Log 10/03/2021 - Martin & Thomas
- Refactored Objects to be aware of which render pass it is
- Added Transform Class to replace ObjectData struct
- Refactored codebase to utilise the Transform class more effectively


Change Log 09/03/2021 - Martin & Thomas
- Refactored Renderer into functions for each pass
- Changed loadOverworld to change the current scene instead of setting it after it's loaded


Change Log 04/03/2021 - Martin

- Refactored Scene to promote usage of it's functions
- Refactored loadOverworld function to utilise scene functions
- Tweaked dispatcher to exit if the event is handled


Change Log 27/02/2021 - Martin

- Refactored Renderer to take a Scene and Camera when rendering instead of when instantiated
- Renamed variables to begin with an underscore and a lowercase letter as opposed to an underscore and an uppercase letter


Change Log 22/02/2021 - Martin & Thomas

- Added Event class for all events to inherit from
- Added EventType enumerator to track events
- Added Dispatcher class to track subscribers and post events
- Added abstract Observer class for observers to inherit from


Change Log 11/02/2021 - Martin & Thomas

- Implemented Shadows
- Implemented post-processing


Change Log 12/01/2021 - Martin & Thomas

- Changed how rendering works to abstract the shader from objects into the renderer


Change Log 08/01/2021 - Martin & Thomas

- Fixed Memory leaks


Change Log 08/01/2021 - Martin

- Abstracted input into the static input class
- Changed Player to control reactions to input
- **Warning** This build may have memory leaks


Change Log 05/01/2021 - Martin

- Change ObjectData to take an angle and direction to simplify the rendering of objects.


Change Log 16/12/2020 - Martin & Thomas

- Added Actor Class to allow for game side players to inherit from
- Added game side Player class which inherits from Actor
- Refactored Game, Engine, and Camera to accomodate an Actor.
- **Most Important Change** Changed "GameEngine" namespace to "Spoonity".


Change Log 9/12/2020 - Martin & Thomas

- Updated GameObject class to better reflect it's usage
- Updated Camera to remove flight
- Updated Function names to better fit convention


Change Log 9/12/2020 - Martin & Thomas

- Added Game class which inherits from Engine to control game logic
- Added pure virtual gameLoop function which is called from runtimeLoop
- Refactored Engine to accomodate being virtual
- Updated Main to create an instance of Game


Change Log 9/12/2020 - Martin & Thomas

- Refactored Renderer to render objects from a scene


Change Log 8/12/2020 - Martin, Thomas & Harry

- Added Scene class to control GameObjects
- Tweaked other classes


Change Log 8/12/2020 - Martin & Thomas

- Added Skybox class to inherit from GameObject
- Tweaked classes to accomodate Skybox


Change Log 7/12/2020 - Martin & Thomas

- Added abstract GameObject class
- Tweaked classes to fix warnings


Change Log 7/12/2020 - Martin & Thomas

- Refactored Mesh and Model classes to have both .h and .cpp files


Change Log 2/12/2020 - Martin

- Added sprinting to Camera


Change Log 30/11/2020 - Martin & Thomas

- Tweaked model loading to fix texturing errors
- Added Rendering for skybox

Change Log 30/11/2020 - Thomas

- Updated Model.h to account for local coordinates within object files


Change Log 27/11/2020 - Martin

- Created Engine class to control the engine, and better abstract game logic from game engine backend
- Created Renderer class to render the scene each frame
- Added Model and Mesh classes to load models


Change Log 26/11/2020 - Martin & Thomas

- Established convensions and refactored code accordingly


Change Log 25/11/2020 - Martin

 - Updated Window class and abstracted the callback functions into a static Input class
 - Added exceptions and exception handling


Change Log 24/11/2020 - Martin & Thomas

 - Created Window Class to control the creation of the window
 - Added camera class for use with window class in future
