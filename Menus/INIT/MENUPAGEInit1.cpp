#include "MENUPAGEInit1.h"

#include <Core/ACARSUser.h>
#include <Core/ACARSInitInfo.h>

#include <Base\ACARSAircraft.h>
#include <Base\ACARSAirport.h>
#include <Base\ACARSFlight.h>

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

			// Check for allowed inputs!

			// Sanity check for input here!
			QString inwhere = ((ACARSActionEvent*) pIEvent)->getInputValue();
			QString inwhat = m_pInputLine->text();

			if ((inwhere == "L1") ||
				(inwhere == "R1") ||
				(inwhere == "L2") ||
				(inwhere == "R2") ||
				(inwhere == "L4") ||
				(inwhere == "L5"))
			{

				if ((inwhere == "L1") || (inwhere == "R1")) {
					if (inwhat.length() != 4)
					{
						pACARSSys->eventFilter((QObject*) new QString("WRONG AIRPORT FORMAT"),new ACARSMenuViewEvent(ACARSEVENT::MESSAGEEVENT));
						return true;
					}
				} else if (inwhere == "R2") {

					if (inwhat.length() != 6)
					{
						pACARSSys->eventFilter((QObject*) new QString("WRONG REGISTRATION FORMAT"),new ACARSMenuViewEvent(ACARSEVENT::MESSAGEEVENT));
						return true;
					}

				} else if (inwhere == "L4") {
					if (inwhat.length() > 6)
					{
						pACARSSys->eventFilter((QObject*) new QString("WRONG FLIGHT NUMBER FORMAT"),new ACARSMenuViewEvent(ACARSEVENT::MESSAGEEVENT));
						return true;
					}
				} else if (inwhere == "L5") {
					if (inwhat.length() > 4)
					{
						pACARSSys->eventFilter((QObject*) new QString("WRONG TIME FORMAT"),new ACARSMenuViewEvent(ACARSEVENT::MESSAGEEVENT));
						return true;
					}
				}

				this->setText(inwhat, inwhere);
				m_pInputLine->clear();
			}
        }
    }

	if ((this->allFilled()) && (pIEvent->isEventType(ACARSEVENT::LSK)))
	{
		ACARSAirport* pNewDepAirport = new ACARSAirport(this->getText("L1"));
		ACARSAirport* pNewArrAirport = new ACARSAirport(this->getText("R1"));
		ACARSAircraft* pAircraft = new ACARSAircraft(this->getText("L2"),this->getText("R2"));
		ACARSFlight* pFlight = new ACARSFlight(this->getText("L4"));

		qDebug() << pFlight->getFlightNum();

		if ((pNewDepAirport->isValid()) && (pNewArrAirport->isValid()) && (pAircraft->isValid()) && (pFlight->isValid())) 
		{
			pACARSSys->eventFilter((QObject*) new ACARSInitInfo(pNewDepAirport, pNewArrAirport, pAircraft, pFlight),new ACARSMenuViewEvent(ACARSEVENT::INITCHANGEEVENT));
		} else {

			if (!pFlight->isValid())
			{
				pACARSSys->eventFilter((QObject*) new QString("INVALID FLIGHT NUMBER"),new ACARSMenuViewEvent(ACARSEVENT::MESSAGEEVENT));
			}

			if (!pNewDepAirport->isValid())
			{
				pACARSSys->eventFilter((QObject*) new QString("INVALID DEP AIRPORT"),new ACARSMenuViewEvent(ACARSEVENT::MESSAGEEVENT));
			}

			if (!pNewArrAirport->isValid())
			{
				pACARSSys->eventFilter((QObject*) new QString("INVALID ARR AIRPORT"),new ACARSMenuViewEvent(ACARSEVENT::MESSAGEEVENT));
			}

			if (!pAircraft->isValid())
			{
				pACARSSys->eventFilter((QObject*) new QString("INVALID AIRCRAFT"),new ACARSMenuViewEvent(ACARSEVENT::MESSAGEEVENT));
			}

			delete(pNewDepAirport);
			delete(pNewArrAirport);
			delete(pFlight);
			delete(pAircraft);
		}
	}


    return true;

}

bool MENUPAGEInit1::allFilled()
{
	return ( (this->getText("L1") != mDefaultEntries[0]) && (this->getText("R1") != mDefaultEntries[1]) && (this->getText("L2") != mDefaultEntries[2]) && (this->getText("L4") != mDefaultEntries[6]));
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

	MainLabels[0]->setText( "EDDK");
	MainLabels[1]->setText( "EDDM");
	MainLabels[2]->setText( "320-200");
	MainLabels[3]->setText( "MARKUS");
	MainLabels[6]->setText( "LH418");

    return true;

}


