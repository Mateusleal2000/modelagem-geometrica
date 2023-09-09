#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.hpp"
#include "Scene.hpp"
#include "Viewport.hpp"

class Camera{
  public:
    // metodo possivelmente substituível pelas coisas do openGL
    void rayCast(Scene* scene, Viewport* vp);
  private:
    Point3 coord;
    Point3 up;
    Point3 eye;
};
#endif