#include "ACARSInput.h"
#include <Core/ACARSEvents.h>



//----------------------------------------------------------

ACARSActionEvent* ACARSVKeyBoardInput::EvaluateClick(QMouseEvent *pEvent)
{
    qDebug() << "(" << pEvent->x() << "," << pEvent->y() << ")" << endl;

    int ClickX, ClickY;
    ClickX = pEvent->x();
    ClickY = pEvent->y();

    //Evaluate first row_ A B C D E
    if ((ClickY < 520) && (ClickY > 480))
    {

        if ((ClickX < 245) && (ClickX > 205))
        {
            return new ACARSActionEvent(ACARSEVENT::VKEY,"A");
        }

        if ((ClickX < 295) && (ClickX > 255))
        {
            return new ACARSActionEvent(ACARSEVENT::VKEY,"B");
        }

        if ((ClickX < 345) && (ClickX > 305))
        {
            return new ACARSActionEvent(ACARSEVENT::VKEY,"C");
        }

        if ((ClickX < 395) && (ClickX > 355))
        {
            return new ACARSActionEvent(ACARSEVENT::VKEY,"D");
        }

        if ((ClickX < 445) && (ClickX > 405))
        {
            return new ACARSActionEvent(ACARSEVENT::VKEY,"E");
        }


        //undef
        return NULL;

    }


    return NULL;
}

//----------------------------------------------------------

ACARSActionEvent* ACARSSpecialKeyKeyBInput::EvaluateClick(QMouseEvent *pEvent)
{
    int ClickX, ClickY;
    ClickX = pEvent->x();
    ClickY = pEvent->y();

    //Evaluate first row_ A B C D E
    if ((ClickY < 765) && (ClickY > 730))
    {

        if ((ClickX < 345) && (ClickX > 305))
        {
            return new ACARSActionEvent(ACARSEVENT::ILINE, "D");
        }

        if ((ClickX < 445) && (ClickX > 405))
        {
            return new ACARSActionEvent(ACARSEVENT::ILINE, "C");
        }

    }


    return NULL;
}
//----------------------------------------------------------

ACARSActionEvent* ACARSLSKinput::EvaluateClick(QMouseEvent *pEvent)
{
    int ClickX, ClickY;
    ClickX = pEvent->x();
    ClickY = pEvent->y();

    //Evaluate first row_ A B C D E
    if ((ClickY < 120) && (ClickY > 90))
    {

        if ((ClickX < 35) && (ClickX > 0))
        {
            return new ACARSActionEvent(ACARSEVENT::LSK, "L1");
        }

        if ((ClickX < 500) && (ClickX > 465))
        {
            return new ACARSActionEvent(ACARSEVENT::LSK, "R1");
        }

    }

    if ((ClickY < 160) && (ClickY > 130))
    {

        if ((ClickX < 35) && (ClickX > 0))
        {
            return new ACARSActionEvent(ACARSEVENT::LSK, "L2");
        }

        if ((ClickX < 500) && (ClickX > 465))
        {
            return new ACARSActionEvent(ACARSEVENT::LSK, "R2");
        }

    }

    if ((ClickY < 200) && (ClickY > 170))
    {

        if ((ClickX < 35) && (ClickX > 0))
        {
            return new ACARSActionEvent(ACARSEVENT::LSK, "L3");
        }

        if ((ClickX < 500) && (ClickX > 465))
        {
            return new ACARSActionEvent(ACARSEVENT::LSK, "R3");
        }

    }

    if ((ClickY < 240) && (ClickY > 210))
    {

        if ((ClickX < 35) && (ClickX > 0))
        {
            return new ACARSActionEvent(ACARSEVENT::LSK, "L4");
        }

        if ((ClickX < 500) && (ClickX > 465))
        {
            return new ACARSActionEvent(ACARSEVENT::LSK, "R4");
        }

    }

    if ((ClickY < 280) && (ClickY > 250))
    {

        if ((ClickX < 35) && (ClickX > 0))
        {
            return new ACARSActionEvent(ACARSEVENT::LSK, "L5");
        }

        if ((ClickX < 500) && (ClickX > 465))
        {
            return new ACARSActionEvent(ACARSEVENT::LSK, "R5");
        }

    }

    if ((ClickY < 320) && (ClickY > 290))
    {

        if ((ClickX < 35) && (ClickX > 0))
        {
            return new ACARSActionEvent(ACARSEVENT::LSK, "L6");
        }

        if ((ClickX < 500) && (ClickX > 465))
        {
            return new ACARSActionEvent(ACARSEVENT::LSK, "R6");
        }

    }


    return NULL;
}


