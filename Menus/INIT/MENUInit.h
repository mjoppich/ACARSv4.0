#ifndef MENUINIT_H
#define MENUINIT_H

#include <Core/ACARSMenu.h>

#include <Menus/INIT/MENUPAGEInit1.h>
#include <Menus/INIT/MENUPAGEInit2.h>

class MENUInit : public ACARSMenu
{
public:

    MENUInit(QWidget *parent)
        : ACARSMenu(parent,1)
    {
    }

    virtual bool handleEvent(ACARSActionEvent *pIEvent);
    virtual bool init();

    ~MENUInit() {}

};

#endif // MENUINIT_H
