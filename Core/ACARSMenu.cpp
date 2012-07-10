#include "ACARSMenu.h"
#include <Core/ACARSEvents.h>
#include <Core/ACARSMenuPage.h>
#include <Core/ACARSDataBunk.h>

#include <QPalette>
#include <QFont>
#include <QSize>
#include <QDebug>

ACARSMenu::ACARSMenu(QWidget *parent, int pagecount)
    : QWidget(parent)
{

    m_iPageCount = pagecount;

    m_pMenuPages = new QStackedWidget(this);
    m_pMenuPages->setFixedSize(365,280);

}

bool ACARSMenu::setInputLine(QLineEdit *pInputLine)
{
    m_pInputLine = pInputLine;

    int i;

    for (i=0; i<m_pMenuPages->count(); ++i)
        ((ACARSMenuPage*)(m_pMenuPages->widget(i)))->setInputLine(pInputLine);

	return true;
}

bool ACARSMenu::setACARSSystem(ACARSSystem* pSys)
{
	if (pSys != 0)
	{
		m_pSystem = pSys;
		return true;
	}

	return false;
}

bool ACARSMenu::setExtComponents(QLineEdit *pInputLine, ACARSSystem *pSys)
{
	this->setInputLine(pInputLine);

	return this->setACARSSystem(pSys);
}

void ACARSMenu::setText(QString *Text, QString *Position, ACARSMenu::LINE label)
{

    ((ACARSMenuPage*)(m_pMenuPages->currentWidget()))->setText(Text,Position,label);

}

void ACARSMenu::setTextWithFormat(QString *Text, QString *Position, ACARSMenu::LINE label, ACARSMenu::COLOR color)
{

    ((ACARSMenuPage*)(m_pMenuPages->currentWidget()))->setTextWithFormat(Text, Position, label, color);

}

void ACARSMenu::updateFSData(ACARSDataBunk *pNewData)
{
    m_pFSData = pNewData;

	((ACARSMenuPage*)(m_pMenuPages->currentWidget()))->updateFSData(pNewData);
}

bool ACARSMenu::handleEvent(ACARSActionEvent *pIEvent)
{
	ACARSMenuPage* pCurrentPage = (ACARSMenuPage*)(m_pMenuPages->currentWidget());
	bool heresult = pCurrentPage->handleEvent(m_pSystem,pIEvent);
    return heresult;
}

void ACARSMenu::nextPage()
{
	int i = (++m_iCurPage) % m_iPageCount;

	qDebug() << i << m_iCurPage << m_iPageCount << endl;

	m_pMenuPages->setCurrentIndex(i);
	m_pMenuPages->activateWindow();

}

void ACARSMenu::prevPage()
{
	int i = (--m_iCurPage) % m_iPageCount;

	qDebug() << i << m_iCurPage << m_iPageCount << endl;

	m_pMenuPages->setCurrentIndex(i);
	m_pMenuPages->activateWindow();
}