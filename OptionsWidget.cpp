#include "OptionsWidget.hpp"
#include <QFileDialog>
#include <QSpacerItem>

OptionsWidget::OptionsWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(500, 960);
    layout = new QFormLayout(this);

    layout->setContentsMargins(0.5, 2, 0.5, 2);
    layout->setSpacing(0);
    addObjectButton = new QPushButton("Add Object");
	addSphereButton = new QPushButton("Add Sphere");
	addBlockButton = new QPushButton("Add Block");


	spherex = new QLineEdit();
	spherey = new QLineEdit();
	spherez = new QLineEdit();
	radius = new QLineEdit();
    
    sphereTitle = new QLabel();
    sphereTitle->setText("Sphere");
    sphereTitle->setAlignment(Qt::AlignCenter);
    objTitle = new QLabel();
    objTitle->setText("Mesh Object");


    objTitle->setAlignment(Qt::AlignCenter);
    blockTitle = new QLabel();
    blockTitle->setText("Block");
    blockTitle->setAlignment(Qt::AlignCenter);

	objLabel = new QLabel();
    objLabel->setText("Mesh Object Path");


	refx = new QLineEdit();
	refy = new QLineEdit();
	refz = new QLineEdit();
	blocksizex = new QLineEdit();
	blocksizey = new QLineEdit();
	blocksizez = new QLineEdit();

    layout->addRow(sphereTitle);
    layout->addRow("Center X", spherex);
    layout->addRow("Center Y", spherey);
    layout->addRow("Center Z", spherez);
    layout->addRow("Radius", radius);
    layout->addRow(addSphereButton);
    layout->addItem(new QSpacerItem(0,100,QSizePolicy::Fixed,QSizePolicy::Fixed));
    connect(addSphereButton, &QPushButton::clicked, this, &OptionsWidget::processSphere);

    addSphereButton->setContentsMargins(0.0, 0.0, 0.0, 50.0);
    layout->addRow(objTitle);
    layout->addRow(objLabel);
    layout->addRow(addObjectButton);
    layout->addItem(new QSpacerItem(0,100,QSizePolicy::Fixed,QSizePolicy::Fixed));
    connect(addObjectButton,&QPushButton::clicked,this,&OptionsWidget::openObj);

    layout->addRow(blockTitle);
    layout->addRow("Size X", blocksizex);
    layout->addRow("Size Y", blocksizey);
    layout->addRow("Size Z", blocksizez);
    layout->addRow("Position X", refx);
    layout->addRow("Position Y", refy);
    layout->addRow("Position Z", refz);
    layout->addRow(addBlockButton);

    connect(addBlockButton,&QPushButton::clicked, this , &OptionsWidget::processBlock);





    setLayout(layout);
}

void OptionsWidget::openObj()
{
    QFileDialog dialog(this);
    dialog.setWindowTitle("Open File");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Object (*.obj)");
    QStringList filePaths;
    if (dialog.exec())
    {
        filePaths = dialog.selectedFiles();
        emit objChosen(filePaths.at(0).toStdString());
    }
}


void OptionsWidget::processSphere(){
    float x = spherex->text()->toString;
    float y = spherey->text();
    float z = spherez->text();
    Point3 center(x,y,z);
    float radius = radius->text();
    emit sphereChosen();
    emit sphereChosen();
}

void OptionsWidget::processBlock(){
    emit blockChosen
}