#include "XPLANEFlightSimData.h"
#include <Core/ACARSSystem.h>
#include <Core/ACARSEvents.h>


#include <QUdpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QObject>
#include <QList>

XPLANEFlightSimData::XPLANEFlightSimData(QObject *pParent)
	:ACARSFlightSimData(pParent)
{

	m_pSocket = new QUdpSocket(this);
	qDebug() << m_pSocket->bind(QHostAddress::LocalHost, 49004) << endl;

	this->connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(readInputData()));

}

void XPLANEFlightSimData::readInputData()
{
	    while (m_pSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_pSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_pSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

		this->parseInputData(datagram);


		}
}

void XPLANEFlightSimData::parseInputData(QByteArray InputData)
{

	qDebug() << InputData.data();

		//altitude, latitude, longitude,vertspeed, groundspeed, indicatedairspeed, machspeed, payloadweight, totalweight, fueltotalweight, counter, heading
		QList<QByteArray> newdata = InputData.split(';');

		if (newdata.length() < 11)
			return;

		mfGroundSpeed = QString(newdata.at(4)).toFloat();
		mfIAS = QString(newdata.at(5)).toFloat();
		mfMach = QString(newdata.at(6)).toFloat();

		mdLatitude = QString(newdata.at(1)).toDouble();
		mdLongitude = QString(newdata.at(2)).toDouble();

		mfAltitude = QString(newdata.at(0)).toFloat();

		mfHeading = QString(newdata.at(11)).toFloat();

		qDebug()  << qSetRealNumberPrecision(10) << mfAltitude << mdLatitude << mdLongitude << mfGroundSpeed << mfIAS << mfMach << mfHeading;

		((ACARSSystem*)this->parent())->eventFilter((QObject*)this, ((QEvent*) new ACARSMenuViewEvent(ACARSEVENT::FSUPDATEEVENT)));

}