#include "OctTree.hpp"
#include "Node.hpp"
#include "TestSolid.hpp"
#include "Sphere.hpp"
#include "GLWidget.hpp"
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <QDebug>
#include <QWidget>
#include <QApplication>
#include <QHBoxLayout>

int main(int argc, char **argv)
{
  //   Vec3 v(1, 2, 3);
  //   Vec3 v1(11, 2, 3);
  //   Vec3 v2(12, 2, 3);
  //   Vec3 v3(13, 2, 3);
  //   Vec3 v4(14, 2, 3);
  //   Vec3 v5(15, 2, 3);
  //   Vec3 v6(16, 2, 3);
  //   Vec3 v7(17, 2, 3);
  //   Vec3 v8(18, 2, 3);
  //   Vec3 v9(19, 2, 3);
  //   Vec3 v10(20, 2, 3);

  //   Vec3 v11(2, 2, 3);
  //   Vec3 v12(3, 2, 3);
  //   Vec3 v13(4, 2, 3);
  //   Vec3 v14(5, 2, 3);
  //   Vec3 v15(6, 2, 3);
  //   Vec3 v16(7, 2, 3);
  //   std::unordered_set<Vec3, MyHashFunction> s;
  //   s.insert(v);
  //   s.insert(v1);
  //   s.insert(v2);
  //   s.insert(v3);
  //   s.insert(v4);
  //   s.insert(v5);
  //   s.insert(v6);
  //   s.insert(v7);
  //   s.insert(v8);
  //   s.insert(v9);
  //   s.insert(v10);

  //  Vec3 a = *std::next(s.begin(), 0);
  //  Vec3 b = *std::next(s.begin(), 1);
  //  std::unordered_set<Vec3>::iterator it1 = s.find(v1);
  //  int c = std::distance(s.begin(), it1);
  //  std::cout<< "Antes das novas insercoes:\n";
  //  std::cout << a;
  //  std::cout<< b;
  //  std::cout<<c<<std::endl;

  //   s.insert(v11);
  //   s.insert(v12);
  //   s.insert(v13);
  //   s.insert(v14);
  //   s.insert(v15);
  //   s.insert(v16);

  //  Vec3 x = *std::next(s.begin(), 0);
  //  Vec3 y = *std::next(s.begin(), 1);
  //  std::unordered_set<Vec3>::iterator it2 = s.find(v1);
  //  int z = std::distance(s.begin(), it2);
  //  std::cout<< "Depois das novas insercoes:\n";
  //  std::cout << x;
  //  std::cout<< y;
  //  std::cout<<z<<std::endl;

  /*
  QApplication app(argc, argv);
  QWidget *w = new QWidget();
  GLWidget *gl = new GLWidget(w);
  w->unordered_setFixedSize(640, 480);

  QHBoxLayout *layout = new QHBoxLayout(w);
  layout->addWidget(gl);
  w->unordered_setLayout(layout);
  w->show();

  app.exec();
  */

  OctTree *oct = new OctTree(7);
  Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
  oct->setSolid(sp);
  oct->initOctTree();
  return 0;
}