# CMakeList.txt : CMake project for WeatherWizard, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("WeatherWizard")

set(WW_RESOURCE_FILES
	"Assets/Wand-Summer.png")
set(WW_INCLUDE_DIRECTORIES
    "./src"
    "./src/Controls"
    "./src/Managers"
    "./src/Renderers"
    ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)

# Add source to this project's executable.
add_executable (WeatherWizard "src/WeatherWizard.cpp" "src/WeatherWizard.h" "src/olcPixelGameEngine.h" "src/Renderers/Renderer.h" "src/main.cpp" "src/WandBar.h"  "src/SeasonWand.h" "src/SkyColor.h" "src/Season.h" "src/Renderers/WandBarRenderer.cpp" "src/Managers/GameEntityManager.h" "src/Managers/GameEntityManager.cpp" "src/Renderers/SkyBoxRenderer.h" "src/Renderers/SkyBoxRenderer.cpp" "src/Managers/AssetManager.h" "src/Asset.h" "src/Managers/AssetManager.cpp" ${WW_RESOURCE_FILES} "src/WandBar.cpp" "src/Renderers/MapRenderer.h" "src/Renderers/MapRenderer.cpp" "src/Map.h" "src/Map.cpp" "src/Wizard.h" "src/Camera.h" "src/Renderers/WizardRenderer.h" "src/Renderers/WizardRenderer.cpp"  "src/Controls/MovementControl.h" "src/Controls/MovementControl.cpp" "src/CollisionCommand.h" "src/MapBlockCorners.h" "src/Controls/InteractionControl.h" "src/Controls/InteractionControl.cpp" "src/Controls/InteractionControlPayload.h" "src/Wizard.cpp" "src/Collectable.h" "src/Book.h" "src/MapBlockRef.h" "src/Renderers/EndGameRenderer.h" "src/Renderers/EndGameRenderer.cpp" "src/Controls/EndGameControl.h" "src/Controls/EndGameControlPayload.h" "src/Controls/EndGameControl.cpp" "src/Renderers/MenuRenderer.h" "src/Renderers/MenuRenderer.cpp" "src/FaceDirection.h")

target_include_directories(WeatherWizard PUBLIC ${WW_INCLUDE_DIRECTORIES})

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E create_symlink
                   ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/Assets)
# TODO: Add tests and install targets if needed.
