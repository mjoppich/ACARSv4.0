#ifndef ACARSINITINFO_H
#define ACARSINITINFO_H

class ACARSAirport;
class ACARSAircraft;

class ACARSInitInfo
{
public:
	ACARSInitInfo(ACARSAirport* pDep, ACARSAirport* pArr, ACARSAircraft* pAC);
	~ACARSInitInfo();

	ACARSAirport* getDepartureAirport();
	ACARSAirport* getArrivalAirport();
	ACARSAircraft* getAircraft();

private:
	ACARSAirport* m_pDepArp;
	ACARSAirport* m_pArrArp;
	ACARSAircraft* m_pAC;

};

#endif // ACARSINITINFO_H