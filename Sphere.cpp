#include "Sphere.hpp"


Sphere::Sphere(double rad, Point3 & center): radius(rad), center(center){
}

void Sphere::classify(Node *node){
    Point3 brf = node->getBox()->getBRF();
    Point3 tlb = node->getBox()->getTLB();
    Point3 temp;
    
    checkIntersect(brf);
    for (int i=0;i<3;i++){
        temp = brf;
        temp[i]=tlb[i];
        checkIntersect(temp);
    }

    checkIntersect(tlb);
    for (int i=0;i<3;i++){
        temp = tlb;
        temp[i]=brf[i];
        checkIntersect(temp);
    }
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
