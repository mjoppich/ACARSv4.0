#include "MENUPAGEInit1.h"

#include <Core/ACARSUser.h>

bool MENUPAGEInit1::handleEvent(ACARSSystem* pACARSSys, ACARSActionEvent *pIEvent)
{

    if (pIEvent->isEventType(ACARSEVENT::MENU))
    {
        if (pIEvent->getInputValue().compare("NEXT") == 0)
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
		int stringcompare = m_pInputLine->text().compare("D");
		if (stringcompare == 0)
        {
            this->resetEntry(pIEvent->getInputValue());
            m_pInputLine->clear();
        } else {
            this->setText(m_pInputLine->text(), ((ACARSActionEvent*) pIEvent)->getInputValue());
            m_pInputLine->clear();
        }
    }


    return true;

}

bool MENUPAGEInit1::init()
{

	int i;

	for (i=0; i < 12; ++i)
	{
		mDefaultEntries[i] = "";
	}
	
	SecondLabels[0]->setText("DEP ICAO");
	mDefaultEntries[0]  = "----";
	SecondLabels[1]->setText("ARR ICAO");
	mDefaultEntries[1]  = "----";
	SecondLabels[2]->setText("AIRCRAFT");
	mDefaultEntries[2]  = "-------";
	SecondLabels[3]->setText("AC REG");
	mDefaultEntries[3]  = "------";
	SecondLabels[4]->setText("");
	mDefaultEntries[4]  = "";
	SecondLabels[5]->setText("");
	mDefaultEntries[5]  = "";
	SecondLabels[6]->setText("FLIGHT NUM");
	mDefaultEntries[6]  = "------";
	SecondLabels[7]->setText("");
	mDefaultEntries[7]  = "";
	SecondLabels[8]->setText("EST TOD");
	mDefaultEntries[8]  = "----";
	SecondLabels[9]->setText("");
	mDefaultEntries[9]  = "";
	SecondLabels[10]->setText("");
	mDefaultEntries[10] = "";
	SecondLabels[11]->setText("");
	mDefaultEntries[11] = "";

    for(i=0; i<12; ++i)
    {

        MainLabels[i]->setText(mDefaultEntries[i]);
        //SecondLabels[i]->setText("");

    }


    return true;

}


