#include "Block.hpp"

Block::Block() {}

Block::Block(Point3 p_min, float size_x, float size_y, float size_z)
{
    this->size_x = size_x;
    this->size_y = size_y;
    this->size_z = size_z;
    this->p_min = p_min;
}

State Block::classify(Node *node)
{
    Point3 p_max = p_min + Point3(size_x, size_y, size_z);
    Point3 boxMax = node->getBox()->getMax();
    Point3 boxMin = node->getBox()->getMin();
    int blackCount = 0;

    for (int i = 0; i < 3; i++)
    {
        if ((boxMax[i] < p_min[i] || boxMax[i] > p_max[i]) && (boxMin[i] < p_min[i] || boxMin[i] > p_max[i]) && !((boxMin[i] < p_min[i]) && (boxMax[i] > p_max[i])))
        {
            node->setState(State::WHITE);
            return State::WHITE;
        }
        else if ((boxMax[i] >= p_min[i] && boxMax[i] <= p_max[i]) && (boxMin[i] >= p_min[i] && boxMin[i] <= p_max[i]))
        {
            blackCount++;
        }
        // else
        // {
        //     //não soma
        // }
    }
    if (blackCount == 3)
    {
        node->setState(State::BLACK);
        return State::BLACK;
    }
    else
    {
        node->setState(State::GRAY);
        return State::GRAY;
    }
}

float Block::dMax()
{
    return std::max({size_x - p_min[0], size_y - p_min[1], size_z - p_min[2]});
}

Vec3 Block::maxValAxis()
{
    return Vec3(size_x + p_min[0], size_y + p_min[1], size_z + p_min[2]);
}

Vec3 Block::minValAxis()
{
    return Vec3(p_min[0], p_min[1], p_min[2]);
}

Point3 Block::getCenter()
{
    float center_x = p_min[0] + (size_x / 2);
    float center_y = p_min[1] + (size_y / 2);
    float center_z = p_min[2] + (size_z / 2);
    return Point3(center_x, center_y, center_z);
}