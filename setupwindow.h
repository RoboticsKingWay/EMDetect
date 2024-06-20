#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QTabWidget>

namespace Ui {
class SetupWindow;
}

class SetupWindow : public QTabWidget
{
    Q_OBJECT

public:
    explicit SetupWindow(QWidget *parent = nullptr);
    ~SetupWindow();

private:
    Ui::SetupWindow *ui;
};

#endif // SETUPWINDOW_H
