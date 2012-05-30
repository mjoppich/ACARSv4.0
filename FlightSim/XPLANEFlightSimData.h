#ifndef XPLANEFLIGHTSIMDATA_H
#define XPLANEFLIGHTSIMDATA_H

#include <QObject.h>

class QUdpSocket;

class XPLANEFlightSimData : public QObject
{

	Q_OBJECT

public:
	explicit XPLANEFlightSimData(QObject *pParent);

public slots:
		void readInputData();

private:
	QUdpSocket* m_pSocket;

};

#endif // XPLANEFLIGHTSIMDATA_H
