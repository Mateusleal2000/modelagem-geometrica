#include "vec3.hpp"
class Box{
  public:
		void setPoint3(double x, double y, double z);

	private:
		Point3 top_left_back;
		Point3 bottom_right_front;


};