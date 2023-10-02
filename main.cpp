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
	int operation = 0;
	std::cout << "Esfera --> 1\n";
	std::cout << "Bloco --> 2\n";
	std::cout << "Volume --> 3\n";
	std::cout << "Uniao --> 4\n";
	std::cout << "Escala --> 5\n";
	std::cin >> operation;

	if (operation == 1)
	{
		// Testing Sphere
		OctTree *oct = new OctTree(8);
		Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
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
	if (operation == 2)
	{
		// Testing Block
		OctTree *oct = new OctTree(8);
		Block *block = new Block(Point3(0., 0., 0.), 2., 8., 10.);
		oct->setSolid(block);
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
	if (operation == 3)
	{
		// Testing Volume
		OctTree *oct = new OctTree(8);
		Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
		oct->setSolid(sp);
		oct->initOctTree();
		float sphereVolume = 0.0;
		oct->treeVolume(&sphereVolume, oct->getRoot());
		std::cout << "Volume :" << sphereVolume << "\n";

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
	if (operation == 4)
	{
		// Testing Union
		OctTree *oct = new OctTree(8);
		Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
		oct->setSolid(sp);
		Block *block = new Block(Point3(0., 0., 0.), 2., 8., 10.);
		oct->setSolid(block);
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
	if (operation == 5)
	{
		// Testing Scale
		OctTree *oct = new OctTree(8);
		Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
		oct->setSolid(sp);
		oct->initOctTree();
		oct->treeScale(0.5, oct->getRoot());

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

	// OctTree *oct = new OctTree(8);

	// Testing Sphere
	// Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
	// oct->setSolid(sp);
	// oct->initOctTree();

	// Testing Mesh
	// Mesh m1("boeing777.obj");
	// oct->setSolid(&m1);
	// oct->initOctTree();

	// Testing Block
	// Block *block = new Block(Point3(0., 0., 0.), 2., 8., 10.);
	// oct->setSolid(block);
	// oct->initOctTree();

	// Testing Scale
	// Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
	// oct->setSolid(sp);
	// oct->initOctTree();
	// oct->treeScale(0.5, oct->getRoot());

	// Testing Union
	// Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
	// oct->setSolid(sp);
	// Block *block = new Block(Point3(0., 0., 0.), 2., 8., 10.);
	// oct->setSolid(block);
	// oct->initOctTree();

	// Testing Volume
	// Sphere *sp = new Sphere(5.0, Point3(0.0, 0.0, 0.0));
	// oct->setSolid(sp);
	// oct->initOctTree();
	// float sphereVolume = 0.0;
	// oct->treeVolume(&sphereVolume, oct->getRoot());
	// std::cout << "Volume :" << sphereVolume << "\n";

	// oct->treeVolume(&sphereVolume, oct->getRoot());
	// std::cout << "Volume da esfera " << sphereVolume;

	// for (int i = 0; i < 8; i++)
	// {
	// 	std::cout << oct->getRoot()->getBox()->getPoint(i);
	// }

	// QApplication app(argc, argv);
	// QWidget *w = new QWidget();
	// GLWidget *gl = new GLWidget(w);
	// gl->setOctTree(oct);
	// // testGL *tgl = new testGL(w);
	// w->setFixedSize(640, 480);
	// QHBoxLayout *layout = new QHBoxLayout(w);
	// layout->addWidget(gl);
	// // layout->addWidget(tgl);
	// w->setLayout(layout);

	// w->show();

	// app.exec();

	// return 0;
}