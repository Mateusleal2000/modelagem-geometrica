#include "vec3.hpp"
#include <vector>

enum class PointLabel{
  TLB = 0,
  BRF = 1,
  TRB = 2,
  BLF = 3,
  BLB = 4,
  TRF = 5,
  TLF = 6,
  BRB = 7
};

class Box{
  public:
		Box();
		Box(Point3 tlb, Point3 brf);
		void setPoint(int label, Point3 point);
		Point3 getPoint(int label);
		double getBmin(int axis);
		double getBmax(int axis);
	private:
		std::vector<Point3> boxPoints;
		std::vector<int> index;
};

inline void Box::setPoint(int label, Point3 point){
  this->boxPoints[label] = point;
}

