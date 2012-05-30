#include "MENUPAGEInit2.h"

#include <Core/ACARSUser.h>

bool MENUPAGEInit2::evaluateLogin(QString username, QString password)
{
    if (username.compare("LH418", Qt::CaseInsensitive) == 0 && password.compare("AAA") == 0)
        return true;

    return false;
}

QString MENUPAGEInit2::getUserSession(QString username, QString password)
{

    return QString("UserSession");

}

bool MENUPAGEInit2::handleEvent(ACARSSystem* pACARSSys, ACARSActionEvent *pIEvent)
{

    if (pIEvent->isEventType(ACARSEVENT::MENU))
    {
        if (pIEvent->getInputValue().compare("PREV") == 0)
        {

            //NOTHING TO HAPPEN HERE!
			return true;
        }
    }


    if (pIEvent->isEventType(ACARSEVENT::ILINE))
    {
        if (pIEvent->getInputValue().compare("C") == 0)
        {
            pACARSSys->ClearInputLine();
        }

        if (pIEvent->getInputValue().compare("D") == 0)
        {
            if (m_pInputLine->text() != "")
            {
                pACARSSys->DelFromInputLine();
            } else {
                pACARSSys->WriteInputLine(QString("D"));
            }

        }
    }

    if (pIEvent->isEventType(ACARSEVENT::LSK))
    {
        this->setText(m_pInputLine->text(), ((ACARSActionEvent*) pIEvent)->getInputValue());
        m_pInputLine->clear();
    }


    return true;

}

bool MENUPAGEInit2::init()
{

    int i;

    for(i=0; i<12; ++i)
    {

        MainLabels[i]->setText("");
        SecondLabels[i]->setText("");

    }

    this->setText(QString("Welcome to"),QString("L2"),ACARSMenu::HELPER);
    this->setText(QString("ACARS 4.0 alpha"),QString("L2"),ACARSMenu::MAIN);

    this->setText(QString("PLEASE LOGIN:"),QString("L3"),ACARSMenu::MAIN);

    this->setTextWithFormat(QString("Username"),QString("L4"),ACARSMenu::HELPER, ACARSMenu::AMBER);
    this->setText(QString("password"),QString("R4"),ACARSMenu::HELPER);

    this->setText(QString("-----"),QString("L4"),ACARSMenu::MAIN);



    this->setText(QString("EXEC TO LOGIN"),QString("L6"),ACARSMenu::MAIN);

    return true;

}