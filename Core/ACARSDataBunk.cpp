#include "ACARSDataBunk.h"
#include <qglobal.h>

#include <FlightSim\XPLANEFlightSimData.h>
#include <QTime>
#include <QtGlobal>
#include <QDebug>

#include <Base\ACARSFlight.h>
#include <Base\ACARSTimeSpan.h>

ACARSDataBunk::ACARSDataBunk()
{
	m_pCurrentUser = new ACARSUser("","");
	m_pCurrentInitInfo = new ACARSInitInfo(new ACARSAirport("EDDK"),new ACARSAirport(""),new ACARSAircraft("",""),new ACARSFlight(""));
	m_pCurrentFSData = NULL;

	FSDataOK = false;
	ACARSUserOK = false;
	INITInfoOK = false;

	m_pCurrentUTCTime = new QTime(0,0,0,0);
	m_pCurrentLCLTime = new QTime(0,0,0,0);

}

bool ACARSDataBunk::ACARSReady()
{
	return (FSDataOK && ACARSUserOK && INITInfoOK);
}

void ACARSDataBunk::Update(ACARSFlightSimData* pUpdate)
{
	this->m_pCurrentFSData = pUpdate;
	FSDataOK = true;
}

void ACARSDataBunk::Update(ACARSUser* pPilot)
{
	this->m_pCurrentUser = pPilot;
	ACARSUserOK = true;
}

void ACARSDataBunk::Update(ACARSInitInfo* pInit)
{
	this->m_pCurrentInitInfo = pInit;
	INITInfoOK = true;
}

QString ACARSDataBunk::getACARSUsername()
{
	return m_pCurrentUser->getUsername();
}

//INIT
ACARSAirport* ACARSDataBunk::getDepartureAirport()
{
	if (m_pCurrentInitInfo != NULL) {
	return this->m_pCurrentInitInfo->getDepartureAirport();
	} else return NULL;
}

ACARSAirport* ACARSDataBunk::getArrivalAirport()
{
	if (m_pCurrentInitInfo != NULL) {
	return this->m_pCurrentInitInfo->getArrivalAirport();
	} else return NULL;
}

ACARSAircraft* ACARSDataBunk::getAircraft()
{
	if (m_pCurrentInitInfo != NULL) {
	return this->m_pCurrentInitInfo->getAircraft();
	} else return NULL;
}
QString ACARSDataBunk::getFlightNumber()
{
	if (m_pCurrentInitInfo != NULL) {
	return this->m_pCurrentInitInfo->getFlightNumber();
	} else return "";
}

ACARSFlight* ACARSDataBunk::getFlight()
{
	return m_pCurrentInitInfo->getFlight();
}

//Position
ACARSLatLon* ACARSDataBunk::getPositionLatLon()
{
	if (m_pCurrentFSData != NULL) {
	return this->m_pCurrentFSData->getPosition();
	} else return 0;
}

float ACARSDataBunk::getDistToDest()
{
	return this->m_pCurrentInitInfo->getArrivalAirport()->getLatLon()->DistanceTo(this->m_pCurrentFSData->getPosition());
}

//Altitude
int ACARSDataBunk::getAltitude(QString smode)
{
	if (m_pCurrentFSData != NULL) {
		return this->m_pCurrentFSData->getAltitude(smode);
	} else return 0;
}

//Speed
float ACARSDataBunk::getMachSpeed()
{
	if (m_pCurrentFSData != NULL) {
	return this->m_pCurrentFSData->getMach();
	} else return 0;
}
float ACARSDataBunk::getIndicatedAirSpeed(QString smode)
{
	if (m_pCurrentFSData != NULL) {
	return this->m_pCurrentFSData->getIAS(smode);
	} else return 0;
}
float ACARSDataBunk::getGroundSpeed(QString smode)
{
	if (m_pCurrentFSData != NULL) {
	return this->m_pCurrentFSData->getGroundSpeed(smode);
	} else return 0;
}

//Orientation
float ACARSDataBunk::getHeading()
{
	if (m_pCurrentFSData != NULL) {
	return qRound(this->m_pCurrentFSData->getHeading());
	} else return 0;
}

// Times
QTime ACARSDataBunk::getCurrentTime(QString mode)
{
	return m_pCurrentFSData->getCurrentTime(mode);
}

ACARSTimeSpan ACARSDataBunk::getTimezone(int iSecs)
{
	return ACARSTimeSpan(iSecs);
}

ACARSTimeSpan ACARSDataBunk::getCurrentTimezone()
{

	int iSecs = m_pCurrentUTCTime->secsTo(*m_pCurrentLCLTime);

	ACARSTimeSpan newTimeSpan = ACARSTimeSpan(m_pCurrentFSData->getCurrentTime("UTC").secsTo(m_pCurrentFSData->getCurrentTime("LCL")));
	
	return newTimeSpan;

}

int ACARSDataBunk::getCurrentTimezoneI()
{

	return (m_pCurrentFSData->getCurrentTime("UTC").secsTo(m_pCurrentFSData->getCurrentTime("LCL")));

}

ACARSTimeSpan* ACARSDataBunk::getTimeToDest()
{

	int itimespan = 0;

	float dist = this->getDistToDest();
	int speed = qRound(this->getGroundSpeed("kts"));

	if (speed > 0) {

		itimespan = std::floor((dist/(float)speed)*3600);
		itimespan = itimespan;
	}

	return new ACARSTimeSpan(itimespan);

}