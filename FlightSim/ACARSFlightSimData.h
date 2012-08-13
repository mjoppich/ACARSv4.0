#ifndef ACARSFLIGHTSIMDATA_H
#define ACARSFLIGHTSIMDATA_H

#include <QObject>

#include <Base\ACARSLatLon.h>

class ACARSFlightSimData : public QObject
{
	Q_OBJECT

public:
	explicit ACARSFlightSimData(QObject *pParent);

	virtual float getAltitude(QString smode) {return mfAltitude;}
	virtual ACARSLatLon* getPosition() {return new ACARSLatLon(mdLatitude, mdLongitude);}
	virtual virtual float getVertSpeed() {return mfAltitude;}
	virtual float getGroundSpeed(QString smode) {return mfGroundSpeed;}
	virtual float getIAS(QString smode) {return mfIAS;}
	virtual float getMach() {return mfMach;}
	virtual float getHeading() {return mfHeading;}
	virtual int getPayload() {return miPayload;}
	virtual int getWeight() {return miWeight;}
	virtual int getFuelWeight() {return miFuelWeight;}
	virtual int getCounter() {return miCounter;}

public slots:
	virtual void readInputData() {};

private:
	int miVertSpeed, miPayload, miWeight, miFuelWeight, miCounter;
	float mfMach, mfGroundSpeed, mfIAS, mfAltitude, mfHeading;
	double mdLatitude, mdLongitude;

};

#endif // ACARSFLIGHTSIMDATA_H
