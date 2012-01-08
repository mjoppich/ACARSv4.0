#ifndef ACARSMAINWINDOW_H
#define ACARSMAINWINDOW_H

#include <QMainWindow>

#include <Core/ACARSMenuView.h>

namespace Ui {
    class ACARSMainWindow;
}

class ACARSMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ACARSMainWindow(QWidget *parent = 0);
    Init();
    ~ACARSMainWindow();

private:

    bool eventFilter(QObject *pObj, QEvent *pEvent);


    Ui::ACARSMainWindow *m_pUI;

    ACARSMenuView m_pCurrentView;
};

#endif // ACARSMAINWINDOW_H
