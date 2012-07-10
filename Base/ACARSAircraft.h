#ifndef ACARSAIRCRAFT_H
#define ACARSAIRCRAFT_H

#include <QString>

class ACARSAircraft
{
public:
	ACARSAircraft(QString sAircraft);
	~ACARSAircraft(void);

	float getMaxMach();
	float getMinMach();

	QString getFTGCode();
	QString getIATACode();
	QString getICAOCode();
};

#endif //ACARSAIRCRAFT_H