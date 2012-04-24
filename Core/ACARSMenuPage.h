#ifndef ACARSMENUPAGE_H
#define ACARSMENUPAGE_H

#include <Core/ACARSMenu.h>

#include <QWidget>
#include <QLabel>

class ACARSMenuPage : public QWidget
{
    Q_OBJECT

public:

    explicit ACARSMenuPage(QWidget *parent);
    ACARSMenuPage(QWidget *parent, int thispage, int pagecount);

    void setText(QString *Text, QString *Position, ACARSMenu::LINE label=ACARSMenu::MAIN);
    void setTextWithFormat(QString *Text, QString *Position, ACARSMenu::LINE label=ACARSMenu::MAIN, ACARSMenu::COLOR color=ACARSMenu::GREEN);

private:
    QLabel *PlaceHolder;
    QLabel* MainLabels[12];
    QLabel* SecondLabels[12];

    int m_iPageCount;
    int m_iPageNum;

};


#endif // ACARSMENUPAGE_H
