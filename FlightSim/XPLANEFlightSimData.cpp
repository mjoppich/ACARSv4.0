#include "XPLANEFlightSimData.h"

#include <QUdpSocket>
#include <QHostAddress>
#include <QByteArray>

XPLANEFlightSimData::XPLANEFlightSimData(QObject *pParent)
	:QObject(pParent)
{

	m_pSocket = new QUdpSocket(this);
	qDebug() << m_pSocket->bind(QHostAddress::LocalHost, 1234) << endl;

	connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(readInputData()));

}

void XPLANEFlightSimData::readInputData()
{
	     while (m_pSocket->hasPendingDatagrams()) {
         QByteArray datagram;
         datagram.resize(m_pSocket->pendingDatagramSize());
         QHostAddress sender;
         quint16 senderPort;

         m_pSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

     }
}