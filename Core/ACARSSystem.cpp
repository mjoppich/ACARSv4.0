#include "ACARSSystem.h"
#include <Core/ACARSInputRegistry.h>
#include <Core/ACARSInput.h>
#include <Core/ACARSEvents.h>
#include <Core/ACARSUser.h>

#include <FlightSim/ACARSFlightSimData.h>
#include <FlightSim/XPLANEFlightSimData.h>

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

#include <QQuaternion.h>
#include <QVector4d.h>
#include <QVector3d.h>
#include <qmatrix4x4.h>

const char *ACARSSystem::ACARSFontName = "Lucida Console";
const char *ACARSSystem::ACARSVersion = "4.0.0a";


ACARSSystem::ACARSSystem(QApplication *pApp, QWidget *parent):
    QMainWindow(parent),
    m_pUI(new Ui::ACARSMainWindow)
{
    m_pUI->setupUi(this);


	/*
	QQuaternion *pQuat = new QQuaternion(-0.090664600000000 , 0.692324000000000  , 0.154004000000000  , 0.699107000000000);
	QVector3D *pVec = new QVector3D(1,1,1);

	QMatrix4x4 *pMat = new QMatrix4x4();
	pMat->rotate(*pQuat);

	qDebug() << pQuat->rotatedVector(*pVec) << endl;
	qDebug() << *pMat << endl;
	*/


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

    m_pACARSInputLine = new QLineEdit(this);
    m_pACARSInputLine->setGeometry(100,335,305,20);
    m_pACARSInputLine->setStyleSheet("border: 0px; background: black;");
    QPalette p = m_pACARSInputLine->palette();

    p.setColor(QPalette::Base, QColor(0,0,0));
    p.setColor(QPalette::Window, QColor(0,0,0));
    p.setColor(QPalette::Text, QColor(117,216,118));


    m_pACARSInputLine->setPalette(p);
    m_pACARSInputLine->setText("");
    m_pACARSInputLine->activateWindow();
    m_pACARSInputLine->setContextMenuPolicy(Qt::PreventContextMenu);
    QFont f = m_pACARSInputLine->font();
    f.setCapitalization(QFont::AllUppercase);
    //f.setBold(true);
    f.setFamily(ACARSSystem::ACARSFontName);
    f.setPixelSize(18);
    m_pACARSInputLine->setFont(f);

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
    pInit->setExtComponents(m_pACARSInputLine,this);
    pInit->init();
    ACARSMenu* pLogin = new MENULogin(m_pViews);
    pLogin->setExtComponents(m_pACARSInputLine,this);
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

	m_pFlightSimData = (ACARSFlightSimData*)new XPLANEFlightSimData(this);


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

	if (pEvent->type() == ACARSEVENT::MESSAGEEVENT)
    {
        qDebug() << *((QString*) pObj) << " Message";

		int pos = m_vMessageDisplay.size()-1;
		if (pos < 0)
			pos = 0;
		m_vMessageDisplay.insert(pos,(QString*) pObj);

		if (m_vMessageDisplay.size() == 1)
			m_vMessageDisplay.append(new QString(m_pACARSInputLine->text()));

		this->ClearInputLine();
    }

    return false;

}

void ACARSSystem::Start()
{
    this->show();
    m_LastTime = QTime::currentTime();
    m_pTimer->start(1);
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
    m_pACARSInputLine->setText(m_pACARSInputLine->text().append(c));
}

void ACARSSystem::ClearInputLine()
{
    m_pACARSInputLine->setText("");
}

void ACARSSystem::DelFromInputLine()
{

    QString newText = m_pACARSInputLine->text();
    newText.chop(1);

    m_pACARSInputLine->setText(newText);
}

QString ACARSSystem::getInputLineText()
{
    return m_pACARSInputLine->text();
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

		//message to delete
		if ((m_vMessageDisplay.size() > 0) && (m_pACARSInputLine->text().compare(*(m_vMessageDisplay.first())) == 0))
			if ((pCurrentIE->isEventType(ACARSEVENT::ILINE)) && (pCurrentIE->getInputValue().compare("C") == 0))
			{
				m_vMessageDisplay.erase(m_vMessageDisplay.begin());
			}

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

		//messages to display
		if ((m_vMessageDisplay.size() > 0) && (m_pACARSInputLine->text().compare(*(m_vMessageDisplay.first())) != 0))
		{
			this->ClearInputLine();

			m_pACARSInputLine->setText(*(m_vMessageDisplay.first()));

			if (m_vMessageDisplay.size() == 1)
				m_vMessageDisplay.erase(m_vMessageDisplay.begin());

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
        if (pIEvent->getInputValue() == "LOGN")
			m_pViews->setCurrentIndex(0);


		if (pIEvent->getInputValue() == "PREV")
			((ACARSMenu*)(m_pViews->currentWidget()))->nextPage();
		if (pIEvent->getInputValue() == "NEXT")
			((ACARSMenu*)(m_pViews->currentWidget()))->prevPage();
    }


}
