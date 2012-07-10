#include "ACARSInitInfo.h"

#include <Base/ACARSAirport.h>


ACARSInitInfo::ACARSInitInfo(ACARSAirport* pDep, ACARSAirport* pArr, ACARSAircraft* pAC)
{
	m_pDepArp = pDep;
	m_pArrArp = pArr;
	m_pAC= pAC;
}


ACARSInitInfo::~ACARSInitInfo(void)
{
}
