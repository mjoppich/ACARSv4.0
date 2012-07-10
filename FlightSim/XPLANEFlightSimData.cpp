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

		qDebug() << datagram.data();


		}
}

void XPLANEFlightSimData::parseInputData(QByteArray InputData)
{

		//altitude, latitude, longitude,vertspeed, groundspeed, indicatedairspeed, machspeed, payloadweight, totalweight, fueltotalweight, counter
		QList<QByteArray> newdata = InputData.split(';');

		mfGroundSpeed = newdata.at(4).toFloat();
		mfIAS = newdata.at(5).toFloat();
		mfMach = newdata.at(6).toFloat();

		mfLatitude = newdata.at(1).toFloat();
		mfLongitude = newdata.at(2).toFloat();

		mfAltitude = newdata.at(0).toFloat();

		((ACARSSystem*)this->parent())->eventFilter((QObject*)this, ((QEvent*) new ACARSActionEvent(ACARSEVENT::FSUPDATEEVENT, "")));

}