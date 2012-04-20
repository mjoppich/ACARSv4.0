#ifndef ACARSDATABUNK_H
#define ACARSDATABUNK_H

#include <QPoint>
#include <QDateTime>

class ACARSFlightSimData;
class QLineEdit;

class ACARSLatLon
{
public:
    ACARSLatLon(float fLat, float fLon);

    float DistanceToNM(ACARSLatLon* to);
    float DistanceToKM(ACARSLatLon* to);

    static float DistanceFromTo(ACARSLatLon* from, ACARSLatLon* to);

    float getLat();
    float getLon();

    void setLat(float fLat);
    void setLon(float fLon);

private:
    float m_fLatitude;
    float m_fLongitude;

};

class ACARSDataBunk
{
public:
    ACARSDataBunk();

    void Update(ACARSFlightSimData* pUpdate);

    //Position
    ACARSLatLon* getPositionLatLon();

    //Altitude
    int getAltimeterAltitude();
    int getRadioAltitude();
    int getFtAboveGround();

    //Speed
    float getMachSpeed();
    int getIndicatedAirSpeed();
    int getGroundSpeed();

    //Times
    QDateTime* getCurrentTime();
    QTime* getLastUpdateTime();


private:

    ACARSFlightSimData* m_pCurrentFSData;
    QTime* LastUpdate;
};

#endif // ACARSDATABUNK_H
