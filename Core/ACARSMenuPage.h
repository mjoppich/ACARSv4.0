#ifndef ACARSMENUPAGE_H
#define ACARSMENUPAGE_H

#include <Core/ACARSMenu.h>
#include <Core/ACARSSystem.h>

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class ACARSMenuPage : public QWidget
{

public:

    explicit ACARSMenuPage(QWidget *parent, int iCount, int iNum);

    void setText(QString *Text, QString *Position, ACARSMenu::LINE label=ACARSMenu::MAIN);
    void setText(QString Text, QString Position, ACARSMenu::LINE label=ACARSMenu::MAIN);
    void setTextWithFormat(QString *Text, QString *Position, ACARSMenu::LINE label=ACARSMenu::MAIN, ACARSMenu::COLOR color=ACARSMenu::GREEN);
    void setTextWithFormat(QString Text, QString Position, ACARSMenu::LINE label=ACARSMenu::MAIN, ACARSMenu::COLOR color=ACARSMenu::GREEN);

    QString getText(QString Position);
    QString* getText(QString* Position);

    void setInputLine(QLineEdit *pInputLine);

    virtual bool handleEvent(ACARSSystem *pACARSSys, ACARSActionEvent *pIEvent) = 0;
    virtual bool init() = 0;

    ~ACARSMenuPage(){}

protected:
    QLabel* PlaceHolder;
    QLabel* PageIdentifier;
    QLabel* MainLabels[12];
    QLabel* SecondLabels[12];

    QLineEdit* m_pInputLine;

    int m_iPageCount;
    int m_iPageNum;

};


#endif // ACARSMENUPAGE_H
