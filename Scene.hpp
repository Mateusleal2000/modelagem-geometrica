#ifndef SCENE_H
#define SCENE_H

#include "OctTree.hpp"
#include "Solid.hpp"

class Scene{
  public:
    void buildGlobalOctTree();
    void render();
  private:
    OctTree global_OCT;
    std::vector<OctTree> individual_OCTs;
};

#endif