#ifndef MENULOGIN_H
#define MENULOGIN_H

#include <Core/ACARSMenu.h>

#include <Menus/LOGIN/MENUPAGELogin.h>

class MENULogin : public ACARSMenu
{
public:

    MENULogin(QWidget *parent)
        : ACARSMenu(parent,1)
    {
    }

    virtual bool init();

    ~MENULogin() {}

};

#endif // MENULOGIN_H
