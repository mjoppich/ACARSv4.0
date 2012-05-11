#include "ACARSSystem.h"
#include <Core/ACARSInputRegistry.h>
#include <Core/ACARSInput.h>
#include <Core/ACARSEvents.h>
#include <Core/ACARSUser.h>

#include <Menus/LOGIN/MENULogin.h>
#include <Menus/INIT/MENUInit.h>

#include"ui_ACARSMainWindow.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QPalette>
#include <QCursor>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPixmap>

#include <QDir>
#include <QFileDialog>

#include <QStackedWidget>

const char *ACARSSystem::ACARSFontName = "Lucida Console";
const char *ACARSSystem::ACARSVersion = "4.0.0a";


ACARSSystem::ACARSSystem(QApplication *pApp, QWidget *parent):
    QMainWindow(parent),
    m_pUI(new Ui::ACARSMainWindow)
{
    m_pUI->setupUi(this);

    this->setWindowTitle(QString("ACARS ").append(ACARSSystem::ACARSVersion));
    this->installEventFilter(this);

    m_pParentApp = pApp;

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

    QPushButton *pSButton = new QPushButton("S",this);
    pSButton->resize(20,20);
    pSButton->move(5,725);
    connect(pSButton,SIGNAL(clicked()),this,SLOT(saveScreenShot()));

    m_pViews = new QStackedWidget(this);
    m_pViews->raise();
    m_pViews->setFixedSize(365,280);
    m_pViews->move(70,50);
    m_pViews->setStyleSheet("QStackedWidget {background-color: green}");

    ACARSMenu* pInit = new MENUInit(m_pViews);
    pInit->setInputLine(mACARSInputLine);
    pInit->init();
    ACARSMenu* pLogin = new MENULogin(m_pViews);
    pLogin->setInputLine(mACARSInputLine);
    pLogin->init();

    m_pViews->addWidget(pLogin);
    m_pViews->addWidget(pInit);
    m_pViews->setCurrentWidget(pLogin);

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

void ACARSSystem::saveScreenShot()
{

    QPixmap originalPixmap = QPixmap::grabWindow(this->winId());
    m_pParentApp->beep();

    QString format = "png";
    QString initialPath = QDir::currentPath() + tr("/untitled.") + format;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),initialPath,tr("%1 Files (*.%2);;All Files (*)").arg(format.toUpper()).arg(format));
    if (!fileName.isEmpty())
        originalPixmap.save(fileName, format.toAscii());

}

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

        if (((ACARSMenu*)m_pViews->currentWidget())->handleEvent(pCurrentIE))
        {

            //HANDLE MENU CHANGES HERE!
            qDebug() << "MENU CHANGE!";

            this->HandleEvents(pCurrentIE);

            // WORK ADDON EVENTS - ONLY EVERY 1000ms and if allowed
            if (m_LastTime.msecsTo(QTime::currentTime()) < 0)
            {
                m_LastTime = QTime::currentTime();
                m_LastTime.addMSecs(1000);
            }
        }

        pInputQueue.erase(pInputQueue.begin());
    }

    m_pViews->show();

    return true;
}

void ACARSSystem::HandleEvents(ACARSActionEvent *pIEvent)
{

    if (pIEvent->getEventType() != ACARSEVENT::MENU)
    {

        ((ACARSMenu*)(m_pViews->currentWidget()))->handleEvent(pIEvent);

    } else {
        //Make another menu active

        if (pIEvent->getInputValue() == "INIT")
            m_pViews->setCurrentIndex(1);
        else m_pViews->setCurrentIndex(0);

    }


}
