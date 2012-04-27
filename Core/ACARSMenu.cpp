#include "ACARSMenu.h"
#include <Core/ACARSEvents.h>
#include <Core/ACARSMenuPage.h>

#include <QPalette>
#include <QFont>
#include <QSize>

ACARSMenu::ACARSMenu(QWidget *parent, int pagecount)
    : QWidget(parent)
{

    m_iPageCount = pagecount;

    this->setFixedSize(365,260);

}

void ACARSMenu::setInputLine(QLineEdit *pInputLine)
{
    m_pInputLine = pInputLine;

    int i;

    for (i=0; i<m_iPageCount; ++i)
        m_pMenuPages[i]->setInputLine(pInputLine);
}

void ACARSMenu::setText(QString *Text, QString *Position, ACARSMenu::LINE label)
{

    m_pCurrentMenu->setText(Text,Position,label);

}

void ACARSMenu::setTextWithFormat(QString *Text, QString *Position, ACARSMenu::LINE label, ACARSMenu::COLOR color)
{

    m_pCurrentMenu->setTextWithFormat(Text, Position, label, color);

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
