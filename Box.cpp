#include "Box.hpp"

Box::Box()
{
  boxPoints.reserve(8);
  boxPoints.resize(8);

  boxIndex.reserve(8);
  boxIndex.resize(8);

  normals.reserve(8);
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

Point3 Box::getMax()
{
  float maxX = std::max((this->getPoint(PointLabel::TLB).x()), this->getPoint(PointLabel::BRF).x());
  float maxY = std::max((this->getPoint(PointLabel::TLB).y()), this->getPoint(PointLabel::BRF).y());
  float maxZ = std::max((this->getPoint(PointLabel::TLB).z()), this->getPoint(PointLabel::BRF).z());
  return Point3(maxX, maxY, maxZ);
}
Point3 Box::getMin()
{
  float minX = std::min((this->getPoint(PointLabel::TLB).x()), this->getPoint(PointLabel::BRF).x());
  float minY = std::min((this->getPoint(PointLabel::TLB).y()), this->getPoint(PointLabel::BRF).y());
  float minZ = std::min((this->getPoint(PointLabel::TLB).z()), this->getPoint(PointLabel::BRF).z());
  return Point3(minX, minY, minZ);
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
  calcBoxNormals();
}

Point3 Box::getCenter()
{
  return Point3({(this->getPoint(PointLabel::TLB)[0] + this->getPoint(PointLabel::BRF)[0]) / 2.0f,
                 (this->getPoint(PointLabel::TLB)[1] + this->getPoint(PointLabel::BRF)[1]) / 2.0f,
                 (this->getPoint(PointLabel::TLB)[2] + this->getPoint(PointLabel::BRF)[2]) / 2.0f});
}

Point3 Box::getExtent()
{
  return Point3({std::fabs(this->getPoint(PointLabel::TLB)[0] - this->getPoint(PointLabel::BRF)[0]),
                 std::fabs(this->getPoint(PointLabel::TLB)[1] - this->getPoint(PointLabel::BRF)[1]),
                 std::fabs(this->getPoint(PointLabel::TLB)[2] - this->getPoint(PointLabel::BRF)[2])});
}

void Box::calcBoxNormals()
{
  normals.emplace_back(std::pair<Point3, Vec3>(getPoint(TLF), unit(cross((getPoint(TLF) - getPoint(TLB)), getPoint(TRB) - getPoint(TLB)))));
  normals.emplace_back(std::pair<Point3, Vec3>(getPoint(TLF), unit(cross((getPoint(TRB) - getPoint(TLB)), getPoint(BLB) - getPoint(TLB)))));
  normals.emplace_back(std::pair<Point3, Vec3>(getPoint(TLF), unit(cross((getPoint(BLF) - getPoint(TLB)), getPoint(TLF) - getPoint(TLB)))));
  normals.emplace_back(std::pair<Point3, Vec3>(getPoint(TLF), unit(cross((getPoint(BLF) - getPoint(BRF)), getPoint(BRB) - getPoint(BRF)))));
  normals.emplace_back(std::pair<Point3, Vec3>(getPoint(TLF), unit(cross((getPoint(TRF) - getPoint(BRF)), getPoint(BLF) - getPoint(BRF)))));
  normals.emplace_back(std::pair<Point3, Vec3>(getPoint(TLF), unit(cross((getPoint(BRB) - getPoint(BRF)), getPoint(TRF) - getPoint(BRF)))));
}

std::pair<Point3, Vec3> &Box::getNormalAt(int idx)
{
  return normals.at(idx);
}
