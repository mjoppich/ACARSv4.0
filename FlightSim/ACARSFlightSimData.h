#ifndef ACARSFLIGHTSIMDATA_H
#define ACARSFLIGHTSIMDATA_H

#include <QObject>
#include <Base/ACARSLatLon.h>
#include <QTime>

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
	virtual QTime getCurrentTime(QString mode) {return QTime(1,1,1);}

public slots:
	virtual void readInputData() {};

private:
	int miVertSpeed, miPayload, miWeight, miFuelWeight, miCounter;
	float mfMach, mfGroundSpeed, mfIAS, mfAltitude, mfHeading;
	double mdLatitude, mdLongitude;
		QTime m_LCLTime;
	QTime m_UTCTime;

};

#endif // ACARSFLIGHTSIMDATA_H
