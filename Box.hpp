#include "vec3.hpp"
#include <vector>
#include <utility>

// Grupo de 12 arestas, 2 a 2
// Arestas
// Face de Tras:
// TLB-TRB , BLB-BRB, TLB-BLB, TRB-BRB
// Face da Frente:
// TLF-TRF , FLF-FRF, TLF-FLF, TRF-FRF
// Arestas da Esquerda:
// BLB-BLF, TLF-TLB
// Face da Direita
// BRB-BRF, TRF-TRB

enum PointLabel
{
  TLB = 0,
  BRF = 1,
  TRB = 2,
  BLF = 3,
  BLB = 4,
  TRF = 5,
  TLF = 6,
  BRB = 7
};

class Box
{
public:
  Box();
  Box(Point3 tlb, Point3 brf);
  void setPoint(int label, Point3 point);
  void setIndex(int label, int idx);
  Point3 &getPoint(int label);
  unsigned int getIndex(int idx);
  Point3 getCenter();
  Point3 getExtent();
  Point3 getMax();
  Point3 getMin();
  float getBmin(int axis);
  float getBmax(int axis);
  void calcBoxPoints();
  void calcBoxNormals();

private:
  std::vector<Point3> boxPoints;
  std::vector<int> boxIndex;
  std::vector<Pair<Point3, Vec3>> normals;
};

inline void Box::setPoint(int label, Point3 point)
{
  this->boxPoints[label] = point;
}

inline void Box::setIndex(int label, int idx)
{
  boxIndex[label] = idx;
}
