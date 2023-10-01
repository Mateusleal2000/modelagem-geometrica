#ifndef OPTIONS_WIDGET_H
#define OPTIONS_WIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include "Mesh.hpp"
#include <string>

class OptionsWidget : public QWidget
{
	Q_OBJECT
public:
	OptionsWidget(QWidget *parent = 0);
	void openObj();

signals:
	void objChosen(std::string filename);
	void sphereChosen(Point3 center, float radius);
	void blockChosen(Point3 ref, float x, float y, float z);

private:
	QHBoxLayout *layout;
	QPushButton *addObjectButton;
	QPushButton *addSphereButton;
	QPushButton *addBlockButton;
	QLabel *sphereLabel;
	QLabel *objLabel;
	QLabel *blockLabel;
	QLineEdit *fileedit;
	QLineEdit *spherex;
	QLineEdit *spherey;
	QLineEdit *spherez;
	QLineEdit *radius;

	QLineEdit *refx;
	QLineEdit *refy;
	QLineEdit *refz;
	QLineEdit *blocksizex;
	QLineEdit *blocksizey;
	QLineEdit *blocksizez;

	QGridLayout *spherelabellayout;
	QGridLayout *objlabellayout;
	QGridLayout *blocklabellayout;

	// QPushButton * addDepthButton;
	// QPushButton * subtractDepthButton;
};
#endif