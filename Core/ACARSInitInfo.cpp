#include "ACARSInitInfo.h"

#include <Base/ACARSAirport.h>
#include <Base/ACARSFlight.h>


ACARSInitInfo::ACARSInitInfo(ACARSAirport* pDep, ACARSAirport* pArr, ACARSAircraft* pAC, ACARSFlight* pFlightNum)
{
	m_pDepArp = pDep;
	m_pArrArp = pArr;
	m_pAC= pAC;
	m_pFlightNum = pFlightNum;
}

QString ACARSInitInfo::getFlightNumber()
{
	return m_pFlightNum->getFlightNum();
}

ACARSInitInfo::~ACARSInitInfo(void)
{
}
