#ifndef FTGLIVEACARS_H
#define FTGLIVEACARS_H


#include <LiveACARS/LiveACARS.h>

class FTGLiveACARS :public LiveACARS
{
	Q_OBJECT

public:
	 FTGLiveACARS(QObject *pParent);
	~FTGLiveACARS();

	bool Send(ACARSDataBunk* pData);

public slots:
	bool loadingFinished(QNetworkReply * reply);
};

#endif // FTGLIVEACARS_H

