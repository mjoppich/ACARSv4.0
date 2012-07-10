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
	float getAltitude() {return mfAltitude;}
	float getLatitude() {return mfLatitude;}
	float getLongitude() {return mfLongitude;}
	float getVertSpeed() {return mfAltitude;}
	float getGroundSpeed() {return mfGroundSpeed;}
	float getIAS() {return mfIAS;}
	float getMach() {return mfMach;}
	int getPayload() {return miPayload;}
	int getWeight() {return miWeight;}
	int getFuelWeight() {return miFuelWeight;}
	int getCounter() {return miCounter;}

public slots:
		void readInputData();

private:
	QUdpSocket* m_pSocket;

	int miVertSpeed, miPayload, miWeight, miFuelWeight, miCounter;
	float mfLatitude, mfLongitude, mfMach, mfGroundSpeed, mfIAS, mfAltitude;

};

#endif // XPLANEFLIGHTSIMDATA_H
