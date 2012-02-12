#include <Core/ACARSMainWindow.h>
#include"ui_ACARSMainWindow.h"

#include <QMouseEvent>
#include <QDebug>


ACARSMainWindow::ACARSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_pUI(new Ui::ACARSMainWindow)
{
    m_pUI->setupUi(this);

    QPixmap *pBGImage = new QPixmap("./images/small_744_acars_day.png");
    QSize oBGImageSize = pBGImage->size();


    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(pBGImage))));
    setPalette(*palette);

    this->resize(oBGImageSize);
    this->installEventFilter(this);
}

ACARSMainWindow::~ACARSMainWindow()
{
    delete m_pUI;
}


/*****************************************************************************

  IMPLEMENTATION

  ****************************************************************************/

bool ACARSMainWindow::eventFilter(QObject *pObj, QEvent *pEvent)
{

    if (pEvent->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *pMouseEvent = static_cast<QMouseEvent*>(pEvent);

        qDebug() << "(" << pMouseEvent->x() << "," << pMouseEvent->y() << ")" << endl;

    }

}

void ACARSMainWindow::Init()
{



}
