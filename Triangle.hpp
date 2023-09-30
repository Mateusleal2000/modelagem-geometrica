#include "vec3.hpp"

class Triangle
{
public:
	Triangle(int index1, int index2, int index3);
	int getIndex(int idx);
	void setIndex(int i, int idx);

private:
	std::vector<int> indices;
};
