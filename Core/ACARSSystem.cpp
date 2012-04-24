#include "ACARSSystem.h"
#include <Core/ACARSMenu.h>
#include <Core/ACARSInputRegistry.h>
#include <Core/ACARSInput.h>
#include <Core/ACARSEvents.h>


#include"ui_ACARSMainWindow.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QPalette>
#include <QCursor>


ACARSSystem::ACARSSystem(QWidget *parent) :
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

    m_pActiveView = new ACARSMenu(this);
    m_pActiveView->setInputLine(mACARSInputLine);
    m_pActiveView->setStyleSheet("QWidget { background-color: black;}");
    m_pActiveView->move(65,85);

    this->installEventFilter(this);

    m_pInputRegistry = new ACARSInputRegistry(this);

    ACARSVKeyBoardInput* vKeyBoard = new ACARSVKeyBoardInput();
    ACARSSpecialKeyKeyBInput* MenuInput = new ACARSSpecialKeyKeyBInput();
    ACARSLSKinput* LSKInput = new ACARSLSKinput();
    m_pInputRegistry->RegisterInput(vKeyBoard);
    m_pInputRegistry->RegisterInput(MenuInput);
    m_pInputRegistry->RegisterInput(LSKInput);

    m_pTimer = new QTimer();
    connect(m_pTimer, SIGNAL(timeout()),this,SLOT(SystemLoop()));
}

ACARSSystem::~ACARSSystem()
{
    delete m_pUI;
    delete m_pInputRegistry;
    delete m_pDefaultInput;
}


/*****************************************************************************

  IMPLEMENTATION

  ****************************************************************************/

bool ACARSSystem::eventFilter(QObject *pObj, QEvent *pEvent)
{

    if (pEvent->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *pMouseEvent = static_cast<QMouseEvent*>(pEvent);
        m_pInputRegistry->ClickEvent(pMouseEvent, &m_vInputEvents);

    }

    if (pEvent->type() == ACARSEVENT::LOGINEVENT)
    {
        QString SentString(*(QString*)pObj);
        qDebug() << SentString << SentString.length();
    }

    return false;

}

void ACARSSystem::Start()
{
    this->show();
    m_LastTime = QTime::currentTime();
    m_pTimer->start(10);
}

void ACARSSystem::GetInputEventsQueue(QVector<ACARSActionEvent*> *copyto)
{
    ACARSActionEvent* pCurrentIE;

    while(m_vInputEvents.count())
    {
        pCurrentIE = *(m_vInputEvents.begin());
        copyto->append(pCurrentIE);
        m_vInputEvents.erase(m_vInputEvents.begin());
    }
}

void ACARSSystem::WriteInputLine(QString *c)
{
    mACARSInputLine->setText(mACARSInputLine->text().append(c));
}

void ACARSSystem::ClearInputLine()
{
    mACARSInputLine->setText("");
}

void ACARSSystem::DelFromInputLine()
{

    QString newText = mACARSInputLine->text();
    newText.chop(1);

    mACARSInputLine->setText(newText);
}

bool ACARSSystem::SystemLoop()
{
    // Get Events
    QVector<ACARSActionEvent*> pInputQueue;
    this->GetInputEventsQueue(&pInputQueue);

    //Debug ACARSInputEvents
    ACARSActionEvent* pCurrentIE;

    while(pInputQueue.count())
    {
        pCurrentIE = *(pInputQueue.begin());

        // Work CORE EVENTS - NOTE: These must NOT alter pInputQueue!

        if (pCurrentIE->isEventType(ACARSEVENT::VKEY))
        {
             this->WriteInputLine(pCurrentIE->getInputValue());
        }

        this->HandleEvents(pCurrentIE);

        if (pCurrentIE->isEventType(ACARSEVENT::ILINE))
        {
            if (pCurrentIE->getInputValue()->compare("C"))
                this->ClearInputLine();

            if (pCurrentIE->getInputValue()->compare("D"))
                this->DelFromInputLine();
        }

        // WORK ADDON EVENTS - ONLY EVERY 1000ms
        if (m_LastTime.msecsTo(QTime::currentTime()) < 0)
        {
            m_LastTime = QTime::currentTime();
            m_LastTime.addMSecs(1000);
        }

        pInputQueue.erase(pInputQueue.begin());
    }

    this->show();
    m_pActiveView->display();

    return true;
}

void ACARSSystem::HandleEvents(ACARSActionEvent *pIEvent)
{

    if (pIEvent->getEventType() != ACARSEVENT::MENU)
    {

        m_pActiveView->handleEvent(pIEvent);

    } else {
        //Make another menu active
    }

    m_pActiveView->show();

}
