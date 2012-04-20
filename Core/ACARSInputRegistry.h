#ifndef ACARSINPUTREGISTRY_H
#define ACARSINPUTREGISTRY_H

#include <QObject>
#include <QVector>
#include <QMouseEvent>
#include <QDebug>

class ACARSInput;
class ACARSInputEvent;
class ACARSSystem;

class ACARSInputRegistry : public QObject
{
    Q_OBJECT
public:
    explicit ACARSInputRegistry(ACARSSystem *pParent);

    void RegisterInput(ACARSInput *pInput);
    void DeRegisterInput(ACARSInput *pInput);

    bool ClickEvent(QMouseEvent *pEvent, QVector<ACARSInputEvent *> *ResultVector);

signals:

public slots:

protected:
    ACARSSystem *m_pParentWindow;

    QVector<ACARSInput*> m_vInputs;

};

#endif // ACARSINPUTREGISTRY_H
