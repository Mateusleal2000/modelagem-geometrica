
#include "MainWidget.hpp"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    glwidget = new GLWidget(this);
    layout = new QHBoxLayout(this);
    opWidget = new OptionsWidget(this);
    setFixedSize(1280, 920);
    layout->addWidget(glwidget);
    layout->addWidget(opWidget);

    setLayout(layout);
}

void MainWidget::objReceived(std::string filename)
{
    Mesh *mesh = new Mesh(filename);
    glwidget->addSolid(mesh);
}
void MainWidget::sphereReceived(Vec3 center, float radius)
{
    Sphere *sphere = new Sphere(radius, center);
    glwidget->addSolid(sphere);
}
void MainWidget::blockReceived(Point3 ref, float x, float y, float z)
{
    Block *block = new Block(ref, x, y, z);
    glwidget->addSolid(block);
}