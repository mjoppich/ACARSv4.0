#ifndef MENUPAGELOGIN_H
#define MENUPAGELOGIN_H

#include <Core/ACARSMenuPage.h>

class MENUPAGELogin : public ACARSMenuPage
{
public:
    MENUPAGELogin(QWidget *parent, int iCount, int iNum)
        :ACARSMenuPage(parent,iCount,iNum)
    {

    }

    virtual void handleEvent(ACARSActionEvent *pIEvent) {};
    virtual bool init();

    ~MENUPAGELogin() {}

};

#endif // MENUPAGELOGIN_H
