#include "MENUPAGEProg2.h"

#include <Base\ACARSAircraft.h>
#include <Base\ACARSAirport.h>
#include <Base\ACARSFlight.h>
#include <Base\ACARSLatLon.h>
#include <Base\ACARSTimeSpan.h>

#include <Core/ACARSDataBunk.h>

bool MENUPAGEProg2::handleEvent(ACARSSystem* pACARSSys, ACARSActionEvent *pIEvent)
{

	this->setText("UTC TIME","L1",ACARSMenu::LINE::HELPER);
	this->setText("LCL TIME","R1",ACARSMenu::LINE::HELPER);

	this->setText("LCL AT DEP","L2",ACARSMenu::LINE::HELPER);
	this->setText("LCL AT DEST","R2",ACARSMenu::LINE::HELPER);

	this->setText("CURRENT TZ","L3",ACARSMenu::LINE::HELPER);
	this->setText("DESTINATION TZ","R3",ACARSMenu::LINE::HELPER);

	this->setText("CUR LAT","L4",ACARSMenu::LINE::HELPER);
	this->setText("CUR LON","R4",ACARSMenu::LINE::HELPER);

	this->setText("CUR HEADING","L5",ACARSMenu::LINE::HELPER);
	this->setText("BRNG TO DEST","R5",ACARSMenu::LINE::HELPER);

	this->setText("DIST TO DEST","L6",ACARSMenu::LINE::HELPER);
	this->setText("TIME TO DEST","R6",ACARSMenu::LINE::HELPER);

	if (pACARSSys->getACARSData()->ACARSReady())
	{
		this->setText(pACARSSys->getACARSData()->getCurrentTime().toString("hhmm"), "L1");
		this->setText(pACARSSys->getACARSData()->getCurrentTime("LCL").toString("hhmm"), "R1");

		this->setText(pACARSSys->getACARSData()->getDepartureAirport()->getCurrentTime(pACARSSys->getACARSData()->getCurrentTime()).toString("hhmm"), "L2");
		this->setText(pACARSSys->getACARSData()->getArrivalAirport()->getCurrentTime(pACARSSys->getACARSData()->getCurrentTime()).toString("hhmm"), "R2");

		this->setText(pACARSSys->getACARSData()->getCurrentTimezone().toString(), "L3");
		this->setText(ACARSTimeSpan(pACARSSys->getACARSData()->getArrivalAirport()->getTimezone()).toString(), "R3");

		this->setText(ts(pACARSSys->getACARSData()->getPositionLatLon()->getLat(),8), "L4");
		this->setText(ts(pACARSSys->getACARSData()->getPositionLatLon()->getLon(),8), "R4");

		this->setText(ts(pACARSSys->getACARSData()->getHeading(),4), "L5");
		this->setText(ts(ACARSLatLon::BearingFromTo(pACARSSys->getACARSData()->getPositionLatLon(),pACARSSys->getACARSData()->getArrivalAirport()->getLatLon())), "R5");

		this->setText(ts(pACARSSys->getACARSData()->getDistToDest(),8), "L6");
		this->setText(pACARSSys->getACARSData()->getTimeToDest()->toString(), "R6");
	}

    return true;

}

bool MENUPAGEProg2::init()
{

    int i;

    for(i=0; i<12; ++i)
    {

        MainLabels[i]->setText("");
        SecondLabels[i]->setText("");

    }

	this->setText("UTC TIME","L1",ACARSMenu::LINE::HELPER);
	this->setText("LCL TIME","R1",ACARSMenu::LINE::HELPER);

	this->setText("LCL AT DEP","L2",ACARSMenu::LINE::HELPER);
	this->setText("LCL AT DEST","R2",ACARSMenu::LINE::HELPER);

	this->setText("CURRENT TZ","L3",ACARSMenu::LINE::HELPER);
	this->setText("DESTINATION TZ","R3",ACARSMenu::LINE::HELPER);

	this->setText("CUR LAT","L4",ACARSMenu::LINE::HELPER);
	this->setText("CUR LON","R4",ACARSMenu::LINE::HELPER);

	this->setText("CUR HEADING","L5",ACARSMenu::LINE::HELPER);
	this->setText("BRNG TO DEST","R5",ACARSMenu::LINE::HELPER);

	this->setText("DIST TO DEST","L6",ACARSMenu::LINE::HELPER);
	this->setText("TIME TO DEST","R6",ACARSMenu::LINE::HELPER);

    return true;

}