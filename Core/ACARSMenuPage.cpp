#include "ACARSMenuPage.h"

#include <QDebug>

ACARSMenuPage::ACARSMenuPage(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(365,240);

    PlaceHolder = new QLabel(this);
    PlaceHolder->setGeometry(0,0,365,240);
    PlaceHolder->setText("");


    int xpos = 0;

    for(int i=0; i < 12;++i)
    {
        MainLabels[i] = new QLabel(this);

        QFont MainFont = MainLabels[i]->font();
        MainFont.setCapitalization(QFont::AllUppercase);
        MainFont.setFamily("Helvetica");
        MainFont.setPixelSize(16);

        if (i % 2 == 0)
        {
            xpos = 0;
            MainLabels[i]->setAlignment(Qt::AlignLeft);
        } else {
            xpos = 260;
            MainLabels[i]->setLayoutDirection(Qt::RightToLeft);
            MainLabels[i]->setAlignment(Qt::AlignAbsolute|Qt::AlignRight);
        }


        QPalette p = MainLabels[i]->palette();
        p.setColor(QPalette::WindowText, QColor(117,216,118));


        MainLabels[i]->setFont(MainFont);
        MainLabels[i]->setPalette(p);
        MainLabels[i]->setGeometry(xpos,15+(i/2)*40,100,16);
        MainLabels[i]->setText("ACARS v4.0");
    }



    for(int i=0; i < 12;++i)
    {
        SecondLabels[i] = new QLabel(this);

        QFont MainFont = SecondLabels[i]->font();
        MainFont.setCapitalization(QFont::AllUppercase);
        MainFont.setFamily("Helvetica");
        MainFont.setPixelSize(12);

        if (i % 2)
        {
            xpos = 0;
            SecondLabels[i]->setAlignment(Qt::AlignLeft);
        } else {
            xpos = 260;
            SecondLabels[i]->setLayoutDirection(Qt::RightToLeft);
            SecondLabels[i]->setAlignment(Qt::AlignAbsolute|Qt::AlignRight);
        }


        QPalette p = SecondLabels[i]->palette();
        p.setColor(QPalette::WindowText, QColor(117,216,118));


        SecondLabels[i]->setFont(MainFont);
        SecondLabels[i]->setPalette(p);
        SecondLabels[i]->setGeometry(xpos,(i/2)*40,100,15);
        SecondLabels[i]->setText("ACARS v4.0");
    }

}

ACARSMenuPage::ACARSMenuPage(QWidget *parent, int thispage, int pagecount)
    : ACARSMenuPage(parent)
{
    m_iPageCount = pagecount;
    m_iPageNum = thispage;

}

void ACARSMenuPage::setText(QString *Text, QString *Position, ACARSMenu::LINE label)
{

    int i = 0;
    if (Position->at(0) == 'L')
    {
        i = (Position->right(1).toInt()-1)*2;
    } else {

        i = (Position->right(1).toInt()-1)*2+1;
    }

    switch (label)
    {
    case ACARSMenu::MAIN:
        {
            MainLabels[i]->setText(*Text);
        } break;

    case ACARSMenu::HELPER:
        {
            SecondLabels[i]->setText(*Text);
        } break;

    default:
        break;
    }

}

void ACARSMenuPage::setTextWithFormat(QString *Text, QString *Position, ACARSMenu::LINE label, ACARSMenu::COLOR color)
{

    int i = 0;
    if (Position->at(0) == 'L')
    {
        i = (Position->left(1).toInt()-1)*2;
    } else {

        i = (Position->left(1).toInt()-1)*2+1;
    }

    QLabel *TextLabel;

    switch (label)
    {
    case ACARSMenu::MAIN:
        {
            TextLabel = MainLabels[i];
        } break;

    case ACARSMenu::HELPER:
        {
            TextLabel = SecondLabels[i];
        } break;

    default:
        break;
    }


    QPalette p = TextLabel->palette();

    if (color == ACARSMenu::AMBER)
    {
        p.setColor(QPalette::WindowText, QColor(216,117,118));
    } else {
        p.setColor(QPalette::WindowText, QColor(117,216,118));
    }

    TextLabel->setPalette(p);

    this->setText(Text,Position,label);

}
