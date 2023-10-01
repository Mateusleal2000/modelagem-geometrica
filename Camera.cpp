#include "Camera.hpp"

Camera::Camera(QVector3D __eye = QVector3D(0,0,0) ,  QVector3D __worldUp = QVector3D(0,1,0)){
    eye = __eye;
    worldUp = __worldUp;
    yaw = YAW;
    pitch = PITCH;
    updateCameraGeometry();
}


void Camera::updateCameraGeometry(){

}