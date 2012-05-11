#include "MENUPAGEInit1.h"

#include <Core/ACARSUser.h>

bool MENUPAGEInit1::handleEvent(ACARSSystem* pACARSSys, ACARSActionEvent *pIEvent)
{

    if (pIEvent->isEventType(ACARSEVENT::MENU))
    {
        if (pIEvent->getInputValue().compare("EXEC") == 0)
        {

            //NOTHING TO HAPPEN HERE!

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

    //not allowed to leave this menu :)
    if (!m_bIsLoggedIn)
        return false;

    // TODO: need to do something

    return true;

}

bool MENUPAGEInit1::init()
{

    int i;

    for(i=0; i<12; ++i)
    {

        MainLabels[i]->setText(QString::number(i));
        SecondLabels[i]->setText(QString::number(i));

    }


    return true;

}
