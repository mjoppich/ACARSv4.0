#include "ACARSCore.h"
#include "ACARSInput.h"

ACARSCore::ACARSCore(QObject *parent) :
    QObject(parent)
{
    m_pTimer = new QTimer(this);

    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(MainLoop()));
}

bool ACARSCore::ACARSInit()
{

    //Do some initialisation stuff
    m_pMainWindow = new ACARSMainWindow();
    m_pMainWindow->Init();
}

bool ACARSCore::ACARSStart()
{
    m_pMainWindow->show();
    m_LastTime = QTime::currentTime();
    m_pTimer->start(10);
}

bool ACARSCore::MainLoop()
{
    // Get Events
    QVector<ACARSInputEvent*> pInputQueue;
    m_pMainWindow->GetInputEventsQueue(&pInputQueue);





    //Debug ACARSInputEvents
    ACARSInputEvent* pCurrentIE;

    while(pInputQueue.count())
    {
        pCurrentIE = *(pInputQueue.begin());

        // Work CORE EVENTS - NOTE: These must NOT alter pInputQueue!

        if (pCurrentIE->isEventType(ACARSInputEvent::MOUSE))
        {
             qDebug(pCurrentIE->getInputValue());
             m_pMainWindow->WriteInputLine(pCurrentIE->getInputValue());

        }

        pInputQueue.erase(pInputQueue.begin());
    }

    // WORK ADDON EVENTS - ONLY EVERY 1000ms
    if (m_LastTime.msecsTo(QTime::currentTime()) < 0)
    {
        m_LastTime = QTime::currentTime();
        m_LastTime.addMSecs(1000);
    }

}
