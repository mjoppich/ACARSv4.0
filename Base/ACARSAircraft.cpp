#include "ACARSAircraft.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QStringList>
#include <QDebug>

ACARSAircraft::ACARSAircraft(QString sAircraft, QString sReg)
{
	m_sReg = sReg;

	m_bValid = false;

	QFile file("./SystemFiles/aircrafts.xml");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "  Couldn't open the file." << endl;
    }
	
	QXmlStreamReader reader(&file);

	float fMinMach, fMaxMach, fOptMach;
	fMinMach = 0;
	fMaxMach = 0;
	fOptMach = 0;

	m_sFTG = "";

	while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
			if ((reader.name() == "aircraft") && (reader.attributes().value("ftg").toString() == sAircraft))
			{
				m_sFTG = reader.attributes().value("ftg").toString();
				m_sIATA = reader.attributes().value("iata").toString();
				m_sICAO = reader.attributes().value("icao").toString();
				m_sName = reader.attributes().value("name").toString();


				fMinMach = reader.attributes().value("minmach").toString().toFloat();
				fMaxMach = reader.attributes().value("maxmach").toString().toFloat();
				fOptMach = reader.attributes().value("optmach").toString().toInt();
			}
        }
    }

    if (reader.hasError()) {
        qDebug() << "  The XML file isn't well-formed: " << reader.errorString()
            << endl;
    }

	if (m_sFTG == "")
	{
		qDebug() << "Invalid Aircraft" << sAircraft << endl;
	} else {

		m_bValid = true;

	}


}

bool ACARSAircraft::isValid()
{
	return m_bValid;
}

ACARSAircraft::~ACARSAircraft(void)
{
}