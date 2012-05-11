#include "MENULogin.h"

bool MENULogin::handleEvent(ACARSActionEvent *pIEvent)
{

    bool heresult = ((ACARSMenuPage*)(m_pMenuPages->currentWidget()))->handleEvent((ACARSSystem*)this->parent(),pIEvent);

    return heresult;
}

bool MENULogin::init()
{

    ACARSMenuPage* pPage1 = new MENUPAGELogin((QWidget*)this->parent(),1,m_iPageCount);

    pPage1->setStyleSheet("QWidget { background-color: black;}");
    pPage1->setInputLine(m_pInputLine);
    pPage1->init();

    m_pMenuPages->addWidget(pPage1);

    m_pMenuPages->setCurrentIndex(1);
    m_pMenuPages->activateWindow();

    return true;
}
