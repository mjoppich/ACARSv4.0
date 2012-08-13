#ifndef FTGLIVEACARS_H
#define FTGLIVEACARS_H

#include <QString>

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

private:
	QString ts(float in) {return QString::number(in);}
	QString ts(double in) {return QString::number(in);}
	QString ts(double in, int prec) {return QString::number(in,'g',prec);}
	QString ts(int in) {return QString::number(in);}
};

#endif // FTGLIVEACARS_H

