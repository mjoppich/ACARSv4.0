#include "ACARSInput.h"

ACARSInputEvent::ACARSInputEvent(ACARSInputEvent::ETYPE type, QString input)
    : mInput(input)
{
    mEventType = type;
}

QString *ACARSInputEvent::getInputValue()
{
    return &mInput;
}

bool ACARSInputEvent::isEventType(ACARSInputEvent::ETYPE compareto)
{
    if (compareto == mEventType)
        return true;

    return false;
}

ACARSInputEvent::ETYPE ACARSInputEvent::getEventType()
{
    return mEventType;
}

//----------------------------------------------------------

ACARSInputEvent* ACARSVKeyBoardInput::EvaluateClick(QMouseEvent *pEvent)
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
            return new ACARSInputEvent(ACARSInputEvent::VKEY,"A");
        }

        if ((ClickX < 295) && (ClickX > 255))
        {
            return new ACARSInputEvent(ACARSInputEvent::VKEY,"B");
        }

        if ((ClickX < 345) && (ClickX > 305))
        {
            return new ACARSInputEvent(ACARSInputEvent::VKEY,"C");
        }

        if ((ClickX < 395) && (ClickX > 355))
        {
            return new ACARSInputEvent(ACARSInputEvent::VKEY,"D");
        }

        if ((ClickX < 445) && (ClickX > 405))
        {
            return new ACARSInputEvent(ACARSInputEvent::VKEY,"E");
        }


        //undef
        return NULL;

    }


    return NULL;
}

//----------------------------------------------------------

ACARSInputEvent* ACARSSpecialKeyKeyBInput::EvaluateClick(QMouseEvent *pEvent)
{
    int ClickX, ClickY;
    ClickX = pEvent->x();
    ClickY = pEvent->y();

    //Evaluate first row_ A B C D E
    if ((ClickY < 765) && (ClickY > 730))
    {

        if ((ClickX < 345) && (ClickX > 305))
        {
            return new ACARSInputEvent(ACARSInputEvent::MENU, "D");
        }

        if ((ClickX < 445) && (ClickX > 405))
        {
            return new ACARSInputEvent(ACARSInputEvent::MENU, "C");
        }

    }


    return NULL;
}
//----------------------------------------------------------

ACARSInputEvent* ACARSLSKinput::EvaluateClick(QMouseEvent *pEvent)
{
    int ClickX, ClickY;
    ClickX = pEvent->x();
    ClickY = pEvent->y();

    //Evaluate first row_ A B C D E
    if ((ClickY < 120) && (ClickY > 90))
    {

        if ((ClickX < 35) && (ClickX > 0))
        {
            return new ACARSInputEvent(ACARSInputEvent::LSK, "L1");
        }

        if ((ClickX < 500) && (ClickX > 465))
        {
            return new ACARSInputEvent(ACARSInputEvent::LSK, "R1");
        }

    }

    if ((ClickY < 160) && (ClickY > 130))
    {

        if ((ClickX < 35) && (ClickX > 0))
        {
            return new ACARSInputEvent(ACARSInputEvent::LSK, "L2");
        }

        if ((ClickX < 500) && (ClickX > 465))
        {
            return new ACARSInputEvent(ACARSInputEvent::LSK, "R2");
        }

    }

    if ((ClickY < 200) && (ClickY > 170))
    {

        if ((ClickX < 35) && (ClickX > 0))
        {
            return new ACARSInputEvent(ACARSInputEvent::LSK, "L3");
        }

        if ((ClickX < 500) && (ClickX > 465))
        {
            return new ACARSInputEvent(ACARSInputEvent::LSK, "R3");
        }

    }

    if ((ClickY < 240) && (ClickY > 210))
    {

        if ((ClickX < 35) && (ClickX > 0))
        {
            return new ACARSInputEvent(ACARSInputEvent::LSK, "L4");
        }

        if ((ClickX < 500) && (ClickX > 465))
        {
            return new ACARSInputEvent(ACARSInputEvent::LSK, "R4");
        }

    }

    if ((ClickY < 280) && (ClickY > 250))
    {

        if ((ClickX < 35) && (ClickX > 0))
        {
            return new ACARSInputEvent(ACARSInputEvent::LSK, "L5");
        }

        if ((ClickX < 500) && (ClickX > 465))
        {
            return new ACARSInputEvent(ACARSInputEvent::LSK, "R5");
        }

    }

    if ((ClickY < 320) && (ClickY > 290))
    {

        if ((ClickX < 35) && (ClickX > 0))
        {
            return new ACARSInputEvent(ACARSInputEvent::LSK, "L6");
        }

        if ((ClickX < 500) && (ClickX > 465))
        {
            return new ACARSInputEvent(ACARSInputEvent::LSK, "R6");
        }

    }


    return NULL;
}


