#ifndef ACARSMAINWINDOW_H
#define ACARSMAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>



namespace Ui {
    class ACARSMainWindow;
}

class ACARSInputRegistry;
class ACARSMenuView;
class ACARSInput;
class ACARSInputEvent;

class ACARSMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ACARSMainWindow(QWidget *parent = 0);
    void Init();
    void GetInputEventsQueue(QVector<ACARSInputEvent *> *copyto);
    void WriteInputLine(const char* c);

    bool ProcessInputs();

    ~ACARSMainWindow();

private:

    bool eventFilter(QObject *pObj, QEvent *pEvent);


    Ui::ACARSMainWindow *m_pUI;
    QLineEdit* mACARSInputLine;

    ACARSInputRegistry *m_pInputRegistry;
    ACARSInput *m_pDefaultInput;

    QVector<ACARSInputEvent*> m_vInputEvents;
};

#endif // ACARSMAINWINDOW_H
