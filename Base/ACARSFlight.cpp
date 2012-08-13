#include "ACARSFlight.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QStringList>
#include <QDebug>

ACARSFlight::ACARSFlight(QString sFlightNumber, QTime* pDepTime, QTime* pArrTime)
{
	m_bValid = false;

	QFile file("./SystemFiles/airlines.xml");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "  Couldn't open the file." << endl;
		return;
    }
	
	QXmlStreamReader reader(&file);

	bool listed;
	listed = false;

	QString sCallsign;
	QString sICAO;
	QString sIATA;
	QString sName;

	qDebug() << sFlightNumber.left(2);

	while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
			if ((reader.name() == "airline") && (!reader.attributes().value("iata").toString().compare(sFlightNumber.left(2),Qt::CaseInsensitive)))
			{
				listed = true;
				sCallsign = reader.attributes().value("callsign").toString();
				sICAO = reader.attributes().value("icao").toString();
				sIATA = reader.attributes().value("iata").toString();
				sName = reader.attributes().value("name").toString();
				m_sFlightNum = sFlightNumber;
			} else {
			
				//qDebug() << reader.attributes().value("iata").toString();

			}
        }
    }

    if (reader.hasError()) {
        qDebug() << "  The XML file isn't well-formed: " << reader.errorString()
            << endl;
    }

	if (!listed)
	{
		qDebug() << "Invalid Flight Num" << sFlightNumber << endl;
	} else {

		m_bValid = true;

		m_sCallsign = sCallsign;
		m_sAirlineICAO = sICAO;
		m_sAirlineIATA = sIATA;
		m_sAirlineName = sName;

		m_pSchedDepTime = new QTime(0,0,0,0);
		m_pSchedArrTime = new QTime(0,0,0,0);

	}


}

bool ACARSFlight::isValid()
{
	return m_bValid;
}

ACARSFlight::~ACARSFlight(void)
{
}