#include "MENUPAGELogin.h"

#include <Core/ACARSUser.h>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

bool MENUPAGELogin::evaluateLogin(QString username, QString password)
{

	QUrl postData;
	postData.addQueryItem("pilot", username);
	postData.addQueryItem("password", password);

	QNetworkRequest oRequest = QNetworkRequest(QUrl("http://www.flyingtigersgroup.org/acarsftg/ftgacars/pwcheck.asp"));
	oRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	m_pNetworkManager->post(oRequest, postData.encodedQuery());

	return true;

}

bool MENUPAGELogin::passwordCheckDone(QNetworkReply * reply)
{
	QByteArray returncode;

	if(reply->error() == QNetworkReply::NoError)
	{
		//then you use this function wich will make you get a bytearray with the xml file
		returncode = reply->readAll();

		if (returncode == "0")
		{
			m_bIsLoggedIn = true;
			qDebug() << "login success";
			QString sUserSession = this->getUserSession(this->getText("L4"),this->getText("R4"));

			m_pACARSSys->eventFilter((QObject*) new ACARSUser(this->getText("L4"),sUserSession),new ACARSMenuViewEvent(ACARSEVENT::LOGINEVENT));
			m_pACARSSys->eventFilter((QObject*) new QString("LOGIN SUCCESSFUL"),new ACARSMenuViewEvent(ACARSEVENT::MESSAGEEVENT));
		} else {
			m_bIsLoggedIn = true;
			qDebug() << "login denied";
			m_pACARSSys->eventFilter((QObject*) new QString("LOGIN DENIED"),new ACARSMenuViewEvent(ACARSEVENT::MESSAGEEVENT));
		}


	} else {
		m_bIsLoggedIn = true;
		qDebug() << "Website error" << (int)reply->error();
		qDebug() << reply->readAll();
	}



	return false;
}

QString MENUPAGELogin::getUserSession(QString username, QString password)
{

    return QString("UserSession");

}

bool MENUPAGELogin::handleEvent(ACARSSystem* pACARSSys, ACARSActionEvent *pIEvent)
{

	m_pACARSSys = pACARSSys;

    if (pIEvent->isEventType(ACARSEVENT::MENU))
    {

		// ADD YOUR CUSTOM ACTIONS HERE

        if (pIEvent->getInputValue().compare("EXEC") == 0)
        {
			//this->evaluateLogin(this->getText("L4"),this->getText("R4"));
			m_bIsLoggedIn = true;
			m_pACARSSys->eventFilter((QObject*) new ACARSUser(this->getText("L4"),""),new ACARSMenuViewEvent(ACARSEVENT::LOGINEVENT));
			m_pACARSSys->eventFilter((QObject*) new QString("LOGIN SUCCESSFUL"),new ACARSMenuViewEvent(ACARSEVENT::MESSAGEEVENT));
        }
    }


	// DO NOT CHANGE THIS WITHOUT REASON
	
	if (pIEvent->isEventType(ACARSEVENT::ILINE))
    {
        if (pIEvent->getInputValue().compare("C") == 0)
        {
            pACARSSys->ClearInputLine();
        }

        if (pIEvent->getInputValue().compare("D") == 0)
        {
			if (m_pInputLine->text().compare(""))
            {
                pACARSSys->DelFromInputLine();
            } else {
                pACARSSys->WriteInputLine(QString("D"));
            }

        }
    }

    if (pIEvent->isEventType(ACARSEVENT::LSK))
    {
		if (m_pInputLine->text().length() > 0)
		{
			if ((pACARSSys->getInputLineText().compare("D") == 0) && this->changedEntry(((ACARSActionEvent*) pIEvent)->getInputValue()))
			{
				this->resetEntry(((ACARSActionEvent*) pIEvent)->getInputValue());
				m_pInputLine->clear();
			} else {
				this->setText(m_pInputLine->text(), ((ACARSActionEvent*) pIEvent)->getInputValue());
				m_pInputLine->clear();
			}
		}
    }

    //not allowed to leave this menu :)
    if (!m_bIsLoggedIn)
        return false;

    return true;

}

bool MENUPAGELogin::init()
{

    int i;


	for (i=0; i < 12; ++i)
	{
		mDefaultEntries[i] = "";
	}
	
	mDefaultEntries[2] = "LiveACARS 4.0a";
	mDefaultEntries[6] = "";
	mDefaultEntries[7] = "";
	mDefaultEntries[10] = "EXEC TO LOGIN";

    for(i=0; i<12; ++i)
    {

        MainLabels[i]->setText(mDefaultEntries[i]);
        SecondLabels[i]->setText("");

    }

    this->setText(QString("Welcome to"),QString("L2"),ACARSMenu::HELPER);
	this->setTextWithFormat(QString("PLEASE LOGIN"),QString("L3"),ACARSMenu::HELPER, ACARSMenu::AMBER);
    this->setTextWithFormat(QString("Username"),QString("L4"),ACARSMenu::HELPER);
    this->setText(QString("password"),QString("R4"),ACARSMenu::HELPER);


	m_pNetworkManager = new QNetworkAccessManager(this);
	this->connect(m_pNetworkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(passwordCheckDone(QNetworkReply *)));

    return true;

}