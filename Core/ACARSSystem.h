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

class ACARSSystem : public QMainWindow
{
    Q_OBJECT

public:

    //ACARS SYSTEM
    explicit ACARSSystem(QWidget *parent = 0);
    void Start();
    bool UpdateACARSCheck();

    //User
    ACARSUser *m_pUser;


    //INPUTLINE
    void WriteInputLine(QString c);
    void ClearInputLine();
    void DelFromInputLine();

    //EVENTS
    void HandleEvents(ACARSActionEvent* pIEvent);
    bool eventFilter(QObject *pObj, QEvent *pEvent);
    void GetInputEventsQueue(QVector<ACARSActionEvent *> *copyto);

    //DATA MANAGEMENT
    void setACARSUser(ACARSUser *pUser);

    ~ACARSSystem();

    static const char* ACARSFontName;
    static const char* ACARSVersion;

private slots:
    bool SystemLoop();

private:

    Ui::ACARSMainWindow *m_pUI;
    QLineEdit* mACARSInputLine;

    ACARSInputRegistry *m_pInputRegistry;
    ACARSInput *m_pDefaultInput;

    QTimer* m_pTimer;
    QTime m_LastTime;

    ACARSMenu* m_pActiveMenu;
    ACARSMenu* m_pMenuViews[12];

    ACARSUser* m_pACARSUser;

    QVector<ACARSActionEvent*> m_vInputEvents;
};

#endif // ACARSMAINWINDOW_H
