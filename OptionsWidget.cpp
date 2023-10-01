#include "OptionsWidget.hpp"
#include <QFileDialog>

OptionsWidget::OptionsWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400, 920);
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