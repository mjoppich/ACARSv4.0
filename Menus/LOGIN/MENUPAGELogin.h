#ifndef MENUPAGELOGIN_H
#define MENUPAGELOGIN_H

#include <Core/ACARSMenuPage.h>
#include <Core/ACARSSystem.h>

class QNetworkReply;
class QNetworkAccessManager;

class MENUPAGELogin : public ACARSMenuPage
{
	Q_OBJECT

public:
    MENUPAGELogin(QWidget *parent, int iCount, int iNum)
        :ACARSMenuPage(parent,iCount,iNum)
    {

        m_bIsLoggedIn = false;

    }

    virtual bool handleEvent(ACARSSystem *pACARSSys, ACARSActionEvent *pIEvent);
    virtual bool init();

	~MENUPAGELogin() {}

public slots:
	bool passwordCheckDone(QNetworkReply* reply);


private:

    bool evaluateLogin(QString username, QString password);
    QString getUserSession(QString username, QString password);
    bool m_bIsLoggedIn;

	QNetworkAccessManager *m_pNetworkManager;

};

#endif // MENUPAGELOGIN_H
