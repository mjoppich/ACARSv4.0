#ifndef MENUPAGEINIT2_H
#define MENUPAGEINIT2_H

#include <Core/ACARSMenuPage.h>
#include <Core/ACARSSystem.h>

class MENUPAGEInit2 : public ACARSMenuPage
{
	Q_OBJECT
public:
    MENUPAGEInit2(QWidget *parent, int iCount, int iNum)
        :ACARSMenuPage(parent,iCount,iNum)
    {

        m_bIsLoggedIn = false;

    }

    virtual bool handleEvent(ACARSSystem *pACARSSys, ACARSActionEvent *pIEvent);
    virtual bool init();

    ~MENUPAGEInit2() {}

private:
    bool evaluateLogin(QString username, QString password);
    QString getUserSession(QString username, QString password);

    bool m_bIsLoggedIn;

};

#endif // MENUPAGEINIT2_H
