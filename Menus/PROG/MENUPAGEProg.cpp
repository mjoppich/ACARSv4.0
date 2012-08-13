#include "MENUPAGEProg.h"

#include <Core/ACARSUser.h>
#include <Core/ACARSInitInfo.h>

#include <Base\ACARSAircraft.h>
#include <Base\ACARSAirport.h>
#include <Base\ACARSFlight.h>

#include <Core/ACARSDataBunk.h>

bool MENUPAGEProg1::handleEvent(ACARSSystem* pACARSSys, ACARSActionEvent *pIEvent)
{

	this->setText("Flight Number","L1",ACARSMenu::LINE::HELPER);
	this->setText("ARR ICAO","L2",ACARSMenu::LINE::HELPER);
	this->setText("ARR ICAO","R2",ACARSMenu::LINE::HELPER);
	this->setText("AIRCRAFT","L5",ACARSMenu::LINE::HELPER);
	this->setText("AC REG","R5",ACARSMenu::LINE::HELPER);

	this->setText("STD","L3",ACARSMenu::LINE::HELPER);
	this->setText("STA","R3",ACARSMenu::LINE::HELPER);

	if (pACARSSys->getACARSData()->ACARSReady())
	{

		this->setText(pACARSSys->getACARSData()->getFlightNumber(), "L1");
		this->setText(pACARSSys->getACARSData()->getDepartureAirport()->getICAOCode(), "L2");
		this->setText(pACARSSys->getACARSData()->getArrivalAirport()->getICAOCode(), "R2");
		this->setText(pACARSSys->getACARSData()->getAircraft()->getFTGCode(), "L3");
		this->setText(pACARSSys->getACARSData()->getAircraft()->getRegistration(), "R3");

		this->setText(pACARSSys->getACARSData()->getFlight()->getDepTime()->toString(), "L3");
		this->setText(pACARSSys->getACARSData()->getFlight()->getArrTime()->toString(), "R3");
	}

    return true;

}

bool MENUPAGEProg1::init()
{

	int i;

	for (i=0; i < 12; ++i)
	{
		mDefaultEntries[i] = "";
	}

	SecondLabels[0]->setText("");
	SecondLabels[1]->setText("");
	SecondLabels[2]->setText("");
	SecondLabels[3]->setText("");
	SecondLabels[4]->setText("");
	SecondLabels[5]->setText("");
	SecondLabels[6]->setText("");
	SecondLabels[7]->setText("");
	SecondLabels[8]->setText("");
	SecondLabels[9]->setText("");
	SecondLabels[10]->setText("");
	SecondLabels[11]->setText("");

    for(i=0; i<12; ++i)
    {

        MainLabels[i]->setText(mDefaultEntries[i]);
        //SecondLabels[i]->setText("");

    }

    return true;

}


