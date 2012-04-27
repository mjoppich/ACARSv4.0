#include "ACARSInput.h"
#include <Core/ACARSEvents.h>


//----------------------------------------------------------

ACARSActionEvent* ACARSMenuKeyInput::EvaluateClick(QMouseEvent *pEvent)
{
    int ClickX, ClickY;
    ClickX = pEvent->x();
    ClickY = pEvent->y();

    if ((ClickY < 420) && (ClickY > 375))
    {

        if ((ClickX < 110) && (ClickX > 50))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "INIT");
        }

        if ((ClickX < 175) && (ClickX > 115))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "RTE");
        }

        if ((ClickX < 240) && (ClickX > 180))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "DEPARR");
        }

        if ((ClickX < 305) && (ClickX > 245))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "ATC");
        }

        if ((ClickX < 370) && (ClickX > 310))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "VNAV");
        }

    }

    if ((ClickY < 470) && (ClickY > 425))
    {


        if ((ClickX < 110) && (ClickX > 50))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "FIX");
        }

        if ((ClickX < 175) && (ClickX > 115))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "LEGS");
        }

        if ((ClickX < 240) && (ClickX > 180))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "HOLD");
        }

        if ((ClickX < 305) && (ClickX > 245))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "FMCCOMM");
        }

        if ((ClickX < 370) && (ClickX > 310))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "PROG");
        }


        if ((ClickX < 440) && (ClickX > 390))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "EXEC");
        }

    }

    if ((ClickY < 515) && (ClickY > 475))
    {

        if ((ClickX < 110) && (ClickX > 50))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "MENU");
        }

        if ((ClickX < 175) && (ClickX > 115))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "NAVRAD");
        }

    }

    if ((ClickY < 565) && (ClickY > 525))
    {

        if ((ClickX < 110) && (ClickX > 50))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "PREV");
        }

        if ((ClickX < 175) && (ClickX > 115))
        {
            return new ACARSActionEvent(ACARSEVENT::MENU, "NEXT");
        }

    }


    return NULL;
}

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

    if ((ClickY < 470) && (ClickY > 430))
    {

        if ((ClickX < 440) && (ClickX > 390))
        {
            return new ACARSActionEvent(ACARSEVENT::ILINE, "E");
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


