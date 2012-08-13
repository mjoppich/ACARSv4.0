#include "ACARSTimeSpan.h"

#include <QString>

ACARSTimeSpan::ACARSTimeSpan(int secs)
{
	m_iTimeSpan = secs;
}

QString ACARSTimeSpan::toString() {
	
	int iHours = floor((float)m_iTimeSpan/float(3600));
	int iMins = floor((float)(m_iTimeSpan-iHours*3600)/float(60));

	return QString::number(iHours).rightJustified(2,'0')+QString("h") + QString::number(iMins).rightJustified(2,'0')+QString("m");

}

int ACARSTimeSpan::getSeconds() {return m_iTimeSpan;}

ACARSTimeSpan ACARSTimeSpan::operator+( ACARSTimeSpan& lh) {return ACARSTimeSpan(m_iTimeSpan+lh.getSeconds());}