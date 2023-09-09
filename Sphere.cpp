#include "Sphere.hpp"


Sphere::Sphere(double rad, Point3 & center): radius(rad), center(center){
}

void Sphere::classify(Node *node){
    return;
}

void Sphere::setRadius(double rad){
    radius = rad;
}

void Sphere::setCenter(Point3 &center){
    this->center = center;
}

double Sphere::getRadius(){
    return radius;
}

Point3* Sphere::getCenter(){
    return &center;
}
