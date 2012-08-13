#ifndef ACARSFLIGHT_H
#define ACARSFLIGHT_H

#include <QString>
#include <QTime>

class ACARSFlight
{
public:
	ACARSFlight(QString sFlightNumber, QTime* pDepTime = NULL, QTime* pArrTime = NULL);
	~ACARSFlight(void);

	float getMaxMach();
	float getMinMach();

	QString getFlightNum() {return m_sFlightNum;}
	QTime* getDepTime() {return m_pSchedDepTime;}
	QTime* getArrTime() {return m_pSchedArrTime;}

	bool isValid();

private:
	QString m_sFlightNum;
	QString m_sCallsign;
	QString m_sAirlineICAO;
	QString m_sAirlineIATA;
	QString m_sAirlineName;

	QTime* m_pSchedDepTime;
	QTime* m_pSchedArrTime;

	bool m_bValid;
};

#endif //ACARSFLIGHT_H