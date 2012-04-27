#include "ACARSSystem.h"
#include <Core/ACARSInputRegistry.h>
#include <Core/ACARSInput.h>
#include <Core/ACARSEvents.h>
#include <Core/ACARSUser.h>

#include <Menus/MENULogin.h>


#include"ui_ACARSMainWindow.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QPalette>
#include <QCursor>

const char *ACARSSystem::ACARSFontName = "Lucida Console";
const char *ACARSSystem::ACARSVersion = "4.0.0a";


ACARSSystem::ACARSSystem(QWidget *parent) :
    QMainWindow(parent),
    m_pUI(new Ui::ACARSMainWindow)
{
    m_pUI->setupUi(this);

    this->setWindowTitle(QString("ACARS ").append(ACARSSystem::ACARSVersion));
    this->installEventFilter(this);


    //BACKGROUND IMAGE
    QPixmap *pBGImage = new QPixmap("./images/small_744_acars_day.png");
    QSize oBGImageSize = pBGImage->size();


    //INPUT LINE
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(pBGImage))));
    this->setPalette(*palette);
    this->resize(oBGImageSize);

    mACARSInputLine = new QLineEdit(this);
    mACARSInputLine->setGeometry(100,335,305,20);
    mACARSInputLine->setStyleSheet("border: 0px; background: black;");
    QPalette p = mACARSInputLine->palette();

    p.setColor(QPalette::Base, QColor(0,0,0));
    p.setColor(QPalette::Window, QColor(0,0,0));
    p.setColor(QPalette::Text, QColor(117,216,118));


    mACARSInputLine->setPalette(p);
    mACARSInputLine->setText("");
    mACARSInputLine->activateWindow();
    mACARSInputLine->setContextMenuPolicy(Qt::PreventContextMenu);
    QFont f = mACARSInputLine->font();
    f.setCapitalization(QFont::AllUppercase);
    //f.setBold(true);
    f.setFamily(ACARSSystem::ACARSFontName);
    f.setPixelSize(18);
    mACARSInputLine->setFont(f);


    //ACARS MENUS
    m_pActiveMenu = new MENULogin(this);
    m_pActiveMenu->init();
    m_pActiveMenu->setInputLine(mACARSInputLine);
    m_pActiveMenu->setStyleSheet("QWidget { background-color: black;}");
    m_pActiveMenu->move(65,55);


    //USER INPUT REGISTY
    m_pInputRegistry = new ACARSInputRegistry(this);
    ACARSVKeyBoardInput* vKeyBoard = new ACARSVKeyBoardInput();
    ACARSSpecialKeyKeyBInput* SpecialKeyInput = new ACARSSpecialKeyKeyBInput();
    ACARSLSKinput* LSKInput = new ACARSLSKinput();
    ACARSMenuKeyInput* MenuInput = new ACARSMenuKeyInput();
    m_pInputRegistry->RegisterInput(vKeyBoard);
    m_pInputRegistry->RegisterInput(SpecialKeyInput);
    m_pInputRegistry->RegisterInput(LSKInput);
    m_pInputRegistry->RegisterInput(MenuInput);


    //TIMER
    m_pTimer = new QTimer();
    connect(m_pTimer, SIGNAL(timeout()),this,SLOT(SystemLoop()));


    //USER
    m_pUser = new ACARSUser("","");
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
        m_pUser = (ACARSUser*) pObj;
        qDebug() << m_pUser->getUsername() << " logged in";
    }

    return false;

}

void ACARSSystem::Start()
{
    this->show();
    m_LastTime = QTime::currentTime();
    m_pTimer->start(10);
}

bool ACARSSystem::UpdateACARSCheck()
{
    return true;
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

void ACARSSystem::setACARSUser(ACARSUser *pUser)
{
    m_pACARSUser = pUser;
}

void ACARSSystem::WriteInputLine(QString c)
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

        if (m_pActiveMenu->handleEvent(pCurrentIE))
        {

            //HANDLE MENU CHANGES HERE!
            qDebug() << "MENU CHANGE!";

            // WORK ADDON EVENTS - ONLY EVERY 1000ms and if allowed
            if (m_LastTime.msecsTo(QTime::currentTime()) < 0)
            {
                m_LastTime = QTime::currentTime();
                m_LastTime.addMSecs(1000);
            }
        }

        pInputQueue.erase(pInputQueue.begin());
    }

    this->show();
    m_pActiveMenu->display();

    return true;
}

void ACARSSystem::HandleEvents(ACARSActionEvent *pIEvent)
{

    if (pIEvent->getEventType() != ACARSEVENT::MENU)
    {

        m_pActiveMenu->handleEvent(pIEvent);

    } else {
        //Make another menu active
    }

    m_pActiveMenu->show();

}
