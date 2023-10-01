#include "MainWidget.hpp"

MainWidget::MainWidget(QWidget * parent ) : QWidget(parent){
    glwidget = new GLWidget(this);
    layout = new QHBoxLayout(this);
    setFixedSize(640,480);
    layout->addWidget(glwidget);

    setLayout(layout);
}