#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QTabWidget>
#include "UnitData.h"

namespace Ui {
class SetupWindow;
}

class SetupWindow : public QTabWidget
{
    Q_OBJECT

public:
    explicit SetupWindow(QWidget *parent = nullptr);
    ~SetupWindow();
public slots:
    void setPortList(QVector<QString>& list);
signals:
    void setSerialParam(SerialParam& param);
private slots:
    void on_pushButton_clicked();

private:
    Ui::SetupWindow *ui;
};

#endif // SETUPWINDOW_H
