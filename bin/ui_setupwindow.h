/********************************************************************************
** Form generated from reading UI file 'setupwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPWINDOW_H
#define UI_SETUPWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetupWindow
{
public:
    QWidget *tab_setup_serial;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_3;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QComboBox *comboBox_4;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QWidget *widget_2;
    QPushButton *pushButton_sure;
    QPushButton *pushButton_cancel;
    QWidget *tab_setup_ip;
    QWidget *widget_4;
    QWidget *widget_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *widget_6;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QWidget *tab_setup_other;
    QWidget *widget_7;

    void setupUi(QTabWidget *SetupWindow)
    {
        if (SetupWindow->objectName().isEmpty())
            SetupWindow->setObjectName(QString::fromUtf8("SetupWindow"));
        SetupWindow->resize(336, 356);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SetupWindow->sizePolicy().hasHeightForWidth());
        SetupWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/source/title.png"), QSize(), QIcon::Normal, QIcon::Off);
        SetupWindow->setWindowIcon(icon);
        tab_setup_serial = new QWidget();
        tab_setup_serial->setObjectName(QString::fromUtf8("tab_setup_serial"));
        horizontalLayout = new QHBoxLayout(tab_setup_serial);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget_3 = new QWidget(tab_setup_serial);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget = new QWidget(widget_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 9, 251, 181));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        comboBox_4 = new QComboBox(widget);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));

        gridLayout_2->addWidget(comboBox_4, 3, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        comboBox_3 = new QComboBox(widget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        gridLayout_2->addWidget(comboBox_3, 2, 1, 1, 1);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(widget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout_2->addWidget(comboBox_2, 1, 1, 1, 1);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(40, 190, 221, 81));
        widget_2->setMaximumSize(QSize(16777215, 200));
        pushButton_sure = new QPushButton(widget_2);
        pushButton_sure->setObjectName(QString::fromUtf8("pushButton_sure"));
        pushButton_sure->setGeometry(QRect(10, 30, 81, 31));
        pushButton_cancel = new QPushButton(widget_2);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(120, 30, 81, 31));

        horizontalLayout->addWidget(widget_3);

        SetupWindow->addTab(tab_setup_serial, QString());
        tab_setup_ip = new QWidget();
        tab_setup_ip->setObjectName(QString::fromUtf8("tab_setup_ip"));
        widget_4 = new QWidget(tab_setup_ip);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(20, 30, 331, 331));
        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(0, 200, 291, 111));
        pushButton_3 = new QPushButton(widget_5);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 20, 80, 24));
        pushButton_4 = new QPushButton(widget_5);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(120, 20, 80, 24));
        widget_6 = new QWidget(widget_4);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setGeometry(QRect(10, 10, 251, 131));
        gridLayout = new QGridLayout(widget_6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(widget_6);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        lineEdit = new QLineEdit(widget_6);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_6 = new QLabel(widget_6);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(widget_6);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        SetupWindow->addTab(tab_setup_ip, QString());
        tab_setup_other = new QWidget();
        tab_setup_other->setObjectName(QString::fromUtf8("tab_setup_other"));
        widget_7 = new QWidget(tab_setup_other);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        widget_7->setGeometry(QRect(10, 20, 331, 371));
        SetupWindow->addTab(tab_setup_other, QString());

        retranslateUi(SetupWindow);

        SetupWindow->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SetupWindow);
    } // setupUi

    void retranslateUi(QTabWidget *SetupWindow)
    {
        SetupWindow->setWindowTitle(QCoreApplication::translate("SetupWindow", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        label_4->setText(QCoreApplication::translate("SetupWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("SetupWindow", "1", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("SetupWindow", "2", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("SetupWindow", "3", nullptr));

        label_3->setText(QCoreApplication::translate("SetupWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("SetupWindow", "8", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("SetupWindow", "5", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("SetupWindow", "6", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("SetupWindow", "7", nullptr));

        label->setText(QCoreApplication::translate("SetupWindow", "\347\253\257\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("SetupWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("SetupWindow", "115200", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("SetupWindow", "9600", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("SetupWindow", "57600", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("SetupWindow", "256000", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("SetupWindow", "460800", nullptr));

        pushButton_sure->setText(QCoreApplication::translate("SetupWindow", "\350\277\236\346\216\245\344\270\262\345\217\243", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("SetupWindow", "\345\217\226\346\266\210", nullptr));
        SetupWindow->setTabText(SetupWindow->indexOf(tab_setup_serial), QCoreApplication::translate("SetupWindow", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        pushButton_3->setText(QCoreApplication::translate("SetupWindow", "\347\241\256\350\256\244", nullptr));
        pushButton_4->setText(QCoreApplication::translate("SetupWindow", "\345\217\226\346\266\210", nullptr));
        label_5->setText(QCoreApplication::translate("SetupWindow", "\347\253\257\345\217\243", nullptr));
        label_6->setText(QCoreApplication::translate("SetupWindow", "\345\234\260\345\235\200", nullptr));
        SetupWindow->setTabText(SetupWindow->indexOf(tab_setup_ip), QCoreApplication::translate("SetupWindow", "\347\275\221\345\217\243\350\256\276\347\275\256", nullptr));
        SetupWindow->setTabText(SetupWindow->indexOf(tab_setup_other), QCoreApplication::translate("SetupWindow", "\345\205\266\344\273\226\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetupWindow: public Ui_SetupWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPWINDOW_H
