# Weather Wizard

Weather Wizard is a game made in C++ using [Javidx9/OneLoneCoder](https://github.com/OneLoneCoder)'s
PixelGameEngine. It's a 2D Platformer and it consists of our main character, the Wizard, trying to
get to a portal by going through the level. The Wizard has weather powers, which means that he can
transform the weather blocks around him by using his wands. The blocks act differently in each weather:

- Hot blocks are only solid in Summer
- Ice blocks are only solid in Winter
- Wind blocks only blow strongly in Fall
- Flower blocks are only climbable in Spring

> This game was developed for the OneLoneCoderK::CodeJam2022. It got ranked #25 out of 81 entries
> overall. Its best ranking was in the `Impression` category (`"Score low for unimpressive, high
> for impressive"`).

## Build

The project is built using CMake:

```sh
cmake --build ./out
```

It can also be compiled for the browser (!!) via WebAssembly. To do so, you must get the
[https://emscripten.org/docs/getting_started/](Emscripten) package and launch their pre-configured
terminal and then run the command to build. I couldn't get their `cmake` environment to work, so I
just ran the full thing everytime. It's ugly, but it works (I should've created a `.bat` file or a
`Makefile` for this but I'm too lazy for that). Here's the full command:

```sh
em++ -std=c++17 -O2 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 "src/WeatherWizard.cpp" "src/main.cpp" "src/Renderers/WandBarRenderer.cpp" "src/Managers/GameEntityManager.cpp" "src/Renderers/SkyBoxRenderer.cpp" "src/Managers/AssetManager.cpp" "src/WandBar.cpp" "src/Renderers/MapRenderer.cpp" "src/Map.cpp" "src/Renderers/WizardRenderer.cpp" "src/Controls/MovementControl.cpp" "src/Controls/InteractionControl.cpp" "src/Wizard.cpp" "src/Renderers/EndGameRenderer.cpp" "src/Controls/EndGameControl.cpp" "src/Renderers/MenuRenderer.cpp" -o web-build/pge.html --preload-file ./Assets
```

> You can check out [this video](https://www.youtube.com/watch?v=MrI5kkVY6zk) for further instructions

## Notes

- The code isn't perfect and when the deadline was getting closer and closer, the code was transforming
more and more into spaghetti. It's still okay though, I was able to create a pretty cool architecture,
even if not the most optimized. I never really studied game design, so this is what I could come up with
from a pure code design standpoint (in a week)
- The 2D platformer collision algorithm was taken from a video by `Javidx9`