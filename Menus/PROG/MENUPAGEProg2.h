#ifndef MENUPAGEPROG2_H
#define MENUPAGEPROG2_H

#include <Core/ACARSMenuPage.h>
#include <Core/ACARSSystem.h>

class MENUPAGEProg2 : public ACARSMenuPage
{
	Q_OBJECT
public:
    MENUPAGEProg2(QWidget *parent, int iCount, int iNum)
        :ACARSMenuPage(parent,iCount,iNum)
    {


    }

    virtual bool handleEvent(ACARSSystem *pACARSSys, ACARSActionEvent *pIEvent);
    virtual bool init();

    ~MENUPAGEProg2() {}

private:

	QString ts(float in) {return QString::number(in);}
	QString ts(double in) {return QString::number(in);}
	QString ts(double in, int prec) {return QString::number(in,'g',prec);}
	QString ts(int in) {return QString::number(in);}

};

#endif // MENUPAGEPROG2_H
