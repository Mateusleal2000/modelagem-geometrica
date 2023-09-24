#include "OctTree.hpp"
#include "Node.hpp"
#include "TestSolid.hpp"
#include "Sphere.hpp"
#include "GLWidget.hpp"
#include <iostream>
#include <fstream>
#include <set>
#include <QDebug>
#include <QWidget>
#include <QApplication>
#include <QHBoxLayout>

int main(int argc, char **argv)
{
  Vec3 v(1, 2, 3);
  Vec3 v1(11, 2, 3);
  std::set<Vec3> s;
  s.insert(v);
  if (s.insert(v1).second)
  {
    std::cout << "conseguiu inserir outro vec3 com valores iguais!!!\n";
  }

  if (s.find(v1) == s.end())
  {
    std::cout << "nao conseguiu encontrar vec3!!!\n";
  }
  /*
  QApplication app(argc, argv);
  QWidget *w = new QWidget();
  GLWidget *gl = new GLWidget(w);
  w->setFixedSize(640, 480);

  QHBoxLayout *layout = new QHBoxLayout(w);
  layout->addWidget(gl);
  w->setLayout(layout);
  w->show();

  app.exec();
  */
  /*
    OctTree *oct = new OctTree(7);
    Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
    oct->setSolid(sp);
    oct->initOctTree();
    std::cout << "depois de makeOctTree\n";
  */
  return 0;
}