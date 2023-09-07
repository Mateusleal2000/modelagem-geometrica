#ifndef SOLID_H
#define SOLID_H


class Box;

class Solid{

  public:
    ~Solid();
    virtual State classify(Box * box) = 0;

  private:
    double area;
    double volume;

};

#endif