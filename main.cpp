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

#include "testGL.hpp"
// #include "testTriangle.hpp"

int main(int argc, char **argv)
{


  OctTree *oct = new OctTree(3);
  Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
  //Sphere *sp = new Sphere(0.5, Point3(0.5, 0.5, 0.5));
  oct->setSolid(sp);
  oct->initOctTree();


  QApplication app(argc, argv);
  QWidget *w = new QWidget();
  GLWidget *gl = new GLWidget(w);
  gl->setOctTree(oct);
  // testGL *tgl = new testGL(w);
  w->setFixedSize(640, 480);
  QHBoxLayout *layout = new QHBoxLayout(w);
  layout->addWidget(gl);
  // layout->addWidget(tgl);
  w->setLayout(layout);

  w->show();

  app.exec();

  return 0;
}