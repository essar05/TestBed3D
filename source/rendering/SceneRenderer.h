#pragma once

#include <Ess3D/gl/Shader.h>
#include <Ess3D/3d/camera/Camera3D.h>
#include <Ess3D/3d/model/Model.h>
#include <glm/glm.hpp>

class SceneRenderer {
  public:
    SceneRenderer();
    SceneRenderer(float _width, float _height);
    ~SceneRenderer();

    void render();
    Ess3D::Camera3D* getCamera();

  private:
    Ess3D::Shader* _shader;
    Ess3D::Camera3D* _camera;
    Ess3D::Model* _nanosuit;
    Ess3D::Model* _cybertruck;

    glm::mat4 _model;
    glm::mat4 _view;
    glm::mat4 _projection;

    float _width;
    float _height;

};

