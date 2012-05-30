#ifndef ACARSFLIGHTSIMDATA_H
#define ACARSFLIGHTSIMDATA_H

#include <QObject>

class ACARSFlightSimData : public QObject
{
	Q_OBJECT

public:
	explicit ACARSFlightSimData(QObject *pParent);
};

#endif // ACARSFLIGHTSIMDATA_H
