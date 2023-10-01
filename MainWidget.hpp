#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H
#include <QWidget>
#include "GLWidget.hpp"
#include "OptionsWidget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWidget : public QWidget
{
	Q_OBJECT
	public:
	MainWidget(QWidget * parent = 0);


	private:
	QHBoxLayout * layout;
	GLWidget * glwidget;
};
#endif