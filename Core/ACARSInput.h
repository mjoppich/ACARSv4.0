#ifndef ACARSINPUT_H
#define ACARSINPUT_H

#include <QObject>
#include <QMouseEvent>
#include <QDebug>

class ACARSInputEvent
{
public:

    enum ETYPE {KEYBOARD, MOUSE, MENU};

    ACARSInputEvent(ETYPE type, char input);

    ETYPE getEventType();

    bool isEventType(ETYPE compareto);
    const char* getInputValue();

private:
    ETYPE mEventType;
    const char mInput;
};

class ACARSInput
{

public:
    ACARSInput();
    ACARSInputEvent* EvaluateClick(QMouseEvent *pEvent);

signals:

public slots:

};

#endif // ACARSINPUT_H
