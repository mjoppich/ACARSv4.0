#include "MENULogin.h"



bool MENULogin::init()
{

    ACARSMenuPage* pPage1 = new MENUPAGELogin((QWidget*)this->parent(),1,m_iPageCount);

	m_iCurPage = 0;
	m_iPageCount = 1;

    pPage1->setStyleSheet("QWidget { background-color: black;}");
    pPage1->setInputLine(m_pInputLine);
    pPage1->init();

    m_pMenuPages->addWidget(pPage1);

	m_pMenuPages->setCurrentIndex(m_iCurPage);

    m_pMenuPages->activateWindow();

    return true;
}
