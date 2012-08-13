#ifndef ACARSDATABUNK_H
#define ACARSDATABUNK_H

#include <QPoint>
#include <QDateTime>

class ACARSFlightSimData;
class QLineEdit;

#include <Base/ACARSAircraft.h>
#include <Base/ACARSAirport.h>
#include <Base/ACARSFlight.h>
#include <Base/ACARSLatLon.h>
#include <Core/ACARSInitInfo.h>

#include <Core/ACARSUser.h>

#include <ostream>

class ACARSTimeSpan;

class ACARSDataBunk
{
public:
    ACARSDataBunk();

    void Update(ACARSFlightSimData* pUpdate);
	void Update(ACARSUser* pPilot);
	void Update(ACARSInitInfo* pInit);

	bool ACARSReady();

	//Getter

	//User
	QString getACARSUsername();

	//INIT
	ACARSAirport* getDepartureAirport();
	ACARSAirport* getArrivalAirport();
	ACARSAircraft* getAircraft();
	ACARSFlight* getFlight();
	QString getFlightNumber();

    //Position
    ACARSLatLon* getPositionLatLon();

    //Altitude
    int getAltitude(QString smode = "m");

    //Speed
    float getMachSpeed();
    float getIndicatedAirSpeed(QString smode = "kts");
    float getGroundSpeed(QString smode = "kts");

	//Orientation
	float getHeading();

    //Times
    QTime* getLastUpdateTime();
	void setLastUpdateTime();
	QTime* getCurrentTime(QString mode = "UTC");
	QString getCurrentTimezone();
	int getCurrentTimezoneI();
	QString getTimezone(int iSecs);

	//Infos
	float getDistToDest();
	ACARSTimeSpan* getTimeToDest();

private:

	int m_iIAS;
	int m_iGS;
	float m_fMach;

	int m_iFtAboveGround;

	ACARSLatLon* m_pPosition;

    ACARSFlightSimData* m_pCurrentFSData;
	ACARSUser* m_pCurrentUser;
	ACARSInitInfo* m_pCurrentInitInfo;

    QTime* m_pLastUpdate;
	QTime* m_pCurrentUTCTime;
	QTime* m_pCurrentLCLTime;

	bool FSDataOK, ACARSUserOK, INITInfoOK;
};

#endif // ACARSDATABUNK_H
