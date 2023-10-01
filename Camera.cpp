#include "Camera.hpp"

Camera::Camera() : QObject(){
    eye = QVector3D(0,0,0);
    worldUp = QVector3D(0,1,0);
    yaw = YAW;
    pitch = PITCH;
    viewMatrix = QMatrix4x4();
    updateCameraGeometry();
}

Camera::Camera(QVector3D __eye = QVector3D(0,0,0) ,  QVector3D __worldUp = QVector3D(0,1,0)) : QObject(){
    eye = __eye;
    worldUp = __worldUp;
    yaw = YAW;
    pitch = PITCH;

    viewMatrix = QMatrix4x4();
    updateCameraGeometry();
}

QMatrix4x4 Camera::getViewMatrix(){
    //viewMatrix.lookAt(QVector3D(0.0,0.0,0.0),QVector3D(0.0,0.0,-1.0),QVector3D(0.0,1.0,0.0));


    
	float * data = viewMatrix.data();
	for(int i = 0; i<16;i++){
		std::cout << data[i] << " ";
	}
	std::cout<<std::endl;
    std::cout << "eye " << eye.x() << " " << eye.y() << " " << eye.z() << std::endl;
    return viewMatrix;
}

void Camera::updateDown(){
    //eye -= front*SPEED;
    viewMatrix.translate(0,0,-SPEED);
    emit viewChanged(getViewMatrix());
}


void Camera::updateUp(){
    //eye += front*SPEED;

    viewMatrix.translate(0,0,SPEED);
    emit viewChanged(getViewMatrix());

}


void Camera::updateLeft(){
    //eye -= right*SPEED;

    viewMatrix.translate(SPEED,0,0);
    emit viewChanged(getViewMatrix());

}


void Camera::updateRight(){
    //eye += right*SPEED;
    
    viewMatrix.translate(-SPEED,0,0);
    emit viewChanged(getViewMatrix());
}

void Camera::updateUpArrow(){
    viewMatrix.translate(0,-SPEED,0);
    emit viewChanged(viewMatrix);
}


void Camera::updateDownArrow(){
    viewMatrix.translate(0,SPEED,0);
    emit viewChanged(viewMatrix);
}

void Camera::updateMouse(float xoffset, float yoffset){}


void Camera::updateCameraGeometry(){
    QVector3D newFront ;
    newFront.setX(qCos(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch)));
    newFront.setY(qSin(qDegreesToRadians(pitch)));
    newFront.setZ(qSin(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch)));


    newFront.normalize();
    //if(newFront.x() < 10e-5) newFront.setX(0);
    std::cout<<"Front "<<newFront.x() << " " << newFront.y() << " " << newFront.z() << "\n";
    
    //right = glm::normalize(glm::cross(Front, WorldUp));
    right = (QVector3D::crossProduct(newFront,worldUp));
    right.normalize();
    std::cout<< "Right "<<right.x() << " " << right.y() << " " << right.z() << "\n";


    up = (QVector3D::crossProduct(right,newFront));
    up.normalize();

    std::cout<< "Up " <<up.x() << " " << up.y() << " " << up.z() << "\n";
    

    
}