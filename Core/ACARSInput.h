#ifndef ACARSINPUT_H
#define ACARSINPUT_H

#include <QObject>
#include <QString>
#include <QMouseEvent>
#include <QDebug>

class ACARSInputEvent
{
public:

    enum ETYPE {LSK, MOUSE, MENU, VKEY};

    ACARSInputEvent(ETYPE type, QString input);

    ETYPE getEventType();

    bool isEventType(ETYPE compareto);
    QString* getInputValue();

private:
    ETYPE mEventType;
    QString mInput;
};

class ACARSInput : public QObject
{

public:
    ACARSInput()
    {
    }

    virtual ACARSInputEvent* EvaluateClick(QMouseEvent *pEvent) {return NULL;}
    ~ACARSInput()
    {
    }

signals:

public slots:

};

class ACARSLSKinput : public ACARSInput
{
public:
    ACARSLSKinput() {}
    ACARSInputEvent* EvaluateClick(QMouseEvent *pEvent);
    ~ACARSLSKinput() {}
};

class ACARSVKeyBoardInput : public ACARSInput
{
public:
    ACARSVKeyBoardInput() {}
    ACARSInputEvent* EvaluateClick(QMouseEvent *pEvent);
    ~ACARSVKeyBoardInput() {}
};

class ACARSSpecialKeyKeyBInput : public ACARSInput
{
public:
    ACARSSpecialKeyKeyBInput() {}
    ACARSInputEvent* EvaluateClick(QMouseEvent *pEvent);
    ~ACARSSpecialKeyKeyBInput() {}
};

#endif // ACARSINPUT_H
