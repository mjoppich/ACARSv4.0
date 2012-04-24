#ifndef ACARSINPUT_H
#define ACARSINPUT_H

#include <Core/ACARSEvents.h>

#include <QObject>
#include <QString>
#include <QMouseEvent>
#include <QDebug>

class ACARSInput : public QObject
{

public:
    ACARSInput()
    {
    }

    virtual ACARSActionEvent* EvaluateClick(QMouseEvent *pEvent) {return NULL;}
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
    ACARSActionEvent* EvaluateClick(QMouseEvent *pEvent);
    ~ACARSLSKinput() {}
};

class ACARSVKeyBoardInput : public ACARSInput
{
public:
    ACARSVKeyBoardInput() {}
    ACARSActionEvent* EvaluateClick(QMouseEvent *pEvent);
    ~ACARSVKeyBoardInput() {}
};

class ACARSSpecialKeyKeyBInput : public ACARSInput
{
public:
    ACARSSpecialKeyKeyBInput() {}
    ACARSActionEvent* EvaluateClick(QMouseEvent *pEvent);
    ~ACARSSpecialKeyKeyBInput() {}
};

#endif // ACARSINPUT_H
