#ifndef ACARSLATLON_H
#define ACARSLATLON_H
#include <qmath.h> 
#include <QString>

class ACARSLatLon
{
public:
    ACARSLatLon(double dLat, double dLon)
	{
		m_dLatitude = dLat;
		m_dLongitude = dLon;
	}

    float DistanceTo(ACARSLatLon* to, QString mode = "nm")
	{
		return DistanceFromTo(this, to, mode);
	}

    static float DistanceFromTo(ACARSLatLon* from, ACARSLatLon* to, QString mode = "nm")
	{
		double R = 6371; // km
		double d = qAcos(qSin(from->getLat())*qSin(to->getLat()) + 
                  qCos(from->getLat())*qCos(to->getLat()) *
				  qCos(to->getLon()-from->getLon())) * R;

		if (mode == "km")
		{
			return (float)d;
		} else {
			return (float)(d*0.5399568034557235);
		}
	}

	static float BearingFromTo(ACARSLatLon* from, ACARSLatLon* to)
	{
		double dLon = to->getLon()-from->getLon();

		double y = qSin(dLon) * qCos(to->getLat());
		double x = qCos(from->getLat())*qSin(to->getLat()) - qSin(from->getLat())*qCos(to->getLat())*cos(dLon);
		double brng = qAtan2(x,y) * 180.0f / M_PI;

		return (float)brng;
	}

    float getLat()
	{
		return m_dLatitude;
	}

    float getLon()
	{
		return m_dLongitude;
	}

    void setLat(double dLat)
	{
		m_dLatitude = dLat;
	}

    void setLon(double dLon)
	{
		m_dLongitude = dLon;
	}

private:
    double m_dLatitude;
    double m_dLongitude;

};

#endif //ACARSLATLON_H