#ifndef ACARSAIRCRAFT_H
#define ACARSAIRCRAFT_H

#include <QString>

class ACARSAircraft
{
public:
	ACARSAircraft(QString sAircraft, QString sReg);
	~ACARSAircraft(void);

	float getMaxMach();
	float getMinMach();

	QString getFTGCode() {return m_sFTG;}
	QString getIATACode() {return m_sIATA;}
	QString getICAOCode() {return m_sICAO;}

	QString getRegistration() {return m_sReg;}

	bool isValid();

private:
	QString m_sReg;
	QString m_sFTG;
	QString m_sIATA;
	QString m_sICAO;
	QString m_sName;

	float m_MinSpeed;
	float m_MaxSpeed;

	bool m_bValid;
};

#endif //ACARSAIRCRAFT_H