#ifndef ACARSEVENTS_H
#define ACARSEVENTS_H

#include <QString>
#include <QEvent>

namespace ACARSEVENT
{
    enum TYPE {LSK=0, MOUSE, MENU, VKEY, ILINE, //ACARSInputEvents
               LOGINEVENT=1000}; //CUSTOM EVENTS
}

class ACARSActionEvent
{
public:

    ACARSActionEvent(ACARSEVENT::TYPE type, QString input);

    ACARSEVENT::TYPE getEventType();

    bool isEventType(ACARSEVENT::TYPE compareto);
    QString* getInputValue();

private:
    ACARSEVENT::TYPE mEventType;
    QString mInput;
};

class ACARSMenuViewEvent : public QEvent
{
  public:
    ACARSMenuViewEvent()
        : QEvent((QEvent::Type) ACARSEVENT::LOGINEVENT)
    {}
    ~ACARSMenuViewEvent(){}
};

#endif // ACARSEVENTS_H
