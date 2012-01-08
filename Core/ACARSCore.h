#ifndef ACARSCORE_H
#define ACARSCORE_H

#include <QObject>
#include <Core/ACARSMainWindow.h>


class ACARSCore : public QObject
{
    Q_OBJECT
public:
    explicit ACARSCore(QObject *parent = 0);

signals:

public slots:

protected:
    ACARSMainWindow *m_pMainWindow;

};

#endif // ACARSCORE_H
