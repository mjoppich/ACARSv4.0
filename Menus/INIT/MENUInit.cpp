#include "MENUInit.h"

bool MENUInit::init()
{

	m_iPageCount = 2;
	m_iCurPage = 0;

    ACARSMenuPage* pPage1 = new MENUPAGEInit1((QWidget*)this->parent(),1,m_iPageCount);
    ACARSMenuPage* pPage2 = new MENUPAGEInit2((QWidget*)this->parent(),2,m_iPageCount);

    pPage1->setStyleSheet("QWidget { background-color: black;}");
    pPage1->setInputLine(m_pInputLine);
    pPage1->init();

    pPage2->setStyleSheet("QWidget { background-color: black;}");
    pPage2->setInputLine(m_pInputLine);
    pPage2->init();


    m_pMenuPages->addWidget(pPage1);
    m_pMenuPages->addWidget(pPage2);

	m_pMenuPages->setCurrentIndex(m_iCurPage);
    m_pMenuPages->activateWindow();

    m_pMenuPages->currentWidget()->show();

    return true;
}
