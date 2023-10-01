#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.hpp"
#include "Scene.hpp"
#include "Viewport.hpp"
#include <QVector3D>
#include <QMatrix4x4>
#include <QObject>
#include <QtMath>

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SENSITIVITY =  0.1f;
const float SPEED       =  0.5f;

class Camera : public QObject{

  Q_OBJECT

  public:
  Camera();
  Camera(QVector3D __eye, QVector3D __worldUp);
  QMatrix4x4 getViewMatrix();

  public slots:
  void updateLeft();
  void updateRight();
  void updateUp();
  void updateDown();
  void updateMouse(float xoffset,float yoffset);
  void updateUpArrow();
  void updateDownArrow();

  signals:
  void viewChanged(QMatrix4x4 view);

  private:
  QVector3D eye;
  QVector3D front;
  QVector3D right;
  QVector3D up;
  QVector3D worldUp;
  float yaw;
  float pitch;
  QMatrix4x4 viewMatrix;

  private:
  void updateCameraGeometry();
};
#endif