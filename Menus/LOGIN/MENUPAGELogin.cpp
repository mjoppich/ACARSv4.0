#include "MENUPAGELogin.h"

#include <Core/ACARSUser.h>

bool MENUPAGELogin::evaluateLogin(QString username, QString password)
{
    if (username.compare("-----", Qt::CaseInsensitive) == 0 && password.compare("-----") == 0)
        return true;

    return false;
}

QString MENUPAGELogin::getUserSession(QString username, QString password)
{

    return QString("UserSession");

}

bool MENUPAGELogin::handleEvent(ACARSSystem* pACARSSys, ACARSActionEvent *pIEvent)
{

    if (pIEvent->isEventType(ACARSEVENT::MENU))
    {

		// ADD YOUR CUSTOM ACTIONS HERE

        if (pIEvent->getInputValue().compare("EXEC") == 0)
        {
            if (this->evaluateLogin(this->getText("L4"),this->getText("R4")))
            {
                m_bIsLoggedIn = true;

                qDebug() << "logged in";

                QString sUserSession = this->getUserSession(this->getText("L4"),this->getText("R4"));

                pACARSSys->eventFilter((QObject*) new ACARSUser(this->getText("L4"),sUserSession),new ACARSMenuViewEvent(ACARSEVENT::LOGINEVENT));
            }


			pACARSSys->eventFilter((QObject*) new QString("TestMessage"),new ACARSMenuViewEvent(ACARSEVENT::MESSAGEEVENT));
        }
    }


	// DO NOT CHANGE THIS WITHOUT REASON
	
	if (pIEvent->isEventType(ACARSEVENT::ILINE))
    {
        if (pIEvent->getInputValue().compare("C") == 0)
        {
            pACARSSys->ClearInputLine();
        }

        if (pIEvent->getInputValue().compare("D") == 0)
        {
			if (m_pInputLine->text().compare(""))
            {
                pACARSSys->DelFromInputLine();
            } else {
                pACARSSys->WriteInputLine(QString("D"));
            }

        }
    }

    if (pIEvent->isEventType(ACARSEVENT::LSK))
    {
		if (m_pInputLine->text().length() > 0)
		{
			if ((pACARSSys->getInputLineText().compare("D") == 0) && this->changedEntry(((ACARSActionEvent*) pIEvent)->getInputValue()))
			{
				this->resetEntry(((ACARSActionEvent*) pIEvent)->getInputValue());
				m_pInputLine->clear();
			} else {
				this->setText(m_pInputLine->text(), ((ACARSActionEvent*) pIEvent)->getInputValue());
				m_pInputLine->clear();
			}
		}
    }

    //not allowed to leave this menu :)
    if (!m_bIsLoggedIn)
        return false;

    return true;

}

bool MENUPAGELogin::init()
{

    int i;


	for (i=0; i < 12; ++i)
	{
		mDefaultEntries[i] = "";
	}
	
	mDefaultEntries[2] = "ACARS 4.0 alpha";
	mDefaultEntries[6] = "-----";
	mDefaultEntries[7] = "-----";
	mDefaultEntries[10] = "EXEC TO LOGIN";

    for(i=0; i<12; ++i)
    {

        MainLabels[i]->setText(mDefaultEntries[i]);
        SecondLabels[i]->setText("");

    }

    this->setText(QString("Welcome to"),QString("L2"),ACARSMenu::HELPER);
	this->setTextWithFormat(QString("PLEASE LOGIN"),QString("L3"),ACARSMenu::HELPER, ACARSMenu::AMBER);
    this->setTextWithFormat(QString("Username"),QString("L4"),ACARSMenu::HELPER);
    this->setText(QString("password"),QString("R4"),ACARSMenu::HELPER);

    return true;

}