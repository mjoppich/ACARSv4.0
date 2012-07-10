#ifndef ACARSDATABUNK_H
#define ACARSDATABUNK_H

#include <QPoint>
#include <QDateTime>

class ACARSFlightSimData;
class QLineEdit;

#include <Base/ACARSAircraft.h>
#include <Base/ACARSAirport.h>
#include <Base/ACARSLatLon.h>
#include <Core/ACARSInitInfo.h>

#include <Core/ACARSUser.h>

class ACARSDataBunk
{
public:
    ACARSDataBunk();

    void Update(ACARSFlightSimData* pUpdate);
	void Update(ACARSUser* pPilot);
	void Update(ACARSInitInfo* pInit);

	//Getter

	//User
	QString getACARSUsername();

	//INIT
	ACARSAirport* getDepartureAirport();
	ACARSAirport* getArrivalAirport();

	ACARSAircraft* getAircraft();

    //Position
    ACARSLatLon* getPositionLatLon();
	void setPositionLatLon(ACARSLatLon *newpos);

    //Altitude
    int getAltimeterAltitude();
    int getRadioAltitude();
    int getFtAboveGround();

    //Speed
    float getMachSpeed();
    int getIndicatedAirSpeed();
    int getGroundSpeed();

    //Times
    QTime* getLastUpdateTime();
	void setLastUpdateTime();


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
};

#endif // ACARSDATABUNK_H
