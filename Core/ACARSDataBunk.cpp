#include "ACARSDataBunk.h"
#include <qglobal.h>

#include <FlightSim\XPLANEFlightSimData.h>
#include <QTime>

#include <QDebug>

ACARSDataBunk::ACARSDataBunk()
{
	m_pCurrentUser = NULL;
}

void ACARSDataBunk::Update(ACARSFlightSimData* pUpdate)
{
	this->m_pCurrentFSData = pUpdate;
}

void ACARSDataBunk::Update(ACARSUser* pPilot)
{
	this->m_pCurrentUser = pPilot;
}

void ACARSDataBunk::Update(ACARSInitInfo* pInit)
{
	this->m_pCurrentInitInfo = pInit;
}

QString ACARSDataBunk::getACARSUsername()
{
	return m_pCurrentUser->getUsername();
}

int ACARSDataBunk::getIndicatedAirSpeed()
{
	return this->m_pCurrentFSData->getIAS();
}



//void ACARSDataBunk::setGroundSpeed(float newspeed)
//{
//	double calc = 1.852f*60.0f*newspeed;
//	m_iGS = qRound(calc);
//}
//
//void ACARSDataBunk::setIndicatedAirSpeed(float newspeed)
//{
//	double calc = 1.852f*60.0f*newspeed;
//	m_iIAS = qRound(calc);
//}
//
//void ACARSDataBunk::setMachSpeed(float newspeed)
//{
//	m_fMach = newspeed;
//}
//
//void ACARSDataBunk::setPositionLatLon(ACARSLatLon *newpos)
//{
//	m_pPosition = newpos;
//}
//
//void ACARSDataBunk::setLastUpdateTime()
//{
//	m_pLastUpdate = new QTime(QTime::currentTime());
//}
//
//void ACARSDataBunk::setFtAboveGround(float newalt)
//{
//	m_iFtAboveGround = 3.2808399f * newalt;
//}