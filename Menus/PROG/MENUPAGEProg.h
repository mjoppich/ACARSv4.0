#ifndef MENUPAGEPROG1_H
#define MENUPAGEPROG1_H

#include <Core/ACARSMenuPage.h>
#include <Core/ACARSSystem.h>

class MENUPAGEProg1 : public ACARSMenuPage
{
	Q_OBJECT

public:
    MENUPAGEProg1(QWidget *parent, int iCount, int iNum)
        :ACARSMenuPage(parent,iCount,iNum)
    {

    }

    virtual bool handleEvent(ACARSSystem *pACARSSys, ACARSActionEvent *pIEvent);
    virtual bool init();

    ~MENUPAGEProg1() {}


private:


};

#endif // MENUPAGEPROG1_H
