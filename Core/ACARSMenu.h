#ifndef ACARSMENUVIEW_H
#define ACARSMENUVIEW_H

#include <Core/ACARSInput.h>
#include <FlightSim/ACARSFlightSimData.h>

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QEvent>

class ACARSActionEvent;
class ACARSMenuPage;

class ACARSMenu : public QWidget
{
    Q_OBJECT

public:

    enum LINE {MAIN, HELPER};
    enum COLOR {AMBER, GREEN};

    explicit ACARSMenu(QWidget *parent);

    void setInputLine(QLineEdit *pInputLine);

    void setText(QString *Text, QString *Position, LINE label=ACARSMenu::MAIN);
    void setTextWithFormat(QString *Text, QString *Position, LINE label=ACARSMenu::MAIN, COLOR color=ACARSMenu::GREEN);

    void handleEvent(ACARSActionEvent *pIEvent);
    void updateFSData(ACARSFlightSimData* pNewData);

    void display();

private:
    QLabel *PlaceHolder;

    QLineEdit *m_pInputLine;
    ACARSFlightSimData* m_pFSData;

    ACARSMenuPage *m_pMenuPages[5];
    ACARSMenuPage *m_pCurrentMenu;

};

#endif // ACARSMENUVIEW_H
