#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H
#include <QWidget>
#include "GLWidget.hpp"
#include "OptionsWidget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <string>
#include "Mesh.hpp"
#include "Sphere.hpp"
#include "Block.hpp"
#include "OptionsWidget.hpp"
#include "vec3.hpp"

class MainWidget : public QWidget
{
	Q_OBJECT
public:
	MainWidget(QWidget *parent = 0);

public slots:
	void objReceived(std::string filename);
	void sphereReceived(Vec3 center, float radius);
	void blockReceived(Point3 ref, float x, float y, float z);

private:
	QHBoxLayout *layout;
	GLWidget *glwidget;
	OptionsWidget *opWidget;
};
#endif