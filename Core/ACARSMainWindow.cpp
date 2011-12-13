#include "ACARSMainWindow.h"
#include "ui_ACARSMainWindow.h"

ACARSMainWindow::ACARSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ACARSMainWindow)
{
    ui->setupUi(this);
}

ACARSMainWindow::~ACARSMainWindow()
{
    delete ui;
}
