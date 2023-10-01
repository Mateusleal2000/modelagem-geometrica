#include "OctTree.hpp"
#include "Node.hpp"
#include "Sphere.hpp"
#include "Block.hpp"
#include "Mesh.hpp"
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

	OctTree *oct = new OctTree(8);
	Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
	// Sphere *sp = new Sphere(0.5, Point3(0.5, 0.5, 0.5));
	// Mesh m1("test.obj");
	// Mesh m1("boeing777.obj");
	// oct->setSolid(&m1);
	Block *block = new Block(Point3(6., 0., 0.), 2., 8., 10.);
	// oct->setSolid(block);
	oct->setSolid(sp);
	oct->initOctTree();
	oct->treeScale(5.0, oct->getRoot());

	// for (int i = 0; i < 8; i++)
	// {
	// 	std::cout << oct->getRoot()->getBox()->getPoint(i);
	// }

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