#include "Box.hpp"

Box::Box()
{
  boxPoints.reserve(8);
  boxPoints.resize(8);

  boxIndex.reserve(8);
  boxIndex.resize(8);
}

Box::Box(Point3 tlb, Point3 brf)
{
  boxPoints.reserve(8);
  boxPoints.resize(8);
  boxPoints[PointLabel::TLB] = tlb;
  boxPoints[PointLabel::BRF] = brf;

  boxIndex.reserve(8);
  boxIndex.resize(8);
}

Point3 &Box::getPoint(int label)
{
  return boxPoints.at(label);
}

unsigned int Box::getIndex(int index)
{
  return boxIndex.at(index);
}

float Box::getBmin(int axis)
{
  Point3 top_left_back = getPoint(PointLabel::TLB);
  Point3 bottom_right_front = getPoint(PointLabel::BRF);
  float min = top_left_back[axis] <= bottom_right_front[axis] ? top_left_back[axis] : bottom_right_front[axis];
  return min;
}

float Box::getBmax(int axis)
{
  Point3 top_left_back = getPoint(PointLabel::TLB);
  Point3 bottom_right_front = getPoint(PointLabel::BRF);
  float max = top_left_back[axis] > bottom_right_front[axis] ? top_left_back[axis] : bottom_right_front[axis];
  return max;
}

void Box::calcBoxPoints()
{
  Point3 tlb = boxPoints[0];
  Point3 brf = boxPoints[1];
  for (int i = 0; i < 3; i++)
  {
    boxPoints[(i + 1) * 2] = tlb;
    boxPoints[(i + 1) * 2][i] = brf[i];
    boxPoints[(i + 1) * 2 + 1] = brf;
    boxPoints[(i + 1) * 2 + 1][i] = tlb[i];
  }
}

Point3 Box::getCenter(){
  return Point3({
    (this->getPoint(PointLabel::TLB)[0] + this->getPoint(PointLabel::BRF)[0] )/2.0f, 
    (this->getPoint(PointLabel::TLB)[1] + this->getPoint(PointLabel::BRF)[1] )/2.0f,
    (this->getPoint(PointLabel::TLB)[2] + this->getPoint(PointLabel::BRF)[2] )/2.0f
  });
}

Point3 Box::getExtent(){
  return Point3({
    fabs(this->getPoint(PointLabel::TLB)[0] - this->getPoint(PointLabel::BRF)[0] ), 
    fabs(this->getPoint(PointLabel::TLB)[1] - this->getPoint(PointLabel::BRF)[1] ),
    fabs(this->getPoint(PointLabel::TLB)[2] - this->getPoint(PointLabel::BRF)[2] )
  });
}