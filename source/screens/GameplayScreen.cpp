#include "GameplayScreen.h"
#include <glm/gtc/type_ptr.hpp>

GameplayScreen::GameplayScreen() {
  _game = Game::GetInstance();
  _config = Ess3D::Config::get();
  _state = Ess3D::State::get();

  _screenIndex = SCREEN_INDEX_GAMEPLAY;
}

GameplayScreen::~GameplayScreen() = default;

int GameplayScreen::getNextScreenIndex() const {
  return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const {
  return SCREEN_INDEX_MAINMENU;
}

void GameplayScreen::onEntry() {
  //Set to true to keep mouse in center always - this will work with getCursorDeltaPosition
  SDL_SetRelativeMouseMode(SDL_TRUE);
  //Set to true to show mouse cursor over screen
  //SDL_ShowCursor(SDL_TRUE);
}

void GameplayScreen::onExit() {}

void GameplayScreen::build() {
  _fboRenderer = new Ess3D::FBORenderer();
  _fboRenderer->initShader();
  _sceneFBO = new Ess3D::FrameBufferObject(_state->getWindow().get(), (GLsizei) _config->getWidth(), (GLsizei) _config->getHeight(), Ess3D::DepthBufferType::TEXTURE);
  _sceneRenderer = new SceneRenderer(_config->getWidth(), _config->getHeight());
}

void GameplayScreen::destroy() {
  delete _fboRenderer;
  delete _sceneFBO;
  delete _sceneRenderer;
}

void GameplayScreen::step(float deltaTime) {
}

void GameplayScreen::update() {
}

void GameplayScreen::input(Ess3D::InputManager *inputManager) {
  if(inputManager->isKeyDown(SDLK_ESCAPE)) {
    _currentState = Ess3D::ScreenState::EXIT_APPLICATION;
  }

  if (inputManager->isKeyDown(SDLK_w)) {
    _sceneRenderer->getCamera()->moveForward();
  }
  if (inputManager->isKeyDown(SDLK_s)) {
    _sceneRenderer->getCamera()->moveBackward();
  }
  if (inputManager->isKeyDown(SDLK_a)) {
    _sceneRenderer->getCamera()->moveLeft();
  }
  if (inputManager->isKeyDown(SDLK_d)) {
    _sceneRenderer->getCamera()->moveRight();
  }
  if (inputManager->hasMouseMoved()) {
    _sceneRenderer->getCamera()->look(inputManager->getCursorDeltaPosition());
  }
}

void GameplayScreen::render() {
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //bind FBO, all rendering will be done to this FBO's color buffer
  _sceneFBO->bind();

  //render scene
  _sceneRenderer->render();

  //unbind FBO, rendering will now be done to screen
  _sceneFBO->unbind();

  _fboRenderer->render(_sceneFBO);
}

void GameplayScreen::onSDLEvent(SDL_Event &event) {
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F3) {
    Ess3D::Config* config = Ess3D::Config::get();
    if (config->isInterpolationEnabled()) {
      printf("Disabling interpolation \n");
      Ess3D::Config::get()->disableInterpolation();
    } else {
      printf("Enabling interpolation \n");
      Ess3D::Config::get()->enableInterpolation();
    }
  }
}