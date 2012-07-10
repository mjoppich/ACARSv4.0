
#ifndef LIVEACARS_H
#define LIVEACARS_H

#include <QObject>
#include <Core/ACARSDataBunk.h>

class QNetworkReply;
class QNetworkAccessManager;

class LiveACARS :public QObject
{

Q_OBJECT

public:
	LiveACARS(QObject *pParent);
	~LiveACARS() {};

	virtual bool Send(ACARSDataBunk* pData) = 0;

public slots:
	bool loadingFinished(QNetworkReply* reply) {return true;}

protected:
	QNetworkAccessManager *m_pNetworkManager;


};

#endif // LIVEACARS_H