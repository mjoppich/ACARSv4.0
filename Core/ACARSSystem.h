#ifndef ACARSMAINWINDOW_H
#define ACARSMAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTime>

namespace Ui {
    class ACARSMainWindow;
}

class ACARSInputRegistry;
class ACARSMenu;
class ACARSInput;
class ACARSActionEvent;
class QTimer;
class ACARSUser;
class QStackedWidget;
class QApplication;
class XPlaneFlightSimData;
class ACARSFlightSimData;
class ACARSDataBunk;
class LiveACARS;
class ACARSDataBunk;

class ACARSSystem : public QMainWindow
{
    Q_OBJECT

public:

    //ACARS SYSTEM
    explicit ACARSSystem(QApplication *pApp, QWidget *parent = 0);
    void Start();
    bool UpdateACARSCheck();
	ACARSDataBunk* getACARSData() {return m_pCurrentData;}

    //User
    ACARSUser *m_pUser;


    //INPUTLINE
    void WriteInputLine(QString c);
    void ClearInputLine();
    void DelFromInputLine();
	QString getInputLineText();

    //EVENTS
    bool HandleEvents(ACARSActionEvent* pIEvent);
    bool eventFilter(QObject *pObj, QEvent *pEvent);
    void GetInputEventsQueue(QVector<ACARSActionEvent *> *copyto);

    ~ACARSSystem();

    static const char* ACARSFontName;
    static const char* ACARSVersion;

private slots:
    bool SystemLoop();
    void saveScreenShot();

private:

    Ui::ACARSMainWindow *m_pUI;
    QLineEdit* m_pACARSInputLine;

    ACARSInputRegistry *m_pInputRegistry;
    ACARSInput *m_pDefaultInput;
	LiveACARS *m_pLiveACARS;

    QTimer* m_pTimer;
    QTime m_LastTime;

    ACARSMenu* m_pActiveMenu;
    ACARSMenu* m_pMenuViews[12];
    QStackedWidget* m_pViews;

	ACARSDataBunk* m_pCurrentData;

    QApplication* m_pParentApp;

    QVector<ACARSActionEvent*> m_vInputEvents;
	QVector<QString*> m_vMessageDisplay;
	QString m_sLastUserInput;
};

#endif // ACARSMAINWINDOW_H
