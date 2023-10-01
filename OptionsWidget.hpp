#ifndef OPTIONS_WIDGET_H
#define OPTIONS_WIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include "Mesh.hpp"
#include <string>

class OptionsWidget : public QWidget
{
	Q_OBJECT
public:
	OptionsWidget(QWidget *parent = 0);
	void openObj();
	void processSphere();
	void processBlock();

signals:
	void objChosen(std::string filename);
	void sphereChosen(Point3 center, float radius);
	void blockChosen(Point3 ref, float x, float y, float z);

private:
	QFormLayout *layout;
	QPushButton *addObjectButton;
	QPushButton *addSphereButton;
	QPushButton *addBlockButton;
	QPushButton *addObjectFile;


	QLabel *objLabel;
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


	QLabel * sphereTitle;
	QLabel * objTitle;
	QLabel * blockTitle;
	// QPushButton * addDepthButton;
	// QPushButton * subtractDepthButton;
};
#endif