#pragma once

#include <Ess3D/core/IGameScreen.h>
#include <Ess3D/core/Config.h>
#include <Ess3D/core/State.h>
#include <Ess3D/gui/GUI.h>
#include "../Game.h"
#include "ScreenIndices.h"
#include "../game/Scene.h"
#include "../rendering/SceneRenderer.h"

class Game;
class InputManager;

class GameplayScreen : public Ess3D::IGameScreen {
  public:
    GameplayScreen();
    ~GameplayScreen();

    int getNextScreenIndex() const override;
    int getPreviousScreenIndex() const override;

    void build() override;
    void destroy() override;

    void step(float deltaTime) override; // step one simulation step forward (deltaTime)
    void update() override; // do non-physics updates
    void input(Ess3D::InputManager* inputManager) override; // handle input
    void render() override; // render
    void onSDLEvent(SDL_Event &event) override;

    void onEntry() override;
    void onExit() override;
    
  private:
    Game* _game = nullptr;

    Ess3D::Config* _config;
    Ess3D::State* _state;

    Ess3D::FrameBufferObject* _sceneFBO;

    Ess3D::FBORenderer* _fboRenderer;
    SceneRenderer* _sceneRenderer;

};

