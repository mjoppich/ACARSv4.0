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

    m_pMenuPages = new QStackedWidget(this);
    m_pMenuPages->setFixedSize(365,280);

}

void ACARSMenu::setInputLine(QLineEdit *pInputLine)
{
    m_pInputLine = pInputLine;

    int i;

    for (i=0; i<m_pMenuPages->count(); ++i)
        ((ACARSMenuPage*)(m_pMenuPages->widget(i)))->setInputLine(pInputLine);
}

void ACARSMenu::setText(QString *Text, QString *Position, ACARSMenu::LINE label)
{

    ((ACARSMenuPage*)(m_pMenuPages->currentWidget()))->setText(Text,Position,label);

}

void ACARSMenu::setTextWithFormat(QString *Text, QString *Position, ACARSMenu::LINE label, ACARSMenu::COLOR color)
{

    ((ACARSMenuPage*)(m_pMenuPages->currentWidget()))->setTextWithFormat(Text, Position, label, color);

}



void ACARSMenu::updateFSData(ACARSFlightSimData *pNewData)
{
    m_pFSData = pNewData;
}
