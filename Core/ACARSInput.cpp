#include "ACARSInput.h"

ACARSInput::ACARSInput()
{
}

ACARSInputEvent* ACARSInput::EvaluateClick(QMouseEvent *pEvent)
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
            return new ACARSInputEvent(ACARSInputEvent::MOUSE,'A');
        }

        if ((ClickX < 295) && (ClickX > 255))
        {
            return new ACARSInputEvent(ACARSInputEvent::MOUSE,'B');
        }

        if ((ClickX < 345) && (ClickX > 305))
        {
            return new ACARSInputEvent(ACARSInputEvent::MOUSE,'C');
        }

        if ((ClickX < 395) && (ClickX > 355))
        {
            return new ACARSInputEvent(ACARSInputEvent::MOUSE,'D');
        }

        if ((ClickX < 445) && (ClickX > 405))
        {
            return new ACARSInputEvent(ACARSInputEvent::MOUSE,'E');
        }


        //undef
        return NULL;

    }


    return NULL;
}

ACARSInputEvent::ACARSInputEvent(ACARSInputEvent::ETYPE type, char input)
    : mInput(input)
{
    mEventType = type;
}

const char *ACARSInputEvent::getInputValue()
{
    return &mInput;
}

bool ACARSInputEvent::isEventType(ACARSInputEvent::ETYPE compareto)
{
    if (compareto == mEventType)
        return true;

    return false;
}
