#ifndef ACARSMENUVIEW_H
#define ACARSMENUVIEW_H

#include <Core/ACARSInput.h>

#include <FlightSim/ACARSFlightSimData.h>

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QEvent>
#include <QStackedWidget>

class ACARSActionEvent;
class ACARSMenuPage;
class ACARSSystem;

class ACARSMenu : public QWidget
{

public:

    enum LINE {MAIN, HELPER};
    enum COLOR {AMBER, GREEN};

    ACARSMenu(QWidget *parent, int pagecount);

    bool setInputLine(QLineEdit *pInputLine);
	bool setACARSSystem(ACARSSystem* pSys);

	bool setExtComponents(QLineEdit *pInputLine, ACARSSystem *pSys);

    void setText(QString *Text, QString *Position, LINE label=ACARSMenu::MAIN);
    void setTextWithFormat(QString *Text, QString *Position, LINE label=ACARSMenu::MAIN, COLOR color=ACARSMenu::GREEN);

    bool handleEvent(ACARSActionEvent *pIEvent);
    virtual bool init() = 0;


    void updateFSData(ACARSFlightSimData* pNewData);

	void nextPage();
	void prevPage();

    ~ACARSMenu() {}

protected:
    QLabel *PlaceHolder;

    int m_iPageCount;
	int m_iCurPage;

    QLineEdit *m_pInputLine;
    ACARSFlightSimData* m_pFSData;

    QStackedWidget *m_pMenuPages;
    ACARSMenuPage *m_pCurrentMenu;

	ACARSSystem* m_pSystem;

};

#endif // ACARSMENUVIEW_H
