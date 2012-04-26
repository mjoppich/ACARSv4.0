#include "ACARSMenuPage.h"

#include <QDebug>

ACARSMenuPage::ACARSMenuPage(QWidget *parent, int iCount, int iNum)
    : QWidget(parent)
{
    this->setFixedSize(365,280);

    PlaceHolder = new QLabel(this);
    PlaceHolder->setGeometry(0,0,365,280);
    PlaceHolder->setText("");

    PageIdentifier = new QLabel(this);
    PageIdentifier->setGeometry(330,20,40,20);

    QString PIString;
    PIString.clear();
    PIString.append(QString::number(iCount));
    PIString.append(" / ");
    PIString.append(QString::number(iNum));

    PageIdentifier->setText(PIString);

    QFont PIFont = PageIdentifier->font();
    PIFont.setCapitalization(QFont::AllUppercase);
    PIFont.setFamily("Helvetica");
    PIFont.setPixelSize(16);

    QPalette pip = PageIdentifier->palette();
    pip.setColor(QPalette::WindowText, QColor(117,216,118));


    PageIdentifier->setFont(PIFont);
    PageIdentifier->setPalette(pip);

    m_iPageCount = iCount;
    m_iPageNum = iNum;


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
            xpos = 260-75;
            MainLabels[i]->setLayoutDirection(Qt::RightToLeft);
            MainLabels[i]->setAlignment(Qt::AlignAbsolute|Qt::AlignRight);
        }


        QPalette p = MainLabels[i]->palette();
        p.setColor(QPalette::WindowText, QColor(117,216,118));


        MainLabels[i]->setFont(MainFont);
        MainLabels[i]->setPalette(p);
        MainLabels[i]->setGeometry(xpos,40+15+(i/2)*40,175,16);
        MainLabels[i]->setText("ACARS v4.0");
    }



    for(int i=0; i < 12;++i)
    {
        SecondLabels[i] = new QLabel(this);

        QFont MainFont = SecondLabels[i]->font();
        MainFont.setCapitalization(QFont::AllUppercase);
        MainFont.setFamily("Helvetica");
        MainFont.setPixelSize(12);

        if (i % 2 == 0)
        {
            xpos = 0;
            SecondLabels[i]->setAlignment(Qt::AlignLeft);
        } else {
            xpos = 260-75;
            SecondLabels[i]->setLayoutDirection(Qt::RightToLeft);
            SecondLabels[i]->setAlignment(Qt::AlignAbsolute|Qt::AlignRight);
        }


        QPalette p = SecondLabels[i]->palette();
        p.setColor(QPalette::WindowText, QColor(117,216,118));


        SecondLabels[i]->setFont(MainFont);
        SecondLabels[i]->setPalette(p);
        SecondLabels[i]->setGeometry(xpos,40+(i/2)*40,175,15);
        SecondLabels[i]->setText("ACARS v4.0");
    }

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
