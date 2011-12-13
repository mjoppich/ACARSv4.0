#include "ACARSMainWindow.h"
#include "ui_ACARSMainWindow.h"

ACARSMainWindow::ACARSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ACARSMainWindow)
{
    ui->setupUi(this);

    QPixmap *pBGImage = new QPixmap("./images/small_744_acars_day.png");
    QSize oBGImageSize = pBGImage->size();


    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(pBGImage))));
    setPalette(*palette);

    this->resize(oBGImageSize);
}

ACARSMainWindow::~ACARSMainWindow()
{
    delete ui;
}
