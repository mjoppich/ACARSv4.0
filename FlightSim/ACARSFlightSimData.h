#ifndef ACARSFLIGHTSIMDATA_H
#define ACARSFLIGHTSIMDATA_H

#include <QObject>

class ACARSFlightSimData : public QObject
{
	Q_OBJECT

public:
	explicit ACARSFlightSimData(QObject *pParent);

	virtual float getAltitude() {return mfAltitude;}
	virtual float getLatitude() {return mfLatitude;}
	virtual float getLongitude() {return mfLongitude;}
	virtual virtual float getVertSpeed() {return mfAltitude;}
	virtual float getGroundSpeed() {return mfGroundSpeed;}
	virtual float getIAS() {return mfIAS;}
	virtual float getMach() {return mfMach;}
	virtual int getPayload() {return miPayload;}
	virtual int getWeight() {return miWeight;}
	virtual int getFuelWeight() {return miFuelWeight;}
	virtual int getCounter() {return miCounter;}

public slots:
	virtual void readInputData() {};

private:
	int miVertSpeed, miPayload, miWeight, miFuelWeight, miCounter;
	float mfLatitude, mfLongitude, mfMach, mfGroundSpeed, mfIAS, mfAltitude;

};

#endif // ACARSFLIGHTSIMDATA_H
