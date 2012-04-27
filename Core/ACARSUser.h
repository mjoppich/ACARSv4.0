#ifndef ACARSUSER_H
#define ACARSUSER_H

#include <QString>
#include <QObject>

class ACARSUser : public QObject
{
public:
    ACARSUser(QString pUsername, QString pUserSession);

    QString getUsername();

    ~ACARSUser() {}

private:
    QString mUsername;
    QString mUserSession;
};

#endif // ACARSUSER_H
