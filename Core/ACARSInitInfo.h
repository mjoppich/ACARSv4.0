#ifndef ACARSINITINFO_H
#define ACARSINITINFO_H

class ACARSAirport;
class ACARSAircraft;
class ACARSFlight;

#include <QString>

class ACARSInitInfo
{
public:
	ACARSInitInfo(ACARSAirport* pDep, ACARSAirport* pArr, ACARSAircraft* pAC, ACARSFlight* pFlightNum);
	~ACARSInitInfo();

	ACARSAirport* getDepartureAirport() {return m_pDepArp;}
	ACARSAirport* getArrivalAirport() {return m_pArrArp;}
	ACARSAircraft* getAircraft() {return m_pAC;}
	ACARSFlight* getFlight() {return m_pFlightNum;}
	QString getFlightNumber();

private:
	ACARSAirport* m_pDepArp;
	ACARSAirport* m_pArrArp;
	ACARSAircraft* m_pAC;
	ACARSFlight* m_pFlightNum;

};

#endif // ACARSINITINFO_H