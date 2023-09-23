#include "OctTree.hpp"
#include "Node.hpp"
#include "TestSolid.hpp"
#include "Sphere.hpp"
#include "GLWidget.hpp"
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QWidget>
#include <QApplication>
#include <QHBoxLayout>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QWidget *w = new QWidget();
  GLWidget *gl = new GLWidget(w);
  w->setFixedSize(640, 480);

  QHBoxLayout *layout = new QHBoxLayout(w);
  layout->addWidget(gl);
  w->setLayout(layout);
  w->show();

  app.exec();

  /*
    OctTree *oct = new OctTree(7);
    Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
    oct->setSolid(sp);
    oct->initOctTree();
    std::cout << "depois de makeOctTree\n";
  */
  return 0;
}