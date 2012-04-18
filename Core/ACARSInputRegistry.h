#ifndef ACARSINPUTREGISTRY_H
#define ACARSINPUTREGISTRY_H

#include <QObject>
#include <QVector>
#include <QMouseEvent>
#include <QDebug>

class ACARSInput;
class ACARSInputEvent;
class ACARSMainWindow;

class ACARSInputRegistry : public QObject
{
    Q_OBJECT
public:
    explicit ACARSInputRegistry(ACARSMainWindow *pParent);

    void RegisterInput(ACARSInput *pInput);
    void DeRegisterInput(ACARSInput *pInput);

    ACARSInputEvent* ClickEvent(QMouseEvent *pEvent);

signals:

public slots:

protected:
    ACARSMainWindow *m_pParentWindow;

    QVector<ACARSInput*> m_vInputs;

};

#endif // ACARSINPUTREGISTRY_H
