#ifndef ACARSMAINWINDOW_H
#define ACARSMAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTime>



namespace Ui {
    class ACARSMainWindow;
}

class ACARSInputRegistry;
class ACARSMenuView;
class ACARSInput;
class ACARSInputEvent;
class QTimer;

class ACARSSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit ACARSSystem(QWidget *parent = 0);
    void Start();
    void GetInputEventsQueue(QVector<ACARSInputEvent *> *copyto);
    void WriteInputLine(QString *c);
    void ClearInputLine();
    void DelFromInputLine();

    void HandleEvents(ACARSInputEvent* pIEvent);

    ~ACARSSystem();

private slots:
    bool SystemLoop();

private:

    bool eventFilter(QObject *pObj, QEvent *pEvent);

    Ui::ACARSMainWindow *m_pUI;
    QLineEdit* mACARSInputLine;

    ACARSInputRegistry *m_pInputRegistry;
    ACARSInput *m_pDefaultInput;

    QTimer* m_pTimer;
    QTime m_LastTime;

    ACARSMenuView* m_pActiveView;
    ACARSMenuView* m_pMenuViews[12];

    QVector<ACARSInputEvent*> m_vInputEvents;
};

#endif // ACARSMAINWINDOW_H
