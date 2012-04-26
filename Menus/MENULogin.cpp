#include "MENULogin.h"

void MENULogin::handleEvent(ACARSActionEvent *pIEvent)
{
    switch (pIEvent->getEventType())
    {
    case ACARSEVENT::LSK:
        {
        QString *InText = new QString(m_pInputLine->text());
        m_pCurrentMenu->setText(InText,pIEvent->getInputValue(), ACARSMenu::MAIN);
        m_pInputLine->clear();
        }
        break;
    case ACARSEVENT::ILINE:
    {
        QString* SendString = new QString();
        SendString->append("Test");
        this->parent()->eventFilter((QObject*) SendString,new ACARSMenuViewEvent());
    }
        break;

    default:
        break;
    }

    m_pCurrentMenu->show();
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
