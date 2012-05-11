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

class ACARSMenu : public QWidget
{

public:

    enum LINE {MAIN, HELPER};
    enum COLOR {AMBER, GREEN};

    ACARSMenu(QWidget *parent, int pagecount);

    void setInputLine(QLineEdit *pInputLine);

    void setText(QString *Text, QString *Position, LINE label=ACARSMenu::MAIN);
    void setTextWithFormat(QString *Text, QString *Position, LINE label=ACARSMenu::MAIN, COLOR color=ACARSMenu::GREEN);

    virtual bool handleEvent(ACARSActionEvent *pIEvent) = 0;
    virtual bool init() = 0;


    void updateFSData(ACARSFlightSimData* pNewData);

    ~ACARSMenu() {}

protected:
    QLabel *PlaceHolder;

    int m_iPageCount;

    QLineEdit *m_pInputLine;
    ACARSFlightSimData* m_pFSData;

    QStackedWidget *m_pMenuPages;
    ACARSMenuPage *m_pCurrentMenu;

};

#endif // ACARSMENUVIEW_H
