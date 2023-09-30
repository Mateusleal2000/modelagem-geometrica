#include "Block.hpp"

Block::Block() {}

Block::Block(Point3 p_min, float size_x, float size_y, float size_z)
{
    size_x = size_x;
    size_y = size_y;
    size_z = size_z;
    p_min = p_min;
}

void Block::classify(Node *node)
{
    Point3 p_max = p_min + Point3(size_x, size_y, size_z);
    Point3 boxMax = node->getBox()->getMax();
    Point3 boxMin = node->getBox()->getMin();
    int blackCount;

    for (int i = 0; i < 3; i++)
    {
        if ((boxMax[i] < p_min[i] || boxMax[i] > p_max[i]) && (boxMin[i] < p_min[i] || boxMin[i] > p_max[i]) && !((boxMin[i] < p_min[i]) && (boxMax[i] > p_max[i])))
        {
            node->setState(State::WHITE);
            return;
        }
        else if ((boxMax[i] >= p_min[i] && boxMax[i] <= p_max[i]) && (boxMin[i] >= p_min[i] && boxMin[i] <= p_max[i]))
        {
            blackCount++;
        }
        // else
        // {
        //     //não soma
        // }
        if (blackCount == 3)
        {
            node->setState(State::BLACK);
        }
        else
        {
            node->setState(State::GRAY);
        }
    }
}

float Block::dMax()
{
    return std::max({size_x, size_y, size_z});
}
Point3 Block::getCenter()
{
}