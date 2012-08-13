#ifndef MENUPROG_H
#define MENUPROG_H

#include <Core/ACARSMenu.h>

#include <Menus/PROG/MENUPAGEProg.h>
#include <Menus/PROG/MENUPAGEProg2.h>

class MENUProg : public ACARSMenu
{
public:

    MENUProg(QWidget *parent)
        : ACARSMenu(parent,1)
    {
    }

    virtual bool init();

    ~MENUProg() {}

};

#endif // MENUPROG_H
