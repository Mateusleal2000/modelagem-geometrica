#ifndef TEST_SOLID_H
#define TEST_SOLID_H
#include "Solid.hpp"

class TestSolid : public Solid{
  public:
  TestSolid();
  ~TestSolid();
  void classify(Node * node) override;
  double dMax() override;
  Point3 getCenter() override;
};

#endif // TEST_SOLID_H
