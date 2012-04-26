#include "MENUPAGELogin.h"

bool MENUPAGELogin::init()
{

    int i;

    for(i=0; i<12; ++i)
    {

        MainLabels[i]->setText("");
        SecondLabels[i]->setText("");

    }

    this->setText(new QString("Welcome to"),new QString("L2"),ACARSMenu::HELPER);

    MainLabels[2]->setText("ACARS 4.0");

    MainLabels[4]->setText("Please LOGIN");

    SecondLabels[6]->setText("Username");
    SecondLabels[7]->setText("password");

    SecondLabels[8]->setText("EXEC TO LOGIN");

    return true;

}
