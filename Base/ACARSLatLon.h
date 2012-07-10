#ifndef ACARSLATLON_H
#define ACARSLATLON_H

#include <QString>

class ACARSLatLon
{
public:
    ACARSLatLon(float fLat, float fLon)
	{
		m_fLatitude = fLat;
		m_fLongitude = fLon;
	}

    float DistanceToNM(ACARSLatLon* to)
	{
		return 0;
	}

    float DistanceToKM(ACARSLatLon* to)
	{
		return 0;
	}

    static float DistanceFromTo(ACARSLatLon* from, ACARSLatLon* to)
	{
		return 0;
	}

    float getLat()
	{
		return m_fLatitude;
	}

    float getLon()
	{
		return m_fLongitude;
	}

    void setLat(float fLat)
	{
		m_fLatitude = fLat;
	}

    void setLon(float fLon)
	{
		m_fLongitude = fLon;
	}

private:
    float m_fLatitude;
    float m_fLongitude;

};

#endif //ACARSLATLON_H