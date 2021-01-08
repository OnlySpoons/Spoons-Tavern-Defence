Spoons: Tavern Defence

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
