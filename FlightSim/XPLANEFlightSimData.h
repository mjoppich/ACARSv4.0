#ifndef XPLANEFLIGHTSIMDATA_H
#define XPLANEFLIGHTSIMDATA_H

#include <QObject.h>
#include <FlightSim/ACARSFlightSimData.h>
#include <Core/ACARSDataBunk.h>

class QUdpSocket;

class XPLANEFlightSimData : public ACARSFlightSimData
{

public:
	XPLANEFlightSimData(QObject *pParent);

	void parseInputData(QByteArray InputData);

	// altitude, latitude, longitude,vertspeed, groundspeed, indicatedairspeed, machspeed, payloadweight, totalweight, fueltotalweight, counter
	float getAltitude(QString smode) {

		if (smode == "ft")
			return qRound(mfAltitude * 1.0f/0.3048f);

		return mfAltitude;
	
	}
	double getLatitude() {return mdLatitude;}
	double getLongitude() {return mdLongitude;}
	float getVertSpeed() {return mfAltitude;}
	float getGroundSpeed(QString smode) {

		if (smode == "kmh")
			return 1.85200*mfGroundSpeed;

		return mfGroundSpeed;
	}
	float getIAS(QString smode) {
		
		if (smode == "kmh")
			return 1.85200*mfGroundSpeed;

		return mfIAS;
	}

	float getHeading()
	{
		return mfHeading;
	}

	float getMach() {return mfMach;}
	int getPayload() {return miPayload;}
	int getWeight() {return miWeight;}
	int getFuelWeight() {return miFuelWeight;}
	int getCounter() {return miCounter;}

	ACARSLatLon* getPosition() {return new ACARSLatLon(mdLatitude,mdLongitude);}
	

public slots:
		void readInputData();

private:
	QUdpSocket* m_pSocket;

	int miVertSpeed, miPayload, miWeight, miFuelWeight, miCounter;
	float mfMach, mfGroundSpeed, mfIAS, mfAltitude, mfHeading;
	double mdLatitude, mdLongitude;

};

#endif // XPLANEFLIGHTSIMDATA_H
