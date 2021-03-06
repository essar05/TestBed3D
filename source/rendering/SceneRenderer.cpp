#include "SceneRenderer.h"
#include "../Game.h"
#include <Ess3D/resources/ModelCache.h>
#include <glm/gtc/type_ptr.hpp>

SceneRenderer::SceneRenderer() {}

SceneRenderer::SceneRenderer(float _width, float _height) {
  this->_width = _width;
  this->_height = _height;

  _nanosuit = Ess3D::ModelCache::getInstance()->getModel("models/ak47/ak47.obj");

  _shader = new Ess3D::Shader(true);

  _shader->loadShader(Ess3D::ShaderType::VERTEX, "shaders/Base3D.vs");
  _shader->loadShader(Ess3D::ShaderType::FRAGMENT, "shaders/Base3D.fs");
  _shader->compileShaders();

  _shader->addAttribute("vertexPosition");
  _shader->addAttribute("vertexNormal");
  _shader->addAttribute("vertexUV");

  _shader->linkShaders();

  _camera = new Ess3D::Camera3D(glm::vec3(0.0f, 0.0f, 40.0f));

  glEnable(GL_DEPTH_TEST);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

SceneRenderer::~SceneRenderer() {
  delete _shader;
  delete _camera;
  delete _nanosuit;
  delete _cybertruck;
}

void SceneRenderer::render() {
  Game* game = Game::GetInstance();

  glClearColor(0.30f, 0.20f, 0.00f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _shader->use();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.0f, -3.75f, 0.0f));
  model = glm::scale(model, glm::vec3(1.0f));
  glm::mat4 view = _camera->getViewMatrix();
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), _width / _height, 0.1f, 300.0f);

  glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(_shader->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(_shader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

  _nanosuit->render(_shader);

  _shader->unuse();
}

Ess3D::Camera3D* SceneRenderer::getCamera() {
  return this->_camera;
}