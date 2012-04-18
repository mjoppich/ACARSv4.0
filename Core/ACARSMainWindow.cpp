#include <Core/ACARSMainWindow.h>
#include <Core/ACARSMenuView.h>
#include <Core/ACARSInputRegistry.h>
#include <Core/ACARSInput.h>


#include"ui_ACARSMainWindow.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPalette>


ACARSMainWindow::ACARSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_pUI(new Ui::ACARSMainWindow)
{
    m_pUI->setupUi(this);


    this->setWindowTitle("ACARS v4.0");

    QPixmap *pBGImage = new QPixmap("./images/small_744_acars_day.png");
    QSize oBGImageSize = pBGImage->size();


    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(pBGImage))));
    this->setPalette(*palette);
    this->resize(oBGImageSize);

    mACARSInputLine = new QLineEdit(this);
    mACARSInputLine->setGeometry(100,325,305,20);
    mACARSInputLine->setStyleSheet("border: 0px; background: black;");
    QPalette p = mACARSInputLine->palette();

    p.setColor(QPalette::Base, QColor(0,0,0));
    p.setColor(QPalette::Window, QColor(0,0,0));
    p.setColor(QPalette::Text, QColor(117,216,118));


    mACARSInputLine->setPalette(p);
    mACARSInputLine->setText("TestString");
    mACARSInputLine->activateWindow();
    mACARSInputLine->setContextMenuPolicy(Qt::PreventContextMenu);
    QFont f = mACARSInputLine->font();
    f.setCapitalization(QFont::AllUppercase);
    //f.setBold(true);
    f.setFamily("Helvetica");
    f.setPixelSize(18);
    mACARSInputLine->setFont(f);


    this->installEventFilter(this);

    m_pInputRegistry = new ACARSInputRegistry(this);

    this->Init();

}

ACARSMainWindow::~ACARSMainWindow()
{
    delete m_pUI;
    delete m_pInputRegistry;
    delete m_pDefaultInput;
}


/*****************************************************************************

  IMPLEMENTATION

  ****************************************************************************/

bool ACARSMainWindow::eventFilter(QObject *pObj, QEvent *pEvent)
{

    if (pEvent->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *pMouseEvent = static_cast<QMouseEvent*>(pEvent);
        ACARSInputEvent* pReturnValue = m_pInputRegistry->ClickEvent(pMouseEvent);

        if (pReturnValue)
            m_vInputEvents.append(pReturnValue);

    }

    return false;

}

void ACARSMainWindow::Init()
{

    m_pDefaultInput = new ACARSInput();
    m_pInputRegistry->RegisterInput(m_pDefaultInput);

}

void ACARSMainWindow::GetInputEventsQueue(QVector<ACARSInputEvent*> *copyto)
{
    ACARSInputEvent* pCurrentIE;

    while(m_vInputEvents.count())
    {
        pCurrentIE = *(m_vInputEvents.begin());
        copyto->append(pCurrentIE);
        m_vInputEvents.erase(m_vInputEvents.begin());
    }
}

void ACARSMainWindow::WriteInputLine(const char *c)
{
    mACARSInputLine->setText(mACARSInputLine->text().append(c));
}
