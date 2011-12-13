#ifndef ACARSMAINWINDOW_H
#define ACARSMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class ACARSMainWindow;
}

class ACARSMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ACARSMainWindow(QWidget *parent = 0);
    ~ACARSMainWindow();

private:
    Ui::ACARSMainWindow *ui;
};

#endif // ACARSMAINWINDOW_H
