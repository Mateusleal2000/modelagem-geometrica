#include "Block.hpp"

Block::Block(){}


Block::Block(Point3 tlb, Point3 brf){
  top_left_back = tlb;
  bottom_right_front = brf;
}

void Block::setBRF(Point3 & brf){
  this->bottom_right_front = brf;
}

void Block::setTLB(Point3 & tlb){
  this->top_left_back = tlb;
}

Point3 & Block::getBRF(){
  return bottom_right_front;
}

Point3 & Block::getTLB(){
  return top_left_back;
}
