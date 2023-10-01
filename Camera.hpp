#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.hpp"
#include "Scene.hpp"
#include "Viewport.hpp"
#include <QVector3D>

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SENSITIVITY =  0.1f;

class Camera{
  public:
  Camera() = default;
  Camera(QVector3D __eye, QVector3D __worldUp);
  private:
  QVector3D eye;
  QVector3D front;
  QVector3D right;
  QVector3D up;
  QVector3D worldUp;
  float yaw;
  float pitch;

  private:
  void updateCameraGeometry();
};
#endif