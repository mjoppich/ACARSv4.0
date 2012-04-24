#include "ACARSEvents.h"

ACARSActionEvent::ACARSActionEvent(ACARSEVENT::TYPE type, QString input)
    : mInput(input)
{
    mEventType = type;
}

QString *ACARSActionEvent::getInputValue()
{
    return &mInput;
}

bool ACARSActionEvent::isEventType(ACARSEVENT::TYPE compareto)
{
    if (compareto == mEventType)
        return true;

    return false;
}

ACARSEVENT::TYPE ACARSActionEvent::getEventType()
{
    return mEventType;
}
