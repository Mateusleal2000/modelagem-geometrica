#include "vec3.hpp"
class Box{
  public:
		Box();
		Box(Point3 tlb, Point3 brf);
		void setTLB(Point3 & tlb);
		void setBRF(Point3 & brf);
		Point3 & getTLB();
		Point3 & getBRF();
		double getBmin(int axis);
		double getBmax(int axis);
	private:
		Point3 top_left_back;
		Point3 bottom_right_front;


};


inline void Box::setBRF(Point3 & brf){
  this->bottom_right_front = brf;
}


inline void Box::setTLB(Point3 & tlb){
  this->top_left_back = tlb;
}