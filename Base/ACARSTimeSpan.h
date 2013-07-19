#ifndef ACARSTIMESPAN_H
#define ACARSTIMESPAN_H

#include <string>
#include <QString>

class ACARSTimeSpan
{
public:
	ACARSTimeSpan(int secs);
	~ACARSTimeSpan() {};

	QString toString();

	int getSeconds();

	ACARSTimeSpan operator+( ACARSTimeSpan& lh);

private:
	int m_iTimeSpan;

};

#endif //ACARSTIMESPAN_H