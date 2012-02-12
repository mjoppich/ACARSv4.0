#ifndef ACARSINPUTREGISTRY_H
#define ACARSINPUTREGISTRY_H

#include <QObject>
#include <QVector>

class ACARSInput;
class ACARSMainWindow;

class ACARSInputRegistry : public QObject
{
    Q_OBJECT
public:
    explicit ACARSInputRegistry(ACARSMainWindow *pParent);

    void RegisterInput(ACARSInput *pInput);
    void DeRegisterInput(ACARSInput *pInput);

signals:

public slots:

protected:
    ACARSMainWindow *m_pParentWindow;

    QVector<ACARSInput> *m_pInputs;

};

#endif // ACARSINPUTREGISTRY_H
