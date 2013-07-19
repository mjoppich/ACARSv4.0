#ifndef ACARSAIRPORT_H
#define ACARSAIRPORT_H

#include <QString>
#include <Base/ACARSLatLon.h>

class QTime;

class ACARSAirport
{
public:
	ACARSAirport(QString sAirport);
	~ACARSAirport(void);

	QString getIATACode();
	QString getICAOCode();

	ACARSLatLon* getLatLon() {return m_pPosition;}
	QTime getCurrentTime(QTime UTCTime);
	int getTimezone() {return m_iTimezone;};

	bool isValid();

private:
	ACARSLatLon* m_pPosition;
	QString m_sICAO;
	QString m_sIATA;
	QString m_sName;

	int m_iAltitude;
	int m_iTimezone; // Secs difference
	bool m_bValid;
};

#endif //ACARSAIRPORT_H