#ifndef ACARSMENUVIEW_H
#define ACARSMENUVIEW_H

#include <Core/ACARSInput.h>
#include <FlightSim/ACARSFlightSimData.h>

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class ACARSMenuView : public QWidget
{
    Q_OBJECT

public:

    enum LINE {MAIN, HELPER};
    enum COLOR {AMBER, GREEN};

    explicit ACARSMenuView(QWidget *parent);

    void setInputLine(QLineEdit *pInputLine);

    void setText(QString *Text, QString *Position, LINE label=ACARSMenuView::MAIN);
    void setTextWithFormat(QString *Text, QString *Position, LINE label=ACARSMenuView::MAIN, COLOR color=ACARSMenuView::GREEN);

    void handleEvent(ACARSInputEvent *pIEvent);
    void updateFSData(ACARSFlightSimData* pNewData);

private:
    QLabel *PlaceHolder;

    QLabel* MainLabels[12];
    QLabel* SecondLabels[12];

    QLineEdit *m_pInputLine;
    ACARSFlightSimData* m_pFSData;

};

#endif // ACARSMENUVIEW_H
