#include "ACARSMenuView.h"

#include <QPalette>
#include <QFont>
#include <QSize>

ACARSMenuView::ACARSMenuView(QWidget *parent)
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

void ACARSMenuView::setInputLine(QLineEdit *pInputLine)
{
    m_pInputLine = pInputLine;
}

void ACARSMenuView::setText(QString *Text, QString *Position, ACARSMenuView::LINE label)
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
    case ACARSMenuView::MAIN:
        {
            MainLabels[i]->setText(*Text);
        } break;

    case ACARSMenuView::HELPER:
        {
            SecondLabels[i]->setText(*Text);
        } break;

    default:
        break;
    }

}

void ACARSMenuView::setTextWithFormat(QString *Text, QString *Position, LINE label, COLOR color)
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
    case ACARSMenuView::MAIN:
        {
            TextLabel = MainLabels[i];
        } break;

    case ACARSMenuView::HELPER:
        {
            TextLabel = SecondLabels[i];
        } break;

    default:
        break;
    }


    QPalette p = TextLabel->palette();

    if (color == ACARSMenuView::AMBER)
    {
        p.setColor(QPalette::WindowText, QColor(216,117,118));
    } else {
        p.setColor(QPalette::WindowText, QColor(117,216,118));
    }

    TextLabel->setPalette(p);

    this->setText(Text,Position,label);

}

void ACARSMenuView::handleEvent(ACARSInputEvent *pIEvent)
{
    switch (pIEvent->getEventType())
    {
    case ACARSInputEvent::LSK:
{
        QString *InText = new QString(m_pInputLine->text());
        this->setText(InText,pIEvent->getInputValue(), ACARSMenuView::MAIN);
        m_pInputLine->clear();
}
        break;
    default:
        break;
    }
}

void ACARSMenuView::updateFSData(ACARSFlightSimData *pNewData)
{
    m_pFSData = pNewData;
}
