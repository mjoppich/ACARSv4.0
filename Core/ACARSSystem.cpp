#include "ACARSSystem.h"
#include <Core/ACARSInputRegistry.h>
#include <Core/ACARSInput.h>
#include <Core/ACARSEvents.h>
#include <Core/ACARSUser.h>
#include <Core/ACARSDataBunk.h>

#include <FlightSim/ACARSFlightSimData.h>
#include <FlightSim/XPLANEFlightSimData.h>

#include <Menus/LOGIN/MENULogin.h>
#include <Menus/INIT/MENUInit.h>
#include <Menus/PROG/MENUProg.h>

#include <LiveACARS/FTGLiveACARS.h>
#include <LiveACARS/LiveACARS.h>

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

#include <QXmlStreamReader>

const char *ACARSSystem::ACARSFontName = "Lucida Console";
const char *ACARSSystem::ACARSVersion = "4.0.0a";


ACARSSystem::ACARSSystem(QApplication *pApp, QWidget *parent):
    QMainWindow(parent),
    m_pUI(new Ui::ACARSMainWindow)
{
    m_pUI->setupUi(this);


	//QQuaternion *pQuat = new QQuaternion(  0.697615000000000 ,  0.145765000000000 ,  0.692863000000000 , -0.109666000000000);
	//QVector3D *pVec = new QVector3D(1,0,0);

	//QMatrix4x4 *pMat = new QMatrix4x4();
	//pMat->rotate(*pQuat);

	//qDebug() << pQuat->rotatedVector(*pVec) << endl;
	//qDebug() << *pMat << endl;

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

	m_vMessageDisplay.clear();

    ACARSMenu* pInit = new MENUInit(m_pViews);
    pInit->setExtComponents(m_pACARSInputLine,this);
    pInit->init();
    ACARSMenu* pLogin = new MENULogin(m_pViews);
    pLogin->setExtComponents(m_pACARSInputLine,this);
    pLogin->init();
    ACARSMenu* pProg = new MENUProg(m_pViews);
    pProg->setExtComponents(m_pACARSInputLine,this);
    pProg->init();


    m_pViews->addWidget(pLogin);
    m_pViews->addWidget(pInit);
	m_pViews->addWidget(pProg);
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

	new XPLANEFlightSimData(this);
	m_pLiveACARS = (LiveACARS*) (new FTGLiveACARS(this));
	m_pCurrentData = new ACARSDataBunk();


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
		m_pCurrentData->Update((ACARSUser*) pObj);
    }

    if (pEvent->type() == ACARSEVENT::INITCHANGEEVENT)
    {
		m_pCurrentData->Update((ACARSInitInfo*) pObj);
        qDebug() << "INIT CHANE EVENT RECEIVED";
    }

    if (pEvent->type() == ACARSEVENT::FSUPDATEEVENT)
    {
        qDebug() << " FS UPDATE RECEIVED";
		m_pCurrentData->Update((ACARSFlightSimData*)pObj);
    }

	if (pEvent->type() == ACARSEVENT::MESSAGEEVENT)
    {
        qDebug() << *((QString*) pObj) << " Message";

		int pos = m_vMessageDisplay.size()-1;
		if (pos < 0)
			pos = 0;
		m_vMessageDisplay.insert(pos,(QString*) pObj);

		//if (m_vMessageDisplay.size() == 1)
		//	m_vMessageDisplay.append(new QString(m_pACARSInputLine->text()));

		//this->ClearInputLine();
    }

    return false;

}

void ACARSSystem::Start()
{
    this->show();
    m_LastTime = QTime::currentTime();
    m_pTimer->start(100);
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

	if (m_pCurrentData->ACARSReady())
		((ACARSMenu*)(m_pViews->currentWidget()))->updateFSData(m_pCurrentData);

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

				if (m_vMessageDisplay.size() == 0)
				{
					this->ClearInputLine();
					this->WriteInputLine(m_sLastUserInput);
				}

				pInputQueue.erase(pInputQueue.begin());
				continue;
			}

        // Work CORE EVENTS - NOTE: These must NOT alter pInputQueue!

        if (pCurrentIE->isEventType(ACARSEVENT::VKEY))
        {
             this->WriteInputLine(pCurrentIE->getInputValue());
        }

        if (((ACARSMenu*)(m_pViews->currentWidget()))->handleEvent(pCurrentIE))
        {
			if (this->HandleEvents(pCurrentIE))
			{
				((ACARSMenu*)(m_pViews->currentWidget()))->handleEvent(new ACARSActionEvent(ACARSEVENT::TYPE::VIEWUPDATEEVENT,""));
			}
        }

        pInputQueue.erase(pInputQueue.begin());
    }

    // WORK ADDON EVENTS - ONLY EVERY 1000ms and if allowed
    if (abs(m_LastTime.msecsTo(QTime::currentTime())) > 1000)
    {
        m_LastTime = QTime::currentTime();
        m_LastTime.addMSecs(1000);

		if (m_pCurrentData->ACARSReady())
		{
			m_pLiveACARS->Send(m_pCurrentData);
		}

    }

	//messages to display
	if ((m_vMessageDisplay.size() > 0) && (m_pACARSInputLine->text() != (*(m_vMessageDisplay.first()))))
	{
	
		QString input = this->m_pACARSInputLine->text();

		if (input != "")
			if (input != (*(m_vMessageDisplay.first())))
			{
				m_sLastUserInput = this->m_pACARSInputLine->text();
			}
		
		this->ClearInputLine();

		m_pACARSInputLine->setText(*(m_vMessageDisplay.first()));

	}

	m_pViews->repaint();
	m_pParentApp->processEvents();

    return true;
}

bool ACARSSystem::HandleEvents(ACARSActionEvent *pIEvent)
{

    if (pIEvent->getEventType() == ACARSEVENT::MENU)
    {

		int iSwitchTo;
		iSwitchTo = m_pViews->currentIndex();

		if (pIEvent->getInputValue() == "PROG")
			iSwitchTo = 2;
		if (pIEvent->getInputValue() == "INIT")
			iSwitchTo = 1;
		if (pIEvent->getInputValue() == "LOGN")
			iSwitchTo = 0;

		if (iSwitchTo != m_pViews->currentIndex())
		{
			m_pViews->setCurrentIndex(iSwitchTo);
			return true;
		}


		if (pIEvent->getInputValue() == "PREV")
		{
			((ACARSMenu*)(m_pViews->currentWidget()))->nextPage();
			return true;
		}

		if (pIEvent->getInputValue() == "NEXT") {
			((ACARSMenu*)(m_pViews->currentWidget()))->prevPage();
			return true;
		}
    
	}

	return false;

}
