#include "ACARSMenu.h"
#include <Core/ACARSEvents.h>
#include <Core/ACARSMenuPage.h>

#include <QPalette>
#include <QFont>
#include <QSize>

ACARSMenu::ACARSMenu(QWidget *parent)
    : QWidget(parent)
{

    this->setFixedSize(365,240);

    PlaceHolder = new QLabel(this);
    PlaceHolder->setGeometry(0,0,365,240);
    PlaceHolder->setText("blubb1");

    int i;

    for (i=0; i<1; ++i)
    {
        m_pMenuPages[i] = new ACARSMenuPage(parent,i,5);
        m_pMenuPages[i]->setStyleSheet("QWidget { background-color: black;}");
        m_pMenuPages[i]->move(65,85);
    }

    m_pCurrentMenu = m_pMenuPages[0];
    m_pCurrentMenu->setFocus();

}

void ACARSMenu::setInputLine(QLineEdit *pInputLine)
{
    m_pInputLine = pInputLine;
}

void ACARSMenu::setText(QString *Text, QString *Position, ACARSMenu::LINE label)
{

    m_pCurrentMenu->setText(Text,Position,label);

}

void ACARSMenu::setTextWithFormat(QString *Text, QString *Position, ACARSMenu::LINE label, ACARSMenu::COLOR color)
{

    m_pCurrentMenu->setTextWithFormat(Text, Position, label, color);

}

void ACARSMenu::handleEvent(ACARSActionEvent *pIEvent)
{
    switch (pIEvent->getEventType())
    {
    case ACARSEVENT::LSK:
        {
        QString *InText = new QString(m_pInputLine->text());
        m_pCurrentMenu->setText(InText,pIEvent->getInputValue(), ACARSMenu::MAIN);
        m_pInputLine->clear();
        }
        break;
    case ACARSEVENT::ILINE:
    {
        QString* SendString = new QString();
        SendString->append("Test");
        this->parent()->eventFilter((QObject*) SendString,new ACARSMenuViewEvent());
    }
        break;

    default:
        break;
    }

    m_pCurrentMenu->show();
}

void ACARSMenu::updateFSData(ACARSFlightSimData *pNewData)
{
    m_pFSData = pNewData;
}

void ACARSMenu::display()
{
    this->show();
    m_pCurrentMenu->show();
}
