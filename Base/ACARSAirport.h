#ifndef ACARSAIRPORT_H
#define ACARSAIRPORT_H

#include <QString>
#include <Base/ACARSLatLon.h>

class ACARSAirport
{
public:
	ACARSAirport(QString sAirport);
	~ACARSAirport(void);

	QString getIATACode();
	QString getICAOCode();
};

#endif //ACARSAIRPORT_H