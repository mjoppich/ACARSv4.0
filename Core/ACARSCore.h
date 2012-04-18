#ifndef ACARSCORE_H
#define ACARSCORE_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <Core/ACARSMainWindow.h>


class ACARSCore : public QObject
{
    Q_OBJECT
public:
    explicit ACARSCore(QObject *parent = 0);
    bool ACARSInit();
    bool ACARSStart();

signals:

public slots:
    bool MainLoop();

protected:
    ACARSMainWindow *m_pMainWindow;

private:
    QTimer* m_pTimer;
    QTime m_LastTime;

};

#endif // ACARSCORE_H
