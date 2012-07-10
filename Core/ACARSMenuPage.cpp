#include "ACARSMenuPage.h"
#include <Core/ACARSSystem.h>

#include <QDebug>

const char *ACARSMenuPage::pCharInputPlaceholder = "_";

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
    PIString.append("/");
    PIString.append(QString::number(iNum));

    PageIdentifier->setText(PIString);

    QFont PIFont = PageIdentifier->font();
    PIFont.setCapitalization(QFont::AllUppercase);
    PIFont.setFamily(ACARSSystem::ACARSFontName);
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
        MainFont.setFamily(ACARSSystem::ACARSFontName);
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
        MainFont.setFamily(ACARSSystem::ACARSFontName);
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

void ACARSMenuPage::setText(QString Text, QString Position, ACARSMenu::LINE label)
{

    int i = 0;
    if (Position.at(0) == 'L')
    {
        i = (Position.right(1).toInt()-1)*2;
    } else {

        i = (Position.right(1).toInt()-1)*2+1;
    }

    switch (label)
    {
    case ACARSMenu::MAIN:
        {
            MainLabels[i]->setStyleSheet("QLabel {color: rgb(117,216,118)}");
            MainLabels[i]->setText(Text);
        } break;

    case ACARSMenu::HELPER:
        {
            SecondLabels[i]->setStyleSheet("QLabel {color: rgb(117,216,118)}");
            SecondLabels[i]->setText(Text);
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
        i = (Position->at(1).digitValue()-1)*2;
    } else {

        i = (Position->at(1).digitValue()-1)*2+1;
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

    this->setText(Text,Position,label);

    TextLabel->setStyleSheet(this->getColorString(color));

}

void ACARSMenuPage::setTextWithFormat(QString Text, QString Position, ACARSMenu::LINE label, ACARSMenu::COLOR color)
{

    int i = 0;
    if (Position.at(0) == 'L')
    {
        i = (Position.at(1).digitValue()-1)*2;
    } else {

        i = (Position.at(1).digitValue()-1)*2+1;
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


    this->setText(Text,Position,label);
    TextLabel->setStyleSheet(this->getColorString(color));
}

QString ACARSMenuPage::getText(QString Position)
{
    int i = 0;
    if (Position.at(0) == 'L')
    {
        i = (Position.at(1).digitValue()-1)*2;
    } else {

        i = (Position.at(1).digitValue()-1)*2+1;
    }

    return MainLabels[i]->text();
}

QString* ACARSMenuPage::getText(QString *Position)
{
    int i = 0;
    if (Position->at(0) == 'L')
    {
        i = (Position->at(1).digitValue()-1)*2;
    } else {

        i = (Position->at(1).digitValue()-1)*2+1;
    }

    return new QString(MainLabels[i]->text());
}

void ACARSMenuPage::setInputLine(QLineEdit *pInputLine)
{
    m_pInputLine = pInputLine;
}

QString ACARSMenuPage::getColorString(ACARSMenu::COLOR color)
{
    switch(color)
    {
    case ACARSMenu::AMBER: return QString("QLabel {color: rgb(216,117,118)}"); break;
    case ACARSMenu::GREEN: return QString("QLabel {color: rgb(117,216,118)}"); break;
    default: return QString("QLabel {color: rgb(100,0,0)}"); break;
    }
}

void ACARSMenuPage::setFilledInput(QString *Position, int iChars, ACARSMenu::COLOR color)
{
    int i = 0;
    if (Position->at(0) == 'L')
    {
        i = (Position->at(1).digitValue()-1)*2;
    } else {

        i = (Position->at(1).digitValue()-1)*2+1;
    }

    QString sPlaceHolder;
    sPlaceHolder.clear();

    for(i=0; i < iChars; ++i)
    {

        sPlaceHolder.append(ACARSMenuPage::pCharInputPlaceholder);

    }

    MainLabels[i]->setText(sPlaceHolder);
    MainLabels[i]->setStyleSheet(this->getColorString(color));


}

int ACARSMenuPage::getLSKIndex(QString sEntry)
{
    int i = 0;
    if (sEntry.at(0) == 'L')
    {
        i = (sEntry.right(1).toInt()-1)*2;
    } else {

        i = (sEntry.right(1).toInt()-1)*2+1;
    }

    return i;
}

void ACARSMenuPage::resetEntry(QString sEntry)
{

    int i = this->getLSKIndex(sEntry);

	MainLabels[i]->setText(mDefaultEntries[i]);

}

bool ACARSMenuPage::changedEntry(QString sEntry)
{

    int i = this->getLSKIndex(sEntry);

	if (MainLabels[i]->text().compare(mDefaultEntries[i]) != 0)
		return true;

	return false;

}

void ACARSMenuPage::updateFSData(ACARSDataBunk *pNewData)
{
    m_pFSData = pNewData;
}