#include "ACARSAirport.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QTime>

ACARSAirport::ACARSAirport(QString sAirport)
{

	m_bValid = false;
	m_iTimezone = 0;

	QFile file("./SystemFiles/airports.xml");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "  Couldn't open the file." << endl;
    }
	
	QXmlStreamReader reader(&file);

	float fLat, fLon;
	fLat = 0;
	fLon = 0;
	m_iAltitude = 0;

	while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {

			if ((reader.name() == "airport") && (!reader.attributes().value("icao").toString().compare(sAirport.toUpper(),Qt::CaseInsensitive)))
			{
				m_sICAO = reader.attributes().value("icao").toString();
				m_sIATA = reader.attributes().value("iata").toString();
				m_sName = reader.attributes().value("name").toString();

				fLat = reader.attributes().value("latitude").toString().toFloat();
				fLon = reader.attributes().value("longitude").toString().toFloat();
				m_iAltitude = reader.attributes().value("altitude").toString().toInt();
			}
        }
    }

    if (reader.hasError()) {
        qDebug() << "  The XML file isn't well-formed: " << reader.errorString()
            << endl;
    }

	if ((fLat == 0) && (fLon == 0) && (m_iAltitude == 0))
	{
		m_bValid = false;
	} else {

		m_pPosition = new ACARSLatLon(fLat,fLon);
		m_bValid = true;
		qDebug() << sAirport.toUpper() << "found!";

	}


}

bool ACARSAirport::isValid()
{
	return m_bValid;
}


ACARSAirport::~ACARSAirport(void)
{
}

QString ACARSAirport::getIATACode() {return m_sIATA;};
QString ACARSAirport::getICAOCode() {return m_sICAO;};

QTime* ACARSAirport::getCurrentTime(QTime* pUTCTime)
{
	QTime* pLCL = new QTime(0,0,0,0);
	pLCL->fromString(pUTCTime->toString());
	pLCL->addSecs(m_iTimezone);

	return pLCL;
}
