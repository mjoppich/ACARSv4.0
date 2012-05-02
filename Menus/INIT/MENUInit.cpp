#include "MENULogin.h"

bool MENULogin::handleEvent(ACARSActionEvent *pIEvent)
{

    bool heresult = m_pCurrentMenu->handleEvent((ACARSSystem*)this->parent(),pIEvent);

    m_pCurrentMenu->show();

    return heresult;
}

bool MENULogin::init()
{

    int i;

    m_pMenuPages = new ACARSMenuPage*[m_iPageCount];

    for (i=0; i<m_iPageCount; ++i)
    {
        m_pMenuPages[i] = (ACARSMenuPage*)new MENUPAGELogin((QWidget*)this->parent(),i+1,m_iPageCount);
        m_pMenuPages[i]->setStyleSheet("QWidget { background-color: black;}");
        m_pMenuPages[i]->move(65,50);
        m_pMenuPages[i]->init();
    }

    m_pCurrentMenu = m_pMenuPages[0];
    m_pCurrentMenu->raise();

    return true;
}
