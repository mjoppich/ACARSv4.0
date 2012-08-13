#ifndef MENUPAGEINIT1_H
#define MENUPAGEINIT1_H

#include <Core/ACARSMenuPage.h>
#include <Core/ACARSSystem.h>

class MENUPAGEInit1 : public ACARSMenuPage
{
	Q_OBJECT

public:
    MENUPAGEInit1(QWidget *parent, int iCount, int iNum)
        :ACARSMenuPage(parent,iCount,iNum)
    {

        m_bIsLoggedIn = false;

    }

    virtual bool handleEvent(ACARSSystem *pACARSSys, ACARSActionEvent *pIEvent);
    virtual bool init();
	bool allFilled();

    ~MENUPAGEInit1() {}


private:
    bool evaluateLogin(QString username, QString password);
    QString getUserSession(QString username, QString password);

    bool m_bIsLoggedIn;

};

#endif // MENUPAGEINIT1_H
